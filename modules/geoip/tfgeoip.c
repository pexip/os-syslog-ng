/*
 * Copyright (c) 2012-2013 Balabit
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

#include "plugin.h"
#include "plugin-types.h"
#include "template/simple-function.h"
#include "messages.h"
#include "cfg.h"
#include "tls-support.h"

#include "syslog-ng-config.h"

#include <GeoIP.h>

typedef struct _TFGeoIPState
{
  GeoIP *gi;
} TFGeoIPState;

TLS_BLOCK_START
{
  TFGeoIPState *geoip_state;
}
TLS_BLOCK_END;

#define local_state __tls_deref(geoip_state)

static inline void
tf_geoip_init(void)
{
  if (!local_state)
    {
      local_state = g_new0(TFGeoIPState, 1);
      local_state->gi = GeoIP_new(GEOIP_MMAP_CACHE);
    }
}

static gboolean
tf_geoip(LogMessage *msg, gint argc, GString *argv[], GString *result)
{
  const char *country;

  tf_geoip_init();

  if (argc != 1)
    {
      msg_debug("tfgeoip takes only one argument",
                evt_tag_int("count", argc));
      return FALSE;
    }

  country = GeoIP_country_code_by_name(local_state->gi, argv[0]->str);
  if (country)
    g_string_append(result, country);

  return TRUE;
}
TEMPLATE_FUNCTION_SIMPLE(tf_geoip);
