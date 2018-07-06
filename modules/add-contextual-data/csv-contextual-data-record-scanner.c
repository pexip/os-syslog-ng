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

#include "csv-contextual-data-record-scanner.h"
#include "scanner/csv-scanner/csv-scanner.h"
#include "string-list.h"
#include <string.h>


static gchar *
_csv_scanner_dup_current_value_with_prefix(CSVScanner *line_scanner,
                                           const gchar *prefix)
{
  if (!prefix)
    return csv_scanner_dup_current_value(line_scanner);

  return g_strdup_printf("%s.%s", prefix,
                         csv_scanner_get_current_value(line_scanner));
}

static gboolean
_fetch_next_with_prefix(ContextualDataRecordScanner *record_scanner,
                        GString **target, const gchar *prefix)
{
  CSVScanner *line_scanner = (CSVScanner *) record_scanner->scanner;
  if (!csv_scanner_scan_next(line_scanner))
    {
      return FALSE;
    }
  gchar *next = _csv_scanner_dup_current_value_with_prefix(line_scanner, prefix);
  *target = g_string_new(next);
  g_free(next);

  return TRUE;
}

static gboolean
_fetch_next_without_prefix(ContextualDataRecordScanner *
                           record_scanner, GString **target)
{
  return _fetch_next_with_prefix(record_scanner, target, NULL);
}

static gboolean
_is_whole_record_parsed(CSVScanner *line_scanner)
{
  csv_scanner_scan_next(line_scanner);
  return csv_scanner_is_scan_finished(line_scanner);
}

const gboolean
get_next_record(ContextualDataRecordScanner *s, const gchar *input, ContextualDataRecord *record)
{
  CSVScanner *line_scanner = (CSVScanner *) s->scanner;
  csv_scanner_input(line_scanner, input);

  if (!_fetch_next_without_prefix(s, &record->selector))
    return FALSE;

  if (!_fetch_next_with_prefix(s, &record->name, s->name_prefix))
    return FALSE;

  if (!_fetch_next_without_prefix(s, &record->value))
    return FALSE;

  return _is_whole_record_parsed(line_scanner);
}

static void
csv_contextual_data_record_scanner_free(ContextualDataRecordScanner *s)
{
  CSVContextualDataRecordScanner *self = (CSVContextualDataRecordScanner *) s;
  csv_scanner_options_clean(&self->options);
  csv_scanner_state_clean(&self->scanner);
  g_free(self);
}

ContextualDataRecordScanner *
csv_contextual_data_record_scanner_new()
{
  CSVContextualDataRecordScanner *self =
    g_new0(CSVContextualDataRecordScanner, 1);
  csv_scanner_options_set_delimiters(&self->options, ",");
  csv_scanner_options_set_quote_pairs(&self->options, "\"\"''");
  const gchar *column_array[] = { "selector", "name", "value", NULL };
  csv_scanner_options_set_columns(&self->options,
                                  string_array_to_list(column_array));
  csv_scanner_options_set_flags(&self->options, CSV_SCANNER_STRIP_WHITESPACE | CSV_SCANNER_DROP_INVALID);
  csv_scanner_options_set_dialect(&self->options, CSV_SCANNER_ESCAPE_NONE);
  csv_scanner_state_init(&self->scanner, &self->options);
  self->super.scanner = &self->scanner;
  self->super.get_next = get_next_record;
  self->super.free_fn = csv_contextual_data_record_scanner_free;

  return &self->super;
}
