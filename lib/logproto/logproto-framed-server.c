/*
 * Copyright (c) 2002-2012 Balabit
 * Copyright (c) 1998-2012 Balázs Scheidler
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * As an additional exemption you are allowed to compile & link against the
 * OpenSSL libraries as published by the OpenSSL project. See the file
 * COPYING for details.
 *
 */
#include "logproto-framed-server.h"
#include "messages.h"

#include <errno.h>
#include <ctype.h>
#include <string.h>

#define LPFSS_FRAME_READ    0
#define LPFSS_MESSAGE_READ  1

#define LPFS_FRAME_BUFFER 10

typedef struct _LogProtoFramedServer
{
  LogProtoServer super;
  gint state;

  guchar *buffer;
  guint32 buffer_size, buffer_pos, buffer_end;
  guint32 frame_len;
  gboolean half_message_in_buffer;
} LogProtoFramedServer;

static gboolean
log_proto_framed_server_prepare(LogProtoServer *s, GIOCondition *cond)
{
  LogProtoFramedServer *self = (LogProtoFramedServer *) s;

  *cond = self->super.transport->cond;

  /* there is a half message in our buffer so try to wait */
  if (!self->half_message_in_buffer)
    {
      if (self->buffer_pos != self->buffer_end)
        {
          /* we have a full message in our buffer so parse it without reading new data from the transport layer */
          return TRUE;
        }
    }

  /* if there's no pending I/O in the transport layer, then we want to do a read */
  if (*cond == 0)
    *cond = G_IO_IN;

  return FALSE;
}

static LogProtoStatus
log_proto_framed_server_fetch_data(LogProtoFramedServer *self, gboolean *may_read)
{
  gint rc;

  if (self->buffer_pos == self->buffer_end)
    self->buffer_pos = self->buffer_end = 0;

  if (self->buffer_size == self->buffer_end)
    {
      /* no more space in the buffer, we can't fetch further data. Move the
       * things we already have to the beginning of the buffer to make
       * space. */

      memmove(self->buffer, &self->buffer[self->buffer_pos], self->buffer_end - self->buffer_pos);
      self->buffer_end = self->buffer_end - self->buffer_pos;
      self->buffer_pos = 0;
    }

  if (!(*may_read))
    return LPS_SUCCESS;

  rc = log_transport_read(self->super.transport, &self->buffer[self->buffer_end], self->buffer_size - self->buffer_end, NULL);

  if (rc < 0)
    {
      if (errno != EAGAIN)
        {
          msg_error("Error reading RFC5428 style framed data",
                    evt_tag_int("fd", self->super.transport->fd),
                    evt_tag_errno("error", errno));
          return LPS_ERROR;
        }
      else
        {
          /* we need more data to parse this message but the data is not available yet */
          self->half_message_in_buffer = TRUE;
        }
    }
  else if (rc == 0)
    {
      msg_verbose("EOF occurred while reading",
                  evt_tag_int(EVT_TAG_FD, self->super.transport->fd));
      return LPS_EOF;
    }
  else
    {
      self->buffer_end += rc;
    }
  return LPS_SUCCESS;

}

static gboolean
log_proto_framed_server_extract_frame_length(LogProtoFramedServer *self, gboolean *need_more_data)
{
  gint i;

  *need_more_data = TRUE;
  self->frame_len = 0;
  for (i = self->buffer_pos; i < self->buffer_end; i++)
    {
      if (isdigit(self->buffer[i]) && (i - self->buffer_pos < 10))
        {
          self->frame_len = self->frame_len * 10 + (self->buffer[i] - '0');
        }
      else if (self->buffer[i] == ' ')
        {
          *need_more_data = FALSE;
          self->buffer_pos = i + 1;
          return TRUE;
        }
      else
        {
          msg_error("Invalid frame header",
                    evt_tag_printf("header", "%.*s", (gint) (i - self->buffer_pos), &self->buffer[self->buffer_pos]));
          return FALSE;
        }
    }
  /* couldn't extract frame header, no error but need more data */
  return TRUE;
}

static LogProtoStatus
log_proto_framed_server_fetch(LogProtoServer *s, const guchar **msg, gsize *msg_len, gboolean *may_read, LogTransportAuxData *aux, Bookmark *bookmark)
{
  LogProtoFramedServer *self = (LogProtoFramedServer *) s;
  LogProtoStatus status;
  gboolean try_read, need_more_data;

  if (G_UNLIKELY(!self->buffer))
    {
      self->buffer_size = self->super.options->init_buffer_size;
      self->buffer = g_malloc(self->buffer_size);
    }

  switch (self->state)
    {
    case LPFSS_FRAME_READ:

      try_read = TRUE;

    read_frame:
      if (!log_proto_framed_server_extract_frame_length(self, &need_more_data))
        {
          /* invalid frame header */
          return LPS_ERROR;
        }
      if (need_more_data && try_read)
        {
          status = log_proto_framed_server_fetch_data(self, may_read);
          if (status != LPS_SUCCESS)
            return status;
          try_read = FALSE;
          goto read_frame;
        }

      if (!need_more_data)
        {
          self->state = LPFSS_MESSAGE_READ;
          if (self->frame_len > self->super.options->max_msg_size)
            {
              msg_error("Incoming frame larger than log_msg_size()",
                        evt_tag_int("log_msg_size", self->super.options->max_msg_size),
                        evt_tag_int("frame_length", self->frame_len));
              return LPS_ERROR;
            }
          if (self->buffer_size < self->super.options->max_buffer_size &&
              self->frame_len > self->buffer_size - self->buffer_pos)
            {
              /* a larger buffer would have prevented moving of data, grow
               * the buffer up to max_buffer_size */

              self->buffer_size = 16 * (self->frame_len + LPFS_FRAME_BUFFER);

              if (self->buffer_size > self->super.options->max_buffer_size)
                self->buffer_size = self->super.options->max_buffer_size;
              self->buffer = g_realloc(self->buffer, self->buffer_size);
              msg_debug("Resizing input buffer",
                        evt_tag_int("new_size", self->buffer_size));
            }
          if (self->buffer_pos + self->frame_len > self->buffer_size)
            {
              /* message would be too large to fit into the buffer at
               * buffer_pos, we need to move data to the beginning of
               * the buffer to make space, and once we are at it, move
               * to the beginning to make space for the maximum number
               * of messages before the next shift */
              memmove(self->buffer, &self->buffer[self->buffer_pos], self->buffer_end - self->buffer_pos);
              self->buffer_end = self->buffer_end - self->buffer_pos;
              self->buffer_pos = 0;
            }
          goto read_message;
        }
      break;
    case LPFSS_MESSAGE_READ:

      try_read = TRUE;
    read_message:
      /* NOTE: here we can assume that the complete message fits into
       * the buffer because of the checks/move operation in the
       * LPFSS_FRAME_READ state */
      if (self->buffer_end - self->buffer_pos >= self->frame_len)
        {
          /* ok, we already have the complete message */

          *msg = &self->buffer[self->buffer_pos];
          *msg_len = self->frame_len;
          self->buffer_pos += self->frame_len;
          self->state = LPFSS_FRAME_READ;

          /* we have the full message here so reset the half message flag */
          self->half_message_in_buffer = FALSE;
          return LPS_SUCCESS;
        }
      if (try_read)
        {
          status = log_proto_framed_server_fetch_data(self, may_read);
          if (status != LPS_SUCCESS)
            return status;
          try_read = FALSE;
          goto read_message;
        }
      break;
    default:
      break;
    }
  return LPS_SUCCESS;
}

static void
log_proto_framed_server_free(LogProtoServer *s)
{
  LogProtoFramedServer *self = (LogProtoFramedServer *) s;
  g_free(self->buffer);

  log_proto_server_free_method(s);
}

LogProtoServer *
log_proto_framed_server_new(LogTransport *transport, const LogProtoServerOptions *options)
{
  LogProtoFramedServer *self = g_new0(LogProtoFramedServer, 1);

  log_proto_server_init(&self->super, transport, options);
  self->super.prepare = log_proto_framed_server_prepare;
  self->super.fetch = log_proto_framed_server_fetch;
  self->super.free_fn = log_proto_framed_server_free;
  self->half_message_in_buffer = FALSE;
  return &self->super;
}
