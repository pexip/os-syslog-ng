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
#line 24 "modules/afprog/afprog-grammar.y" /* yacc.c:316  */

#include "afprog-parser.h"


#line 68 "modules/afprog/afprog-grammar.c" /* yacc.c:316  */

/* Substitute the variable and function names.  */
#define yyparse         afprog_parse
#define yylex           afprog_lex
#define yyerror         afprog_error
#define yydebug         afprog_debug
#define yynerrs         afprog_nerrs


/* Copy the first part of user declarations.  */

#line 80 "modules/afprog/afprog-grammar.c" /* yacc.c:339  */

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
#ifndef YY_AFPROG_MODULES_AFPROG_AFPROG_GRAMMAR_H_INCLUDED
# define YY_AFPROG_MODULES_AFPROG_AFPROG_GRAMMAR_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int afprog_debug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
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
    KW_RETRIES = 10511,
    KW_PROGRAM = 10513,
    KW_KEEP_ALIVE = 10514,
    KW_INHERIT_ENVIRONMENT = 10515
  };
#endif
/* Tokens.  */
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
#define KW_PROGRAM 10513
#define KW_KEEP_ALIVE 10514
#define KW_INHERIT_ENVIRONMENT 10515

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



int afprog_parse (CfgLexer *lexer, LogDriver **instance, gpointer arg);

#endif /* !YY_AFPROG_MODULES_AFPROG_AFPROG_GRAMMAR_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 417 "modules/afprog/afprog-grammar.c" /* yacc.c:358  */
/* Unqualified %code blocks.  */
#line 29 "modules/afprog/afprog-grammar.y" /* yacc.c:359  */


#include "afprog.h"
#include "cfg-parser.h"
#include "afprog-grammar.h"
#include "syslog-names.h"
#include "messages.h"
#include "plugin.h"
#include "cfg-grammar.h"

#include <string.h>

#line 60 "modules/afprog/afprog-grammar.y" /* yacc.c:359  */


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



#line 493 "modules/afprog/afprog-grammar.c" /* yacc.c:359  */

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
#define YYFINAL  8
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   218

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  146
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  35
/* YYNRULES -- Number of rules.  */
#define YYNRULES  90
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  230

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   10515

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     140,   141,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   145,   144,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   142,     2,   143,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      33,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,     2,     2,     2,     2,     2,     2,
      47,    48,    49,    50,    51,     2,     2,     2,     2,     2,
      52,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      53,    54,    55,     2,     2,     2,     2,     2,     2,     2,
      56,    57,     2,     2,     2,     2,     2,     2,     2,     2,
      58,    59,    60,     2,     2,     2,     2,     2,     2,     2,
      61,    62,    63,     2,     2,     2,     2,     2,     2,     2,
      64,    65,    66,     2,     2,     2,     2,     2,     2,     2,
      67,     2,    68,    69,    70,    71,    72,     2,     2,     2,
      73,    74,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      77,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      78,    79,    80,    81,    82,    83,     2,     2,     2,     2,
      84,    85,    86,     2,     2,     2,     2,     2,     2,     2,
      87,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      88,    75,     2,     2,     2,     2,     2,     2,     2,     2,
      89,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      90,    91,    92,     2,     2,     2,     2,     2,     2,     2,
      93,    94,    95,     2,     2,     2,     2,     2,     2,     2,
      96,    97,    98,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      99,   100,    76,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   101,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     102,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     103,   104,   105,   106,   107,   108,   109,   110,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     111,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     112,   113,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     114,   115,     2,     2,     2,     2,     2,     2,     2,     2,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     126,     2,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,     2,   137,   138,   139
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   371,   371,   372,   376,   381,   380,   389,   390,   394,
     395,   399,   404,   403,   412,   413,   417,   418,   419,   420,
     644,   645,   649,   650,   651,   655,   656,   666,   670,   671,
     680,   691,   699,   717,   718,   719,   720,   721,   722,   723,
     724,   725,   725,   726,   730,   737,   745,   746,   747,   748,
     752,   753,   759,   772,   773,   774,   775,   776,   776,   777,
     777,   778,   778,   782,   783,   784,   788,   800,   801,   802,
     820,   831,   832,   833,   834,   835,   842,   843,   844,   845,
     846,   852,   852,   856,   857,   876,   877,   878,   879,   880,
     881
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "LL_CONTEXT_ROOT",
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
  "KW_ADD_PREFIX", "KW_REPLACE_PREFIX", "KW_ON_ERROR", "KW_RETRIES",
  "KW_PROGRAM", "KW_KEEP_ALIVE", "KW_INHERIT_ENVIRONMENT", "'('", "')'",
  "'{'", "'}'", "';'", "':'", "$accept", "start", "source_afprogram",
  "source_afprogram_params", "$@1", "source_afprogram_options",
  "source_afprogram_option", "dest_afprogram", "dest_afprogram_params",
  "$@2", "dest_afprogram_options", "dest_afprogram_option", "string",
  "yesno", "dnsmode", "string_list", "string_list_build", "level_string",
  "facility_string", "source_option", "$@9", "source_proto_option",
  "host_resolve_option", "msg_format_option", "source_reader_option",
  "$@10", "$@11", "$@12", "source_reader_option_flags", "driver_option",
  "dest_driver_option", "dest_writer_option", "$@13",
  "dest_writer_options_flags", "template_option", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256, 10512,     1,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18, 10000, 10001, 10002, 10003, 10004, 10005, 10006, 10007, 10008,
   10009, 10010, 10011, 10060, 10071, 10072, 10073, 10074, 10075, 10076,
   10077, 10078, 10079, 10080, 10081, 10082, 10083, 10090, 10091, 10092,
   10093, 10094, 10100, 10110, 10111, 10112, 10120, 10121, 10130, 10131,
   10132, 10140, 10141, 10142, 10150, 10151, 10152, 10160, 10162, 10163,
   10164, 10165, 10166, 10170, 10171, 10231, 10302, 10190, 10200, 10201,
   10202, 10203, 10204, 10205, 10210, 10211, 10212, 10220, 10230, 10240,
   10250, 10251, 10252, 10260, 10261, 10262, 10270, 10271, 10272, 10300,
   10301, 10323, 10340, 10350, 10351, 10352, 10353, 10354, 10355, 10356,
   10357, 10370, 10380, 10381, 10410, 10411, 10420, 10421, 10422, 10423,
   10424, 10425, 10426, 10427, 10428, 10429, 10500, 10502, 10503, 10504,
   10505, 10506, 10507, 10508, 10509, 10510, 10511, 10513, 10514, 10515,
      40,    41,   123,   125,    59,    58
};
# endif

#define YYPACT_NINF -133

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-133)))

#define YYTABLE_NINF -62

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      11,  -132,  -115,    34,  -105,  -133,   -81,  -133,  -133,   -75,
     -75,  -133,  -133,   -79,  -133,   -73,  -133,  -133,   -20,  -133,
     -39,   -68,   -62,   -55,   -54,   -50,   -47,   -46,   -45,   -44,
     -42,   -36,   -35,  -133,   -34,   -33,  -133,   -20,  -133,  -133,
    -133,   -56,   -32,   -30,   -25,   -24,   -23,  -133,   -39,  -133,
      -6,    26,   -67,     2,     4,     5,     6,   -28,     7,    16,
     -75,   -75,    17,   -75,   -63,   -63,   -63,  -133,     0,     1,
       3,     8,     9,    10,  -133,   -63,    24,   -37,   -75,   -63,
    -133,    12,    13,    14,    15,    18,    19,    20,    21,  -133,
     -17,  -133,    22,    23,  -133,    25,    27,    28,  -133,   -57,
     -40,    29,    30,    31,    32,    33,    36,    37,   -75,    38,
      39,    40,  -133,  -133,  -133,    41,    42,    43,   -75,    46,
     -75,   -75,   -75,   -75,    44,    45,   -37,   -37,    47,    48,
      49,   -63,   -63,   -63,    51,   -75,   -75,   -75,   -75,    35,
      52,    53,    54,  -133,    69,   -75,   -75,   -29,   -75,  -133,
    -133,  -133,  -133,  -133,  -133,  -133,  -133,  -133,  -133,  -133,
    -133,  -133,  -133,  -133,  -133,    50,    55,    56,    57,    58,
      59,  -133,  -133,  -133,  -133,  -133,  -133,  -133,    60,    61,
      62,    63,    64,    65,    66,   -75,    67,  -133,   -63,   -31,
     -63,   -63,    68,    70,    71,  -133,  -133,    72,  -133,    73,
    -133,  -133,  -133,  -133,  -133,  -133,  -133,  -133,  -133,  -133,
    -133,  -133,  -133,  -133,  -133,    74,  -133,  -133,    75,    76,
      77,  -133,  -133,  -133,  -133,  -133,  -133,  -133,  -133,  -133
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     3,     0,     2,     1,     0,
       0,    20,    21,     0,    12,     0,     5,    11,    81,     4,
      57,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    69,     0,     0,    13,    81,    70,    17,
      16,     0,     0,     0,     0,     0,     0,     6,    57,     9,
      41,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    84,     0,     0,     0,     0,     0,    14,     0,     0,
       0,     0,     0,     0,    82,     0,     0,    65,     0,     0,
       7,     0,     0,     0,     0,     0,     0,     0,     0,    58,
       0,    43,     0,     0,    60,     0,     0,     0,    62,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    84,     0,
       0,     0,    22,    23,    24,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    65,    65,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    29,     0,
       0,     0,     0,    42,     0,     0,     0,     0,     0,    78,
      72,    74,    73,    79,    80,    67,    68,    66,    83,    71,
      77,    75,    76,    18,    19,     0,     0,     0,     0,     0,
       0,    53,    55,    64,    63,    54,    56,    10,     0,     0,
       0,     0,     0,     0,     0,    29,     0,    27,     0,     0,
       0,     0,     0,     0,     0,    32,    31,     0,    30,     0,
      85,    86,    87,    88,    89,    90,    34,    35,    39,    33,
      38,    36,    37,    28,    40,     0,    26,    25,     0,     0,
       0,    45,    44,    50,    52,    51,    49,    47,    46,    48
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -133,  -133,  -133,  -133,  -133,    96,  -133,  -133,  -133,  -133,
     108,  -133,    -9,   -58,  -133,  -133,   -38,  -133,  -133,  -133,
    -133,  -133,  -133,  -133,  -133,  -133,  -133,  -133,   -99,   101,
    -133,  -133,  -133,    87,  -133
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     3,     7,    15,    20,    47,    48,     5,    13,    18,
      36,    37,   127,   115,   218,   186,   187,   199,   197,    89,
      90,    94,   143,    98,    49,    50,    51,    52,   128,    38,
      39,    40,    41,   109,    74
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      14,    16,   -59,   103,   195,     4,   -59,   116,   117,    68,
      69,    42,    95,   126,    21,     1,     2,   124,    22,    23,
      24,   130,     6,    70,    25,    71,    72,   173,   174,    43,
     216,   139,    96,    97,     8,     9,   140,   141,    44,   142,
     -61,    81,    11,    82,    45,    12,    83,    26,   104,   112,
     113,   107,   108,    27,   111,   114,    28,    29,    30,    10,
     -61,   -61,    17,    84,    85,    86,    87,    92,    19,   129,
      28,    93,    53,   178,   179,   180,    31,    32,    54,    73,
      11,   112,   113,    12,   149,    55,    56,   114,    11,    11,
      57,    12,    12,    58,    59,    60,    61,    33,    62,   108,
      46,   150,    -8,    88,    63,    64,    65,    66,    75,   165,
      76,   167,   168,   169,   170,    77,    78,    79,    34,    35,
      99,   -15,   100,   101,   102,   105,   182,   183,   184,   185,
     215,   217,   219,   220,   106,   110,   193,   194,   196,   198,
     118,   119,   125,   120,    80,    67,     0,   213,   121,   122,
     123,    91,   131,   132,   133,   134,     0,     0,   135,   136,
     137,   138,   144,   145,   166,   146,     0,   147,   148,   181,
     151,   152,   153,   154,   155,   188,   185,   156,   157,   159,
     160,   161,   162,   163,   164,   171,   172,   192,   175,   176,
     177,   200,   189,   190,   191,   158,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   214,   221,
       0,   222,   223,   224,   225,   226,   227,   228,   229
};

static const yytype_int16 yycheck[] =
{
       9,    10,    41,    31,    33,   137,    45,    65,    66,    65,
      66,    50,    79,    50,    34,     4,     5,    75,    38,    39,
      40,    79,   137,    79,    44,    81,    82,   126,   127,    68,
      61,    48,    99,   100,     0,   140,    53,    54,    77,    56,
      79,    47,   117,    49,    83,   120,    52,    67,    57,   112,
     113,    60,    61,    73,    63,   118,    76,    77,    78,   140,
      99,   100,   141,    69,    70,    71,    72,    41,   141,    78,
      76,    45,   140,   131,   132,   133,    96,    97,   140,   135,
     117,   112,   113,   120,   141,   140,   140,   118,   117,   117,
     140,   120,   120,   140,   140,   140,   140,   117,   140,   108,
     139,   141,   141,   109,   140,   140,   140,   140,   140,   118,
     140,   120,   121,   122,   123,   140,   140,   140,   138,   139,
     118,   141,   118,   118,   118,   118,   135,   136,   137,   138,
     188,   189,   190,   191,   118,   118,   145,   146,   147,   148,
     140,   140,   118,   140,    48,    37,    -1,   185,   140,   140,
     140,    50,   140,   140,   140,   140,    -1,    -1,   140,   140,
     140,   140,   140,   140,   118,   140,    -1,   140,   140,   118,
     141,   141,   141,   141,   141,   140,   185,   141,   141,   141,
     141,   141,   141,   141,   141,   141,   141,   118,   141,   141,
     141,   141,   140,   140,   140,   108,   141,   141,   141,   141,
     141,   141,   141,   141,   141,   141,   141,   141,   141,   141,
      -1,   141,   141,   141,   141,   141,   141,   141,   141
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,     5,   147,   137,   153,   137,   148,     0,   140,
     140,   117,   120,   154,   158,   149,   158,   141,   155,   141,
     150,    34,    38,    39,    40,    44,    67,    73,    76,    77,
      78,    96,    97,   117,   138,   139,   156,   157,   175,   176,
     177,   178,    50,    68,    77,    83,   139,   151,   152,   170,
     171,   172,   173,   140,   140,   140,   140,   140,   140,   140,
     140,   140,   140,   140,   140,   140,   140,   156,    65,    66,
      79,    81,    82,   135,   180,   140,   140,   140,   140,   140,
     151,    47,    49,    52,    69,    70,    71,    72,   109,   165,
     166,   175,    41,    45,   167,    79,    99,   100,   169,   118,
     118,   118,   118,    31,   158,   118,   118,   158,   158,   179,
     118,   158,   112,   113,   118,   159,   159,   159,   140,   140,
     140,   140,   140,   140,   159,   118,    50,   158,   174,   158,
     159,   140,   140,   140,   140,   140,   140,   140,   140,    48,
      53,    54,    56,   168,   140,   140,   140,   140,   140,   141,
     141,   141,   141,   141,   141,   141,   141,   141,   179,   141,
     141,   141,   141,   141,   141,   158,   118,   158,   158,   158,
     158,   141,   141,   174,   174,   141,   141,   141,   159,   159,
     159,   118,   158,   158,   158,   158,   161,   162,   140,   140,
     140,   140,   118,   158,   158,    33,   158,   164,   158,   163,
     141,   141,   141,   141,   141,   141,   141,   141,   141,   141,
     141,   141,   141,   162,   141,   159,    61,   159,   160,   159,
     159,   141,   141,   141,   141,   141,   141,   141,   141,   141
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   146,   147,   147,   148,   150,   149,   151,   151,   152,
     152,   153,   155,   154,   156,   156,   157,   157,   157,   157,
     158,   158,   159,   159,   159,   160,   160,   161,   162,   162,
     163,   164,   164,   165,   165,   165,   165,   165,   165,   165,
     165,   166,   165,   165,   167,   167,   168,   168,   168,   168,
     169,   169,   169,   170,   170,   170,   170,   171,   170,   172,
     170,   173,   170,   174,   174,   174,   175,   176,   176,   176,
     176,   177,   177,   177,   177,   177,   177,   177,   177,   177,
     177,   178,   177,   179,   179,   180,   180,   180,   180,   180,
     180
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     2,     4,     0,     3,     2,     0,     1,
       4,     4,     0,     3,     2,     0,     1,     1,     4,     4,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     0,
       1,     1,     1,     4,     4,     4,     4,     4,     4,     4,
       4,     0,     2,     1,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     0,     2,     0,
       2,     0,     2,     2,     2,     0,     4,     4,     4,     1,
       1,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     0,     2,     2,     0,     4,     4,     4,     4,     4,
       4
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
          case 117: /* LL_IDENTIFIER  */
#line 294 "modules/afprog/afprog-grammar.y" /* yacc.c:1257  */
      { free(((*yyvaluep).cptr)); }
#line 2608 "modules/afprog/afprog-grammar.c" /* yacc.c:1257  */
        break;

    case 120: /* LL_STRING  */
#line 294 "modules/afprog/afprog-grammar.y" /* yacc.c:1257  */
      { free(((*yyvaluep).cptr)); }
#line 2614 "modules/afprog/afprog-grammar.c" /* yacc.c:1257  */
        break;

    case 122: /* LL_BLOCK  */
#line 294 "modules/afprog/afprog-grammar.y" /* yacc.c:1257  */
      { free(((*yyvaluep).cptr)); }
#line 2620 "modules/afprog/afprog-grammar.c" /* yacc.c:1257  */
        break;

    case 158: /* string  */
#line 294 "modules/afprog/afprog-grammar.y" /* yacc.c:1257  */
      { free(((*yyvaluep).cptr)); }
#line 2626 "modules/afprog/afprog-grammar.c" /* yacc.c:1257  */
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
#line 371 "modules/afprog/afprog-grammar.y" /* yacc.c:1646  */
    { YYACCEPT; }
#line 2920 "modules/afprog/afprog-grammar.c" /* yacc.c:1646  */
    break;

  case 3:
#line 372 "modules/afprog/afprog-grammar.y" /* yacc.c:1646  */
    { YYACCEPT; }
#line 2926 "modules/afprog/afprog-grammar.c" /* yacc.c:1646  */
    break;

  case 4:
#line 376 "modules/afprog/afprog-grammar.y" /* yacc.c:1646  */
    { (yyval.ptr) = (yyvsp[-1].ptr); }
#line 2932 "modules/afprog/afprog-grammar.c" /* yacc.c:1646  */
    break;

  case 5:
#line 381 "modules/afprog/afprog-grammar.y" /* yacc.c:1646  */
    {
	    last_driver = *instance = afprogram_sd_new((yyvsp[0].cptr), configuration);
	    last_reader_options = &((AFProgramSourceDriver *) last_driver)->reader_options;
	  }
#line 2941 "modules/afprog/afprog-grammar.c" /* yacc.c:1646  */
    break;

  case 6:
#line 385 "modules/afprog/afprog-grammar.y" /* yacc.c:1646  */
    { (yyval.ptr) = last_driver; free((yyvsp[-2].cptr)); }
#line 2947 "modules/afprog/afprog-grammar.c" /* yacc.c:1646  */
    break;

  case 10:
#line 395 "modules/afprog/afprog-grammar.y" /* yacc.c:1646  */
    { afprogram_set_inherit_environment(&((AFProgramSourceDriver *)last_driver)->process_info, (yyvsp[-1].num)); }
#line 2953 "modules/afprog/afprog-grammar.c" /* yacc.c:1646  */
    break;

  case 11:
#line 399 "modules/afprog/afprog-grammar.y" /* yacc.c:1646  */
    { (yyval.ptr) = (yyvsp[-1].ptr); }
#line 2959 "modules/afprog/afprog-grammar.c" /* yacc.c:1646  */
    break;

  case 12:
#line 404 "modules/afprog/afprog-grammar.y" /* yacc.c:1646  */
    {
	    last_driver = *instance = afprogram_dd_new((yyvsp[0].cptr), configuration);
	    last_writer_options = &((AFProgramDestDriver *) last_driver)->writer_options;
	  }
#line 2968 "modules/afprog/afprog-grammar.c" /* yacc.c:1646  */
    break;

  case 13:
#line 408 "modules/afprog/afprog-grammar.y" /* yacc.c:1646  */
    { (yyval.ptr) = last_driver; free((yyvsp[-2].cptr)); }
#line 2974 "modules/afprog/afprog-grammar.c" /* yacc.c:1646  */
    break;

  case 18:
#line 419 "modules/afprog/afprog-grammar.y" /* yacc.c:1646  */
    { afprogram_dd_set_keep_alive((AFProgramDestDriver *)last_driver, (yyvsp[-1].num)); }
#line 2980 "modules/afprog/afprog-grammar.c" /* yacc.c:1646  */
    break;

  case 19:
#line 420 "modules/afprog/afprog-grammar.y" /* yacc.c:1646  */
    { afprogram_set_inherit_environment(&((AFProgramDestDriver *)last_driver)->process_info, (yyvsp[-1].num)); }
#line 2986 "modules/afprog/afprog-grammar.c" /* yacc.c:1646  */
    break;

  case 22:
#line 649 "modules/afprog/afprog-grammar.y" /* yacc.c:1646  */
    { (yyval.num) = 1; }
#line 2992 "modules/afprog/afprog-grammar.c" /* yacc.c:1646  */
    break;

  case 23:
#line 650 "modules/afprog/afprog-grammar.y" /* yacc.c:1646  */
    { (yyval.num) = 0; }
#line 2998 "modules/afprog/afprog-grammar.c" /* yacc.c:1646  */
    break;

  case 24:
#line 651 "modules/afprog/afprog-grammar.y" /* yacc.c:1646  */
    { (yyval.num) = (yyvsp[0].num); }
#line 3004 "modules/afprog/afprog-grammar.c" /* yacc.c:1646  */
    break;

  case 25:
#line 655 "modules/afprog/afprog-grammar.y" /* yacc.c:1646  */
    { (yyval.num) = (yyvsp[0].num); }
#line 3010 "modules/afprog/afprog-grammar.c" /* yacc.c:1646  */
    break;

  case 26:
#line 656 "modules/afprog/afprog-grammar.y" /* yacc.c:1646  */
    { (yyval.num) = 2; }
#line 3016 "modules/afprog/afprog-grammar.c" /* yacc.c:1646  */
    break;

  case 27:
#line 666 "modules/afprog/afprog-grammar.y" /* yacc.c:1646  */
    { (yyval.ptr) = g_list_reverse((yyvsp[0].ptr)); }
#line 3022 "modules/afprog/afprog-grammar.c" /* yacc.c:1646  */
    break;

  case 28:
#line 670 "modules/afprog/afprog-grammar.y" /* yacc.c:1646  */
    { (yyval.ptr) = g_list_append((yyvsp[0].ptr), g_strdup((yyvsp[-1].cptr))); free((yyvsp[-1].cptr)); }
#line 3028 "modules/afprog/afprog-grammar.c" /* yacc.c:1646  */
    break;

  case 29:
#line 671 "modules/afprog/afprog-grammar.y" /* yacc.c:1646  */
    { (yyval.ptr) = NULL; }
#line 3034 "modules/afprog/afprog-grammar.c" /* yacc.c:1646  */
    break;

  case 30:
#line 681 "modules/afprog/afprog-grammar.y" /* yacc.c:1646  */
    {
	    /* return the numeric value of the "level" */
	    int n = syslog_name_lookup_level_by_name((yyvsp[0].cptr));
	    CHECK_ERROR((n != -1), (yylsp[0]), "Unknown priority level\"%s\"", (yyvsp[0].cptr));
	    free((yyvsp[0].cptr));
            (yyval.num) = n;
	  }
#line 3046 "modules/afprog/afprog-grammar.c" /* yacc.c:1646  */
    break;

  case 31:
#line 692 "modules/afprog/afprog-grammar.y" /* yacc.c:1646  */
    {
            /* return the numeric value of facility */
	    int n = syslog_name_lookup_facility_by_name((yyvsp[0].cptr));
	    CHECK_ERROR((n != -1), (yylsp[0]), "Unknown facility \"%s\"", (yyvsp[0].cptr));
	    free((yyvsp[0].cptr));
	    (yyval.num) = n;
	  }
#line 3058 "modules/afprog/afprog-grammar.c" /* yacc.c:1646  */
    break;

  case 32:
#line 699 "modules/afprog/afprog-grammar.y" /* yacc.c:1646  */
    { (yyval.num) = LOG_SYSLOG; }
#line 3064 "modules/afprog/afprog-grammar.c" /* yacc.c:1646  */
    break;

  case 33:
#line 717 "modules/afprog/afprog-grammar.y" /* yacc.c:1646  */
    { last_source_options->init_window_size = (yyvsp[-1].num); }
#line 3070 "modules/afprog/afprog-grammar.c" /* yacc.c:1646  */
    break;

  case 34:
#line 718 "modules/afprog/afprog-grammar.y" /* yacc.c:1646  */
    { last_source_options->chain_hostnames = (yyvsp[-1].num); }
#line 3076 "modules/afprog/afprog-grammar.c" /* yacc.c:1646  */
    break;

  case 35:
#line 719 "modules/afprog/afprog-grammar.y" /* yacc.c:1646  */
    { last_source_options->keep_hostname = (yyvsp[-1].num); }
#line 3082 "modules/afprog/afprog-grammar.c" /* yacc.c:1646  */
    break;

  case 36:
#line 720 "modules/afprog/afprog-grammar.y" /* yacc.c:1646  */
    { last_source_options->program_override = g_strdup((yyvsp[-1].cptr)); free((yyvsp[-1].cptr)); }
#line 3088 "modules/afprog/afprog-grammar.c" /* yacc.c:1646  */
    break;

  case 37:
#line 721 "modules/afprog/afprog-grammar.y" /* yacc.c:1646  */
    { last_source_options->host_override = g_strdup((yyvsp[-1].cptr)); free((yyvsp[-1].cptr)); }
#line 3094 "modules/afprog/afprog-grammar.c" /* yacc.c:1646  */
    break;

  case 38:
#line 722 "modules/afprog/afprog-grammar.y" /* yacc.c:1646  */
    { gchar *p = strrchr((yyvsp[-1].cptr), ':'); if (p) *p = 0; last_source_options->program_override = g_strdup((yyvsp[-1].cptr)); free((yyvsp[-1].cptr)); }
#line 3100 "modules/afprog/afprog-grammar.c" /* yacc.c:1646  */
    break;

  case 39:
#line 723 "modules/afprog/afprog-grammar.y" /* yacc.c:1646  */
    { last_source_options->keep_timestamp = (yyvsp[-1].num); }
#line 3106 "modules/afprog/afprog-grammar.c" /* yacc.c:1646  */
    break;

  case 40:
#line 724 "modules/afprog/afprog-grammar.y" /* yacc.c:1646  */
    { log_source_options_set_tags(last_source_options, (yyvsp[-1].ptr)); }
#line 3112 "modules/afprog/afprog-grammar.c" /* yacc.c:1646  */
    break;

  case 41:
#line 725 "modules/afprog/afprog-grammar.y" /* yacc.c:1646  */
    { last_host_resolve_options = &last_source_options->host_resolve_options; }
#line 3118 "modules/afprog/afprog-grammar.c" /* yacc.c:1646  */
    break;

  case 44:
#line 731 "modules/afprog/afprog-grammar.y" /* yacc.c:1646  */
    {
            CHECK_ERROR(log_proto_server_options_set_encoding(last_proto_server_options, (yyvsp[-1].cptr)),
                        (yylsp[-1]),
                        "unknown encoding %s", (yyvsp[-1].cptr));
            free((yyvsp[-1].cptr));
          }
#line 3129 "modules/afprog/afprog-grammar.c" /* yacc.c:1646  */
    break;

  case 45:
#line 737 "modules/afprog/afprog-grammar.y" /* yacc.c:1646  */
    { last_proto_server_options->max_msg_size = (yyvsp[-1].num); }
#line 3135 "modules/afprog/afprog-grammar.c" /* yacc.c:1646  */
    break;

  case 46:
#line 745 "modules/afprog/afprog-grammar.y" /* yacc.c:1646  */
    { last_host_resolve_options->use_fqdn = (yyvsp[-1].num); }
#line 3141 "modules/afprog/afprog-grammar.c" /* yacc.c:1646  */
    break;

  case 47:
#line 746 "modules/afprog/afprog-grammar.y" /* yacc.c:1646  */
    { last_host_resolve_options->use_dns = (yyvsp[-1].num); }
#line 3147 "modules/afprog/afprog-grammar.c" /* yacc.c:1646  */
    break;

  case 48:
#line 747 "modules/afprog/afprog-grammar.y" /* yacc.c:1646  */
    { last_host_resolve_options->use_dns_cache = (yyvsp[-1].num); }
#line 3153 "modules/afprog/afprog-grammar.c" /* yacc.c:1646  */
    break;

  case 49:
#line 748 "modules/afprog/afprog-grammar.y" /* yacc.c:1646  */
    { last_host_resolve_options->normalize_hostnames = (yyvsp[-1].num); }
#line 3159 "modules/afprog/afprog-grammar.c" /* yacc.c:1646  */
    break;

  case 50:
#line 752 "modules/afprog/afprog-grammar.y" /* yacc.c:1646  */
    { last_msg_format_options->recv_time_zone = g_strdup((yyvsp[-1].cptr)); free((yyvsp[-1].cptr)); }
#line 3165 "modules/afprog/afprog-grammar.c" /* yacc.c:1646  */
    break;

  case 51:
#line 754 "modules/afprog/afprog-grammar.y" /* yacc.c:1646  */
    {
	    if (last_msg_format_options->default_pri == 0xFFFF)
	      last_msg_format_options->default_pri = LOG_USER;
	    last_msg_format_options->default_pri = (last_msg_format_options->default_pri & ~7) | (yyvsp[-1].num);
          }
#line 3175 "modules/afprog/afprog-grammar.c" /* yacc.c:1646  */
    break;

  case 52:
#line 760 "modules/afprog/afprog-grammar.y" /* yacc.c:1646  */
    {
	    if (last_msg_format_options->default_pri == 0xFFFF)
	      last_msg_format_options->default_pri = LOG_NOTICE;
	    last_msg_format_options->default_pri = (last_msg_format_options->default_pri & 7) | (yyvsp[-1].num);
          }
#line 3185 "modules/afprog/afprog-grammar.c" /* yacc.c:1646  */
    break;

  case 53:
#line 772 "modules/afprog/afprog-grammar.y" /* yacc.c:1646  */
    { last_reader_options->check_hostname = (yyvsp[-1].num); }
#line 3191 "modules/afprog/afprog-grammar.c" /* yacc.c:1646  */
    break;

  case 55:
#line 774 "modules/afprog/afprog-grammar.y" /* yacc.c:1646  */
    { last_reader_options->fetch_limit = (yyvsp[-1].num); }
#line 3197 "modules/afprog/afprog-grammar.c" /* yacc.c:1646  */
    break;

  case 56:
#line 775 "modules/afprog/afprog-grammar.y" /* yacc.c:1646  */
    { last_reader_options->parse_options.format = g_strdup((yyvsp[-1].cptr)); free((yyvsp[-1].cptr)); }
#line 3203 "modules/afprog/afprog-grammar.c" /* yacc.c:1646  */
    break;

  case 57:
#line 776 "modules/afprog/afprog-grammar.y" /* yacc.c:1646  */
    { last_source_options = &last_reader_options->super; }
#line 3209 "modules/afprog/afprog-grammar.c" /* yacc.c:1646  */
    break;

  case 59:
#line 777 "modules/afprog/afprog-grammar.y" /* yacc.c:1646  */
    { last_proto_server_options = &last_reader_options->proto_options.super; }
#line 3215 "modules/afprog/afprog-grammar.c" /* yacc.c:1646  */
    break;

  case 61:
#line 778 "modules/afprog/afprog-grammar.y" /* yacc.c:1646  */
    { last_msg_format_options = &last_reader_options->parse_options; }
#line 3221 "modules/afprog/afprog-grammar.c" /* yacc.c:1646  */
    break;

  case 63:
#line 782 "modules/afprog/afprog-grammar.y" /* yacc.c:1646  */
    { CHECK_ERROR(log_reader_options_process_flag(last_reader_options, (yyvsp[-1].cptr)), (yylsp[-1]), "Unknown flag %s", (yyvsp[-1].cptr)); free((yyvsp[-1].cptr)); }
#line 3227 "modules/afprog/afprog-grammar.c" /* yacc.c:1646  */
    break;

  case 64:
#line 783 "modules/afprog/afprog-grammar.y" /* yacc.c:1646  */
    { log_reader_options_process_flag(last_reader_options, "check-hostname"); }
#line 3233 "modules/afprog/afprog-grammar.c" /* yacc.c:1646  */
    break;

  case 66:
#line 788 "modules/afprog/afprog-grammar.y" /* yacc.c:1646  */
    { log_pipe_set_persist_name(&last_driver->super, g_strdup((yyvsp[-1].cptr))); free((yyvsp[-1].cptr)); }
#line 3239 "modules/afprog/afprog-grammar.c" /* yacc.c:1646  */
    break;

  case 67:
#line 800 "modules/afprog/afprog-grammar.y" /* yacc.c:1646  */
    { ((LogDestDriver *) last_driver)->log_fifo_size = (yyvsp[-1].num); }
#line 3245 "modules/afprog/afprog-grammar.c" /* yacc.c:1646  */
    break;

  case 68:
#line 801 "modules/afprog/afprog-grammar.y" /* yacc.c:1646  */
    { ((LogDestDriver *) last_driver)->throttle = (yyvsp[-1].num); }
#line 3251 "modules/afprog/afprog-grammar.c" /* yacc.c:1646  */
    break;

  case 69:
#line 803 "modules/afprog/afprog-grammar.y" /* yacc.c:1646  */
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
#line 3273 "modules/afprog/afprog-grammar.c" /* yacc.c:1646  */
    break;

  case 71:
#line 831 "modules/afprog/afprog-grammar.y" /* yacc.c:1646  */
    { last_writer_options->options = (yyvsp[-1].num); }
#line 3279 "modules/afprog/afprog-grammar.c" /* yacc.c:1646  */
    break;

  case 72:
#line 832 "modules/afprog/afprog-grammar.y" /* yacc.c:1646  */
    { last_writer_options->flush_lines = (yyvsp[-1].num); }
#line 3285 "modules/afprog/afprog-grammar.c" /* yacc.c:1646  */
    break;

  case 73:
#line 833 "modules/afprog/afprog-grammar.y" /* yacc.c:1646  */
    { last_writer_options->flush_timeout = (yyvsp[-1].num); }
#line 3291 "modules/afprog/afprog-grammar.c" /* yacc.c:1646  */
    break;

  case 74:
#line 834 "modules/afprog/afprog-grammar.y" /* yacc.c:1646  */
    { last_writer_options->suppress = (yyvsp[-1].num); }
#line 3297 "modules/afprog/afprog-grammar.c" /* yacc.c:1646  */
    break;

  case 75:
#line 835 "modules/afprog/afprog-grammar.y" /* yacc.c:1646  */
    {
                                                  GError *error = NULL;

                                                  last_writer_options->template = cfg_tree_check_inline_template(&configuration->tree, (yyvsp[-1].cptr), &error);
                                                  CHECK_ERROR_GERROR(last_writer_options->template != NULL, (yylsp[-1]), error, "Error compiling template");
	                                          free((yyvsp[-1].cptr));
	                                        }
#line 3309 "modules/afprog/afprog-grammar.c" /* yacc.c:1646  */
    break;

  case 76:
#line 842 "modules/afprog/afprog-grammar.y" /* yacc.c:1646  */
    { log_writer_options_set_template_escape(last_writer_options, (yyvsp[-1].num)); }
#line 3315 "modules/afprog/afprog-grammar.c" /* yacc.c:1646  */
    break;

  case 77:
#line 843 "modules/afprog/afprog-grammar.y" /* yacc.c:1646  */
    { last_writer_options->padding = (yyvsp[-1].num); }
#line 3321 "modules/afprog/afprog-grammar.c" /* yacc.c:1646  */
    break;

  case 78:
#line 844 "modules/afprog/afprog-grammar.y" /* yacc.c:1646  */
    { last_writer_options->mark_freq = (yyvsp[-1].num); }
#line 3327 "modules/afprog/afprog-grammar.c" /* yacc.c:1646  */
    break;

  case 79:
#line 845 "modules/afprog/afprog-grammar.y" /* yacc.c:1646  */
    { log_writer_options_set_mark_mode(last_writer_options, "internal"); }
#line 3333 "modules/afprog/afprog-grammar.c" /* yacc.c:1646  */
    break;

  case 80:
#line 847 "modules/afprog/afprog-grammar.y" /* yacc.c:1646  */
    {
	    CHECK_ERROR(cfg_lookup_mark_mode((yyvsp[-1].cptr)) != -1, (yylsp[-1]), "illegal mark mode: %s", (yyvsp[-1].cptr));
            log_writer_options_set_mark_mode(last_writer_options, (yyvsp[-1].cptr));
            free((yyvsp[-1].cptr));
          }
#line 3343 "modules/afprog/afprog-grammar.c" /* yacc.c:1646  */
    break;

  case 81:
#line 852 "modules/afprog/afprog-grammar.y" /* yacc.c:1646  */
    { last_template_options = &last_writer_options->template_options; }
#line 3349 "modules/afprog/afprog-grammar.c" /* yacc.c:1646  */
    break;

  case 83:
#line 856 "modules/afprog/afprog-grammar.y" /* yacc.c:1646  */
    { (yyval.num) = log_writer_options_lookup_flag((yyvsp[-1].cptr)) | (yyvsp[0].num); free((yyvsp[-1].cptr)); }
#line 3355 "modules/afprog/afprog-grammar.c" /* yacc.c:1646  */
    break;

  case 84:
#line 857 "modules/afprog/afprog-grammar.y" /* yacc.c:1646  */
    { (yyval.num) = 0; }
#line 3361 "modules/afprog/afprog-grammar.c" /* yacc.c:1646  */
    break;

  case 85:
#line 876 "modules/afprog/afprog-grammar.y" /* yacc.c:1646  */
    { last_template_options->ts_format = cfg_ts_format_value((yyvsp[-1].cptr)); free((yyvsp[-1].cptr)); }
#line 3367 "modules/afprog/afprog-grammar.c" /* yacc.c:1646  */
    break;

  case 86:
#line 877 "modules/afprog/afprog-grammar.y" /* yacc.c:1646  */
    { last_template_options->frac_digits = (yyvsp[-1].num); }
#line 3373 "modules/afprog/afprog-grammar.c" /* yacc.c:1646  */
    break;

  case 87:
#line 878 "modules/afprog/afprog-grammar.y" /* yacc.c:1646  */
    { last_template_options->time_zone[LTZ_SEND] = g_strdup((yyvsp[-1].cptr)); free((yyvsp[-1].cptr)); }
#line 3379 "modules/afprog/afprog-grammar.c" /* yacc.c:1646  */
    break;

  case 88:
#line 879 "modules/afprog/afprog-grammar.y" /* yacc.c:1646  */
    { last_template_options->time_zone[LTZ_SEND] = g_strdup((yyvsp[-1].cptr)); free((yyvsp[-1].cptr)); }
#line 3385 "modules/afprog/afprog-grammar.c" /* yacc.c:1646  */
    break;

  case 89:
#line 880 "modules/afprog/afprog-grammar.y" /* yacc.c:1646  */
    { last_template_options->time_zone[LTZ_LOCAL] = g_strdup((yyvsp[-1].cptr)); free((yyvsp[-1].cptr)); }
#line 3391 "modules/afprog/afprog-grammar.c" /* yacc.c:1646  */
    break;

  case 90:
#line 882 "modules/afprog/afprog-grammar.y" /* yacc.c:1646  */
    {
          gint on_error;

          CHECK_ERROR(log_template_on_error_parse((yyvsp[-1].cptr), &on_error), (yylsp[-1]), "Invalid on-error() setting");
          free((yyvsp[-1].cptr));

          log_template_options_set_on_error(last_template_options, on_error);
        }
#line 3404 "modules/afprog/afprog-grammar.c" /* yacc.c:1646  */
    break;


#line 3408 "modules/afprog/afprog-grammar.c" /* yacc.c:1646  */
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
#line 963 "modules/afprog/afprog-grammar.y" /* yacc.c:1906  */

