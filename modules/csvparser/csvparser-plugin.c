/*
 * Copyright (c) 2002-2010 BalaBit IT Ltd, Budapest, Hungary
 * Copyright (c) 1998-2010 Balázs Scheidler
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published
 * by the Free Software Foundation, or (at your option) any later version.
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

#include "cfg-parser.h"
#include "plugin.h"
#include "csvparser.h"

extern CfgParser csvparser_parser;

static Plugin csvparser_plugins[] =
{
  {
    .type = LL_CONTEXT_PARSER,
    .name = "csv-parser",
    .parser = &csvparser_parser,
  },
};

gboolean
csvparser_module_init(GlobalConfig *cfg, CfgArgs *args)
{
  plugin_register(cfg, csvparser_plugins, G_N_ELEMENTS(csvparser_plugins));
  return TRUE;
}

const ModuleInfo module_info =
{
  .canonical_name = "csvparser",
  .version = VERSION,
  .description = "The csvparser module provides parsing support for CSV and other separated value formats for syslog-ng.",
  .core_revision = SOURCE_REVISION,
  .plugins = csvparser_plugins,
  .plugins_len = G_N_ELEMENTS(csvparser_plugins),
};
