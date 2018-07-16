/*
 * Copyright (c) 2002-2013 Balabit
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
  
#ifndef AFFILE_SOURCE_H_INCLUDED
#define AFFILE_SOURCE_H_INCLUDED

#include "driver.h"
#include "logreader.h"
#include "logproto/logproto-regexp-multiline-server.h"
#include "affile-common.h"


enum
{
  MLM_NONE,
  MLM_INDENTED,
  MLM_PREFIX_GARBAGE,
  MLM_PREFIX_SUFFIX,
};

typedef struct _AFFileSourceDriver
{
  LogSrcDriver super;
  GString *filename;
  LogReader *reader;
  LogReaderOptions reader_options;
  FilePermOptions file_perm_options;
  FileOpenOptions file_open_options;
  gint pad_size;
  gint follow_freq;
  gint multi_line_mode;
  MultiLineRegexp *multi_line_prefix, *multi_line_garbage;
  /* state information to follow a set of files using a wildcard expression */
} AFFileSourceDriver;

LogDriver *affile_sd_new(gchar *filename, GlobalConfig *cfg);
LogDriver *afpipe_sd_new(gchar *filename, GlobalConfig *cfg);

gboolean affile_sd_set_multi_line_prefix(LogDriver *s, const gchar *prefix_regexp, GError **error);
gboolean affile_sd_set_multi_line_garbage(LogDriver *s, const gchar *garbage_regexp, GError **error);
gboolean affile_sd_set_multi_line_mode(LogDriver *s, const gchar *mode);
void affile_sd_set_follow_freq(LogDriver *s, gint follow_freq);

void affile_sd_set_recursion(LogDriver *s, const gint recursion);
void affile_sd_set_pri_level(LogDriver *s, const gint16 severity);
void affile_sd_set_pri_facility(LogDriver *s, const gint16 facility);

#endif
