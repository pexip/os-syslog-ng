/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* "%code top" blocks.  */
#line 24 "modules/afsocket/afsocket-grammar.y" /* yacc.c:316  */

#include "afsocket-parser.h"


#line 68 "modules/afsocket/afsocket-grammar.c" /* yacc.c:316  */

/* Substitute the variable and function names.  */
#define yyparse         afsocket_parse
#define yylex           afsocket_lex
#define yyerror         afsocket_error
#define yydebug         afsocket_debug
#define yynerrs         afsocket_nerrs


/* Copy the first part of user declarations.  */

#line 80 "modules/afsocket/afsocket-grammar.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
#ifndef YY_AFSOCKET_MODULES_AFSOCKET_AFSOCKET_GRAMMAR_H_INCLUDED
# define YY_AFSOCKET_MODULES_AFSOCKET_AFSOCKET_GRAMMAR_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int afsocket_debug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    KW_UNIX_STREAM = 20000,
    KW_UNIX_DGRAM = 20002,
    KW_TCP = 20003,
    KW_UDP = 20004,
    KW_TCP6 = 20005,
    KW_UDP6 = 20006,
    KW_NETWORK = 20007,
    KW_TRANSPORT = 20008,
    KW_IP_PROTOCOL = 20009,
    KW_SYSTEMD_SYSLOG = 20010,
    KW_IP_TTL = 20011,
    KW_SO_BROADCAST = 20012,
    KW_IP_TOS = 20013,
    KW_SO_SNDBUF = 20014,
    KW_SO_RCVBUF = 20015,
    KW_SO_KEEPALIVE = 20016,
    KW_TCP_KEEPALIVE_TIME = 20017,
    KW_TCP_KEEPALIVE_PROBES = 20018,
    KW_TCP_KEEPALIVE_INTVL = 20019,
    KW_SPOOF_SOURCE = 20020,
    KW_KEEP_ALIVE = 20021,
    KW_MAX_CONNECTIONS = 20022,
    KW_LOCALIP = 20023,
    KW_IP = 20024,
    KW_LOCALPORT = 20025,
    KW_DESTPORT = 20026,
    KW_TLS = 20027,
    KW_PEER_VERIFY = 20028,
    KW_KEY_FILE = 20029,
    KW_CERT_FILE = 20030,
    KW_CA_DIR = 20031,
    KW_CRL_DIR = 20032,
    KW_TRUSTED_KEYS = 20033,
    KW_TRUSTED_DN = 20034,
    KW_CIPHER_SUITE = 20035,
    KW_SSL_OPTIONS = 20036,
    LL_CONTEXT_ROOT = 1,
    LL_CONTEXT_DESTINATION = 2,
    LL_CONTEXT_SOURCE = 3,
    LL_CONTEXT_PARSER = 4,
    LL_CONTEXT_REWRITE = 5,
    LL_CONTEXT_FILTER = 6,
    LL_CONTEXT_LOG = 7,
    LL_CONTEXT_BLOCK_DEF = 8,
    LL_CONTEXT_BLOCK_REF = 9,
    LL_CONTEXT_BLOCK_CONTENT = 10,
    LL_CONTEXT_BLOCK_ARG = 11,
    LL_CONTEXT_PRAGMA = 12,
    LL_CONTEXT_FORMAT = 13,
    LL_CONTEXT_TEMPLATE_FUNC = 14,
    LL_CONTEXT_INNER_DEST = 15,
    LL_CONTEXT_INNER_SRC = 16,
    LL_CONTEXT_CLIENT_PROTO = 17,
    LL_CONTEXT_SERVER_PROTO = 18,
    KW_SOURCE = 10000,
    KW_FILTER = 10001,
    KW_PARSER = 10002,
    KW_DESTINATION = 10003,
    KW_LOG = 10004,
    KW_OPTIONS = 10005,
    KW_INCLUDE = 10006,
    KW_BLOCK = 10007,
    KW_JUNCTION = 10008,
    KW_CHANNEL = 10009,
    KW_INTERNAL = 10010,
    KW_FILE = 10011,
    KW_SYSLOG = 10060,
    KW_MARK_FREQ = 10071,
    KW_STATS_FREQ = 10072,
    KW_STATS_LEVEL = 10073,
    KW_STATS_LIFETIME = 10074,
    KW_FLUSH_LINES = 10075,
    KW_SUPPRESS = 10076,
    KW_FLUSH_TIMEOUT = 10077,
    KW_LOG_MSG_SIZE = 10078,
    KW_FILE_TEMPLATE = 10079,
    KW_PROTO_TEMPLATE = 10080,
    KW_MARK_MODE = 10081,
    KW_ENCODING = 10082,
    KW_TYPE = 10083,
    KW_CHAIN_HOSTNAMES = 10090,
    KW_NORMALIZE_HOSTNAMES = 10091,
    KW_KEEP_HOSTNAME = 10092,
    KW_CHECK_HOSTNAME = 10093,
    KW_BAD_HOSTNAME = 10094,
    KW_KEEP_TIMESTAMP = 10100,
    KW_USE_DNS = 10110,
    KW_USE_FQDN = 10111,
    KW_CUSTOM_DOMAIN = 10112,
    KW_DNS_CACHE = 10120,
    KW_DNS_CACHE_SIZE = 10121,
    KW_DNS_CACHE_EXPIRE = 10130,
    KW_DNS_CACHE_EXPIRE_FAILED = 10131,
    KW_DNS_CACHE_HOSTS = 10132,
    KW_PERSIST_ONLY = 10140,
    KW_USE_RCPTID = 10141,
    KW_USE_UNIQID = 10142,
    KW_TZ_CONVERT = 10150,
    KW_TS_FORMAT = 10151,
    KW_FRAC_DIGITS = 10152,
    KW_LOG_FIFO_SIZE = 10160,
    KW_LOG_FETCH_LIMIT = 10162,
    KW_LOG_IW_SIZE = 10163,
    KW_LOG_PREFIX = 10164,
    KW_PROGRAM_OVERRIDE = 10165,
    KW_HOST_OVERRIDE = 10166,
    KW_THROTTLE = 10170,
    KW_THREADED = 10171,
    KW_PASS_UNIX_CREDENTIALS = 10231,
    KW_PERSIST_NAME = 10302,
    KW_FLAGS = 10190,
    KW_PAD_SIZE = 10200,
    KW_TIME_ZONE = 10201,
    KW_RECV_TIME_ZONE = 10202,
    KW_SEND_TIME_ZONE = 10203,
    KW_LOCAL_TIME_ZONE = 10204,
    KW_FORMAT = 10205,
    KW_TIME_REOPEN = 10210,
    KW_TIME_REAP = 10211,
    KW_TIME_SLEEP = 10212,
    KW_TMPL_ESCAPE = 10220,
    KW_OPTIONAL = 10230,
    KW_CREATE_DIRS = 10240,
    KW_OWNER = 10250,
    KW_GROUP = 10251,
    KW_PERM = 10252,
    KW_DIR_OWNER = 10260,
    KW_DIR_GROUP = 10261,
    KW_DIR_PERM = 10262,
    KW_TEMPLATE = 10270,
    KW_TEMPLATE_ESCAPE = 10271,
    KW_TEMPLATE_FUNCTION = 10272,
    KW_DEFAULT_FACILITY = 10300,
    KW_DEFAULT_LEVEL = 10301,
    KW_PORT = 10323,
    KW_USE_TIME_RECVD = 10340,
    KW_FACILITY = 10350,
    KW_LEVEL = 10351,
    KW_HOST = 10352,
    KW_MATCH = 10353,
    KW_MESSAGE = 10354,
    KW_NETMASK = 10355,
    KW_TAGS = 10356,
    KW_NETMASK6 = 10357,
    KW_REWRITE = 10370,
    KW_YES = 10380,
    KW_NO = 10381,
    KW_IFDEF = 10410,
    KW_ENDIF = 10411,
    LL_DOTDOT = 10420,
    LL_IDENTIFIER = 10421,
    LL_NUMBER = 10422,
    LL_FLOAT = 10423,
    LL_STRING = 10424,
    LL_TOKEN = 10425,
    LL_BLOCK = 10426,
    LL_PRAGMA = 10427,
    LL_EOL = 10428,
    LL_ERROR = 10429,
    KW_VALUE_PAIRS = 10500,
    KW_EXCLUDE = 10502,
    KW_PAIR = 10503,
    KW_KEY = 10504,
    KW_SCOPE = 10505,
    KW_SHIFT = 10506,
    KW_REKEY = 10507,
    KW_ADD_PREFIX = 10508,
    KW_REPLACE_PREFIX = 10509,
    KW_ON_ERROR = 10510,
    KW_RETRIES = 10511
  };
#endif
/* Tokens.  */
#define KW_UNIX_STREAM 20000
#define KW_UNIX_DGRAM 20002
#define KW_TCP 20003
#define KW_UDP 20004
#define KW_TCP6 20005
#define KW_UDP6 20006
#define KW_NETWORK 20007
#define KW_TRANSPORT 20008
#define KW_IP_PROTOCOL 20009
#define KW_SYSTEMD_SYSLOG 20010
#define KW_IP_TTL 20011
#define KW_SO_BROADCAST 20012
#define KW_IP_TOS 20013
#define KW_SO_SNDBUF 20014
#define KW_SO_RCVBUF 20015
#define KW_SO_KEEPALIVE 20016
#define KW_TCP_KEEPALIVE_TIME 20017
#define KW_TCP_KEEPALIVE_PROBES 20018
#define KW_TCP_KEEPALIVE_INTVL 20019
#define KW_SPOOF_SOURCE 20020
#define KW_KEEP_ALIVE 20021
#define KW_MAX_CONNECTIONS 20022
#define KW_LOCALIP 20023
#define KW_IP 20024
#define KW_LOCALPORT 20025
#define KW_DESTPORT 20026
#define KW_TLS 20027
#define KW_PEER_VERIFY 20028
#define KW_KEY_FILE 20029
#define KW_CERT_FILE 20030
#define KW_CA_DIR 20031
#define KW_CRL_DIR 20032
#define KW_TRUSTED_KEYS 20033
#define KW_TRUSTED_DN 20034
#define KW_CIPHER_SUITE 20035
#define KW_SSL_OPTIONS 20036
#define LL_CONTEXT_ROOT 1
#define LL_CONTEXT_DESTINATION 2
#define LL_CONTEXT_SOURCE 3
#define LL_CONTEXT_PARSER 4
#define LL_CONTEXT_REWRITE 5
#define LL_CONTEXT_FILTER 6
#define LL_CONTEXT_LOG 7
#define LL_CONTEXT_BLOCK_DEF 8
#define LL_CONTEXT_BLOCK_REF 9
#define LL_CONTEXT_BLOCK_CONTENT 10
#define LL_CONTEXT_BLOCK_ARG 11
#define LL_CONTEXT_PRAGMA 12
#define LL_CONTEXT_FORMAT 13
#define LL_CONTEXT_TEMPLATE_FUNC 14
#define LL_CONTEXT_INNER_DEST 15
#define LL_CONTEXT_INNER_SRC 16
#define LL_CONTEXT_CLIENT_PROTO 17
#define LL_CONTEXT_SERVER_PROTO 18
#define KW_SOURCE 10000
#define KW_FILTER 10001
#define KW_PARSER 10002
#define KW_DESTINATION 10003
#define KW_LOG 10004
#define KW_OPTIONS 10005
#define KW_INCLUDE 10006
#define KW_BLOCK 10007
#define KW_JUNCTION 10008
#define KW_CHANNEL 10009
#define KW_INTERNAL 10010
#define KW_FILE 10011
#define KW_SYSLOG 10060
#define KW_MARK_FREQ 10071
#define KW_STATS_FREQ 10072
#define KW_STATS_LEVEL 10073
#define KW_STATS_LIFETIME 10074
#define KW_FLUSH_LINES 10075
#define KW_SUPPRESS 10076
#define KW_FLUSH_TIMEOUT 10077
#define KW_LOG_MSG_SIZE 10078
#define KW_FILE_TEMPLATE 10079
#define KW_PROTO_TEMPLATE 10080
#define KW_MARK_MODE 10081
#define KW_ENCODING 10082
#define KW_TYPE 10083
#define KW_CHAIN_HOSTNAMES 10090
#define KW_NORMALIZE_HOSTNAMES 10091
#define KW_KEEP_HOSTNAME 10092
#define KW_CHECK_HOSTNAME 10093
#define KW_BAD_HOSTNAME 10094
#define KW_KEEP_TIMESTAMP 10100
#define KW_USE_DNS 10110
#define KW_USE_FQDN 10111
#define KW_CUSTOM_DOMAIN 10112
#define KW_DNS_CACHE 10120
#define KW_DNS_CACHE_SIZE 10121
#define KW_DNS_CACHE_EXPIRE 10130
#define KW_DNS_CACHE_EXPIRE_FAILED 10131
#define KW_DNS_CACHE_HOSTS 10132
#define KW_PERSIST_ONLY 10140
#define KW_USE_RCPTID 10141
#define KW_USE_UNIQID 10142
#define KW_TZ_CONVERT 10150
#define KW_TS_FORMAT 10151
#define KW_FRAC_DIGITS 10152
#define KW_LOG_FIFO_SIZE 10160
#define KW_LOG_FETCH_LIMIT 10162
#define KW_LOG_IW_SIZE 10163
#define KW_LOG_PREFIX 10164
#define KW_PROGRAM_OVERRIDE 10165
#define KW_HOST_OVERRIDE 10166
#define KW_THROTTLE 10170
#define KW_THREADED 10171
#define KW_PASS_UNIX_CREDENTIALS 10231
#define KW_PERSIST_NAME 10302
#define KW_FLAGS 10190
#define KW_PAD_SIZE 10200
#define KW_TIME_ZONE 10201
#define KW_RECV_TIME_ZONE 10202
#define KW_SEND_TIME_ZONE 10203
#define KW_LOCAL_TIME_ZONE 10204
#define KW_FORMAT 10205
#define KW_TIME_REOPEN 10210
#define KW_TIME_REAP 10211
#define KW_TIME_SLEEP 10212
#define KW_TMPL_ESCAPE 10220
#define KW_OPTIONAL 10230
#define KW_CREATE_DIRS 10240
#define KW_OWNER 10250
#define KW_GROUP 10251
#define KW_PERM 10252
#define KW_DIR_OWNER 10260
#define KW_DIR_GROUP 10261
#define KW_DIR_PERM 10262
#define KW_TEMPLATE 10270
#define KW_TEMPLATE_ESCAPE 10271
#define KW_TEMPLATE_FUNCTION 10272
#define KW_DEFAULT_FACILITY 10300
#define KW_DEFAULT_LEVEL 10301
#define KW_PORT 10323
#define KW_USE_TIME_RECVD 10340
#define KW_FACILITY 10350
#define KW_LEVEL 10351
#define KW_HOST 10352
#define KW_MATCH 10353
#define KW_MESSAGE 10354
#define KW_NETMASK 10355
#define KW_TAGS 10356
#define KW_NETMASK6 10357
#define KW_REWRITE 10370
#define KW_YES 10380
#define KW_NO 10381
#define KW_IFDEF 10410
#define KW_ENDIF 10411
#define LL_DOTDOT 10420
#define LL_IDENTIFIER 10421
#define LL_NUMBER 10422
#define LL_FLOAT 10423
#define LL_STRING 10424
#define LL_TOKEN 10425
#define LL_BLOCK 10426
#define LL_PRAGMA 10427
#define LL_EOL 10428
#define LL_ERROR 10429
#define KW_VALUE_PAIRS 10500
#define KW_EXCLUDE 10502
#define KW_PAIR 10503
#define KW_KEY 10504
#define KW_SCOPE 10505
#define KW_SHIFT 10506
#define KW_REKEY 10507
#define KW_ADD_PREFIX 10508
#define KW_REPLACE_PREFIX 10509
#define KW_ON_ERROR 10510
#define KW_RETRIES 10511

/* Value type.  */

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif



int afsocket_parse (CfgLexer *lexer, LogDriver **instance, gpointer arg);

#endif /* !YY_AFSOCKET_MODULES_AFSOCKET_AFSOCKET_GRAMMAR_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 483 "modules/afsocket/afsocket-grammar.c" /* yacc.c:358  */
/* Unqualified %code blocks.  */
#line 30 "modules/afsocket/afsocket-grammar.y" /* yacc.c:359  */


#include "afsocket.h"
#include "cfg-parser.h"
#include "afsocket-grammar.h"
#include "afunix-source.h"
#include "afunix-dest.h"
#include "afinet-source.h"
#include "afinet-dest.h"
#include "messages.h"
#include "syslog-names.h"
#include "plugin.h"
#include "cfg-grammar.h"
#include "socket-options-inet.h"
#include "transport-mapper-inet.h"
#include "service-management.h"

#include "systemd-syslog-source.h"
#include "afsocket-systemd-override.h"

#include "tlscontext.h"


static SocketOptions *last_sock_options;
static TransportMapper *last_transport_mapper;

TLSContext *last_tls_context;


#if ! SYSLOG_NG_ENABLE_IPV6
#undef AF_INET6
#define AF_INET6 0; g_assert_not_reached()

#endif

static void
afsocket_grammar_set_source_driver(AFSocketSourceDriver *sd)
{
  last_driver = &sd->super.super;

  last_reader_options = &((AFSocketSourceDriver *) last_driver)->reader_options;
  last_sock_options = ((AFSocketSourceDriver *) last_driver)->socket_options;
  last_transport_mapper = ((AFSocketSourceDriver *) last_driver)->transport_mapper;
}

static void
afsocket_grammar_set_dest_driver(AFSocketDestDriver *dd)
{
  last_driver = &dd->super.super;

  last_writer_options = &((AFSocketDestDriver *) last_driver)->writer_options;
  last_sock_options = ((AFSocketDestDriver *) last_driver)->socket_options;
  last_transport_mapper = ((AFSocketDestDriver *) last_driver)->transport_mapper;
}

void
afunix_grammar_set_source_driver(AFUnixSourceDriver *sd)
{
  afsocket_grammar_set_source_driver(&sd->super);
  last_file_perm_options = &sd->file_perm_options;
}

static void
afinet_grammar_set_source_driver(AFInetSourceDriver *sd)
{
  afsocket_grammar_set_source_driver(&sd->super);
}

static void
afunix_grammar_set_dest_driver(AFUnixDestDriver *dd)
{
  afsocket_grammar_set_dest_driver(&dd->super);
}

static void
afinet_grammar_set_dest_driver(AFInetDestDriver *dd)
{
  afsocket_grammar_set_dest_driver(&dd->super);
}

void
systemd_syslog_grammar_set_source_driver(SystemDSyslogSourceDriver *sd)
{
  afsocket_grammar_set_source_driver(&sd->super);
}

#line 178 "modules/afsocket/afsocket-grammar.y" /* yacc.c:359  */


# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
  do {                                                                  \
    if (N)                                                              \
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
  } while (0)

#define CHECK_ERROR_WITHOUT_MESSAGE(val, token) do {                    \
    if (!(val))                                                         \
      {                                                                 \
        YYERROR;                                                        \
      }                                                                 \
  } while (0)

#define CHECK_ERROR(val, token, errorfmt, ...) do {                     \
    if (!(val))                                                         \
      {                                                                 \
        if (errorfmt)                                                   \
          {                                                             \
            gchar __buf[256];                                           \
            g_snprintf(__buf, sizeof(__buf), errorfmt, ## __VA_ARGS__); \
            yyerror(& (token), lexer, NULL, NULL, __buf);               \
          }                                                             \
        YYERROR;                                                        \
      }                                                                 \
  } while (0)

#define CHECK_ERROR_GERROR(val, token, error, errorfmt, ...) do {       \
    if (!(val))                                                         \
      {                                                                 \
        if (errorfmt)                                                   \
          {                                                             \
            gchar __buf[256];                                           \
            g_snprintf(__buf, sizeof(__buf), errorfmt ", error=%s", ## __VA_ARGS__, error->message); \
            yyerror(& (token), lexer, NULL, NULL, __buf);               \
          }                                                             \
        g_clear_error(&error);						\
        YYERROR;                                                        \
      }                                                                 \
  } while (0)

#define YYMAXDEPTH 20000



#line 633 "modules/afsocket/afsocket-grammar.c" /* yacc.c:359  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  31
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1017

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  179
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  109
/* YYNRULES -- Number of rules.  */
#define YYNRULES  256
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  576

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   20036

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     173,   174,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   178,   177,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   175,     2,   176,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      69,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,     2,     2,     2,     2,     2,     2,
      83,    84,    85,    86,    87,     2,     2,     2,     2,     2,
      88,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      89,    90,    91,     2,     2,     2,     2,     2,     2,     2,
      92,    93,     2,     2,     2,     2,     2,     2,     2,     2,
      94,    95,    96,     2,     2,     2,     2,     2,     2,     2,
      97,    98,    99,     2,     2,     2,     2,     2,     2,     2,
     100,   101,   102,     2,     2,     2,     2,     2,     2,     2,
     103,     2,   104,   105,   106,   107,   108,     2,     2,     2,
     109,   110,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     113,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     114,   115,   116,   117,   118,   119,     2,     2,     2,     2,
     120,   121,   122,     2,     2,     2,     2,     2,     2,     2,
     123,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     124,   111,     2,     2,     2,     2,     2,     2,     2,     2,
     125,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     126,   127,   128,     2,     2,     2,     2,     2,     2,     2,
     129,   130,   131,     2,     2,     2,     2,     2,     2,     2,
     132,   133,   134,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     135,   136,   112,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   137,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     138,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     139,   140,   141,   142,   143,   144,   145,   146,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     147,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     148,   149,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     150,   151,     2,     2,     2,     2,     2,     2,     2,     2,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     162,     2,   163,   164,   165,   166,   167,   168,   169,   170,
     171,   172,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       3,     2,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   511,   511,   521,   522,   523,   524,   525,   526,   527,
     528,   529,   534,   535,   540,   539,   548,   547,   556,   557,
     561,   562,   563,   564,   565,   566,   571,   579,   580,   581,
     582,   587,   587,   597,   597,   606,   607,   611,   615,   616,
     617,   618,   619,   620,   625,   625,   635,   635,   644,   645,
     649,   651,   650,   658,   662,   663,   667,   672,   672,   682,
     683,   687,   688,   689,   693,   698,   698,   708,   709,   713,
     714,   715,   719,   721,   720,   731,   735,   735,   750,   751,
     755,   756,   760,   761,   766,   765,   776,   775,   785,   786,
     790,   791,   792,   793,   797,   798,   799,   800,   805,   804,
     815,   814,   825,   826,   831,   832,   833,   834,   835,   836,
     837,   838,   843,   844,   849,   848,   859,   858,   868,   869,
     873,   875,   874,   885,   890,   894,   893,   904,   905,   909,
     910,   914,   919,   918,   928,   929,   933,   934,   938,   939,
     941,   940,   951,   952,   953,   954,   955,   960,   961,   965,
     968,   973,   978,   983,   988,   993,   997,  1001,  1006,  1010,
    1016,  1017,  1018,  1019,  1023,  1024,  1025,  1026,  1027,  1028,
    1032,  1268,  1269,  1273,  1274,  1275,  1279,  1280,  1284,  1285,
    1286,  1290,  1294,  1295,  1304,  1315,  1323,  1341,  1342,  1343,
    1344,  1345,  1346,  1347,  1348,  1349,  1349,  1350,  1354,  1361,
    1369,  1370,  1371,  1372,  1376,  1377,  1383,  1396,  1397,  1398,
    1399,  1400,  1400,  1401,  1401,  1402,  1402,  1406,  1407,  1408,
    1412,  1424,  1425,  1426,  1444,  1455,  1456,  1457,  1458,  1459,
    1466,  1467,  1468,  1469,  1470,  1476,  1476,  1480,  1481,  1485,
    1486,  1487,  1488,  1489,  1490,  1491,  1492,  1493,  1494,  1495,
    1496,  1500,  1501,  1502,  1503,  1504,  1505
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "KW_UNIX_STREAM", "KW_UNIX_DGRAM",
  "KW_TCP", "KW_UDP", "KW_TCP6", "KW_UDP6", "KW_NETWORK", "KW_TRANSPORT",
  "KW_IP_PROTOCOL", "KW_SYSTEMD_SYSLOG", "KW_IP_TTL", "KW_SO_BROADCAST",
  "KW_IP_TOS", "KW_SO_SNDBUF", "KW_SO_RCVBUF", "KW_SO_KEEPALIVE",
  "KW_TCP_KEEPALIVE_TIME", "KW_TCP_KEEPALIVE_PROBES",
  "KW_TCP_KEEPALIVE_INTVL", "KW_SPOOF_SOURCE", "KW_KEEP_ALIVE",
  "KW_MAX_CONNECTIONS", "KW_LOCALIP", "KW_IP", "KW_LOCALPORT",
  "KW_DESTPORT", "KW_TLS", "KW_PEER_VERIFY", "KW_KEY_FILE", "KW_CERT_FILE",
  "KW_CA_DIR", "KW_CRL_DIR", "KW_TRUSTED_KEYS", "KW_TRUSTED_DN",
  "KW_CIPHER_SUITE", "KW_SSL_OPTIONS", "LL_CONTEXT_ROOT",
  "LL_CONTEXT_DESTINATION", "LL_CONTEXT_SOURCE", "LL_CONTEXT_PARSER",
  "LL_CONTEXT_REWRITE", "LL_CONTEXT_FILTER", "LL_CONTEXT_LOG",
  "LL_CONTEXT_BLOCK_DEF", "LL_CONTEXT_BLOCK_REF",
  "LL_CONTEXT_BLOCK_CONTENT", "LL_CONTEXT_BLOCK_ARG", "LL_CONTEXT_PRAGMA",
  "LL_CONTEXT_FORMAT", "LL_CONTEXT_TEMPLATE_FUNC", "LL_CONTEXT_INNER_DEST",
  "LL_CONTEXT_INNER_SRC", "LL_CONTEXT_CLIENT_PROTO",
  "LL_CONTEXT_SERVER_PROTO", "KW_SOURCE", "KW_FILTER", "KW_PARSER",
  "KW_DESTINATION", "KW_LOG", "KW_OPTIONS", "KW_INCLUDE", "KW_BLOCK",
  "KW_JUNCTION", "KW_CHANNEL", "KW_INTERNAL", "KW_FILE", "KW_SYSLOG",
  "KW_MARK_FREQ", "KW_STATS_FREQ", "KW_STATS_LEVEL", "KW_STATS_LIFETIME",
  "KW_FLUSH_LINES", "KW_SUPPRESS", "KW_FLUSH_TIMEOUT", "KW_LOG_MSG_SIZE",
  "KW_FILE_TEMPLATE", "KW_PROTO_TEMPLATE", "KW_MARK_MODE", "KW_ENCODING",
  "KW_TYPE", "KW_CHAIN_HOSTNAMES", "KW_NORMALIZE_HOSTNAMES",
  "KW_KEEP_HOSTNAME", "KW_CHECK_HOSTNAME", "KW_BAD_HOSTNAME",
  "KW_KEEP_TIMESTAMP", "KW_USE_DNS", "KW_USE_FQDN", "KW_CUSTOM_DOMAIN",
  "KW_DNS_CACHE", "KW_DNS_CACHE_SIZE", "KW_DNS_CACHE_EXPIRE",
  "KW_DNS_CACHE_EXPIRE_FAILED", "KW_DNS_CACHE_HOSTS", "KW_PERSIST_ONLY",
  "KW_USE_RCPTID", "KW_USE_UNIQID", "KW_TZ_CONVERT", "KW_TS_FORMAT",
  "KW_FRAC_DIGITS", "KW_LOG_FIFO_SIZE", "KW_LOG_FETCH_LIMIT",
  "KW_LOG_IW_SIZE", "KW_LOG_PREFIX", "KW_PROGRAM_OVERRIDE",
  "KW_HOST_OVERRIDE", "KW_THROTTLE", "KW_THREADED",
  "KW_PASS_UNIX_CREDENTIALS", "KW_PERSIST_NAME", "KW_FLAGS", "KW_PAD_SIZE",
  "KW_TIME_ZONE", "KW_RECV_TIME_ZONE", "KW_SEND_TIME_ZONE",
  "KW_LOCAL_TIME_ZONE", "KW_FORMAT", "KW_TIME_REOPEN", "KW_TIME_REAP",
  "KW_TIME_SLEEP", "KW_TMPL_ESCAPE", "KW_OPTIONAL", "KW_CREATE_DIRS",
  "KW_OWNER", "KW_GROUP", "KW_PERM", "KW_DIR_OWNER", "KW_DIR_GROUP",
  "KW_DIR_PERM", "KW_TEMPLATE", "KW_TEMPLATE_ESCAPE",
  "KW_TEMPLATE_FUNCTION", "KW_DEFAULT_FACILITY", "KW_DEFAULT_LEVEL",
  "KW_PORT", "KW_USE_TIME_RECVD", "KW_FACILITY", "KW_LEVEL", "KW_HOST",
  "KW_MATCH", "KW_MESSAGE", "KW_NETMASK", "KW_TAGS", "KW_NETMASK6",
  "KW_REWRITE", "KW_YES", "KW_NO", "KW_IFDEF", "KW_ENDIF", "LL_DOTDOT",
  "LL_IDENTIFIER", "LL_NUMBER", "LL_FLOAT", "LL_STRING", "LL_TOKEN",
  "LL_BLOCK", "LL_PRAGMA", "LL_EOL", "LL_ERROR", "KW_VALUE_PAIRS",
  "KW_EXCLUDE", "KW_PAIR", "KW_KEY", "KW_SCOPE", "KW_SHIFT", "KW_REKEY",
  "KW_ADD_PREFIX", "KW_REPLACE_PREFIX", "KW_ON_ERROR", "KW_RETRIES", "'('",
  "')'", "'{'", "'}'", "';'", "':'", "$accept", "start", "driver",
  "source_afunix", "source_afunix_dgram_params", "$@1",
  "source_afunix_stream_params", "$@2", "source_afunix_options",
  "source_afunix_option", "source_afinet", "source_afinet_udp_params",
  "$@3", "source_afinet_udp6_params", "$@4", "source_afinet_udp_options",
  "source_afinet_udp_option", "source_afinet_option",
  "source_afinet_tcp_params", "$@5", "source_afinet_tcp6_params", "$@6",
  "source_afinet_tcp_options", "source_afinet_tcp_option", "$@7",
  "source_afsocket_stream_params", "source_afsyslog",
  "source_afsyslog_params", "$@8", "source_afsyslog_options",
  "source_afsyslog_option", "source_afnetwork", "source_afnetwork_params",
  "$@9", "source_afnetwork_options", "source_afnetwork_option",
  "source_afsocket_transport", "$@10", "source_systemd_syslog",
  "source_systemd_syslog_params", "$@11", "source_systemd_syslog_options",
  "source_systemd_syslog_option", "dest_afunix",
  "dest_afunix_dgram_params", "$@12", "dest_afunix_stream_params", "$@13",
  "dest_afunix_options", "dest_afunix_option", "dest_afinet",
  "dest_afinet_udp_params", "$@14", "dest_afinet_udp6_params", "$@15",
  "dest_afinet_udp_options", "dest_afinet_option",
  "dest_afinet_udp_option", "dest_afinet_tcp_params", "$@16",
  "dest_afinet_tcp6_params", "$@17", "dest_afinet_tcp_options",
  "dest_afinet_tcp_option", "$@18", "dest_afsocket_option",
  "dest_afsyslog", "dest_afsyslog_params", "$@19", "dest_afsyslog_options",
  "dest_afsyslog_option", "dest_afnetwork", "dest_afnetwork_params",
  "$@20", "dest_afnetwork_options", "dest_afnetwork_option",
  "dest_afsocket_transport", "$@21", "afsocket_transport", "tls_options",
  "tls_option", "socket_option", "inet_socket_option",
  "inet_ip_protocol_option", "string", "yesno", "dnsmode",
  "string_or_number", "string_list", "string_list_build", "level_string",
  "facility_string", "source_option", "$@28", "source_proto_option",
  "host_resolve_option", "msg_format_option", "source_reader_option",
  "$@29", "$@30", "$@31", "source_reader_option_flags", "driver_option",
  "dest_driver_option", "dest_writer_option", "$@32",
  "dest_writer_options_flags", "file_perm_option", "template_option", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256, 20001, 20000, 20002, 20003, 20004, 20005, 20006, 20007,
   20008, 20009, 20010, 20011, 20012, 20013, 20014, 20015, 20016, 20017,
   20018, 20019, 20020, 20021, 20022, 20023, 20024, 20025, 20026, 20027,
   20028, 20029, 20030, 20031, 20032, 20033, 20034, 20035, 20036,     1,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18, 10000, 10001, 10002,
   10003, 10004, 10005, 10006, 10007, 10008, 10009, 10010, 10011, 10060,
   10071, 10072, 10073, 10074, 10075, 10076, 10077, 10078, 10079, 10080,
   10081, 10082, 10083, 10090, 10091, 10092, 10093, 10094, 10100, 10110,
   10111, 10112, 10120, 10121, 10130, 10131, 10132, 10140, 10141, 10142,
   10150, 10151, 10152, 10160, 10162, 10163, 10164, 10165, 10166, 10170,
   10171, 10231, 10302, 10190, 10200, 10201, 10202, 10203, 10204, 10205,
   10210, 10211, 10212, 10220, 10230, 10240, 10250, 10251, 10252, 10260,
   10261, 10262, 10270, 10271, 10272, 10300, 10301, 10323, 10340, 10350,
   10351, 10352, 10353, 10354, 10355, 10356, 10357, 10370, 10380, 10381,
   10410, 10411, 10420, 10421, 10422, 10423, 10424, 10425, 10426, 10427,
   10428, 10429, 10500, 10502, 10503, 10504, 10505, 10506, 10507, 10508,
   10509, 10510, 10511,    40,    41,   123,   125,    59,    58
};
# endif

#define YYPACT_NINF -273

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-273)))

#define YYTABLE_NINF -216

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       1,   414,   227,    16,  -273,  -141,  -115,  -113,  -109,   -97,
     -92,   -86,   -70,  -273,  -273,  -273,  -273,   -68,   -66,   -41,
     -35,   -31,   -29,   -13,     6,    15,  -273,  -273,  -273,  -273,
    -273,  -273,  -110,  -110,  -110,  -110,  -110,  -110,  -110,  -110,
    -110,  -110,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,
    -273,   -23,  -273,    23,  -273,    28,  -273,    30,  -273,    33,
    -273,    40,  -273,    41,  -273,    51,  -273,    64,  -273,    68,
    -273,    71,   735,    79,   770,    89,   735,   113,   770,   120,
     241,   135,    76,   136,   387,  -273,  -273,  -273,  -273,  -273,
    -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,
    -273,  -273,   255,  -273,   255,  -273,    17,    53,   126,   139,
     142,   147,   150,   151,   152,   156,   160,   161,   162,   169,
    -273,   170,   171,   173,   174,   179,  -273,  -273,   735,  -273,
    -273,  -273,  -273,   243,   -64,    50,  -273,  -273,   770,  -273,
    -273,  -273,  -273,  -273,  -273,   180,   192,  -273,  -273,  -273,
    -273,   241,  -273,  -273,  -273,  -273,    76,  -273,  -273,  -273,
    -273,  -273,  -273,   387,  -273,   755,   843,   423,   525,   593,
     667,     8,    34,   198,   199,   200,   202,   214,   216,   219,
     220,   221,  -273,   255,  -273,  -273,  -273,  -273,  -273,    69,
      52,   163,   203,   215,    52,   242,   245,   270,    52,   272,
    -110,  -110,   208,   236,    52,   273,    20,  -110,   208,  -273,
     258,   274,   276,   289,   290,   292,   293,   294,   305,  -273,
     -15,  -273,   306,   307,  -273,   308,   309,   319,  -273,  -273,
      60,   291,   323,  -273,  -273,  -273,   328,   331,   332,   334,
     335,   336,   337,   338,   339,   340,   341,   342,  -273,  -273,
    -273,  -273,  -273,  -273,  -273,   196,   343,   344,   345,  -273,
     346,  -273,  -273,  -273,  -273,  -273,  -273,   347,  -273,  -273,
     348,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,    52,
      52,    52,   130,   184,   -75,   316,   321,    18,  -273,   254,
    -273,  -273,  -273,   320,   351,   353,   354,   355,   356,   357,
     359,   360,   375,   377,   380,  -273,  -273,  -273,   383,    93,
     384,   385,    20,    20,   388,   389,   390,    52,    52,    52,
     411,  -110,  -110,  -110,  -110,  -110,   393,   394,   395,   396,
    -273,   416,  -110,  -110,    -1,  -110,   397,   398,   399,   400,
    -273,   401,    93,    52,   424,   425,   426,   427,   -55,   428,
     429,  -110,   430,  -110,    52,   404,   412,   413,   415,   417,
     418,  -273,  -110,   208,   208,   419,   208,    52,    52,   420,
     422,   441,   443,  -273,   445,  -273,   449,   450,  -273,  -273,
     451,  -273,   452,   453,  -273,  -273,  -273,  -273,  -273,  -273,
    -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,   421,
     431,   456,   457,   458,   459,   460,   462,   463,  -273,  -273,
     466,    93,  -273,  -273,  -273,  -273,  -273,  -273,  -273,   467,
     468,   469,   470,   471,   472,   473,   474,  -110,   475,  -273,
      52,   -63,    52,    52,   476,   477,   478,  -273,  -273,   479,
    -273,   480,  -273,  -273,  -273,  -273,  -273,   481,   482,   485,
     486,   487,   490,   491,   492,   496,   497,  -110,   498,   500,
     501,   502,  -110,   433,  -110,  -110,  -110,  -110,   503,   505,
     517,    93,   519,   523,   524,    93,  -273,  -273,  -273,  -273,
    -273,  -273,  -273,  -273,  -273,  -110,  -110,  -110,  -110,  -110,
    -110,  -110,  -110,  -110,  -273,  -273,  -273,  -273,  -273,  -273,
    -273,  -273,  -273,  -273,  -273,  -273,   526,  -273,  -273,   527,
     529,   530,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,
    -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,
    -273,  -273,   534,   535,   536,   537,   538,   539,  -273,  -273,
    -273,   540,  -273,  -273,  -273,   541,   542,   543,   544,   545,
     546,   547,   548,   549,   550,  -273,  -273,  -273,  -273,  -273,
    -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,
    -273,  -273,  -273,  -273,  -273,  -273
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       0,     0,     0,     0,     2,     0,     0,     0,     0,     0,
       0,     0,     0,     8,     9,    10,    11,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     3,     4,     5,     6,
       7,     1,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    44,    31,    46,    33,    65,    76,    57,   171,
     172,     0,    86,     0,    84,     0,   114,     0,    98,     0,
     116,     0,   100,     0,   132,     0,   125,     0,    16,     0,
      14,     0,   211,     0,   211,     0,   211,     0,   211,     0,
     211,     0,   211,     0,   211,    83,    89,    82,    89,    95,
     119,    94,   103,    97,   119,    96,   103,   131,   135,   124,
     128,    13,   211,    12,   211,    28,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      51,     0,     0,     0,     0,     0,    50,    45,   211,    53,
     164,    43,    42,   195,     0,     0,    27,    32,   211,    37,
      30,    47,    29,    34,    64,     0,     0,    73,    69,    71,
      66,   211,    70,    72,    75,    77,   211,    81,    80,    56,
      61,    63,    58,   211,    62,   235,   235,   235,   235,   235,
     235,   235,   235,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    17,   211,    21,    23,    22,    20,    15,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   219,     0,     0,    48,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   212,
       0,   197,     0,     0,   214,     0,     0,     0,   216,    35,
       0,     0,     0,    67,    78,    59,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   223,    88,
      91,    92,   224,    93,    90,     0,     0,     0,     0,   121,
       0,   120,   118,   110,   108,   111,   109,     0,   112,   102,
       0,   140,   136,   134,   137,   138,   129,   127,   130,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    18,     0,
     173,   174,   175,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   179,   180,   178,     0,   148,
       0,     0,   219,   219,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   183,     0,     0,     0,     0,
     196,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     170,     0,   148,     0,     0,     0,     0,     0,     0,     0,
       0,   238,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   236,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   240,     0,   242,     0,     0,   244,   246,
       0,   248,     0,     0,   250,   165,   162,   166,   160,   161,
     163,   167,   169,   168,    54,    55,    38,    39,    40,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   149,   159,
       0,   148,   207,   209,   218,   217,   208,   210,    41,     0,
       0,     0,     0,     0,     0,     0,     0,   183,     0,   181,
       0,     0,     0,     0,     0,     0,     0,   186,   185,     0,
     184,     0,   143,   144,   145,   142,   146,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   238,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   148,     0,     0,     0,   148,    25,    24,    26,   239,
     241,   243,   245,   247,   249,     0,     0,     0,     0,     0,
     183,   183,     0,   183,    52,   147,   188,   189,   193,   187,
     192,   190,   191,   220,   182,   194,     0,   177,   176,     0,
       0,     0,   199,   198,   204,   206,   205,    74,   123,   232,
     226,   228,   227,   233,   234,   221,   222,   237,   225,   231,
     229,   230,     0,     0,     0,     0,     0,     0,   104,   105,
     107,     0,   106,   113,   139,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   203,   201,   200,   202,   251,
     252,   253,   254,   255,   256,   122,   141,   150,   151,   152,
     153,   154,   155,   156,   157,   158
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,   -65,  -273,
    -273,  -273,  -273,  -273,  -273,   -67,  -273,   144,  -273,  -273,
    -273,  -273,   -61,  -273,  -273,   125,  -273,  -273,  -273,   435,
    -273,  -273,  -273,  -273,   438,  -273,   -44,  -273,  -273,  -273,
    -273,   446,  -273,  -273,  -273,  -273,  -273,  -273,   515,  -273,
    -273,  -273,  -273,  -273,  -273,   631,    49,  -273,  -273,  -273,
    -273,  -273,   634,  -273,  -273,   -93,  -273,  -273,  -273,  -273,
    -273,  -273,  -273,  -273,  -273,  -273,   557,  -273,   -22,  -272,
    -273,    -2,   317,  -273,   -32,  -184,  -273,  -170,  -216,   304,
    -273,  -273,  -273,  -273,  -273,  -273,  -273,    54,  -273,  -273,
    -273,  -135,   599,    75,   140,  -273,   277,  -273,  -273
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     3,     4,    26,    69,   104,    67,   102,   182,   183,
      27,    73,    74,    77,    78,   137,   138,   126,    71,    72,
      75,    76,   127,   128,   203,   129,    28,    83,    84,   162,
     163,    29,    79,    80,   150,   151,   152,   232,    30,    81,
      82,   155,   156,    13,    53,    88,    51,    86,   165,   249,
      14,    57,    92,    61,    96,   168,   261,   269,    55,    90,
      59,    94,   167,   262,   365,   263,    15,    65,   100,   172,
     277,    16,    63,    98,   171,   273,   274,   369,   153,   410,
     411,   130,   131,   341,   307,   293,   509,   308,   428,   429,
     441,   439,   219,   220,   224,   330,   228,   132,   133,   134,
     135,   314,   252,   265,   266,   255,   458,   187,   361
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      52,    54,    56,    58,    60,    62,    64,    66,    68,    70,
     297,   143,   453,   222,   301,   141,    31,   223,   145,   146,
     310,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     270,   236,    32,   256,   507,   257,   258,   271,   316,   188,
     164,     1,     2,    49,   145,   146,    50,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   270,   236,    33,   256,
      34,   257,   258,   271,    35,   336,   337,   209,   437,   326,
     447,   229,   250,   250,   327,   328,    36,   329,   237,   377,
     157,    37,   238,   239,   240,   290,   291,    38,   241,   338,
     107,   292,   109,   110,   111,   370,   371,   372,    49,   378,
     185,    50,   185,    39,   237,    40,   312,    41,   238,   239,
     240,   242,   374,   376,   241,   380,   382,   243,   288,   164,
     217,   244,   245,   399,   400,   401,   402,   403,   404,   405,
     406,   407,    42,   419,   420,   421,   158,   242,    43,   495,
     246,   247,    44,   243,    45,   260,   217,   244,   245,   275,
     275,    85,    49,  -213,   157,    50,   186,  -213,   186,   448,
      46,   248,   121,   251,   251,   225,   246,   247,   303,   304,
     461,   260,   383,    49,   313,   315,    50,   414,   415,    47,
     122,   185,  -133,   473,   474,   226,   227,   248,    48,   123,
     189,  -215,   384,   469,   470,   124,   472,    87,   339,   541,
     290,   291,    89,   545,    91,   149,   292,    93,  -126,   161,
     158,  -215,  -215,    49,    95,    97,    50,   268,   139,   268,
     272,   276,   139,   289,   148,    99,   190,   184,   160,   184,
      17,    18,    19,    20,    21,    22,    23,   186,   101,    24,
     253,   253,   103,   408,   409,   105,   506,   508,   510,   511,
     -79,   145,   146,   136,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   140,   115,   116,   117,   118,   119,   107,
     147,   109,   110,   111,   551,   552,   149,   554,   115,   116,
     313,   313,   139,    49,   305,   306,    50,   142,   161,   423,
     424,   425,   426,   427,   144,   148,    25,   355,   356,   191,
     435,   436,   438,   440,   373,   254,   254,   160,   184,   154,
     159,   357,   192,   358,   359,   193,   454,   294,  -213,   457,
     194,   460,  -213,   195,   196,   197,   210,   121,   211,   198,
     468,   212,  -213,   199,   200,   201,  -213,    49,   305,   306,
      50,   121,   202,   204,   205,   122,   206,   207,   213,   214,
     215,   216,   208,   230,   123,   217,  -215,   295,   375,   122,
     124,    49,   305,   306,    50,   231,   173,   360,   123,   296,
    -215,   279,   280,   281,   124,   282,  -215,  -215,   125,   174,
     175,   176,   177,   178,   179,   180,   181,   283,   218,   284,
    -215,  -215,   285,   286,   287,   427,   298,   145,   146,   299,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   309,
     115,   116,   117,   118,   119,   -68,   147,     5,     6,     7,
       8,     9,    10,    11,   300,   457,   302,   311,   385,   -19,
     532,   317,   534,   535,   536,   537,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   340,   236,   318,   256,   319,
     257,   258,   259,   546,   547,   548,   549,   550,   427,   427,
     553,   427,   320,   321,  -213,   322,   323,   324,  -213,    49,
     305,   306,    50,   121,    49,   305,   306,    50,   325,   331,
     332,   333,   334,    12,   264,   264,   264,   264,   264,   264,
     379,   122,   335,   237,   386,   381,   342,   238,   239,   240,
     123,   343,  -215,   241,   344,   345,   124,   346,   347,   348,
     349,   350,   351,   352,   353,   354,   362,   363,   364,   366,
     367,   368,  -215,  -215,   125,   387,   242,   388,   389,   390,
     391,   392,   243,   393,   394,   217,   244,   245,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   267,   236,   395,
     256,   396,   257,   258,   397,   246,   247,   398,   412,   413,
     260,   -60,   416,   417,   418,   422,   430,   431,   432,   433,
     434,   442,   443,   444,   445,   446,   248,   462,   449,   450,
     451,   452,   455,   456,   459,   463,   464,   533,   465,   233,
     466,   467,   471,   475,   485,   237,   476,  -115,   235,   238,
     239,   240,   234,   166,   486,   241,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   477,   236,   478,   256,   479,
     257,   258,   259,   480,   481,   482,   483,   484,   242,   487,
     488,   489,   490,   491,   243,   492,   493,   217,   244,   245,
     494,   496,   497,   498,   499,   500,   501,   502,   503,   505,
     512,   513,   514,   515,   516,   517,   518,   246,   247,   519,
     520,   521,   260,   237,   522,   523,   524,   238,   239,   240,
     525,   526,   528,   241,   529,   530,   531,   538,   248,   539,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   267,
     236,   540,   256,   542,   257,   258,   242,   543,   544,   -99,
     555,   556,   243,   557,   558,   217,   244,   245,   559,   560,
     561,   562,   563,   564,   565,   566,   567,   568,   569,   570,
     571,   572,   573,   574,   575,   246,   247,   170,   169,   278,
     260,   504,   221,     0,   527,     0,     0,   237,     0,     0,
       0,   238,   239,   240,     0,     0,   248,   241,   106,   107,
     108,   109,   110,   111,   112,   113,   114,     0,   115,   116,
     117,   118,   119,     0,   120,     0,     0,  -117,     0,   107,
     242,   109,   110,   111,     0,     0,   243,     0,   236,   217,
     244,   245,     0,   106,   107,   108,   109,   110,   111,   112,
     113,   114,     0,     0,     0,   117,   118,   119,     0,   246,
     247,     0,     0,     0,   260,     0,     0,     0,     0,     0,
       0,     0,  -213,     0,     0,     0,  -213,     0,     0,     0,
     248,   121,     0,     0,     0,   237,     0,     0,     0,   238,
     239,   240,     0,     0,     0,   241,     0,     0,     0,   122,
       0,  -101,     0,     0,     0,     0,     0,  -213,   123,     0,
    -215,  -213,     0,     0,   124,     0,   121,   107,   242,   109,
     110,   111,     0,     0,   243,     0,   236,   217,   244,   245,
    -215,  -215,   125,     0,   122,     0,     0,     0,     0,     0,
       0,     0,     0,   123,     0,  -215,     0,   246,   247,   124,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  -215,  -215,   125,   248,   -49,
       0,     0,     0,   237,     0,     0,     0,   238,   239,   240,
       0,     0,     0,   241,     0,     0,     0,     0,     0,   -87,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -36,     0,   242,     0,     0,     0,
       0,     0,   243,     0,     0,   217,   244,   245,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   246,   247,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   248,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   -85
};

static const yytype_int16 yycheck[] =
{
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
     194,    78,    67,    77,   198,    76,     0,    81,    10,    11,
     204,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,   173,    25,    97,    27,    28,    29,   208,   104,
      84,    40,    41,   153,    10,    11,   156,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,   173,    25,
     173,    27,    28,    29,   173,     5,     6,   128,    69,    84,
     342,   138,   165,   166,    89,    90,   173,    92,    70,   154,
      82,   173,    74,    75,    76,   148,   149,   173,    80,    29,
      14,   154,    16,    17,    18,   279,   280,   281,   153,   174,
     102,   156,   104,   173,    70,   173,    86,   173,    74,    75,
      76,   103,   282,   283,    80,   285,   286,   109,   183,   163,
     112,   113,   114,    30,    31,    32,    33,    34,    35,    36,
      37,    38,   173,   317,   318,   319,    82,   103,   173,   411,
     132,   133,   173,   109,   173,   137,   112,   113,   114,   171,
     172,   174,   153,    77,   156,   156,   102,    81,   104,   343,
     173,   153,    86,   165,   166,   115,   132,   133,   200,   201,
     354,   137,   154,   153,   206,   207,   156,   312,   313,   173,
     104,   183,   174,   367,   368,   135,   136,   153,   173,   113,
     173,   115,   174,   363,   364,   119,   366,   174,   230,   471,
     148,   149,   174,   475,   174,    80,   154,   174,   174,    84,
     156,   135,   136,   153,   174,   174,   156,   168,    74,   170,
     171,   172,    78,   154,    80,   174,   173,   102,    84,   104,
       3,     4,     5,     6,     7,     8,     9,   183,   174,    12,
     165,   166,   174,   150,   151,   174,   430,   431,   432,   433,
     174,    10,    11,   174,    13,    14,    15,    16,    17,    18,
      19,    20,    21,   174,    23,    24,    25,    26,    27,    14,
      29,    16,    17,    18,   490,   491,   151,   493,    23,    24,
     312,   313,   138,   153,   154,   155,   156,   174,   163,   321,
     322,   323,   324,   325,   174,   151,    69,   101,   102,   173,
     332,   333,   334,   335,   174,   165,   166,   163,   183,   174,
     174,   115,   173,   117,   118,   173,   348,   154,    77,   351,
     173,   353,    81,   173,   173,   173,    83,    86,    85,   173,
     362,    88,    77,   173,   173,   173,    81,   153,   154,   155,
     156,    86,   173,   173,   173,   104,   173,   173,   105,   106,
     107,   108,   173,   173,   113,   112,   115,   154,   174,   104,
     119,   153,   154,   155,   156,   173,   111,   171,   113,   154,
     115,   173,   173,   173,   119,   173,   135,   136,   137,   124,
     125,   126,   127,   128,   129,   130,   131,   173,   145,   173,
     135,   136,   173,   173,   173,   427,   154,    10,    11,   154,
      13,    14,    15,    16,    17,    18,    19,    20,    21,   173,
      23,    24,    25,    26,    27,   174,    29,     3,     4,     5,
       6,     7,     8,     9,   154,   457,   154,   154,   174,   174,
     462,   173,   464,   465,   466,   467,    13,    14,    15,    16,
      17,    18,    19,    20,    21,   154,    23,   173,    25,   173,
      27,    28,    29,   485,   486,   487,   488,   489,   490,   491,
     492,   493,   173,   173,    77,   173,   173,   173,    81,   153,
     154,   155,   156,    86,   153,   154,   155,   156,   173,   173,
     173,   173,   173,    69,   167,   168,   169,   170,   171,   172,
     174,   104,   173,    70,   174,   174,   173,    74,    75,    76,
     113,   173,   115,    80,   173,   173,   119,   173,   173,   173,
     173,   173,   173,   173,   173,   173,   173,   173,   173,   173,
     173,   173,   135,   136,   137,   174,   103,   174,   174,   174,
     174,   174,   109,   174,   174,   112,   113,   114,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,   174,
      25,   174,    27,    28,   174,   132,   133,   174,   174,   174,
     137,   174,   174,   174,   174,   154,   173,   173,   173,   173,
     154,   174,   174,   174,   174,   174,   153,   173,   154,   154,
     154,   154,   154,   154,   154,   173,   173,   154,   173,   151,
     173,   173,   173,   173,   173,    70,   174,   174,   163,    74,
      75,    76,   156,    88,   173,    80,    13,    14,    15,    16,
      17,    18,    19,    20,    21,   174,    23,   174,    25,   174,
      27,    28,    29,   174,   174,   174,   174,   174,   103,   173,
     173,   173,   173,   173,   109,   173,   173,   112,   113,   114,
     174,   174,   174,   174,   174,   174,   174,   174,   174,   174,
     174,   174,   174,   174,   174,   174,   174,   132,   133,   174,
     174,   174,   137,    70,   174,   174,   174,    74,    75,    76,
     174,   174,   174,    80,   174,   174,   174,   174,   153,   174,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,   174,    25,   174,    27,    28,   103,   174,   174,   174,
     174,   174,   109,   174,   174,   112,   113,   114,   174,   174,
     174,   174,   174,   174,   174,   174,   174,   174,   174,   174,
     174,   174,   174,   174,   174,   132,   133,    96,    94,   172,
     137,   427,   133,    -1,   457,    -1,    -1,    70,    -1,    -1,
      -1,    74,    75,    76,    -1,    -1,   153,    80,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    -1,    23,    24,
      25,    26,    27,    -1,    29,    -1,    -1,   174,    -1,    14,
     103,    16,    17,    18,    -1,    -1,   109,    -1,    23,   112,
     113,   114,    -1,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    -1,    -1,    -1,    25,    26,    27,    -1,   132,
     133,    -1,    -1,    -1,   137,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    77,    -1,    -1,    -1,    81,    -1,    -1,    -1,
     153,    86,    -1,    -1,    -1,    70,    -1,    -1,    -1,    74,
      75,    76,    -1,    -1,    -1,    80,    -1,    -1,    -1,   104,
      -1,   174,    -1,    -1,    -1,    -1,    -1,    77,   113,    -1,
     115,    81,    -1,    -1,   119,    -1,    86,    14,   103,    16,
      17,    18,    -1,    -1,   109,    -1,    23,   112,   113,   114,
     135,   136,   137,    -1,   104,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   113,    -1,   115,    -1,   132,   133,   119,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   135,   136,   137,   153,   174,
      -1,    -1,    -1,    70,    -1,    -1,    -1,    74,    75,    76,
      -1,    -1,    -1,    80,    -1,    -1,    -1,    -1,    -1,   174,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   174,    -1,   103,    -1,    -1,    -1,
      -1,    -1,   109,    -1,    -1,   112,   113,   114,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   132,   133,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   153,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   174
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,    40,    41,   180,   181,     3,     4,     5,     6,     7,
       8,     9,    69,   222,   229,   245,   250,     3,     4,     5,
       6,     7,     8,     9,    12,    69,   182,   189,   205,   210,
     217,     0,   173,   173,   173,   173,   173,   173,   173,   173,
     173,   173,   173,   173,   173,   173,   173,   173,   173,   153,
     156,   225,   263,   223,   263,   237,   263,   230,   263,   239,
     263,   232,   263,   251,   263,   246,   263,   185,   263,   183,
     263,   197,   198,   190,   191,   199,   200,   192,   193,   211,
     212,   218,   219,   206,   207,   174,   226,   174,   224,   174,
     238,   174,   231,   174,   240,   174,   233,   174,   252,   174,
     247,   174,   186,   174,   184,   174,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    23,    24,    25,    26,    27,
      29,    86,   104,   113,   119,   137,   196,   201,   202,   204,
     260,   261,   276,   277,   278,   279,   174,   194,   195,   196,
     174,   201,   174,   194,   174,    10,    11,    29,   196,   204,
     213,   214,   215,   257,   174,   220,   221,   260,   276,   174,
     196,   204,   208,   209,   215,   227,   227,   241,   234,   241,
     234,   253,   248,   111,   124,   125,   126,   127,   128,   129,
     130,   131,   187,   188,   204,   260,   276,   286,   187,   173,
     173,   173,   173,   173,   173,   173,   173,   173,   173,   173,
     173,   173,   173,   203,   173,   173,   173,   173,   173,   201,
      83,    85,    88,   105,   106,   107,   108,   112,   145,   271,
     272,   281,    77,    81,   273,   115,   135,   136,   275,   194,
     173,   173,   216,   213,   220,   208,    23,    70,    74,    75,
      76,    80,   103,   109,   113,   114,   132,   133,   153,   228,
     244,   260,   281,   282,   283,   284,    25,    27,    28,    29,
     137,   235,   242,   244,   261,   282,   283,    22,   235,   236,
      22,    29,   235,   254,   255,   257,   235,   249,   255,   173,
     173,   173,   173,   173,   173,   173,   173,   173,   187,   154,
     148,   149,   154,   264,   154,   154,   154,   264,   154,   154,
     154,   264,   154,   263,   263,   154,   155,   263,   266,   173,
     264,   154,    86,   263,   280,   263,   266,   173,   173,   173,
     173,   173,   173,   173,   173,   173,    84,    89,    90,    92,
     274,   173,   173,   173,   173,   173,     5,     6,    29,   263,
     154,   262,   173,   173,   173,   173,   173,   173,   173,   173,
     173,   173,   173,   173,   173,   101,   102,   115,   117,   118,
     171,   287,   173,   173,   173,   243,   173,   173,   173,   256,
     264,   264,   264,   174,   266,   174,   266,   154,   174,   174,
     266,   174,   266,   154,   174,   174,   174,   174,   174,   174,
     174,   174,   174,   174,   174,   174,   174,   174,   174,    30,
      31,    32,    33,    34,    35,    36,    37,    38,   150,   151,
     258,   259,   174,   174,   280,   280,   174,   174,   174,   264,
     264,   264,   154,   263,   263,   263,   263,   263,   267,   268,
     173,   173,   173,   173,   154,   263,   263,    69,   263,   270,
     263,   269,   174,   174,   174,   174,   174,   258,   264,   154,
     154,   154,   154,    67,   263,   154,   154,   263,   285,   154,
     263,   264,   173,   173,   173,   173,   173,   173,   263,   266,
     266,   173,   266,   264,   264,   173,   174,   174,   174,   174,
     174,   174,   174,   174,   174,   173,   173,   173,   173,   173,
     173,   173,   173,   173,   174,   258,   174,   174,   174,   174,
     174,   174,   174,   174,   268,   174,   264,    97,   264,   265,
     264,   264,   174,   174,   174,   174,   174,   174,   174,   174,
     174,   174,   174,   174,   174,   174,   174,   285,   174,   174,
     174,   174,   263,   154,   263,   263,   263,   263,   174,   174,
     174,   258,   174,   174,   174,   258,   263,   263,   263,   263,
     263,   267,   267,   263,   267,   174,   174,   174,   174,   174,
     174,   174,   174,   174,   174,   174,   174,   174,   174,   174,
     174,   174,   174,   174,   174,   174
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   179,   180,   181,   181,   181,   181,   181,   181,   181,
     181,   181,   182,   182,   184,   183,   186,   185,   187,   187,
     188,   188,   188,   188,   188,   188,   188,   189,   189,   189,
     189,   191,   190,   193,   192,   194,   194,   195,   196,   196,
     196,   196,   196,   196,   198,   197,   200,   199,   201,   201,
     202,   203,   202,   202,   204,   204,   205,   207,   206,   208,
     208,   209,   209,   209,   210,   212,   211,   213,   213,   214,
     214,   214,   215,   216,   215,   217,   219,   218,   220,   220,
     221,   221,   222,   222,   224,   223,   226,   225,   227,   227,
     228,   228,   228,   228,   229,   229,   229,   229,   231,   230,
     233,   232,   234,   234,   235,   235,   235,   235,   235,   235,
     235,   235,   236,   236,   238,   237,   240,   239,   241,   241,
     242,   243,   242,   244,   245,   247,   246,   248,   248,   249,
     249,   250,   252,   251,   253,   253,   254,   254,   255,   255,
     256,   255,   257,   257,   257,   257,   257,   258,   258,   259,
     259,   259,   259,   259,   259,   259,   259,   259,   259,   259,
     260,   260,   260,   260,   261,   261,   261,   261,   261,   261,
     262,   263,   263,   264,   264,   264,   265,   265,   266,   266,
     266,   267,   268,   268,   269,   270,   270,   271,   271,   271,
     271,   271,   271,   271,   271,   272,   271,   271,   273,   273,
     274,   274,   274,   274,   275,   275,   275,   276,   276,   276,
     276,   277,   276,   278,   276,   279,   276,   280,   280,   280,
     281,   282,   282,   282,   282,   283,   283,   283,   283,   283,
     283,   283,   283,   283,   283,   284,   283,   285,   285,   286,
     286,   286,   286,   286,   286,   286,   286,   286,   286,   286,
     286,   287,   287,   287,   287,   287,   287
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     4,     4,     0,     3,     0,     3,     2,     0,
       1,     1,     1,     1,     4,     4,     4,     4,     4,     4,
       4,     0,     2,     0,     2,     2,     0,     1,     4,     4,
       4,     4,     1,     1,     0,     2,     0,     2,     2,     0,
       1,     0,     5,     1,     4,     4,     4,     0,     2,     2,
       0,     1,     1,     1,     4,     0,     2,     2,     0,     1,
       1,     1,     1,     0,     5,     4,     0,     2,     2,     0,
       1,     1,     4,     4,     0,     3,     0,     3,     2,     0,
       1,     1,     1,     1,     4,     4,     4,     4,     0,     3,
       0,     3,     2,     0,     4,     4,     4,     4,     1,     1,
       1,     1,     1,     4,     0,     3,     0,     3,     2,     0,
       1,     0,     5,     4,     4,     0,     3,     2,     0,     1,
       1,     4,     0,     3,     2,     0,     1,     1,     1,     4,
       0,     5,     4,     4,     4,     4,     4,     2,     0,     1,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     1,
       4,     4,     4,     4,     1,     4,     4,     4,     4,     4,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     0,     1,     1,     1,     4,     4,     4,
       4,     4,     4,     4,     4,     0,     2,     1,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     0,     2,     0,     2,     0,     2,     2,     2,     0,
       4,     4,     4,     1,     1,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     0,     2,     2,     0,     4,
       3,     4,     3,     4,     3,     4,     3,     4,     3,     4,
       3,     4,     4,     4,     4,     4,     4
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (&yylloc, lexer, instance, arg, YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  unsigned res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location, lexer, instance, arg); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, CfgLexer *lexer, LogDriver **instance, gpointer arg)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (yylocationp);
  YYUSE (lexer);
  YYUSE (instance);
  YYUSE (arg);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, CfgLexer *lexer, LogDriver **instance, gpointer arg)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, lexer, instance, arg);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule, CfgLexer *lexer, LogDriver **instance, gpointer arg)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       , lexer, instance, arg);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule, lexer, instance, arg); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, CfgLexer *lexer, LogDriver **instance, gpointer arg)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  YYUSE (lexer);
  YYUSE (instance);
  YYUSE (arg);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  switch (yytype)
    {
          case 153: /* LL_IDENTIFIER  */
#line 412 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1257  */
      { free(((*yyvaluep).cptr)); }
#line 4062 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1257  */
        break;

    case 156: /* LL_STRING  */
#line 412 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1257  */
      { free(((*yyvaluep).cptr)); }
#line 4068 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1257  */
        break;

    case 158: /* LL_BLOCK  */
#line 412 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1257  */
      { free(((*yyvaluep).cptr)); }
#line 4074 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1257  */
        break;

    case 263: /* string  */
#line 412 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1257  */
      { free(((*yyvaluep).cptr)); }
#line 4080 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1257  */
        break;

    case 266: /* string_or_number  */
#line 412 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1257  */
      { free(((*yyvaluep).cptr)); }
#line 4086 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1257  */
        break;


      default:
        break;
    }
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/*----------.
| yyparse.  |
`----------*/

int
yyparse (CfgLexer *lexer, LogDriver **instance, gpointer arg)
{
/* The lookahead symbol.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

/* Location data for the lookahead symbol.  */
static YYLTYPE yyloc_default
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
YYLTYPE yylloc = yyloc_default;

    /* Number of syntax errors so far.  */
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yyls1, yysize * sizeof (*yylsp),
                    &yystacksize);

        yyls = yyls1;
        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex (&yylval, &yylloc, lexer);
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 512 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    {
            *instance = (yyvsp[0].ptr);
            if (yychar != YYEMPTY)
              cfg_lexer_unput_token(lexer, &yylval);
            YYACCEPT;
          }
#line 4385 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 3:
#line 521 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { (yyval.ptr) = (yyvsp[0].ptr); }
#line 4391 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 4:
#line 522 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { (yyval.ptr) = (yyvsp[0].ptr); }
#line 4397 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 5:
#line 523 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { (yyval.ptr) = (yyvsp[0].ptr); }
#line 4403 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 6:
#line 524 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { (yyval.ptr) = (yyvsp[0].ptr); }
#line 4409 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 7:
#line 525 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { (yyval.ptr) = (yyvsp[0].ptr); }
#line 4415 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 8:
#line 526 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { (yyval.ptr) = (yyvsp[0].ptr); }
#line 4421 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 9:
#line 527 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { (yyval.ptr) = (yyvsp[0].ptr); }
#line 4427 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 10:
#line 528 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { (yyval.ptr) = (yyvsp[0].ptr); }
#line 4433 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 11:
#line 529 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { (yyval.ptr) = (yyvsp[0].ptr); }
#line 4439 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 12:
#line 534 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { (yyval.ptr) = (yyvsp[-1].ptr); }
#line 4445 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 13:
#line 535 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { (yyval.ptr) = (yyvsp[-1].ptr); }
#line 4451 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 14:
#line 540 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    {
      create_and_set_unix_dgram_or_systemd_syslog_source((yyvsp[0].cptr), configuration);
	  }
#line 4459 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 15:
#line 543 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { (yyval.ptr) = last_driver; free((yyvsp[-2].cptr)); }
#line 4465 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 16:
#line 548 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    {
      create_and_set_unix_stream_or_systemd_syslog_source((yyvsp[0].cptr), configuration);
	  }
#line 4473 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 17:
#line 551 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { (yyval.ptr) = last_driver; free((yyvsp[-2].cptr)); }
#line 4479 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 21:
#line 562 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    {}
#line 4485 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 22:
#line 563 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    {}
#line 4491 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 23:
#line 564 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    {}
#line 4497 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 24:
#line 565 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { last_driver->optional = (yyvsp[-1].num); }
#line 4503 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 25:
#line 567 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    {
	    AFUnixSourceDriver *self = (AFUnixSourceDriver*) last_driver;
	    afunix_sd_set_pass_unix_credentials(self, (yyvsp[-1].num));
	  }
#line 4512 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 26:
#line 572 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    {
	    AFUnixSourceDriver *self = (AFUnixSourceDriver*) last_driver;
	    afunix_sd_set_create_dirs(self, (yyvsp[-1].num));
	  }
#line 4521 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 27:
#line 579 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { (yyval.ptr) = (yyvsp[-1].ptr); }
#line 4527 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 28:
#line 580 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { (yyval.ptr) = (yyvsp[-1].ptr); }
#line 4533 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 29:
#line 581 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { (yyval.ptr) = (yyvsp[-1].ptr); }
#line 4539 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 30:
#line 582 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { (yyval.ptr) = (yyvsp[-1].ptr); }
#line 4545 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 31:
#line 587 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    {
            AFInetSourceDriver *d = afinet_sd_new_udp(configuration);

            afinet_grammar_set_source_driver(d);
	  }
#line 4555 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 32:
#line 592 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { (yyval.ptr) = last_driver; }
#line 4561 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 33:
#line 597 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    {
            AFInetSourceDriver *d = afinet_sd_new_udp6(configuration);

            afinet_grammar_set_source_driver(d);
          }
#line 4571 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 34:
#line 602 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { (yyval.ptr) = last_driver; }
#line 4577 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 38:
#line 615 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { afinet_sd_set_localip(last_driver, (yyvsp[-1].cptr)); free((yyvsp[-1].cptr)); }
#line 4583 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 39:
#line 616 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { afinet_sd_set_localip(last_driver, (yyvsp[-1].cptr)); free((yyvsp[-1].cptr)); }
#line 4589 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 40:
#line 617 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { afinet_sd_set_localport(last_driver, (yyvsp[-1].cptr)); free((yyvsp[-1].cptr)); }
#line 4595 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 41:
#line 618 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { afinet_sd_set_localport(last_driver, (yyvsp[-1].cptr)); free((yyvsp[-1].cptr)); }
#line 4601 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 44:
#line 625 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    {
	    AFInetSourceDriver *d = afinet_sd_new_tcp(configuration);

	    afinet_grammar_set_source_driver(d);
	  }
#line 4611 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 45:
#line 630 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { (yyval.ptr) = last_driver; }
#line 4617 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 46:
#line 635 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    {
	    AFInetSourceDriver *d = afinet_sd_new_tcp6(configuration);

	    afinet_grammar_set_source_driver(d);
	  }
#line 4627 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 47:
#line 640 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { (yyval.ptr) = last_driver; }
#line 4633 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 51:
#line 651 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    {
	    last_tls_context = tls_context_new(TM_SERVER);
	  }
#line 4641 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 52:
#line 655 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    {
	    afinet_sd_set_tls_context(last_driver, last_tls_context);
          }
#line 4649 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 53:
#line 658 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    {}
#line 4655 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 54:
#line 662 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { afsocket_sd_set_keep_alive(last_driver, (yyvsp[-1].num)); }
#line 4661 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 55:
#line 663 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { afsocket_sd_set_max_connections(last_driver, (yyvsp[-1].num)); }
#line 4667 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 56:
#line 667 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { (yyval.ptr) = (yyvsp[-1].ptr); }
#line 4673 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 57:
#line 672 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    {
            /* we use transport(tcp) transport by default */
            AFInetSourceDriver *d = afinet_sd_new_syslog(configuration);

            afinet_grammar_set_source_driver(d);
	  }
#line 4684 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 58:
#line 678 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { (yyval.ptr) = last_driver; }
#line 4690 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 63:
#line 689 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    {}
#line 4696 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 64:
#line 693 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { (yyval.ptr) = (yyvsp[-1].ptr); }
#line 4702 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 65:
#line 698 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    {
            /* we use transport(tcp) transport by default */
            AFInetSourceDriver *d = afinet_sd_new_network(configuration);

            afinet_grammar_set_source_driver(d);
	  }
#line 4713 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 66:
#line 704 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { (yyval.ptr) = last_driver; }
#line 4719 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 71:
#line 715 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    {}
#line 4725 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 73:
#line 721 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    {
	    last_tls_context = tls_context_new(TM_SERVER);
	  }
#line 4733 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 74:
#line 725 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    {
	    afinet_sd_set_tls_context(last_driver, last_tls_context);
          }
#line 4741 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 75:
#line 731 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { (yyval.ptr) = (yyvsp[-1].ptr); }
#line 4747 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 76:
#line 735 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    {
#if ! SYSLOG_NG_ENABLE_SYSTEMD
            msg_error("systemd-syslog() source cannot be enabled and it is not"
                      " functioning. Please compile your syslog-ng with --enable-systemd"
                      " flag");
            YYERROR;
#else
            SystemDSyslogSourceDriver *d = systemd_syslog_sd_new(configuration, FALSE);
            systemd_syslog_grammar_set_source_driver(d);
#endif
          }
#line 4763 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 77:
#line 746 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { (yyval.ptr) = last_driver; }
#line 4769 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 82:
#line 760 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { (yyval.ptr) = (yyvsp[-1].ptr); }
#line 4775 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 83:
#line 761 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { (yyval.ptr) = (yyvsp[-1].ptr); }
#line 4781 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 84:
#line 766 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    {
	    AFUnixDestDriver *d = afunix_dd_new_dgram((yyvsp[0].cptr), configuration);

      afunix_grammar_set_dest_driver(d);
	  }
#line 4791 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 85:
#line 771 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { (yyval.ptr) = last_driver; free((yyvsp[-2].cptr)); }
#line 4797 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 86:
#line 776 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    {
	    AFUnixDestDriver *d = afunix_dd_new_stream((yyvsp[0].cptr), configuration);

      afunix_grammar_set_dest_driver(d);
	  }
#line 4807 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 87:
#line 781 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { (yyval.ptr) = last_driver; free((yyvsp[-2].cptr)); }
#line 4813 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 94:
#line 797 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { (yyval.ptr) = (yyvsp[-1].ptr); }
#line 4819 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 95:
#line 798 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { (yyval.ptr) = (yyvsp[-1].ptr); }
#line 4825 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 96:
#line 799 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { (yyval.ptr) = (yyvsp[-1].ptr); }
#line 4831 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 97:
#line 800 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { (yyval.ptr) = (yyvsp[-1].ptr); }
#line 4837 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 98:
#line 805 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    {
	    AFInetDestDriver *d = afinet_dd_new_udp((yyvsp[0].cptr), configuration);

      afinet_grammar_set_dest_driver(d);
	  }
#line 4847 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 99:
#line 810 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { (yyval.ptr) = last_driver; free((yyvsp[-2].cptr)); }
#line 4853 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 100:
#line 815 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    {
	    AFInetDestDriver *d = afinet_dd_new_udp6((yyvsp[0].cptr), configuration);

	    afinet_grammar_set_dest_driver(d);
	  }
#line 4863 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 101:
#line 820 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { (yyval.ptr) = last_driver; free((yyvsp[-2].cptr)); }
#line 4869 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 104:
#line 831 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { afinet_dd_set_localip(last_driver, (yyvsp[-1].cptr)); free((yyvsp[-1].cptr)); }
#line 4875 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 105:
#line 832 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { afinet_dd_set_localport(last_driver, (yyvsp[-1].cptr)); free((yyvsp[-1].cptr)); }
#line 4881 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 106:
#line 833 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { afinet_dd_set_destport(last_driver, (yyvsp[-1].cptr)); free((yyvsp[-1].cptr)); }
#line 4887 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 107:
#line 834 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { afinet_dd_set_destport(last_driver, (yyvsp[-1].cptr)); free((yyvsp[-1].cptr)); }
#line 4893 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 113:
#line 844 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { afinet_dd_set_spoof_source(last_driver, (yyvsp[-1].num)); }
#line 4899 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 114:
#line 849 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    {
	    AFInetDestDriver *d = afinet_dd_new_tcp((yyvsp[0].cptr), configuration);

      afinet_grammar_set_dest_driver(d);
	  }
#line 4909 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 115:
#line 854 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { (yyval.ptr) = last_driver; free((yyvsp[-2].cptr)); }
#line 4915 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 116:
#line 859 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    {
	    AFInetDestDriver *d = afinet_dd_new_tcp6((yyvsp[0].cptr), configuration);

	    afinet_grammar_set_dest_driver(d);
	  }
#line 4925 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 117:
#line 864 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { (yyval.ptr) = last_driver; free((yyvsp[-2].cptr)); }
#line 4931 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 121:
#line 875 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    {
	    last_tls_context = tls_context_new(TM_CLIENT);
	  }
#line 4939 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 122:
#line 879 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    {
	    afinet_dd_set_tls_context(last_driver, last_tls_context);
          }
#line 4947 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 123:
#line 885 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { afsocket_dd_set_keep_alive(last_driver, (yyvsp[-1].num)); }
#line 4953 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 124:
#line 890 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { (yyval.ptr) = (yyvsp[-1].ptr); }
#line 4959 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 125:
#line 894 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    {
            AFInetDestDriver *d = afinet_dd_new_syslog((yyvsp[0].cptr), configuration);

            afinet_grammar_set_dest_driver(d);
	  }
#line 4969 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 126:
#line 899 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { (yyval.ptr) = last_driver; free((yyvsp[-2].cptr)); }
#line 4975 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 131:
#line 914 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { (yyval.ptr) = (yyvsp[-1].ptr); }
#line 4981 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 132:
#line 919 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    {
            AFInetDestDriver *d = afinet_dd_new_network((yyvsp[0].cptr), configuration);

            afinet_grammar_set_dest_driver(d);
	  }
#line 4991 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 133:
#line 924 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { (yyval.ptr) = last_driver; free((yyvsp[-2].cptr)); }
#line 4997 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 139:
#line 939 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { afinet_dd_set_spoof_source(last_driver, (yyvsp[-1].num)); }
#line 5003 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 140:
#line 941 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    {
            last_tls_context = tls_context_new(TM_CLIENT);
          }
#line 5011 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 141:
#line 945 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    {
            afinet_dd_set_tls_context(last_driver, last_tls_context);
          }
#line 5019 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 142:
#line 951 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { transport_mapper_set_transport(last_transport_mapper, (yyvsp[-1].cptr)); free((yyvsp[-1].cptr)); }
#line 5025 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 143:
#line 952 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { transport_mapper_set_transport(last_transport_mapper, "tcp"); }
#line 5031 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 144:
#line 953 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { transport_mapper_set_transport(last_transport_mapper, "udp"); }
#line 5037 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 145:
#line 954 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { transport_mapper_set_transport(last_transport_mapper, "tls"); }
#line 5043 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 146:
#line 955 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { transport_mapper_set_address_family(last_transport_mapper, (yyvsp[-1].num)); }
#line 5049 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 149:
#line 965 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    {
}
#line 5056 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 150:
#line 969 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    {
	    last_tls_context->verify_mode = tls_lookup_verify_mode((yyvsp[-1].cptr));
            free((yyvsp[-1].cptr));
          }
#line 5065 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 151:
#line 974 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    {
	    last_tls_context->key_file = g_strdup((yyvsp[-1].cptr));
            free((yyvsp[-1].cptr));
          }
#line 5074 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 152:
#line 979 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    {
	    last_tls_context->cert_file = g_strdup((yyvsp[-1].cptr));
            free((yyvsp[-1].cptr));
          }
#line 5083 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 153:
#line 984 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    {
	    last_tls_context->ca_dir = g_strdup((yyvsp[-1].cptr));
            free((yyvsp[-1].cptr));
          }
#line 5092 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 154:
#line 989 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    {
	    last_tls_context->crl_dir = g_strdup((yyvsp[-1].cptr));
            free((yyvsp[-1].cptr));
          }
#line 5101 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 155:
#line 994 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    {
            tls_session_set_trusted_fingerprints(last_tls_context, (yyvsp[-1].ptr));
          }
#line 5109 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 156:
#line 998 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    {
            tls_session_set_trusted_dn(last_tls_context, (yyvsp[-1].ptr));
          }
#line 5117 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 157:
#line 1002 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    {
            last_tls_context->cipher_suite = g_strdup((yyvsp[-1].cptr));
            free((yyvsp[-1].cptr));
	  }
#line 5126 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 158:
#line 1007 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    {
            last_tls_context->ssl_options = tls_lookup_options((yyvsp[-1].ptr));
	  }
#line 5134 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 159:
#line 1010 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    {
}
#line 5141 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 160:
#line 1016 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { last_sock_options->so_sndbuf = (yyvsp[-1].num); }
#line 5147 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 161:
#line 1017 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { last_sock_options->so_rcvbuf = (yyvsp[-1].num); }
#line 5153 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 162:
#line 1018 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { last_sock_options->so_broadcast = (yyvsp[-1].num); }
#line 5159 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 163:
#line 1019 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { last_sock_options->so_keepalive = (yyvsp[-1].num); }
#line 5165 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 165:
#line 1024 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { ((SocketOptionsInet *) last_sock_options)->ip_ttl = (yyvsp[-1].num); }
#line 5171 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 166:
#line 1025 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { ((SocketOptionsInet *) last_sock_options)->ip_tos = (yyvsp[-1].num); }
#line 5177 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 167:
#line 1026 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { ((SocketOptionsInet *) last_sock_options)->tcp_keepalive_time = (yyvsp[-1].num); }
#line 5183 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 168:
#line 1027 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { ((SocketOptionsInet *) last_sock_options)->tcp_keepalive_intvl = (yyvsp[-1].num); }
#line 5189 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 169:
#line 1028 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { ((SocketOptionsInet *) last_sock_options)->tcp_keepalive_probes = (yyvsp[-1].num); }
#line 5195 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 170:
#line 1033 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    {
          CHECK_ERROR((yyvsp[0].num) == 4 || (yyvsp[0].num) == 6, (yylsp[0]), "ip-protocol option can only be 4 or 6!");
          if ((yyvsp[0].num) == 4)
            {
              (yyval.num) = AF_INET;
            }
          else
            {
              (yyval.num) = AF_INET6;
            }
        }
#line 5211 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 173:
#line 1273 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { (yyval.num) = 1; }
#line 5217 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 174:
#line 1274 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { (yyval.num) = 0; }
#line 5223 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 175:
#line 1275 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { (yyval.num) = (yyvsp[0].num); }
#line 5229 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 176:
#line 1279 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { (yyval.num) = (yyvsp[0].num); }
#line 5235 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 177:
#line 1280 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { (yyval.num) = 2; }
#line 5241 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 178:
#line 1284 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { (yyval.cptr) = (yyvsp[0].cptr); }
#line 5247 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 179:
#line 1285 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { (yyval.cptr) = strdup(lexer->token_text->str); }
#line 5253 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 180:
#line 1286 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { (yyval.cptr) = strdup(lexer->token_text->str); }
#line 5259 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 181:
#line 1290 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { (yyval.ptr) = g_list_reverse((yyvsp[0].ptr)); }
#line 5265 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 182:
#line 1294 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { (yyval.ptr) = g_list_append((yyvsp[0].ptr), g_strdup((yyvsp[-1].cptr))); free((yyvsp[-1].cptr)); }
#line 5271 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 183:
#line 1295 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { (yyval.ptr) = NULL; }
#line 5277 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 184:
#line 1305 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    {
	    /* return the numeric value of the "level" */
	    int n = syslog_name_lookup_level_by_name((yyvsp[0].cptr));
	    CHECK_ERROR((n != -1), (yylsp[0]), "Unknown priority level\"%s\"", (yyvsp[0].cptr));
	    free((yyvsp[0].cptr));
            (yyval.num) = n;
	  }
#line 5289 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 185:
#line 1316 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    {
            /* return the numeric value of facility */
	    int n = syslog_name_lookup_facility_by_name((yyvsp[0].cptr));
	    CHECK_ERROR((n != -1), (yylsp[0]), "Unknown facility \"%s\"", (yyvsp[0].cptr));
	    free((yyvsp[0].cptr));
	    (yyval.num) = n;
	  }
#line 5301 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 186:
#line 1323 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { (yyval.num) = LOG_SYSLOG; }
#line 5307 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 187:
#line 1341 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { last_source_options->init_window_size = (yyvsp[-1].num); }
#line 5313 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 188:
#line 1342 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { last_source_options->chain_hostnames = (yyvsp[-1].num); }
#line 5319 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 189:
#line 1343 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { last_source_options->keep_hostname = (yyvsp[-1].num); }
#line 5325 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 190:
#line 1344 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { last_source_options->program_override = g_strdup((yyvsp[-1].cptr)); free((yyvsp[-1].cptr)); }
#line 5331 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 191:
#line 1345 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { last_source_options->host_override = g_strdup((yyvsp[-1].cptr)); free((yyvsp[-1].cptr)); }
#line 5337 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 192:
#line 1346 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { gchar *p = strrchr((yyvsp[-1].cptr), ':'); if (p) *p = 0; last_source_options->program_override = g_strdup((yyvsp[-1].cptr)); free((yyvsp[-1].cptr)); }
#line 5343 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 193:
#line 1347 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { last_source_options->keep_timestamp = (yyvsp[-1].num); }
#line 5349 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 194:
#line 1348 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { log_source_options_set_tags(last_source_options, (yyvsp[-1].ptr)); }
#line 5355 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 195:
#line 1349 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { last_host_resolve_options = &last_source_options->host_resolve_options; }
#line 5361 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 198:
#line 1355 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    {
            CHECK_ERROR(log_proto_server_options_set_encoding(last_proto_server_options, (yyvsp[-1].cptr)),
                        (yylsp[-1]),
                        "unknown encoding %s", (yyvsp[-1].cptr));
            free((yyvsp[-1].cptr));
          }
#line 5372 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 199:
#line 1361 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { last_proto_server_options->max_msg_size = (yyvsp[-1].num); }
#line 5378 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 200:
#line 1369 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { last_host_resolve_options->use_fqdn = (yyvsp[-1].num); }
#line 5384 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 201:
#line 1370 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { last_host_resolve_options->use_dns = (yyvsp[-1].num); }
#line 5390 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 202:
#line 1371 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { last_host_resolve_options->use_dns_cache = (yyvsp[-1].num); }
#line 5396 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 203:
#line 1372 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { last_host_resolve_options->normalize_hostnames = (yyvsp[-1].num); }
#line 5402 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 204:
#line 1376 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { last_msg_format_options->recv_time_zone = g_strdup((yyvsp[-1].cptr)); free((yyvsp[-1].cptr)); }
#line 5408 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 205:
#line 1378 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    {
	    if (last_msg_format_options->default_pri == 0xFFFF)
	      last_msg_format_options->default_pri = LOG_USER;
	    last_msg_format_options->default_pri = (last_msg_format_options->default_pri & ~7) | (yyvsp[-1].num);
          }
#line 5418 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 206:
#line 1384 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    {
	    if (last_msg_format_options->default_pri == 0xFFFF)
	      last_msg_format_options->default_pri = LOG_NOTICE;
	    last_msg_format_options->default_pri = (last_msg_format_options->default_pri & 7) | (yyvsp[-1].num);
          }
#line 5428 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 207:
#line 1396 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { last_reader_options->check_hostname = (yyvsp[-1].num); }
#line 5434 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 209:
#line 1398 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { last_reader_options->fetch_limit = (yyvsp[-1].num); }
#line 5440 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 210:
#line 1399 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { last_reader_options->parse_options.format = g_strdup((yyvsp[-1].cptr)); free((yyvsp[-1].cptr)); }
#line 5446 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 211:
#line 1400 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { last_source_options = &last_reader_options->super; }
#line 5452 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 213:
#line 1401 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { last_proto_server_options = &last_reader_options->proto_options.super; }
#line 5458 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 215:
#line 1402 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { last_msg_format_options = &last_reader_options->parse_options; }
#line 5464 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 217:
#line 1406 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { CHECK_ERROR(log_reader_options_process_flag(last_reader_options, (yyvsp[-1].cptr)), (yylsp[-1]), "Unknown flag %s", (yyvsp[-1].cptr)); free((yyvsp[-1].cptr)); }
#line 5470 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 218:
#line 1407 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { log_reader_options_process_flag(last_reader_options, "check-hostname"); }
#line 5476 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 220:
#line 1412 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { log_pipe_set_persist_name(&last_driver->super, g_strdup((yyvsp[-1].cptr))); free((yyvsp[-1].cptr)); }
#line 5482 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 221:
#line 1424 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { ((LogDestDriver *) last_driver)->log_fifo_size = (yyvsp[-1].num); }
#line 5488 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 222:
#line 1425 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { ((LogDestDriver *) last_driver)->throttle = (yyvsp[-1].num); }
#line 5494 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 223:
#line 1427 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    {
            Plugin *p;
            gint context = LL_CONTEXT_INNER_DEST;
            gpointer value;

            p = plugin_find(configuration, context, (yyvsp[0].cptr));
            CHECK_ERROR(p, (yylsp[0]), "%s plugin %s not found", cfg_lexer_lookup_context_name_by_type(context), (yyvsp[0].cptr));

            value = plugin_parse_config(p, configuration, &(yylsp[0]), last_driver);

            free((yyvsp[0].cptr));
            if (!value)
              {
                YYERROR;
              }
            log_driver_add_plugin(last_driver, (LogDriverPlugin *) value);
          }
#line 5516 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 225:
#line 1455 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { last_writer_options->options = (yyvsp[-1].num); }
#line 5522 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 226:
#line 1456 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { last_writer_options->flush_lines = (yyvsp[-1].num); }
#line 5528 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 227:
#line 1457 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { last_writer_options->flush_timeout = (yyvsp[-1].num); }
#line 5534 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 228:
#line 1458 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { last_writer_options->suppress = (yyvsp[-1].num); }
#line 5540 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 229:
#line 1459 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    {
                                                  GError *error = NULL;

                                                  last_writer_options->template = cfg_tree_check_inline_template(&configuration->tree, (yyvsp[-1].cptr), &error);
                                                  CHECK_ERROR_GERROR(last_writer_options->template != NULL, (yylsp[-1]), error, "Error compiling template");
	                                          free((yyvsp[-1].cptr));
	                                        }
#line 5552 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 230:
#line 1466 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { log_writer_options_set_template_escape(last_writer_options, (yyvsp[-1].num)); }
#line 5558 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 231:
#line 1467 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { last_writer_options->padding = (yyvsp[-1].num); }
#line 5564 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 232:
#line 1468 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { last_writer_options->mark_freq = (yyvsp[-1].num); }
#line 5570 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 233:
#line 1469 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { log_writer_options_set_mark_mode(last_writer_options, "internal"); }
#line 5576 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 234:
#line 1471 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    {
	    CHECK_ERROR(cfg_lookup_mark_mode((yyvsp[-1].cptr)) != -1, (yylsp[-1]), "illegal mark mode: %s", (yyvsp[-1].cptr));
            log_writer_options_set_mark_mode(last_writer_options, (yyvsp[-1].cptr));
            free((yyvsp[-1].cptr));
          }
#line 5586 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 235:
#line 1476 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { last_template_options = &last_writer_options->template_options; }
#line 5592 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 237:
#line 1480 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { (yyval.num) = log_writer_options_lookup_flag((yyvsp[-1].cptr)) | (yyvsp[0].num); free((yyvsp[-1].cptr)); }
#line 5598 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 238:
#line 1481 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { (yyval.num) = 0; }
#line 5604 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 239:
#line 1485 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { file_perm_options_set_file_uid(last_file_perm_options, (yyvsp[-1].cptr)); free((yyvsp[-1].cptr)); }
#line 5610 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 240:
#line 1486 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { file_perm_options_dont_change_file_uid(last_file_perm_options); }
#line 5616 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 241:
#line 1487 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { file_perm_options_set_file_gid(last_file_perm_options, (yyvsp[-1].cptr)); free((yyvsp[-1].cptr)); }
#line 5622 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 242:
#line 1488 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { file_perm_options_dont_change_file_gid(last_file_perm_options); }
#line 5628 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 243:
#line 1489 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { file_perm_options_set_file_perm(last_file_perm_options, (yyvsp[-1].num)); }
#line 5634 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 244:
#line 1490 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { file_perm_options_dont_change_file_perm(last_file_perm_options); }
#line 5640 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 245:
#line 1491 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { file_perm_options_set_dir_uid(last_file_perm_options, (yyvsp[-1].cptr)); free((yyvsp[-1].cptr)); }
#line 5646 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 246:
#line 1492 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { file_perm_options_dont_change_dir_uid(last_file_perm_options); }
#line 5652 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 247:
#line 1493 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { file_perm_options_set_dir_gid(last_file_perm_options, (yyvsp[-1].cptr)); free((yyvsp[-1].cptr)); }
#line 5658 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 248:
#line 1494 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { file_perm_options_dont_change_dir_gid(last_file_perm_options); }
#line 5664 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 249:
#line 1495 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { file_perm_options_set_dir_perm(last_file_perm_options, (yyvsp[-1].num)); }
#line 5670 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 250:
#line 1496 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { file_perm_options_dont_change_dir_perm(last_file_perm_options); }
#line 5676 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 251:
#line 1500 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { last_template_options->ts_format = cfg_ts_format_value((yyvsp[-1].cptr)); free((yyvsp[-1].cptr)); }
#line 5682 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 252:
#line 1501 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { last_template_options->frac_digits = (yyvsp[-1].num); }
#line 5688 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 253:
#line 1502 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { last_template_options->time_zone[LTZ_SEND] = g_strdup((yyvsp[-1].cptr)); free((yyvsp[-1].cptr)); }
#line 5694 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 254:
#line 1503 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { last_template_options->time_zone[LTZ_SEND] = g_strdup((yyvsp[-1].cptr)); free((yyvsp[-1].cptr)); }
#line 5700 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 255:
#line 1504 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    { last_template_options->time_zone[LTZ_LOCAL] = g_strdup((yyvsp[-1].cptr)); free((yyvsp[-1].cptr)); }
#line 5706 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;

  case 256:
#line 1506 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1646  */
    {
          gint on_error;

          CHECK_ERROR(log_template_on_error_parse((yyvsp[-1].cptr), &on_error), (yylsp[-1]), "Invalid on-error() setting");
          free((yyvsp[-1].cptr));

          log_template_options_set_on_error(last_template_options, on_error);
        }
#line 5719 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
    break;


#line 5723 "modules/afsocket/afsocket-grammar.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (&yylloc, lexer, instance, arg, YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (&yylloc, lexer, instance, arg, yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc, lexer, instance, arg);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[1] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp, lexer, instance, arg);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (&yylloc, lexer, instance, arg, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc, lexer, instance, arg);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, yylsp, lexer, instance, arg);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 1587 "modules/afsocket/afsocket-grammar.y" /* yacc.c:1906  */

