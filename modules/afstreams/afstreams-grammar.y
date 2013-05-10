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

%code top {
#include "afstreams-parser.h"

}


%code {

#include "afstreams.h"
#include "cfg-parser.h"
#include "afstreams-grammar.h"
#include "messages.h"

extern LogDriver *last_driver;

}

%name-prefix "afstreams_"

/* this parameter is needed in order to instruct bison to use a complete
 * argument list for yylex/yyerror */

%lex-param {CfgLexer *lexer}
%parse-param {CfgLexer *lexer}
%parse-param {LogDriver **instance}
%parse-param {gpointer arg}



%require "2.4.1"
%locations
%define api.pure
%pure-parser
%error-verbose

%code {

# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
  do {                                                                  \
    if (YYID (N))                                                       \
      {                                                                 \
        (Current).level = YYRHSLOC(Rhs, 1).level;                       \
        (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;          \
        (Current).first_column = YYRHSLOC (Rhs, 1).first_column;        \
        (Current).last_line    = YYRHSLOC (Rhs, N).last_line;           \
        (Current).last_column  = YYRHSLOC (Rhs, N).last_column;         \
      }                                                                 \
    else                                                                \
      {                                                                 \
        (Current).level = YYRHSLOC(Rhs, 0).level;                       \
        (Current).first_line   = (Current).last_line   =                \
          YYRHSLOC (Rhs, 0).last_line;                                  \
        (Current).first_column = (Current).last_column =                \
          YYRHSLOC (Rhs, 0).last_column;                                \
      }                                                                 \
  } while (YYID (0))

#define CHECK_ERROR(val, token, errorfmt, ...) do {                     \
    if (!(val))                                                         \
      {                                                                 \
        if (errorfmt)                                                   \
          {                                                             \
            gchar __buf[256];                                           \
            g_snprintf(__buf, sizeof(__buf), errorfmt ? errorfmt : "x", ## __VA_ARGS__); \
            yyerror(& (token), lexer, NULL, NULL, __buf);               \
          }                                                             \
        YYERROR;                                                        \
      }                                                                 \
  } while (0)

#define YYMAXDEPTH 20000


}

/* plugin types, must be equal to the numerical values of the plugin type in plugin.h */

%token LL_CONTEXT_ROOT                1
%token LL_CONTEXT_DESTINATION         2
%token LL_CONTEXT_SOURCE              3
%token LL_CONTEXT_PARSER              4
%token LL_CONTEXT_REWRITE             5
%token LL_CONTEXT_FILTER              6
%token LL_CONTEXT_LOG                 7
%token LL_CONTEXT_BLOCK_DEF           8
%token LL_CONTEXT_BLOCK_REF           9
%token LL_CONTEXT_BLOCK_CONTENT       10
%token LL_CONTEXT_PRAGMA              11
%token LL_CONTEXT_FORMAT              12
%token LL_CONTEXT_TEMPLATE_FUNC       13
%token LL_CONTEXT_INNER_DEST          14
%token LL_CONTEXT_INNER_SRC           15

/* statements */
%token KW_SOURCE                      10000
%token KW_FILTER                      10001
%token KW_PARSER                      10002
%token KW_DESTINATION                 10003
%token KW_LOG                         10004
%token KW_OPTIONS                     10005
%token KW_INCLUDE                     10006
%token KW_BLOCK                       10007

/* source & destination items */
%token KW_INTERNAL                    10010
%token KW_FILE                        10011

%token KW_SQL                         10030
%token KW_TYPE                        10031
%token KW_COLUMNS                     10032
%token KW_INDEXES                     10033
%token KW_VALUES                      10034
%token KW_PASSWORD                    10035
%token KW_DATABASE                    10036
%token KW_USERNAME                    10037
%token KW_TABLE                       10038
%token KW_ENCODING                    10039
%token KW_SESSION_STATEMENTS          10040

%token KW_DELIMITERS                  10050
%token KW_QUOTES                      10051
%token KW_QUOTE_PAIRS                 10052
%token KW_NULL                        10053

%token KW_SYSLOG                      10060

/* option items */
%token KW_MARK_FREQ                   10071
%token KW_STATS_FREQ                  10072
%token KW_STATS_LEVEL                 10073
%token KW_FLUSH_LINES                 10074
%token KW_SUPPRESS                    10075
%token KW_FLUSH_TIMEOUT               10076
%token KW_LOG_MSG_SIZE                10077
%token KW_FILE_TEMPLATE               10078
%token KW_PROTO_TEMPLATE              10079

%token KW_CHAIN_HOSTNAMES             10090
%token KW_NORMALIZE_HOSTNAMES         10091
%token KW_KEEP_HOSTNAME               10092
%token KW_CHECK_HOSTNAME              10093
%token KW_BAD_HOSTNAME                10094

%token KW_KEEP_TIMESTAMP              10100

%token KW_USE_DNS                     10110
%token KW_USE_FQDN                    10111

%token KW_DNS_CACHE                   10120
%token KW_DNS_CACHE_SIZE              10121

%token KW_DNS_CACHE_EXPIRE            10130
%token KW_DNS_CACHE_EXPIRE_FAILED     10131
%token KW_DNS_CACHE_HOSTS             10132

%token KW_PERSIST_ONLY                10140

%token KW_TZ_CONVERT                  10150
%token KW_TS_FORMAT                   10151
%token KW_FRAC_DIGITS                 10152

%token KW_LOG_FIFO_SIZE               10160
%token KW_LOG_FETCH_LIMIT             10162
%token KW_LOG_IW_SIZE                 10163
%token KW_LOG_PREFIX                  10164
%token KW_PROGRAM_OVERRIDE            10165
%token KW_HOST_OVERRIDE               10166

%token KW_THROTTLE                    10170
%token KW_THREADED                    10171

/* log statement options */
%token KW_FLAGS                       10190

/* reader options */
%token KW_PAD_SIZE                    10200
%token KW_TIME_ZONE                   10201
%token KW_RECV_TIME_ZONE              10202
%token KW_SEND_TIME_ZONE              10203
%token KW_LOCAL_TIME_ZONE             10204
%token KW_FORMAT                      10205

/* timers */
%token KW_TIME_REOPEN                 10210
%token KW_TIME_REAP                   10211
%token KW_TIME_SLEEP                  10212

/* destination options */
%token KW_TMPL_ESCAPE                 10220

/* driver specific options */
%token KW_OPTIONAL                    10230

/* file related options */
%token KW_CREATE_DIRS                 10240

%token KW_OWNER                       10250
%token KW_GROUP                       10251
%token KW_PERM                        10252

%token KW_DIR_OWNER                   10260
%token KW_DIR_GROUP                   10261
%token KW_DIR_PERM                    10262

%token KW_TEMPLATE                    10270
%token KW_TEMPLATE_ESCAPE             10271

%token KW_DEFAULT_FACILITY            10300
%token KW_DEFAULT_LEVEL               10301

%token KW_PORT                        10323
/* misc options */

%token KW_USE_TIME_RECVD              10340

/* filter items*/
%token KW_FACILITY                    10350
%token KW_LEVEL                       10351
%token KW_HOST                        10352
%token KW_MATCH                       10353
%token KW_MESSAGE                     10354
%token KW_NETMASK                     10355
%token KW_TAGS                        10356

/* parser items */

%token KW_VALUE                       10361

/* rewrite items */

%token KW_REWRITE                     10370
%token KW_SET                         10371
%token KW_SUBST                       10372

/* yes/no switches */

%token KW_YES                         10380
%token KW_NO                          10381

%token KW_IFDEF                       10410
%token KW_ENDIF                       10411

%token LL_DOTDOT                      10420

%token <cptr> LL_IDENTIFIER           10421
%token <num>  LL_NUMBER               10422
%token <fnum> LL_FLOAT                10423
%token <cptr> LL_STRING               10424
%token <token> LL_TOKEN               10425
%token <cptr> LL_BLOCK                10426
%token LL_PRAGMA                      10427
%token LL_EOL                         10428
%token LL_ERROR                       10429

/* value pairs */
%token KW_VALUE_PAIRS                 10500
%token KW_SELECT                      10501
%token KW_EXCLUDE                     10502
%token KW_PAIR                        10503
%token KW_KEY                         10504
%token KW_SCOPE                       10505


%type   <ptr> value_pair_option

%type	<num> yesno
%type   <num> dnsmode
%type   <num> regexp_option_flags
%type	<num> dest_writer_options_flags

%type	<cptr> string
%type	<cptr> string_or_number
%type   <ptr> string_list
%type   <ptr> string_list_build
%type   <num> facility_string
%type   <num> level_string


%token KW_DOOR                        10020
%token KW_SUN_STREAMS                 10021


%type	<ptr> source_afstreams
%type	<ptr> source_afstreams_params

%%

start
        : LL_CONTEXT_SOURCE source_afstreams                        { YYACCEPT; }
        ;


source_afstreams
	: KW_IFDEF {
#if ENABLE_SUN_STREAMS
}
        | KW_SUN_STREAMS '(' source_afstreams_params ')'	{ $$ = $3; }
        | KW_ENDIF {
#endif
}
	;

source_afstreams_params
	: string
	  {
#if ENABLE_SUN_STREAMS
	    last_driver = *instance = afstreams_sd_new($1);
	    free($1);
#endif
	  }
	  source_afstreams_options		{ $$ = last_driver; }
	;

source_afstreams_options
	: source_afstreams_option source_afstreams_options
	|
	;

source_afstreams_option
	: KW_IFDEF {
#if ENABLE_SUN_STREAMS
}
	| KW_DOOR '(' string ')'		{ afstreams_sd_set_sundoor(last_driver, $3); free($3); }
	| KW_ENDIF {
#endif
}
	;



string
	: LL_IDENTIFIER
	| LL_STRING
	;

yesno
	: KW_YES				{ $$ = 1; }
	| KW_NO					{ $$ = 0; }
	| LL_NUMBER				{ $$ = $1; }
	;

dnsmode
	: yesno					{ $$ = $1; }
	| KW_PERSIST_ONLY                       { $$ = 2; }
	;

string_or_number
        : string                                { $$ = $1; }
        | LL_NUMBER                             { $$ = strdup(lexer->token_text->str); }
        | LL_FLOAT                              { $$ = strdup(lexer->token_text->str); }
        ;

string_list
        : string_list_build                     { $$ = g_list_reverse($1); }
        ;

string_list_build
        : string string_list_build		{ $$ = g_list_append($2, g_strdup($1)); free($1); }
        |					{ $$ = NULL; }
        ;

level_string
        : string
	  {
	    /* return the numeric value of the "level" */
	    int n = syslog_name_lookup_level_by_name($1);
	    CHECK_ERROR((n != -1), @1, "Unknown priority level\"%s\"", $1);
	    free($1);
            $$ = n;
	  }
        ;

facility_string
        : string
          {
            /* return the numeric value of facility */
	    int n = syslog_name_lookup_facility_by_name($1);
	    CHECK_ERROR((n != -1), @1, "Unknown facility \"%s\"", $1);
	    free($1);
	    $$ = n;
	  }
        | KW_SYSLOG 				{ $$ = LOG_SYSLOG; }
        ;

regexp_option_flags
        : string regexp_option_flags            { $$ = log_matcher_lookup_flag($1) | $2; free($1); }
        |                                       { $$ = 0; }
        ;


/* LogSource related options */
source_option
        /* NOTE: plugins need to set "last_source_options" in order to incorporate this rule in their grammar */
	: KW_LOG_IW_SIZE '(' LL_NUMBER ')'	{ last_source_options->init_window_size = $3; }
	| KW_CHAIN_HOSTNAMES '(' yesno ')'	{ last_source_options->chain_hostnames = $3; }
	| KW_NORMALIZE_HOSTNAMES '(' yesno ')'	{ last_source_options->normalize_hostnames = $3; }
	| KW_KEEP_HOSTNAME '(' yesno ')'	{ last_source_options->keep_hostname = $3; }
        | KW_USE_FQDN '(' yesno ')'             { last_source_options->use_fqdn = $3; }
        | KW_USE_DNS '(' dnsmode ')'            { last_source_options->use_dns = $3; }
	| KW_DNS_CACHE '(' yesno ')' 		{ last_source_options->use_dns_cache = $3; }
	| KW_PROGRAM_OVERRIDE '(' string ')'	{ last_source_options->program_override = g_strdup($3); free($3); }
	| KW_HOST_OVERRIDE '(' string ')'	{ last_source_options->host_override = g_strdup($3); free($3); }
	| KW_LOG_PREFIX '(' string ')'	        { gchar *p = strrchr($3, ':'); if (p) *p = 0; last_source_options->program_override = g_strdup($3); free($3); }
	| KW_KEEP_TIMESTAMP '(' yesno ')'	{ last_source_options->keep_timestamp = $3; }
        | KW_TAGS '(' string_list ')'		{ log_source_options_set_tags(last_source_options, $3); }
        ;


source_reader_options
	: source_reader_option source_reader_options
	|
	;

/* LogReader related options, inherits from LogSource */
source_reader_option
        /* NOTE: plugins need to set "last_reader_options" in order to incorporate this rule in their grammar */

	: KW_TIME_ZONE '(' string ')'		{ last_reader_options->parse_options.recv_time_zone = g_strdup($3); free($3); }
	| KW_CHECK_HOSTNAME '(' yesno ')'	{ last_reader_options->check_hostname = $3; }
	| KW_FLAGS '(' source_reader_option_flags ')'
	| KW_LOG_MSG_SIZE '(' LL_NUMBER ')'	{ last_reader_options->msg_size = $3; }
	| KW_LOG_FETCH_LIMIT '(' LL_NUMBER ')'	{ last_reader_options->fetch_limit = $3; }
	| KW_PAD_SIZE '(' LL_NUMBER ')'		{ last_reader_options->padding = $3; }
        | KW_ENCODING '(' string ')'		{ last_reader_options->text_encoding = g_strdup($3); free($3); }
        | KW_FORMAT '(' string ')'              { last_reader_options->parse_options.format = g_strdup($3); free($3); }
	| KW_DEFAULT_LEVEL '(' level_string ')'
	  {
	    if (last_reader_options->parse_options.default_pri == 0xFFFF)
	      last_reader_options->parse_options.default_pri = LOG_USER;
	    last_reader_options->parse_options.default_pri = (last_reader_options->parse_options.default_pri & ~7) | $3;
          }
	| KW_DEFAULT_FACILITY '(' facility_string ')'
	  {
	    if (last_reader_options->parse_options.default_pri == 0xFFFF)
	      last_reader_options->parse_options.default_pri = LOG_NOTICE;
	    last_reader_options->parse_options.default_pri = (last_reader_options->parse_options.default_pri & 7) | $3;
          }
        | { last_source_options = &last_reader_options->super; } source_option
	;

source_reader_option_flags
        : string source_reader_option_flags     { CHECK_ERROR(log_reader_options_process_flag(last_reader_options, $1), @1, "Unknown flag %s", $1); free($1); }
        | KW_CHECK_HOSTNAME source_reader_option_flags     { log_reader_options_process_flag(last_reader_options, "check-hostname"); }
	|
	;

dest_driver_option
        /* NOTE: plugins need to set "last_driver" in order to incorporate this rule in their grammar */

	: KW_LOG_FIFO_SIZE '(' LL_NUMBER ')'	{ ((LogDestDriver *) last_driver)->log_fifo_size = $3; }
	| KW_THROTTLE '(' LL_NUMBER ')'         { ((LogDestDriver *) last_driver)->throttle = $3; }
        | LL_IDENTIFIER
          {
            Plugin *p;
            gint context = LL_CONTEXT_INNER_DEST;
            gpointer value;

            p = plugin_find(configuration, context, $1);
            CHECK_ERROR(p, @1, "%s plugin %s not found", cfg_lexer_lookup_context_name_by_type(context), $1);

            value = plugin_parse_config(p, configuration, &@1, last_driver);

            free($1);
            if (!value)
              {
                YYERROR;
              }
            log_driver_add_plugin(last_driver, (LogDriverPlugin *) value);
          }
        ;

dest_writer_options
	: dest_writer_option dest_writer_options
	|
	;

dest_writer_option
        /* NOTE: plugins need to set "last_writer_options" in order to incorporate this rule in their grammar */

	: KW_FLAGS '(' dest_writer_options_flags ')' { last_writer_options->options = $3; }
	| KW_FLUSH_LINES '(' LL_NUMBER ')'		{ last_writer_options->flush_lines = $3; }
	| KW_FLUSH_TIMEOUT '(' LL_NUMBER ')'	{ last_writer_options->flush_timeout = $3; }
        | KW_SUPPRESS '(' LL_NUMBER ')'            { last_writer_options->suppress = $3; }
	| KW_TEMPLATE '(' string ')'       	{
                                                  GError *error = NULL;

                                                  last_writer_options->template = cfg_check_inline_template(configuration, $3, &error);
                                                  CHECK_ERROR(last_writer_options->template != NULL, @3, "Error compiling template (%s)", error->message);
	                                          free($3);
	                                        }
	| KW_TEMPLATE_ESCAPE '(' yesno ')'	{ log_writer_options_set_template_escape(last_writer_options, $3); }
	| KW_TIME_ZONE '(' string ')'           { last_writer_options->template_options.time_zone[LTZ_SEND] = g_strdup($3); free($3); }
	| KW_TS_FORMAT '(' string ')'		{ last_writer_options->template_options.ts_format = cfg_ts_format_value($3); free($3); }
	| KW_FRAC_DIGITS '(' LL_NUMBER ')'	{ last_writer_options->template_options.frac_digits = $3; }
	| KW_PAD_SIZE '(' LL_NUMBER ')'         { last_writer_options->padding = $3; }
	;

dest_writer_options_flags
	: string dest_writer_options_flags      { $$ = log_writer_options_lookup_flag($1) | $2; free($1); }
	|					{ $$ = 0; }
	;

value_pair_option
	: KW_VALUE_PAIRS
          { last_value_pairs = value_pairs_new(); }
          '(' vp_options ')'
          { $$ = last_value_pairs; }
	;

vp_options
	: vp_option vp_options
	|
	;

vp_option
        : KW_PAIR '(' string ':' string ')'      { value_pairs_add_pair(last_value_pairs, configuration, $3, $5); free($3); free($5); }
        | KW_PAIR '(' string string ')'          { value_pairs_add_pair(last_value_pairs, configuration, $3, $4); free($3); free($4); }
	| KW_KEY '(' string ')'		    {
                gchar *k = g_strconcat("$", $3, NULL);
                value_pairs_add_pair(last_value_pairs, configuration, $3, k);
                g_free(k);
                free($3);
	  }
	| KW_EXCLUDE '(' string ')'	         { value_pairs_add_exclude_glob(last_value_pairs, $3); free($3); }
	| KW_SCOPE '(' vp_scope_list ')'
	;

vp_scope_list
	: string vp_scope_list              { value_pairs_add_scope(last_value_pairs, $1); free($1); }
	|
	;


%%
