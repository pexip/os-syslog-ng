/*
 * Copyright (c) 2014 Balabit
 * Copyright (c) 2014 Laszlo Budai
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

#include "host-id.h"
#include "str-format.h"
#include <openssl/rand.h>

guint32 global_host_id = 0;

static guint32
_create_host_id()
{
  union {
    unsigned char _raw[sizeof(guint32)];
    guint32 id;
  } host_id;

  RAND_bytes(host_id._raw, sizeof(host_id._raw));

  return host_id.id;
}

void
host_id_init(PersistState* state)
{
  gsize size;
  guint8 version;
  PersistEntryHandle handle;
  HostIdState *host_id_state;
  gboolean new_host_id_required = FALSE;

  handle = persist_state_lookup_entry(state, HOST_ID_PERSIST_KEY, &size, &version);

  if (handle == 0)
    {
      new_host_id_required = TRUE;
      handle = persist_state_alloc_entry(state, HOST_ID_PERSIST_KEY, sizeof(HostIdState));
    }

  host_id_state = persist_state_map_entry(state, handle);
    {
      if (new_host_id_required)
        {
          global_host_id = _create_host_id();
          host_id_state->host_id = global_host_id;
        }
      else
        {
          global_host_id = host_id_state->host_id;
        }
    }
  persist_state_unmap_entry(state, handle);
}

guint32
host_id_get(void)
{
  return global_host_id;
}

void
host_id_append_formatted_id(GString *str, guint32 id)
{
  format_uint32_padded(str, 8, '0', 16, id);
}
