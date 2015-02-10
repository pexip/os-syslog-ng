/*
 * Copyright (c) 2002-2013 BalaBit IT Ltd, Budapest, Hungary
 * Copyright (c) 1998-2013 Balázs Scheidler
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

#include "filter/filter-pipe.h"

/*******************************************************************
 * LogFilterPipe
 *******************************************************************/

static gboolean
log_filter_pipe_init(LogPipe *s)
{
  LogFilterPipe *self = (LogFilterPipe *) s;
  GlobalConfig *cfg = log_pipe_get_config(s);

  if (self->expr->init)
    self->expr->init(self->expr, log_pipe_get_config(s));
  if (!self->name)
    self->name = cfg_tree_get_rule_name(&cfg->tree, ENC_FILTER, s->expr_node);
  return TRUE;
}

static void
log_filter_pipe_queue(LogPipe *s, LogMessage *msg, const LogPathOptions *path_options, gpointer user_data)
{
  LogFilterPipe *self = (LogFilterPipe *) s;
  gchar buf[128];
  gboolean res;

  msg_debug("Filter rule evaluation begins",
            evt_tag_str("rule", self->name),
            evt_tag_str("location", log_expr_node_format_location(s->expr_node, buf, sizeof(buf))),
            NULL);

  res = filter_expr_eval_root(self->expr, &msg, path_options);
  msg_debug("Filter rule evaluation result",
            evt_tag_str("result", res ? "match" : "not-match"),
            evt_tag_str("rule", self->name),
            evt_tag_str("location", log_expr_node_format_location(s->expr_node, buf, sizeof(buf))),
            NULL);
  if (res)
    {
      log_pipe_forward_msg(s, msg, path_options);
    }
  else
    {
      if (path_options->matched)
        (*path_options->matched) = FALSE;
      log_msg_drop(msg, path_options);
    }
}

static LogPipe *
log_filter_pipe_clone(LogPipe *s)
{
  LogFilterPipe *self = (LogFilterPipe *) s;

  return log_filter_pipe_new(filter_expr_ref(self->expr));
}

static void
log_filter_pipe_free(LogPipe *s)
{
  LogFilterPipe *self = (LogFilterPipe *) s;

  g_free(self->name);
  filter_expr_unref(self->expr);
  log_pipe_free_method(s);
}

LogPipe *
log_filter_pipe_new(FilterExprNode *expr)
{
  LogFilterPipe *self = g_new0(LogFilterPipe, 1);

  log_pipe_init_instance(&self->super);
  self->super.init = log_filter_pipe_init;
  self->super.queue = log_filter_pipe_queue;
  self->super.free_fn = log_filter_pipe_free;
  self->super.clone = log_filter_pipe_clone;
  self->expr = expr;
  return &self->super;
}
