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

#ifndef LOGPROTO_SERVER_H_INCLUDED
#define LOGPROTO_SERVER_H_INCLUDED

#include "logproto.h"
#include "persist-state.h"
#include "transport/transport-aux-data.h"
#include "bookmark.h"

typedef struct _LogProtoServer LogProtoServer;
typedef struct _LogProtoServerOptions LogProtoServerOptions;

#define LOG_PROTO_SERVER_OPTIONS_SIZE 32

struct _LogProtoServerOptions
{
  void (*destroy)(LogProtoServerOptions *self);
  gboolean initialized;
  gchar *encoding;
  /* maximum message length in bytes */
  gint max_msg_size;
  gint max_buffer_size;
  gint init_buffer_size;
};

typedef union LogProtoServerOptionsStorage
{
  LogProtoServerOptions super;
  gchar __padding[LOG_PROTO_SERVER_OPTIONS_SIZE];
} LogProtoServerOptionsStorage;

gboolean log_proto_server_options_validate(const LogProtoServerOptions *options);
gboolean log_proto_server_options_set_encoding(LogProtoServerOptions *s, const gchar *encoding);
void log_proto_server_options_defaults(LogProtoServerOptions *options);
void log_proto_server_options_init(LogProtoServerOptions *options, GlobalConfig *cfg);
void log_proto_server_options_destroy(LogProtoServerOptions *options);

struct _LogProtoServer
{
  LogProtoStatus status;
  const LogProtoServerOptions *options;
  LogTransport *transport;
  /* FIXME: rename to something else */
  gboolean (*is_position_tracked)(LogProtoServer *s);
  gboolean (*prepare)(LogProtoServer *s, GIOCondition *cond);
  gboolean (*is_preemptable)(LogProtoServer *s);
  gboolean (*restart_with_state)(LogProtoServer *s, PersistState *state, const gchar *persist_name);
  LogProtoStatus (*fetch)(LogProtoServer *s, const guchar **msg, gsize *msg_len, gboolean *may_read, LogTransportAuxData *aux, Bookmark *bookmark);
  gboolean (*validate_options)(LogProtoServer *s);
  void (*free_fn)(LogProtoServer *s);
};

static inline gboolean
log_proto_server_validate_options(LogProtoServer *self)
{
  return self->validate_options(self);
}

static inline void
log_proto_server_set_options(LogProtoServer *self, const LogProtoServerOptions *options)
{
  self->options = options;
}

static inline gboolean
log_proto_server_prepare(LogProtoServer *s, GIOCondition *cond)
{
  return s->prepare(s, cond);
}

static inline gboolean
log_proto_server_is_preemptable(LogProtoServer *s)
{
  if (s->is_preemptable)
    return s->is_preemptable(s);
  return TRUE;
}

static inline gboolean
log_proto_server_restart_with_state(LogProtoServer *s, PersistState *state, const gchar *persist_name)
{
  if (s->restart_with_state)
    return s->restart_with_state(s, state, persist_name);
  return FALSE;
}

static inline LogProtoStatus
log_proto_server_fetch(LogProtoServer *s, const guchar **msg, gsize *msg_len, gboolean *may_read, LogTransportAuxData *aux, Bookmark *bookmark)
{
  if (s->status == LPS_SUCCESS)
    return s->fetch(s, msg, msg_len, may_read, aux, bookmark);
  return s->status;
}

static inline gint
log_proto_server_get_fd(LogProtoServer *s)
{
  /* FIXME: Layering violation */
  return s->transport->fd;
}

static inline void
log_proto_server_reset_error(LogProtoServer *s)
{
  s->status = LPS_SUCCESS;
}

static inline gboolean
log_proto_server_is_position_tracked(LogProtoServer *s)
{
  if (s->is_position_tracked)
    return s->is_position_tracked(s);

  return FALSE;
}

gboolean log_proto_server_validate_options_method(LogProtoServer *s);
void log_proto_server_init(LogProtoServer *s, LogTransport *transport, const LogProtoServerOptions *options);
void log_proto_server_free_method(LogProtoServer *s);
void log_proto_server_free(LogProtoServer *s);

#define DEFINE_LOG_PROTO_SERVER(prefix) \
  static gpointer                                                       \
  prefix ## _server_plugin_construct(Plugin *self,                      \
                  GlobalConfig *cfg,                                    \
                  gint plugin_type, const gchar *plugin_name)           \
  {                                                                     \
    static LogProtoServerFactory proto = {                              \
      .construct = prefix ## _server_new,                    		\
    };                                                                  \
    return &proto;                                                      \
  }

#define LOG_PROTO_SERVER_PLUGIN(prefix, __name) \
  {							\
    .type = LL_CONTEXT_SERVER_PROTO,		        \
    .name = __name,					\
    .construct = prefix ## _server_plugin_construct,	\
  }

typedef struct _LogProtoServerFactory LogProtoServerFactory;

struct _LogProtoServerFactory
{
  LogProtoServer *(*construct)(LogTransport *transport, const LogProtoServerOptions *options);
};

static inline LogProtoServer *
log_proto_server_factory_construct(LogProtoServerFactory *self, LogTransport *transport, const LogProtoServerOptions *options)
{
  return self->construct(transport, options);
}

LogProtoServerFactory *log_proto_server_get_factory(GlobalConfig *cfg, const gchar *name);

const guchar *find_eom(const guchar *s, gsize n);

#endif
