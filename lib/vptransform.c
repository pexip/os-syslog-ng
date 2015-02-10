/*
 * Copyright (c) 2011-2013 BalaBit IT Ltd, Budapest, Hungary
 * Copyright (c) 2011-2013 Gergely Nagy <algernon@balabit.hu>
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

#include "value-pairs.h"
#include "vptransform.h"
#include "template/templates.h"
#include "cfg-parser.h"
#include "misc.h"
#include "scratch-buffers.h"

#include <string.h>

typedef void (*VPTransFunc)(ValuePairsTransform *t, SBGString *name);
typedef void (*VPTransDestroyFunc)(ValuePairsTransform *t);

struct _ValuePairsTransformSet
{
  GPatternSpec *pattern;

  GList *transforms;
};

struct _ValuePairsTransform
{
  VPTransFunc transform;
  VPTransDestroyFunc destroy;
};

typedef struct
{
  ValuePairsTransform super;

  gint amount;
} VPTransShift;

typedef struct
{
  ValuePairsTransform super;

  gchar *prefix;
} VPTransAddPrefix;

typedef struct
{
  ValuePairsTransform super;

  gchar *old_prefix;
  gchar *new_prefix;
  gint new_prefix_len;
  gint old_prefix_len;
} VPTransReplacePrefix;

static void
vp_trans_init(ValuePairsTransform *t,
              VPTransFunc trans,
              VPTransDestroyFunc dest)
{
  if (!t)
    return;

  t->transform = trans;
  t->destroy = dest;
}

void
value_pairs_transform_free(ValuePairsTransform *t)
{
  if (t->destroy)
    t->destroy(t);
  g_free(t);
}

static inline void
value_pairs_transform_apply(ValuePairsTransform *t, SBGString *key)
{
  t->transform(t, key);
}

/* add_prefix() */

static void
vp_trans_add_prefix(ValuePairsTransform *t, SBGString *key)
{
  VPTransAddPrefix *self = (VPTransAddPrefix *)t;

  g_string_prepend(sb_gstring_string(key), self->prefix);
}

static void
vp_trans_add_prefix_destroy(ValuePairsTransform *t)
{
  VPTransAddPrefix *self = (VPTransAddPrefix *)t;

  g_free(self->prefix);
}

ValuePairsTransform *
value_pairs_new_transform_add_prefix (const gchar *prefix)
{
  VPTransAddPrefix *vpt;

  vpt = g_new(VPTransAddPrefix, 1);
  vp_trans_init((ValuePairsTransform *)vpt,
                vp_trans_add_prefix,
                vp_trans_add_prefix_destroy);
  vpt->prefix = g_strdup(prefix);

  return (ValuePairsTransform *)vpt;
}

/* shift() */

static void
vp_trans_shift(ValuePairsTransform *t, SBGString* key)
{
  VPTransShift *self = (VPTransShift *)t;

  g_string_erase(sb_gstring_string(key), 0, self->amount);
}

ValuePairsTransform *
value_pairs_new_transform_shift (gint amount)
{
  VPTransShift *vpt;

  vpt = g_new(VPTransShift, 1);
  vp_trans_init((ValuePairsTransform *)vpt,
                vp_trans_shift, NULL);

  vpt->amount = amount;

  return (ValuePairsTransform *)vpt;
}

/* replace-prefix() */

static void
vp_trans_replace_prefix(ValuePairsTransform *t, SBGString *key)
{
  VPTransReplacePrefix *self = (VPTransReplacePrefix *)t;

  if (strncmp(self->old_prefix, sb_gstring_string(key)->str,
              self->old_prefix_len) != 0)
    return;

  g_string_erase(sb_gstring_string(key), 0, self->old_prefix_len);
  g_string_prepend_len(sb_gstring_string(key),
                       self->new_prefix, self->new_prefix_len);
}

static void
vp_trans_replace_prefix_destroy(ValuePairsTransform *t)
{
  VPTransReplacePrefix *self = (VPTransReplacePrefix *)t;

  g_free(self->old_prefix);
  g_free(self->new_prefix);
}

ValuePairsTransform *
value_pairs_new_transform_replace_prefix(const gchar *prefix, const gchar *new_prefix)
{
  VPTransReplacePrefix *vpt;

  vpt = g_new(VPTransReplacePrefix, 1);
  vp_trans_init((ValuePairsTransform *)vpt,
                vp_trans_replace_prefix,
                vp_trans_replace_prefix_destroy);

  vpt->old_prefix = g_strdup(prefix);
  vpt->old_prefix_len = strlen(prefix);
  vpt->new_prefix = g_strdup(new_prefix);
  vpt->new_prefix_len = strlen(vpt->new_prefix);

  return (ValuePairsTransform *)vpt;
}

/*
 * ValuePairsTransformSet
 */

ValuePairsTransformSet *
value_pairs_transform_set_new(const gchar *glob)
{
  ValuePairsTransformSet *vpts;

  vpts = g_new(ValuePairsTransformSet, 1);
  vpts->transforms = NULL;
  vpts->pattern = g_pattern_spec_new(glob);

  return vpts;
}

void
value_pairs_transform_set_add_func(ValuePairsTransformSet *vpts,
                                   ValuePairsTransform *vpt)
{
  vpts->transforms = g_list_append(vpts->transforms, vpt);
}

void
value_pairs_transform_set_free(ValuePairsTransformSet *vpts)
{
  GList *l;

  l = vpts->transforms;
  while (l)
    {
      value_pairs_transform_free((ValuePairsTransform *)l->data);
      l = g_list_delete_link(l, l);
    }
  g_pattern_spec_free(vpts->pattern);
  g_free(vpts);
}

gchar *
value_pairs_transform_set_apply(ValuePairsTransformSet *vpts, gchar *key)
{
  if (g_pattern_match_string(vpts->pattern, key))
    {
      GList *l;
      SBGString *sb;
      gchar *new_key;

      sb = sb_gstring_acquire ();
      g_string_assign(sb_gstring_string(sb), key);

      l = vpts->transforms;
      while (l)
        {
          value_pairs_transform_apply((ValuePairsTransform *)l->data, sb);
          l = l->next;
        }

      new_key = sb_gstring_string(sb)->str;
      g_string_steal(sb_gstring_string(sb));
      sb_gstring_release (sb);

      return new_key;
    }
  return g_strdup(key);
}
