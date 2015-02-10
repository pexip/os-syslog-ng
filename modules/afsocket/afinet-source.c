/*
 * Copyright (c) 2002-2012 BalaBit IT Ltd, Budapest, Hungary
 * Copyright (c) 1998-2012 Balázs Scheidler
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published
 * by the Free Software Foundation, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * As an additional exemption you are allowed to compile & link against the
 * OpenSSL libraries as published by the OpenSSL project. See the file
 * COPYING for details.
 *
 */

#include "afinet-source.h"
#include "messages.h"
#include "misc.h"
#include "transport-mapper-inet.h"
#include "socket-options-inet.h"
#include "tlstransport.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>

void
afinet_sd_set_localport(LogDriver *s, gchar *service)
{
  AFInetSourceDriver *self = (AFInetSourceDriver *) s;

  if (self->bind_port)
    g_free(self->bind_port);
  self->bind_port = g_strdup(service);
}

void
afinet_sd_set_localip(LogDriver *s, gchar *ip)
{
  AFInetSourceDriver *self = (AFInetSourceDriver *) s;

  if (self->bind_ip)
    g_free(self->bind_ip);
  self->bind_ip = g_strdup(ip);
}

#if BUILD_WITH_SSL
void
afinet_sd_set_tls_context(LogDriver *s, TLSContext *tls_context)
{
  AFInetSourceDriver *self = (AFInetSourceDriver *) s;

  self->tls_context = tls_context;
}

static gboolean
afinet_sd_is_tls_required(AFInetSourceDriver *self)
{
  TransportMapperInet *transport_mapper_inet = ((TransportMapperInet *) (self->super.transport_mapper));

  return transport_mapper_inet_is_tls_required(transport_mapper_inet);
}

static gboolean
afinet_sd_is_tls_allowed(AFInetSourceDriver *self)
{
  TransportMapperInet *transport_mapper_inet = ((TransportMapperInet *) (self->super.transport_mapper));

  return transport_mapper_inet_is_tls_allowed(transport_mapper_inet);
}

static LogTransport *
afinet_sd_construct_tls_transport(AFInetSourceDriver *self, TLSContext *tls_context, gint fd)
{
  TLSSession *tls_session;

  tls_session = tls_context_setup_session(self->tls_context);
  if (!tls_session)
    return NULL;

  return log_transport_tls_new(tls_session, fd);
}


LogTransport *
afinet_sd_construct_transport(AFSocketSourceDriver *s, gint fd)
{
  AFInetSourceDriver *self = (AFInetSourceDriver *) s;

  if (self->tls_context)
    return afinet_sd_construct_tls_transport(self, self->tls_context, fd);
  else
    return afsocket_sd_construct_transport_method(s, fd);
}

#else

#define afinet_sd_construct_transport afsocket_sd_construct_transport_method

#endif


static gboolean
afinet_sd_setup_addresses(AFSocketSourceDriver *s)
{
  AFInetSourceDriver *self = (AFInetSourceDriver *) s;
  gchar *default_bind_ip = NULL;

  if (!afsocket_sd_setup_addresses_method(s))
    return FALSE;

  g_sockaddr_unref(self->super.bind_addr);

  if (self->super.transport_mapper->address_family == AF_INET)
    {
      self->super.bind_addr = g_sockaddr_inet_new("0.0.0.0", 0);
      default_bind_ip = "0.0.0.0";
    }
#if ENABLE_IPV6
  else if (self->super.transport_mapper->address_family == AF_INET6)
    {
      self->super.bind_addr = g_sockaddr_inet6_new("::", 0);
      default_bind_ip = "::";
    }
#endif
  else
    {
      g_assert_not_reached();
    }

  if (!self->bind_port)
    {
      const gchar *port_change_warning = transport_mapper_inet_get_port_change_warning(self->super.transport_mapper);

      if (port_change_warning)
        {
          msg_warning(port_change_warning,
                      evt_tag_str("id", self->super.super.super.id),
                      NULL);
        }
      g_sockaddr_set_port(self->super.bind_addr, transport_mapper_inet_get_server_port(self->super.transport_mapper));
    }
  else
    g_sockaddr_set_port(self->super.bind_addr, afinet_lookup_service(self->super.transport_mapper, self->bind_port));
  if (!resolve_hostname(&self->super.bind_addr, self->bind_ip ? : default_bind_ip))
    return FALSE;

  return TRUE;
}

gboolean
afinet_sd_init(LogPipe *s)
{
  AFInetSourceDriver *self = (AFInetSourceDriver *) s;

  if (!afsocket_sd_init_method(&self->super.super.super.super))
    return FALSE;
#if BUILD_WITH_SSL

  if (!self->tls_context && afinet_sd_is_tls_required(self))
    {
      msg_error("transport(tls) was specified, but tls() options missing",
                evt_tag_str("id", self->super.super.super.id),
                NULL);
      return FALSE;
    }
  else if (self->tls_context && !afinet_sd_is_tls_allowed(self))
    {
      msg_error("tls() options specified for a transport that doesn't allow TLS encryption",
                evt_tag_str("id", self->super.super.super.id),
                NULL);
      return FALSE;
    }
#endif
  return TRUE;
}

void
afinet_sd_free(LogPipe *s)
{
  AFInetSourceDriver *self = (AFInetSourceDriver *) s;

  g_free(self->bind_ip);
  g_free(self->bind_port);
  afsocket_sd_free_method(s);
}

static AFInetSourceDriver *
afinet_sd_new_instance(TransportMapper *transport_mapper)
{
  AFInetSourceDriver *self = g_new0(AFInetSourceDriver, 1);

  afsocket_sd_init_instance(&self->super,
                            socket_options_inet_new(),
                            transport_mapper);
  self->super.super.super.super.init = afinet_sd_init;
  self->super.super.super.super.free_fn = afinet_sd_free;
  self->super.construct_transport = afinet_sd_construct_transport;
  self->super.setup_addresses = afinet_sd_setup_addresses;
  return self;
}

AFInetSourceDriver *
afinet_sd_new_tcp(void)
{
  return afinet_sd_new_instance(transport_mapper_tcp_new());
}

AFInetSourceDriver *
afinet_sd_new_tcp6(void)
{
  return afinet_sd_new_instance(transport_mapper_tcp6_new());
}


AFInetSourceDriver *
afinet_sd_new_udp(void)
{
  return afinet_sd_new_instance(transport_mapper_udp_new());
}

AFInetSourceDriver *
afinet_sd_new_udp6(void)
{
  return afinet_sd_new_instance(transport_mapper_udp6_new());
}


AFInetSourceDriver *
afinet_sd_new_syslog(void)
{
  AFInetSourceDriver *self = afinet_sd_new_instance(transport_mapper_syslog_new());

  self->super.reader_options.parse_options.flags |= LP_SYSLOG_PROTOCOL;
  return self;
}

AFInetSourceDriver *
afinet_sd_new_network(void)
{
  AFInetSourceDriver *self = afinet_sd_new_instance(transport_mapper_network_new());
 return self;
}
