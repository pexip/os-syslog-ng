/*
 * Copyright (c) 2002-2012 BalaBit IT Ltd, Budapest, Hungary
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

#ifndef PAYLOAD_H_INCLUDED
#define PAYLOAD_H_INCLUDED

#include "syslog-ng.h"

typedef struct _NVTable NVTable;
typedef struct _NVRegistry NVRegistry;
typedef struct _NVDynValue NVDynValue;
typedef struct _NVEntry NVEntry;
typedef guint32 NVHandle;
typedef struct _NVHandleDesc NVHandleDesc;
typedef gboolean (*NVTableForeachFunc)(NVHandle handle, const gchar *name, const gchar *value, gssize value_len, gpointer user_data);
typedef gboolean (*NVTableForeachEntryFunc)(NVHandle handle, NVEntry *entry, gpointer user_data);

struct _NVDynValue
{
  NVHandle handle;
  guint32 ofs;
};

struct _NVHandleDesc
{
  gchar *name;
  guint16 flags;
  guint8 name_len;
};

struct _NVRegistry
{
  /* number of static names that are statically allocated in each payload */
  gint num_static_names;
  GArray *names;
  GHashTable *name_map;
};

extern const gchar *null_string;

void nv_registry_add_alias(NVRegistry *self, NVHandle handle, const gchar *alias);
NVHandle nv_registry_get_handle(NVRegistry *self, const gchar *name);
NVHandle nv_registry_alloc_handle(NVRegistry *self, const gchar *name);
void nv_registry_set_handle_flags(NVRegistry *self, NVHandle handle, guint16 flags);
NVRegistry *nv_registry_new(const gchar **static_names);
void nv_registry_free(NVRegistry *self);

static inline guint16
nv_registry_get_handle_flags(NVRegistry *self, NVHandle handle)
{
  NVHandleDesc *stored;

  if (G_UNLIKELY(!handle))
    return 0;

  stored = &g_array_index(self->names, NVHandleDesc, handle - 1);
  return stored->flags;
}

static inline const gchar *
nv_registry_get_handle_name(NVRegistry *self, NVHandle handle, gssize *length)
{
  NVHandleDesc *stored;

  if (G_UNLIKELY(!handle))
    {
      if (length)
        *length = 4;
      return "None";
    }

  stored = &g_array_index(self->names, NVHandleDesc, handle - 1);
  if (G_LIKELY(length))
    *length = stored->name_len;
  return stored->name;
}

/*
 * Contains a name-value pair.
 */
struct _NVEntry
{
  /* negative offset, counting from string table top, e.g. start of the string is at @top + ofs */
  guint8 indirect:1, referenced:1;
  guint8 name_len;
  guint32 alloc_len;
  union
  {
    struct
    {
      guint32 value_len;
      /* variable data, first the name of this entry, then the value, both are NUL terminated */
      gchar data[0];
    } vdirect;
    struct
    {
      NVHandle handle;
      guint32 ofs;
      guint32 len;
      guint8 type;
      gchar name[0];
    } vindirect;
  };
};

#define NV_ENTRY_DIRECT_HDR ((gsize) (&((NVEntry *) NULL)->vdirect.data))
#define NV_ENTRY_INDIRECT_HDR (sizeof(NVEntry))

static inline const gchar *
nv_entry_get_name(NVEntry *self)
{
  if (self->indirect)
    return self->vindirect.name;
  else
    return self->vdirect.data;
}

/*
 * Contains a set of ordered name-value pairs.
 *
 * This struct is used to track a set of name-value pairs that make up
 * a LogMessage structure. The storage layout is as concise as
 * possible to make it possible to serialize this payload as a single
 * writev() operation.
 *
 * Memory layout:
 * =============
 *
 *  || struct || static value offsets || dynamic value (id, offset) pairs || <free space> || stored (name, value)  ||
 *
 * Name value area:
 *   - the name-value area grows down (e.g. lower addresses) from the end of the struct
 *   - name-value pairs are referenced by the offset counting down from the end of the struct
 *   - all NV pairs are positioned at 4 bytes boundary, so 32 bit variables in NVEntry
 *     can be accessed in an aligned manner
 *
 * Static value offsets:
 *   - a fixed size of guint32 array, containing 32 bit offsets for statically allocated entries
 *   - the handles for static values have a low value and they match the index in this array
 *
 * Dynamic values:
 *   - a dynamically sized NVDynEntry array (contains ID + offset)
 *   - dynamic values are sorted by the global ID
 *
 * Memory allocation
 * =================
 *   - the memory used by NVTable is managed by the caller, sometimes it is
 *     allocated inside an existing data structure (we preallocate space
 *     with LogMessage)
 *
 *   - when the structure needs to grow the instance pointer itself needs to
 *     be changed. In order to avoid doing that in all the API calls, a
 *     separate nv_table_realloc() call is provided.
 *
 *   - NVTable instances are reference counted, but the reference counts are
 *     not thread safe (and accessing NVTable itself isn't either). When
 *     reallocation is needed and multiple references exist, NVTable clones
 *     itself and leaves the old copy be.
 *
 *   - It is possible to clone an NVTable, which basically copies the
 *     underlying memory contents.
 */
struct _NVTable
{
  /* byte order indication, etc. */
  guint32 size;
  guint32 used;
  guint16 num_dyn_entries;
  guint8 num_static_entries;
  guint8 ref_cnt:7,
    borrowed:1; /* specifies if the memory used by NVTable was borrowed from the container struct */

  /* variable data, see memory layout in the comment above */
  union
  {
    guint32 __dummy_for_alignment;
    guint32 static_entries[0];
    gchar data[0];
  };
};

#define NV_TABLE_BOUND(x)  (((x) + 0x3) & ~0x3)
#define NV_TABLE_ADDR(self, x) ((gchar *) ((self)) + ((gssize)(x)))


/* 256MB, this is an artificial limit, but must be less than MAX_GUINT32 as
 * we want to compare a guint32 to this variable without overflow.  */
#define NV_TABLE_MAX_BYTES  (256*1024*1024)

gboolean nv_table_add_value(NVTable *self, NVHandle handle, const gchar *name, gsize name_len, const gchar *value, gsize value_len, gboolean *new_entry);
gboolean nv_table_add_value_indirect(NVTable *self, NVHandle handle, const gchar *name, gsize name_len, NVHandle ref_handle, guint8 type, guint32 ofs, guint32 len, gboolean *new_entry);

gboolean nv_table_foreach(NVTable *self, NVRegistry *registry, NVTableForeachFunc func, gpointer user_data);
gboolean nv_table_foreach_entry(NVTable *self, NVTableForeachEntryFunc func, gpointer user_data);

void nv_table_clear(NVTable *self);
NVTable *nv_table_new(gint num_static_values, gint num_dyn_values, gint init_length);
NVTable *nv_table_init_borrowed(gpointer space, gsize space_len, gint num_static_entries);
gboolean nv_table_realloc(NVTable *self, NVTable **new);
NVTable *nv_table_clone(NVTable *self, gint additional_space);
NVTable *nv_table_ref(NVTable *self);
void nv_table_unref(NVTable *self);

static inline gsize
nv_table_get_alloc_size(gint num_static_entries, gint num_dyn_values, gint init_length)
{
  NVTable *self G_GNUC_UNUSED = NULL;
  gsize size;

  size = NV_TABLE_BOUND(init_length) + NV_TABLE_BOUND(sizeof(NVTable) + num_static_entries * sizeof(self->static_entries[0]) + num_dyn_values * sizeof(NVDynValue));
  if (size < 128)
    return 128;
  if (size > NV_TABLE_MAX_BYTES)
    size = NV_TABLE_MAX_BYTES;
  return size;
}

static inline gchar *
nv_table_get_top(NVTable *self)
{
  return NV_TABLE_ADDR(self, self->size);
}

/* private declarations for inline functions */
NVEntry *nv_table_get_entry_slow(NVTable *self, NVHandle handle, NVDynValue **dyn_slot);
const gchar *nv_table_resolve_indirect(NVTable *self, NVEntry *entry, gssize *len);


static inline NVEntry *
__nv_table_get_entry(NVTable *self, NVHandle handle, guint16 num_static_entries, NVDynValue **dyn_slot)
{
  guint32 ofs;

  if (G_UNLIKELY(!handle))
    {
      *dyn_slot = NULL;
      return NULL;
    }

  if (G_LIKELY(handle <= num_static_entries))
    {
      ofs = self->static_entries[handle - 1];
      *dyn_slot = NULL;
      if (G_UNLIKELY(!ofs))
        return NULL;
      return (NVEntry *) (nv_table_get_top(self) - ofs);
    }
  else
    {
      return nv_table_get_entry_slow(self, handle, dyn_slot);
    }
}

static inline NVEntry *
nv_table_get_entry(NVTable *self, NVHandle handle, NVDynValue **dyn_slot)
{
  return __nv_table_get_entry(self, handle, self->num_static_entries, dyn_slot);
}

static inline const gchar *
__nv_table_get_value(NVTable *self, NVHandle handle, guint16 num_static_entries, gssize *length)
{
  NVEntry *entry;
  NVDynValue *dyn_slot;

  entry = nv_table_get_entry(self, handle, &dyn_slot);
  if (G_UNLIKELY(!entry))
    {
      if (length)
        *length = 0;
      return null_string;
    }

  if (!entry->indirect)
    {
      if (length)
        *length = entry->vdirect.value_len;
      return entry->vdirect.data + entry->name_len + 1;
    }
  return nv_table_resolve_indirect(self, entry, length);
}

static inline const gchar *
nv_table_get_value(NVTable *self, NVHandle handle, gssize *length)
{
  return __nv_table_get_value(self, handle, self->num_static_entries, length);
}


#endif
