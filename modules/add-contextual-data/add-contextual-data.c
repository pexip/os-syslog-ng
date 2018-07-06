/*
 * Copyright (c) 2016 Balabit
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

#include "add-contextual-data.h"
#include "logmsg/logmsg.h"
#include "logpipe.h"
#include "parser/parser-expr.h"
#include "reloc.h"
#include "contextual-data-record-scanner.h"
#include "template/templates.h"
#include "context-info-db.h"
#include "pathutils.h"

#include <stdio.h>
#include <string.h>


typedef struct AddContextualData
{
  LogParser super;
  ContextInfoDB *context_info_db;
  gchar *selector_template_string;
  LogTemplate *selector_template;
  gchar *default_selector;
  gchar *filename;
  gchar *prefix;
} AddContextualData;

void
add_contextual_data_set_filename(LogParser *p, const gchar *filename)
{
  AddContextualData *self = (AddContextualData *) p;

  g_free(self->filename);
  self->filename = g_strdup(filename);
}

void
add_contextual_data_set_database_selector_template(LogParser *p,
                                                   const gchar *selector)
{
  AddContextualData *self = (AddContextualData *) p;
  g_free(self->selector_template_string);
  self->selector_template_string = g_strdup(selector);
}

void
add_contextual_data_set_prefix(LogParser *p, const gchar *prefix)
{
  AddContextualData *self = (AddContextualData *) p;

  g_free(self->prefix);
  self->prefix = g_strdup(prefix);
}

void
add_contextual_data_set_database_default_selector(LogParser *p,
                                                  const gchar *
                                                  default_selector)
{
  AddContextualData *self = (AddContextualData *) p;

  g_free(self->default_selector);
  self->default_selector = g_strdup(default_selector);
}

static gboolean
_is_default_selector_set(const AddContextualData *self)
{
  return (self->default_selector != NULL);
}

static void
_add_context_data_to_message(gpointer pmsg,
                             const ContextualDataRecord *record)
{
  LogMessage *msg = (LogMessage *) pmsg;
  log_msg_set_value_by_name(msg, record->name->str, record->value->str, record->value->len);
}

static gboolean
_process(LogParser *s, LogMessage **pmsg,
         const LogPathOptions *path_options,
         const gchar *input, gsize input_len)
{
  AddContextualData *self = (AddContextualData *) s;
  LogMessage *msg = log_msg_make_writable(pmsg, path_options);
  GString *selector_str = g_string_new(NULL);
  const gchar *selector = NULL;

  log_template_format(self->selector_template, msg, NULL, LTZ_LOCAL, 0, NULL,
                      selector_str);

  if (context_info_db_contains(self->context_info_db, selector_str->str))
    selector = selector_str->str;
  else if (_is_default_selector_set(self))
    selector = self->default_selector;

  if (selector)
    context_info_db_foreach_record(self->context_info_db, selector,
                                   _add_context_data_to_message,
                                   (gpointer) msg);

  g_string_free(selector_str, TRUE);

  return TRUE;
}

static void
_replace_template(LogTemplate **old_template, LogTemplate *new_template)
{
  log_template_unref(*old_template);
  *old_template = log_template_ref(new_template);
}

static void
_replace_context_info_db(ContextInfoDB **old_db, ContextInfoDB *new_db)
{
  context_info_db_unref(*old_db);
  *old_db = context_info_db_ref(new_db);
}

static LogPipe *
_clone(LogPipe *s)
{
  AddContextualData *self = (AddContextualData *) s;
  AddContextualData *cloned =
    (AddContextualData *) add_contextual_data_parser_new(s->cfg);

  log_parser_set_template(&cloned->super,
                          log_template_ref(self->super.template));
  _replace_context_info_db(&cloned->context_info_db, self->context_info_db);
  _replace_template(&cloned->selector_template, self->selector_template);
  add_contextual_data_set_prefix(&cloned->super, self->prefix);
  add_contextual_data_set_filename(&cloned->super, self->filename);
  add_contextual_data_set_database_default_selector(&cloned->super,
                                                    self->default_selector);

  return &cloned->super.super;
}

static void
_free(LogPipe *s)
{
  AddContextualData *self = (AddContextualData *) s;

  context_info_db_unref(self->context_info_db);
  g_free(self->filename);
  g_free(self->prefix);
  log_template_unref(self->selector_template);
  log_parser_free_method(s);
  g_free(self->selector_template_string);
}

static gboolean
_is_relative_path(const gchar *filename)
{
  return (filename[0] != '/');
}

static gchar *
_complete_relative_path_with_config_path(const gchar *filename)
{
  return
    g_build_filename(get_installation_path_for(SYSLOG_NG_PATH_SYSCONFDIR),
                     filename, NULL);
}

static FILE *
_open_data_file(const gchar *filename)
{
  FILE *f = NULL;

  if (_is_relative_path(filename))
    {
      gchar *absolute_path =
        _complete_relative_path_with_config_path(filename);
      f = fopen(absolute_path, "r");
      g_free(absolute_path);
    }
  else
    {
      f = fopen(filename, "r");
    }

  return f;
}

static ContextualDataRecordScanner *
_get_scanner(AddContextualData *self)
{
  const gchar *type = get_filename_extension(self->filename);
  ContextualDataRecordScanner *scanner =
    create_contextual_data_record_scanner_by_type(type);

  if (!scanner)
    {
      msg_error("Unknown file extension",
                evt_tag_str("filename", self->filename));
      return NULL;
    }

  contextual_data_record_scanner_set_name_prefix(scanner, self->prefix);

  return scanner;
}

static gboolean
_load_context_info_db(AddContextualData *self)
{
  ContextualDataRecordScanner *scanner = _get_scanner(self);

  if (!scanner)
    return FALSE;

  FILE *f = _open_data_file(self->filename);
  if (!f)
    {
      msg_error("Error loading add_contextual_data database",
                evt_tag_str("filename", self->filename));
      contextual_data_record_scanner_free(scanner);
      return FALSE;
    }

  gboolean tag_db_loaded =
    context_info_db_import(self->context_info_db, f, scanner);
  contextual_data_record_scanner_free(scanner);

  fclose(f);
  if (!tag_db_loaded)
    {
      msg_error("Error while parsing add_contextual_data database");
      return FALSE;
    }

  return TRUE;
}

static gboolean
_is_initialized(AddContextualData *self)
{
  return context_info_db_is_loaded(self->context_info_db);
}

gboolean
_compile_selector_template(AddContextualData *self)
{
  GError *error = NULL;
  if (!self->selector_template_string)
    {
      msg_error("No selector set.");
      return FALSE;
    }

  if (!log_template_compile(self->selector_template, self->selector_template_string, &error))
    {
      msg_error("Failed to compile template",
                evt_tag_str("template", self->selector_template_string),
                evt_tag_str("error", error->message));
      return FALSE;
    }

  return TRUE;
}

static gboolean
_first_init(AddContextualData *self)
{
  if (self->filename == NULL)
    {
      msg_error("No database file set.");
      return FALSE;
    }

  if (!_compile_selector_template(self))
    return FALSE;

  if (!_load_context_info_db(self))
    {
      msg_error("Failed to load the database file.");
      return FALSE;
    }

  return TRUE;
}

static gboolean
_init(LogPipe *s)
{
  AddContextualData *self = (AddContextualData *) s;

  if (_is_initialized(self) || _first_init(self))
    return log_parser_init_method(s);

  return FALSE;
}

LogParser *
add_contextual_data_parser_new(GlobalConfig *cfg)
{
  AddContextualData *self = g_new0(AddContextualData, 1);

  log_parser_init_instance(&self->super, cfg);

  self->selector_template = log_template_new(cfg, NULL);

  self->super.process = _process;
  self->context_info_db = context_info_db_new();

  self->super.super.clone = _clone;
  self->super.super.free_fn = _free;
  self->super.super.init = _init;
  self->default_selector = NULL;
  self->prefix = NULL;
  self->selector_template_string = NULL;

  return &self->super;
}
