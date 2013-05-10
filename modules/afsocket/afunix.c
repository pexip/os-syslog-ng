/*
 * Copyright (c) 2002-2010 BalaBit IT Ltd, Budapest, Hungary
 * Copyright (c) 1998-2010 Balázs Scheidler
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published
 * by the Free Software Foundation, or (at your option) any later version.
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

#include "afunix.h"
#include "misc.h"
#include "messages.h"
#include "gprocess.h"

#if WITH_LIBSYSTEMD
#include <systemd/sd-daemon.h>
#else
#include "sd-daemon.h"
#endif

#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

void
afunix_sd_set_uid(LogDriver *s, gchar *owner)
{
  AFUnixSourceDriver *self = (AFUnixSourceDriver *) s;

  if (!resolve_user(owner, &self->owner))
    msg_error("Error resolving username",
              evt_tag_str("owner", owner),
              NULL);
}

void
afunix_sd_set_gid(LogDriver *s, gchar *group)
{
  AFUnixSourceDriver *self = (AFUnixSourceDriver *) s;

  if (!resolve_group(group, &self->group))
    msg_error("Error resolving group",
              evt_tag_str("group", group),
              NULL);
}

void
afunix_sd_set_perm(LogDriver *s, gint perm)
{
  AFUnixSourceDriver *self = (AFUnixSourceDriver *) s;

  self->perm = perm & 0777;
}

#if ENABLE_SYSTEMD
static gboolean
afunix_sd_acquire_socket(AFSocketSourceDriver *s, gint *result_fd)
{
  AFUnixSourceDriver *self = (AFUnixSourceDriver *) s;
  gint fd, fds;

  *result_fd = -1;
  fd = -1;
  fds = sd_listen_fds(0);

  if (fds == 0)
    return TRUE;

  msg_debug("Systemd socket activation",
	    evt_tag_int("systemd-sockets", fds),
	    evt_tag_str("systemd-listen-pid", getenv("LISTEN_PID")),
	    evt_tag_str("systemd-listen-fds", getenv("LISTEN_FDS")),
	    NULL);

  if (fds < 0)
    {
      msg_error("Failed to acquire systemd sockets, incorrectly set LISTEN_FDS environment variable?",
		NULL);
      return FALSE;
    }
  else if (fds > 0)
    {
      for (fd = SD_LISTEN_FDS_START; fd < SD_LISTEN_FDS_START + fds; fd++)
	{
	  /* check if any type is available */
	  if (sd_is_socket_unix(fd, 0, -1, self->filename, 0))
	    {
              int type = (self->super.flags & AFSOCKET_STREAM) ? SOCK_STREAM : SOCK_DGRAM;

	      /* check if it matches our idea of the socket type */
              if (sd_is_socket_unix(fd, type, -1, self->filename, 0))
                {
                  *result_fd = fd;
                  break;
                }
              else
                {
                  msg_error("The systemd supplied UNIX domain socket is of a different type, check the configured driver and the matching systemd unit file",
		            evt_tag_str("filename", self->filename),
		            evt_tag_int("systemd-sock-fd", fd),
                            evt_tag_str("expecting", type == SOCK_STREAM ? "unix-stream()" : "unix-dgram()"),
                            NULL);
                  return FALSE;
                }
            }
          else
            {

              /* systemd passed an fd we didn't really care about. This is
               * not an error, but might be worth mentioning it at the debug
               * level.
               */

              msg_debug("Ignoring systemd supplied fd as it is not a UNIX domain socket",
		        evt_tag_str("filename", self->filename),
		        evt_tag_int("systemd-sock-fd", fd),
		        NULL);
            }
	}
    }
  else
    return TRUE;

  if (*result_fd != -1)
    {
      g_fd_set_nonblock(*result_fd, TRUE);
      g_fd_set_cloexec(*result_fd, TRUE);
      msg_verbose("Acquired systemd socket",
		  evt_tag_str("filename", self->filename),
		  evt_tag_int("systemd-sock-fd", *result_fd),
		  NULL);
    }
  else
    {
      msg_debug("Failed to acquire systemd socket, trying to open ourselves",
		evt_tag_str("filename", self->filename),
		NULL);
    }
  return TRUE;
}

#else

static gboolean
afunix_sd_acquire_socket(AFSocketSourceDriver *s, gint *result_fd)
{
  return TRUE;
}
#endif

static gboolean
afunix_sd_apply_transport(AFSocketSourceDriver *s)
{
  AFUnixSourceDriver *self = (AFUnixSourceDriver *) s;

  if (!self->super.bind_addr)
    self->super.bind_addr = g_sockaddr_unix_new(self->filename);
  return TRUE;
}

static gboolean
afunix_sd_init(LogPipe *s)
{
  AFUnixSourceDriver *self = (AFUnixSourceDriver *) s;

  if (afsocket_sd_init(s))
    {
      cap_t saved_caps;

      saved_caps = g_process_cap_save();
      g_process_cap_modify(CAP_CHOWN, TRUE);
      g_process_cap_modify(CAP_FOWNER, TRUE);
      g_process_cap_modify(CAP_DAC_OVERRIDE, TRUE);
      set_permissions(self->filename, self->owner, self->group, self->perm);
      g_process_cap_restore(saved_caps);

      return TRUE;
    }
  return FALSE;
}

static void
afunix_sd_free(LogPipe *s)
{
  AFUnixSourceDriver *self = (AFUnixSourceDriver *) s;

  g_free(self->filename);
  afsocket_sd_free(s);
}

LogDriver *
afunix_sd_new(gchar *filename, guint32 flags)
{
  AFUnixSourceDriver *self = g_new0(AFUnixSourceDriver, 1);

  afsocket_sd_init_instance(&self->super, &self->sock_options, AF_UNIX, flags);

  self->super.super.super.super.init = afunix_sd_init;
  self->super.super.super.super.free_fn = afunix_sd_free;
  self->super.acquire_socket = afunix_sd_acquire_socket;
  self->super.apply_transport = afunix_sd_apply_transport;

  self->super.max_connections = 256;

  if (self->super.flags & AFSOCKET_STREAM)
    self->super.reader_options.super.init_window_size = self->super.max_connections * 100;

  if (self->super.flags & AFSOCKET_DGRAM)
    afsocket_sd_set_transport(&self->super.super.super, "unix-dgram");
  else if (self->super.flags & AFSOCKET_STREAM)
    afsocket_sd_set_transport(&self->super.super.super, "unix-stream");

  self->filename = g_strdup(filename);
  self->owner = -1;
  self->group = -1;
  self->perm = 0666;
  return &self->super.super.super;
}

static gboolean
afunix_dd_apply_transport(AFSocketDestDriver *s)
{
  AFUnixDestDriver *self = (AFUnixDestDriver *) s;

  if (!self->super.bind_addr)
    self->super.bind_addr = g_sockaddr_unix_new(NULL);

  if (!self->super.dest_addr)
    self->super.dest_addr = g_sockaddr_unix_new(self->filename);

  if (!self->super.dest_name)
    self->super.dest_name = g_strdup_printf("localhost.afunix:%s", self->filename);
  return TRUE;
}

static void
afunix_dd_free(LogPipe *s)
{
  AFUnixDestDriver *self = (AFUnixDestDriver *) s;

  g_free(self->filename);
  afsocket_dd_free(s);
}

LogDriver *
afunix_dd_new(gchar *filename, guint flags)
{
  AFUnixDestDriver *self = g_new0(AFUnixDestDriver, 1);

  afsocket_dd_init_instance(&self->super, &self->sock_options, AF_UNIX, "localhost", flags);
  self->super.super.super.super.free_fn = afunix_dd_free;
  self->super.apply_transport = afunix_dd_apply_transport;

  self->filename = g_strdup(filename);

  if (self->super.flags & AFSOCKET_DGRAM)
    afsocket_dd_set_transport(&self->super.super.super, "unix-dgram");
  else if (self->super.flags & AFSOCKET_STREAM)
    afsocket_dd_set_transport(&self->super.super.super, "unix-stream");

  return &self->super.super.super;
}
