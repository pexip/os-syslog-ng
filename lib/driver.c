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
  
#include "driver.h"
#include "logqueue-fifo.h"
#include "afinter.h"
#include "cfg-tree.h"

#include <string.h>

/* LogDriverPlugin */

void
log_driver_plugin_free_method(LogDriverPlugin *self)
{
  g_free(self);
}

void
log_driver_plugin_init_instance(LogDriverPlugin *self)
{
  self->free_fn = log_driver_plugin_free_method;
}

/* LogDriver */

void
log_driver_add_plugin(LogDriver *self, LogDriverPlugin *plugin)
{
  self->plugins = g_list_append(self->plugins, plugin);
}

gboolean
log_driver_init_method(LogPipe *s)
{
  LogDriver *self = (LogDriver *) s;
  gboolean success = TRUE;
  GList *l;

  for (l = self->plugins; l; l = l->next)
    {
      if (!log_driver_plugin_attach((LogDriverPlugin *) l->data, self))
        success = FALSE;
    }
  return success;
}

gboolean
log_driver_deinit_method(LogPipe *s)
{
  LogDriver *self = (LogDriver *) s;
  gboolean success = TRUE;
  GList *l;

  for (l = self->plugins; l; l = l->next)
    {
      log_driver_plugin_detach((LogDriverPlugin *) l->data, self);
    }
  return success;
}

/* NOTE: intentionally static, as only cDriver or LogDestDriver will derive from LogDriver */
static void
log_driver_free(LogPipe *s)
{
  LogDriver *self = (LogDriver *) s;
  GList *l;
  
  for (l = self->plugins; l; l = l->next)
    {
      log_driver_plugin_free((LogDriverPlugin *) l->data);
    }
  if (self->plugins)
    {
      g_list_free(self->plugins);
    }
  if (self->group)
    g_free(self->group);
  if (self->id)
    g_free(self->id);
  log_pipe_free_method(s);
}

/* NOTE: intentionally static, as only LogSrcDriver or LogDestDriver will derive from LogDriver */
static void
log_driver_init_instance(LogDriver *self, GlobalConfig *cfg)
{
  log_pipe_init_instance(&self->super, cfg);
  self->super.free_fn = log_driver_free;
  self->super.init = log_driver_init_method;
  self->super.deinit = log_driver_deinit_method;
}

/* LogSrcDriver */

gboolean
log_src_driver_init_method(LogPipe *s)
{
  LogSrcDriver *self = (LogSrcDriver *) s;
  GlobalConfig *cfg = log_pipe_get_config(s);

  if (!log_driver_init_method(s))
    return FALSE;

  if (!self->super.group)
    {
      self->super.group = cfg_tree_get_rule_name(&cfg->tree, ENC_SOURCE, s->expr_node);
      self->group_len = strlen(self->super.group);
      self->super.id = cfg_tree_get_child_id(&cfg->tree, ENC_SOURCE, s->expr_node);
    }

  stats_lock();
  stats_register_counter(0, SCS_SOURCE | SCS_GROUP, self->super.group, NULL, SC_TYPE_PROCESSED, &self->super.processed_group_messages);
  stats_register_counter(0, SCS_CENTER, NULL, "received", SC_TYPE_PROCESSED, &self->received_global_messages);
  stats_unlock();

  return TRUE;
}

gboolean
log_src_driver_deinit_method(LogPipe *s)
{
  LogSrcDriver *self = (LogSrcDriver *) s;

  if (!log_driver_deinit_method(s))
    return FALSE;

  stats_lock();
  stats_unregister_counter(SCS_SOURCE | SCS_GROUP, self->super.group, NULL, SC_TYPE_PROCESSED, &self->super.processed_group_messages);
  stats_unregister_counter(SCS_CENTER, NULL, "received", SC_TYPE_PROCESSED, &self->received_global_messages);
  stats_unlock();
  return TRUE;
}

void
log_src_driver_queue_method(LogPipe *s, LogMessage *msg, const LogPathOptions *path_options, gpointer user_data)
{
  LogSrcDriver *self = (LogSrcDriver *) s;
  GlobalConfig *cfg = log_pipe_get_config(s);

  /* $SOURCE */

  if (msg->flags & LF_LOCAL)
    afinter_postpone_mark(cfg->mark_freq);

  log_msg_set_value(msg, LM_V_SOURCE, self->super.group, self->group_len);
  stats_counter_inc(self->super.processed_group_messages);
  stats_counter_inc(self->received_global_messages);
  log_pipe_forward_msg(s, msg, path_options);
}

void
log_src_driver_init_instance(LogSrcDriver *self, GlobalConfig *cfg)
{
  log_driver_init_instance(&self->super, cfg);
  self->super.super.init = log_src_driver_init_method;
  self->super.super.deinit = log_src_driver_deinit_method;
  self->super.super.queue = log_src_driver_queue_method;
  self->super.super.flags |= PIF_SOURCE;
}

void
log_src_driver_free(LogPipe *s)
{
  log_driver_free(s);
}

/* LogDestDriver */

/* returns a reference */
static LogQueue *
log_dest_driver_acquire_queue_method(LogDestDriver *self, const gchar *persist_name,
                                     gpointer user_data)
{
  GlobalConfig *cfg = log_pipe_get_config(&self->super.super);
  LogQueue *queue = NULL;

  g_assert(user_data == NULL);

  if (persist_name)
    queue = cfg_persist_config_fetch(cfg, persist_name);

  if (!queue)
    {
      queue = log_queue_fifo_new(self->log_fifo_size < 0 ? cfg->log_fifo_size : self->log_fifo_size, persist_name);
      log_queue_set_throttle(queue, self->throttle);
    }
  return queue;
}

/* consumes the reference in @q */
static void
log_dest_driver_release_queue_method(LogDestDriver *self, LogQueue *q, gpointer user_data)
{
  GlobalConfig *cfg = log_pipe_get_config(&self->super.super);

  /* we only save the LogQueue instance if it contains data */
  if (q->persist_name && log_queue_keep_on_reload(q) > 0)
    {
      cfg_persist_config_add(cfg, q->persist_name, q, (GDestroyNotify) log_queue_unref, FALSE);
    }
  else
    {
      log_queue_unref(q);
    }
}

void
log_dest_driver_queue_method(LogPipe *s, LogMessage *msg, const LogPathOptions *path_options, gpointer user_data)
{
  LogDestDriver *self = (LogDestDriver *) s;

  stats_counter_inc(self->super.processed_group_messages);
  stats_counter_inc(self->queued_global_messages);
  log_pipe_forward_msg(s, msg, path_options);
}

gboolean
log_dest_driver_init_method(LogPipe *s)
{
  LogDestDriver *self = (LogDestDriver *) s;
  GlobalConfig *cfg = log_pipe_get_config(s);

  if (!log_driver_init_method(s))
    return FALSE;

  if (!self->super.group)
    {
      self->super.group = cfg_tree_get_rule_name(&cfg->tree, ENC_DESTINATION, s->expr_node);
      self->super.id = cfg_tree_get_child_id(&cfg->tree, ENC_DESTINATION, s->expr_node);
    }

  stats_lock();
  stats_register_counter(0, SCS_DESTINATION | SCS_GROUP, self->super.group, NULL, SC_TYPE_PROCESSED, &self->super.processed_group_messages);
  stats_register_counter(0, SCS_CENTER, NULL, "queued", SC_TYPE_PROCESSED, &self->queued_global_messages);
  stats_unlock();

  return TRUE;
}

gboolean
log_dest_driver_deinit_method(LogPipe *s)
{
  LogDestDriver *self = (LogDestDriver *) s;
  GList *l, *l_next;

  for (l = self->queues; l; l = l_next)
    {
      LogQueue *q = (LogQueue *) l->data;

      /* the GList struct will be freed by log_dest_driver_release_queue */
      l_next = l->next;

      /* we have to pass a reference to log_dest_driver_release_queue(),
       * which automatically frees the ref on the list too */
      log_dest_driver_release_queue(self, log_queue_ref(q));
    }
  g_assert(self->queues == NULL);

  stats_lock();
  stats_unregister_counter(SCS_DESTINATION | SCS_GROUP, self->super.group, NULL, SC_TYPE_PROCESSED, &self->super.processed_group_messages);
  stats_unregister_counter(SCS_CENTER, NULL, "queued", SC_TYPE_PROCESSED, &self->queued_global_messages);
  stats_unlock();

  if (!log_driver_deinit_method(s))
    return FALSE;
  return TRUE;
}

void
log_dest_driver_init_instance(LogDestDriver *self, GlobalConfig *cfg)
{
  log_driver_init_instance(&self->super, cfg);
  self->super.super.init = log_dest_driver_init_method;
  self->super.super.deinit = log_dest_driver_deinit_method;
  self->super.super.queue = log_dest_driver_queue_method;
  self->acquire_queue = log_dest_driver_acquire_queue_method;
  self->release_queue = log_dest_driver_release_queue_method;
  self->log_fifo_size = -1;
  self->throttle = 0;
}

void
log_dest_driver_free(LogPipe *s)
{
  LogDestDriver *self = (LogDestDriver *) s;
  GList *l;

  for (l = self->queues; l; l = l->next)
    {
      log_queue_unref((LogQueue *) l->data);
    }
  g_list_free(self->queues);
  log_driver_free(s);
}
