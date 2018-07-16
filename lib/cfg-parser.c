/*
 * Copyright (c) 2002-2013 Balabit
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

#include "cfg-parser.h"
#include "cfg-lexer.h"
#include "cfg-grammar.h"

#include <string.h>

extern int main_debug;

/* defined in the parser */
int main_parse(CfgLexer *lexer, gpointer *dummy, gpointer arg);

/*
 * PLEASE: if at all possible avoid adding keywords here, as these
 * keywords might collide with user-defined identifiers (e.g. source,
 * destination & block names).
 *
 * Add the keyword & the token to the parser of the module in question
 * instead, even if there are multiple modules using the same
 * keywords.
 *
 * Tokens (e.g. KW_xxx) associated with core keywords (e.g. those
 * listed here) should be declared only once and only in cfg-grammar.y
 * and NOT in external modules.
 */
static CfgLexerKeyword main_keywords[] = {
  /* statements */
  { "source",             KW_SOURCE },
  { "filter",             KW_FILTER },
  { "parser",             KW_PARSER },
  { "rewrite",            KW_REWRITE },
  { "destination",        KW_DESTINATION },
  { "log",                KW_LOG },
  { "junction",           KW_JUNCTION },
  { "channel",            KW_CHANNEL },
  { "options",            KW_OPTIONS },
  { "include",            KW_INCLUDE, },
  { "block",              KW_BLOCK },

  /* source or destination items */
  { "internal",           KW_INTERNAL },

  /* value pairs */
  { "value_pairs",        KW_VALUE_PAIRS },
  { "exclude",            KW_EXCLUDE },
  { "pair",               KW_PAIR },
  { "key",                KW_KEY },
  { "scope",              KW_SCOPE },
  { "rekey",              KW_REKEY },
  { "shift",              KW_SHIFT },
  { "add_prefix",         KW_ADD_PREFIX },
  { "replace",            KW_REPLACE_PREFIX, KWS_OBSOLETE, "replace_prefix" },
  { "replace_prefix",     KW_REPLACE_PREFIX },

  /* option items */
  { "flags",              KW_FLAGS },
  { "pad_size",           KW_PAD_SIZE },
  { "mark_freq",          KW_MARK_FREQ },
  { "mark",               KW_MARK_FREQ, KWS_OBSOLETE, "mark_freq" },
  { "mark_mode",          KW_MARK_MODE },
  { "stats_freq",         KW_STATS_FREQ },
  { "stats_lifetime",     KW_STATS_LIFETIME },
  { "stats_level",        KW_STATS_LEVEL },
  { "stats",              KW_STATS_FREQ, KWS_OBSOLETE, "stats_freq" },
  { "flush_lines",        KW_FLUSH_LINES },
  { "flush_timeout",      KW_FLUSH_TIMEOUT },
  { "suppress",           KW_SUPPRESS },
  { "sync_freq",          KW_FLUSH_LINES, KWS_OBSOLETE, "flush_lines" },
  { "sync",               KW_FLUSH_LINES, KWS_OBSOLETE, "flush_lines" },
  { "long_hostnames",     KW_CHAIN_HOSTNAMES, KWS_OBSOLETE, "chain_hostnames" },
  { "chain_hostnames",    KW_CHAIN_HOSTNAMES },
  { "normalize_hostnames",KW_NORMALIZE_HOSTNAMES },
  { "keep_hostname",      KW_KEEP_HOSTNAME },
  { "check_hostname",     KW_CHECK_HOSTNAME },
  { "bad_hostname",       KW_BAD_HOSTNAME },
  { "custom_domain",      KW_CUSTOM_DOMAIN },
  { "keep_timestamp",     KW_KEEP_TIMESTAMP },
  { "encoding",           KW_ENCODING },
  { "ts_format",          KW_TS_FORMAT },
  { "frac_digits",        KW_FRAC_DIGITS },
  { "time_zone",          KW_TIME_ZONE },
  { "recv_time_zone",     KW_RECV_TIME_ZONE },
  { "send_time_zone",     KW_SEND_TIME_ZONE },
  { "local_time_zone",    KW_LOCAL_TIME_ZONE },
  { "format",             KW_FORMAT },
  { "use_time_recvd",     KW_USE_TIME_RECVD, KWS_OBSOLETE, "Use R_ or S_ prefixed macros in templates or keep_timestamp(no)" },
  { "use_fqdn",           KW_USE_FQDN },
  { "use_dns",            KW_USE_DNS },
  { "time_reopen",        KW_TIME_REOPEN },
  { "time_reap",          KW_TIME_REAP },
  { "time_sleep",         KW_TIME_SLEEP, KWS_OBSOLETE, "time_sleep() has been deprecated since " VERSION_3_3 },
  { "file_template",      KW_FILE_TEMPLATE },
  { "proto_template",     KW_PROTO_TEMPLATE },
  { "default_level",      KW_DEFAULT_LEVEL },
  { "default_priority",   KW_DEFAULT_LEVEL },
  { "default_facility",   KW_DEFAULT_FACILITY },
  { "threaded",           KW_THREADED },
  { "use_rcptid",         KW_USE_RCPTID, KWS_OBSOLETE, "This has been deprecated since " VERSION_3_7  ", try use_uniqid() instead" },
  { "use_uniqid",         KW_USE_UNIQID },

  { "log_fifo_size",      KW_LOG_FIFO_SIZE },
  { "log_fetch_limit",    KW_LOG_FETCH_LIMIT },
  { "log_iw_size",        KW_LOG_IW_SIZE },
  { "log_msg_size",       KW_LOG_MSG_SIZE },
  { "log_prefix",         KW_LOG_PREFIX, KWS_OBSOLETE, "program_override" },
  { "program_override",   KW_PROGRAM_OVERRIDE },
  { "host_override",      KW_HOST_OVERRIDE },
  { "throttle",           KW_THROTTLE },

  { "create_dirs",        KW_CREATE_DIRS },
  { "optional",           KW_OPTIONAL },

  { "owner",              KW_OWNER },
  { "group",              KW_GROUP },
  { "perm",               KW_PERM },
  { "dir_owner",          KW_DIR_OWNER },
  { "dir_group",          KW_DIR_GROUP },
  { "dir_perm",           KW_DIR_PERM },
  { "template",           KW_TEMPLATE },
  { "template_escape",    KW_TEMPLATE_ESCAPE },
  { "template_function",  KW_TEMPLATE_FUNCTION },
  { "on_error",           KW_ON_ERROR },
  { "persist_only",       KW_PERSIST_ONLY },
  { "dns_cache_hosts",    KW_DNS_CACHE_HOSTS },
  { "dns_cache",          KW_DNS_CACHE },
  { "dns_cache_size",     KW_DNS_CACHE_SIZE },
  { "dns_cache_expire",   KW_DNS_CACHE_EXPIRE },
  { "dns_cache_expire_failed", KW_DNS_CACHE_EXPIRE_FAILED },
  { "pass_unix_credentials",   KW_PASS_UNIX_CREDENTIALS },
  { "persist_name",            KW_PERSIST_NAME, 0x0308 },

  { "retries",            KW_RETRIES },

  /* filter items */
  { "type",               KW_TYPE },
  { "tags",               KW_TAGS },

  /* on/off switches */
  { "yes",                KW_YES },
  { "on",                 KW_YES },
  { "no",                 KW_NO },
  { "off",                KW_NO },
  { NULL, 0 }
};


CfgParser main_parser =
{
#if SYSLOG_NG_ENABLE_DEBUG
  .debug_flag = &main_debug,
#endif
  .name = "config",
  .context = LL_CONTEXT_ROOT,
  .keywords = main_keywords,
  .parse = main_parse,
};

CFG_PARSER_IMPLEMENT_LEXER_BINDING(main_, gpointer *)

static void
_underline_source(YYLTYPE *yylloc, gchar *buf)
{
  gint i;

  if (buf[0])
    {
      fprintf(stderr, "\n%s", buf);
      if (buf[strlen(buf) - 1] != '\n')
        fprintf(stderr, "\n");
      for (i = 0; buf[i] && i < yylloc->first_column - 1; i++)
        {
          fprintf(stderr, "%c", buf[i] == '\t' ? '\t' : ' ');
        }
      for (i = yylloc->first_column; (i == yylloc->first_column) || (i < yylloc->last_column); i++)
        fprintf(stderr, "^");
      fprintf(stderr, "\n");
    }
}

static void
_report_file_location(const gchar *filename, YYLTYPE *yylloc)
{
  FILE *f;
  gint lineno = 1;
  gchar buf[1024];

  f = fopen(filename, "r");
  if (f)
    {
      while (fgets(buf, sizeof(buf), f) && lineno < yylloc->first_line)
        lineno++;
      if (lineno != yylloc->first_line)
        buf[0] = 0;
      fclose(f);
    }
  _underline_source(yylloc, buf);
}

static void
_report_buffer_location(const gchar *buffer_content, YYLTYPE *yylloc)
{
  const gchar *sol, *eol;
  gchar buf[1024];
  gint lineno = 1;

  sol = buffer_content;
  eol = strchr(sol, '\n');
  while (eol && lineno < yylloc->first_line)
    {
      lineno++;
      sol = eol + 1;
      eol = strchr(sol, '\n');
    }
  if (lineno == yylloc->first_line)
    {
      gsize cs = MIN(eol ? eol - sol - 1 : strlen(sol), sizeof(buf) - 2);

      memcpy(buf, sol, cs);
      buf[cs] = 0;
    }
  _underline_source(yylloc, buf);
}

void
report_syntax_error(CfgLexer *lexer, YYLTYPE *yylloc, const char *what, const char *msg)
{
  CfgIncludeLevel *level = yylloc->level, *from;
  gint file_pos;

  fprintf(stderr, "Error parsing %s, %s in %n%s at line %d, column %d:\n",
          what,
          msg,
          &file_pos,
          yylloc->level->name,
          yylloc->first_line,
          yylloc->first_column);

  from = level - 1;
  while (from >= lexer->include_stack)
    {
      fprintf(stderr, "%*sincluded from %s line %d, column %d\n", MAX(file_pos - 14, 0), "", from->name, from->lloc.first_line, from->lloc.first_column);
      from--;
    }

  if (level->include_type == CFGI_FILE)
    {
      _report_file_location(level->name, yylloc);
    }
  else if (level->include_type == CFGI_BUFFER)
    {
      _report_buffer_location(level->buffer.content, yylloc);
    }

  fprintf(stderr, "\nsyslog-ng documentation: http://www.balabit.com/support/documentation/?product=syslog-ng\n"
                  "mailing list: https://lists.balabit.hu/mailman/listinfo/syslog-ng\n");

}

/*
 * This function can be used to parse flags in a flags(...) option. It
 * makes it quite easy to write a flags parser by specifying the
 * operations to be performed in a getopt-like array.
 */
gboolean
cfg_process_flag(CfgFlagHandler *handlers, gpointer base, const gchar *flag_)
{
  gint h;
  gchar flag[32];

  for (h = 0; flag_[h] && h < sizeof(flag); h++)
    {
      if (flag_[h] == '_')
        flag[h] = '-';
      else
        flag[h] = flag_[h];
    }
  flag[h] = 0;

  for (h = 0; handlers[h].name; h++)
    {
      CfgFlagHandler *handler = &handlers[h];

      if (strcmp(handlers[h].name, flag) == 0)
        {
          guint32 *field = ((guint32 *) (((gchar *) base) + handler->ofs));
          switch (handler->op)
            {
            case CFH_SET:
              /* this works if handler->mask is unset and handler->param is a single bit only */

              if (handler->mask)
                *field = ((*field) & ~handler->mask) | handler->param;
              else
                *field = (*field) | handler->param;
              return TRUE;
            case CFH_CLEAR:
              /* set the bitfield to zero */

              if (handler->mask)
                *field = (*field) & ~handler->mask;
              else
                *field = (*field) & ~handler->param;
              return TRUE;
            }
        }
    }
  return FALSE;
}
