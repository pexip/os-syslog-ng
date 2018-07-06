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

#include "cfg-lexer.h"
#include "cfg-lexer-subst.h"
#include "cfg-lex.h"
#include "cfg-grammar.h"
#include "block-ref-parser.h"
#include "pragma-parser.h"
#include "messages.h"
#include "pathutils.h"

#include <string.h>
#include <glob.h>
#include <sys/stat.h>

/*
 * A token block is a series of tokens to be injected into the tokens
 * fetched by the lexer.  It is assumed to be filled and then depleted, the
 * two operations cannot be intermixed.
 */
struct _CfgTokenBlock
{
  gint pos;
  GArray *tokens;
};

/**
 * CfgBlockGenerator:
 *
 * This class describes a block generator, e.g. a function callback
 * that returns a configuration snippet in a given context. Each
 * user-defined "block" results in a generator to be registered, but
 * theoretically this mechanism can be used to write plugins that
 * generate syslog-ng configuration on the fly, based on system
 * settings for example.
 **/
struct _CfgBlockGenerator
{
  gint context;
  gchar *name;
  CfgBlockGeneratorFunc generator;
  gpointer generator_data;
  GDestroyNotify generator_data_free;
};

/**
 * CfgLexerContext:
 *
 * This object tells the lexer in which context it is operating right
 * now. The context influences the way the lexer works, for example in
 * LL_CONTEXT_BLOCK_DEF/REF all keyword resolutions are disabled.
 *
 * A textual description is also associated with the current context
 * in order to give better error messages.
 **/
typedef struct _CfgLexerContext
{
  gint type;
  CfgLexerKeyword *keywords;
  gchar desc[0];
} CfgLexerContext;

/*
 * cfg_lexer_push_context:
 *
 * This function can be used to push a lexer context to the stack. The top
 * of the stack determines how an error is reported and can also influence
 * the lexer.
 */
void
cfg_lexer_push_context(CfgLexer *self, gint type, CfgLexerKeyword *keywords, const gchar *desc)
{
  CfgLexerContext *context;

  context = g_malloc(sizeof(CfgLexerContext) + strlen(desc) + 1);
  context->type = type ? type : cfg_lexer_get_context_type(self);
  context->keywords = keywords;
  memcpy(&context->desc, desc, strlen(desc) + 1);
  self->context_stack = g_list_prepend(self->context_stack, context);
}

/*
 * cfg_lexer_pop_context:
 *
 * Pop the topmost item off the stack.
 */
void
cfg_lexer_pop_context(CfgLexer *self)
{
  if (self->context_stack)
    {
      g_free((gchar *) self->context_stack->data);
      self->context_stack = g_list_delete_link(self->context_stack, self->context_stack);
    }
}

/*
 * cfg_lexer_get_context_type:
 *
 * Get the current context type (one of LL_CONTEXT_* values).
 */
gint
cfg_lexer_get_context_type(CfgLexer *self)
{
  GList *l;

  l = self->context_stack;
  if (l)
    return ((CfgLexerContext *) l->data)->type;
  return 0;
}

/*
 * cfg_lexer_get_context_description:
 *
 * Get the description of the current context.
 */
const gchar *
cfg_lexer_get_context_description(CfgLexer *self)
{
  GList *l;

  l = self->context_stack;
  if (l)
    return ((CfgLexerContext *) l->data)->desc;
  return "configuration";
}

gchar *
cfg_lexer_subst_args(CfgArgs *globals, CfgArgs *defs, CfgArgs *args, const gchar *input, gssize input_length, gsize *output_length, GError **error)
{
  CfgLexerSubst *subst = cfg_lexer_subst_new(cfg_args_ref(globals), cfg_args_ref(defs), cfg_args_ref(args));
  gchar *result;

  result = cfg_lexer_subst_invoke(subst, input, input_length, output_length, error);
  cfg_lexer_subst_free(subst);
  return result;
}

int
cfg_lexer_lookup_keyword(CfgLexer *self, YYSTYPE *yylval, YYLTYPE *yylloc, const char *token)
{
  GList *l;

  l = self->context_stack;
  while (l)
    {
      CfgLexerContext *context = ((CfgLexerContext *) l->data);
      CfgLexerKeyword *keywords = context->keywords;

      if (keywords)
        {
          int i, j;

          for (i = 0; keywords[i].kw_name; i++)
            {
              if (strcmp(keywords[i].kw_name, CFG_KEYWORD_STOP) == 0)
                {
                  yylval->type = LL_IDENTIFIER;
                  yylval->cptr = strdup(token);
                  return LL_IDENTIFIER;
                }

              for (j = 0; token[j] && keywords[i].kw_name[j]; j++)
                {
                  if (token[j] == '-' || token[j] == '_')
                    {
                      if (keywords[i].kw_name[j] != '_')
                        break;
                    }
                  else if (token[j] != keywords[i].kw_name[j])
                    break;
                }
              if (token[j] == 0 && keywords[i].kw_name[j] == 0)
                {
                  /* match */
                  switch (keywords[i].kw_status)
                    {
                    case KWS_OBSOLETE:
                      msg_warning("WARNING: Your configuration file uses an obsoleted keyword, please update your configuration",
                                  evt_tag_str("keyword", keywords[i].kw_name),
                                  evt_tag_str("change", keywords[i].kw_explain));
                      break;
                    default:
                      break;
                    }
                  keywords[i].kw_status = KWS_NORMAL;
                  yylval->type = LL_TOKEN;
                  yylval->token = keywords[i].kw_token;
                  return keywords[i].kw_token;
                }
            }
        }
      l = l->next;
    }
  yylval->type = LL_IDENTIFIER;
  yylval->cptr = strdup(token);
  return LL_IDENTIFIER;
}

gboolean
cfg_lexer_start_next_include(CfgLexer *self)
{
  CfgIncludeLevel *level = &self->include_stack[self->include_depth];
  gchar *filename;
  gboolean buffer_processed = FALSE;

  if (self->include_depth == 0)
    {
      return FALSE;
    }

  if (level->yybuf)
    {
      msg_debug("Finishing include",
                evt_tag_str((level->include_type == CFGI_FILE ? "filename" : "content"), level->name),
                evt_tag_int("depth", self->include_depth));
      buffer_processed = TRUE;
    }

  /* reset the include state, should also handle initial invocations, in which case everything is NULL */
  if (level->yybuf)
    _cfg_lexer__delete_buffer(level->yybuf, self->state);

  if (level->include_type == CFGI_FILE)
    {
      if (level->file.include_file)
        {
          fclose(level->file.include_file);
        }
    }

  if ((level->include_type == CFGI_BUFFER && buffer_processed) ||
      (level->include_type == CFGI_FILE && !level->file.files))
    {
      /* we finished with an include statement that included a series of
       * files (e.g.  directory include). */
      g_free(level->name);

      if (level->include_type == CFGI_BUFFER)
        g_free(level->buffer.content);

      memset(level, 0, sizeof(*level));

      self->include_depth--;
      _cfg_lexer__switch_to_buffer(self->include_stack[self->include_depth].yybuf, self->state);

      return TRUE;
    }

  /* now populate "level" with the new include information */
  if (level->include_type == CFGI_BUFFER)
    {
      level->yybuf = _cfg_lexer__scan_buffer(level->buffer.content, level->buffer.content_length, self->state);
    }
  else if (level->include_type == CFGI_FILE)
    {
      FILE *include_file;

      filename = (gchar *) level->file.files->data;
      level->file.files = g_slist_delete_link(level->file.files, level->file.files);

      include_file = fopen(filename, "r");
      if (!include_file)
        {
          msg_error("Error opening include file",
                    evt_tag_str("filename", filename),
                    evt_tag_int("depth", self->include_depth));
          g_free(filename);
          return FALSE;
        }
      msg_debug("Starting to read include file",
                evt_tag_str("filename", filename),
                evt_tag_int("depth", self->include_depth));
      g_free(level->name);
      level->name = filename;

      level->file.include_file = include_file;
      level->yybuf = _cfg_lexer__create_buffer(level->file.include_file, YY_BUF_SIZE, self->state);
    }
  else
    {
      g_assert_not_reached();
    }

  level->lloc.first_line = level->lloc.last_line = 1;
  level->lloc.first_column = level->lloc.last_column = 1;
  level->lloc.level = level;

  _cfg_lexer__switch_to_buffer(level->yybuf, self->state);
  return TRUE;
}

static gboolean
cfg_lexer_include_file_simple(CfgLexer *self, const gchar *filename)
{
  CfgIncludeLevel *level;
  struct stat st;

  if (stat(filename, &st) < 0)
    {
      return FALSE;
    }

  self->include_depth++;
  level = &self->include_stack[self->include_depth];
  level->include_type = CFGI_FILE;
  if (S_ISDIR(st.st_mode))
    {
      GDir *dir;
      GError *error = NULL;
      const gchar *entry;

      dir = g_dir_open(filename, 0, &error);
      if (!dir)
        {
          msg_error("Error opening directory for reading",
                evt_tag_str("filename", filename),
                evt_tag_str("error", error->message));
          goto drop_level;
        }
      while ((entry = g_dir_read_name(dir)))
        {
          const gchar *p;
          if (entry[0] == '.')
            {
              msg_debug("Skipping include file, it cannot begin with .",
                        evt_tag_str("filename", entry));
              continue;
            }
          for (p = entry; *p; p++)
            {
              if (!((*p >= 'a' && *p <= 'z') ||
                   (*p >= 'A' && *p <= 'Z') ||
                   (*p >= '0' && *p <= '9') ||
                   (*p == '_') || (*p == '-') || (*p == '.')))
                {
                  msg_debug("Skipping include file, does not match pattern [\\-_a-zA-Z0-9]+",
                            evt_tag_str("filename", entry));
                  p = NULL;
                  break;
                }
            }
          if (p)
            {
              gchar *full_filename = g_build_filename(filename, entry, NULL);
              if (stat(full_filename, &st) < 0 || S_ISDIR(st.st_mode))
                {
                  msg_debug("Skipping include file as it is a directory",
                            evt_tag_str("filename", entry));
                  g_free(full_filename);
                  continue;
                }
              level->file.files = g_slist_insert_sorted(level->file.files, full_filename, (GCompareFunc) strcmp);
              msg_debug("Adding include file",
                        evt_tag_str("filename", entry),
                        evt_tag_int("depth", self->include_depth));
            }
        }
      g_dir_close(dir);
      if (!level->file.files)
        {
          /* no include files in the specified directory */
          msg_debug("No files in this include directory",
                    evt_tag_str("dir", filename));
          self->include_depth--;
          return TRUE;
        }
    }
  else
    {
      g_assert(level->file.files == NULL);
      level->file.files = g_slist_prepend(level->file.files, g_strdup(filename));
    }
  return cfg_lexer_start_next_include(self);
 drop_level:
  g_slist_foreach(level->file.files, (GFunc) g_free, NULL);
  g_slist_free(level->file.files);
  level->file.files = NULL;

  return FALSE;
}

static int
_cfg_lexer_glob_err (const char *p, gint e)
{
  if (e != ENOENT)
    {
      msg_debug ("Error processing path for inclusion",
                 evt_tag_str("path", p),
                 evt_tag_errno("errno", e));
      return -1;
    }
  return 0;
}

#ifndef GLOB_NOMAGIC
#define GLOB_NOMAGIC 0

int
__glob_pattern_p (const char *pattern)
{
  register const char *p;
  int open = 0;

  for (p = pattern; *p != '\0'; ++p)
    switch (*p)
      {
      case '?':
      case '*':
        return 1;

      case '\\':
        if (p[1] != '\0')
          ++p;
        break;

      case '[':
        open = 1;
        break;

      case ']':
        if (open)
          return 1;
        break;
      }

  return 0;
}
#else
#define SYSLOG_NG_HAVE_GLOB_NOMAGIC 1
#endif

static gboolean
cfg_lexer_include_file_add(CfgLexer *self, const gchar *fn)
{
  CfgIncludeLevel *level;

  level = &self->include_stack[self->include_depth];
  level->include_type = CFGI_FILE;

  level->file.files = g_slist_insert_sorted(level->file.files,
                                            strdup(fn),
                                            (GCompareFunc) strcmp);

  msg_debug("Adding include file",
            evt_tag_str("filename", fn),
            evt_tag_int("depth", self->include_depth));

  return TRUE;
}

static gboolean
cfg_lexer_include_file_glob_at(CfgLexer *self, const gchar *pattern)
{
  glob_t globbuf;
  size_t i;
  int r;

  r = glob(pattern, GLOB_NOMAGIC, _cfg_lexer_glob_err, &globbuf);

  if (r != 0)
    {
      globfree(&globbuf);
      if (r == GLOB_NOMATCH)
        {
#ifndef SYSLOG_NG_HAVE_GLOB_NOMAGIC
          if (!__glob_pattern_p (pattern))
            {
              return cfg_lexer_include_file_add(self, pattern);
            }
#endif
          return FALSE;
        }
      return TRUE;
    }

  for (i = 0; i < globbuf.gl_pathc; i++)
    {
      cfg_lexer_include_file_add(self, globbuf.gl_pathv[i]);
    }

  globfree(&globbuf);

  return TRUE;
}

static gboolean
cfg_lexer_include_file_glob(CfgLexer *self, const gchar *filename_)
{
  const gchar *path = cfg_args_get(self->globals, "include-path");
  gboolean process = FALSE;

  self->include_depth++;

  if (filename_[0] == '/' || !path)
    process = cfg_lexer_include_file_glob_at(self, filename_);
  else
    {
      gchar **dirs;
      gchar *cf;
      gint i = 0;

      dirs = g_strsplit(path, G_SEARCHPATH_SEPARATOR_S, 0);
      while (dirs && dirs[i])
        {
          cf = g_build_filename(dirs[i], filename_, NULL);
          process |= cfg_lexer_include_file_glob_at(self, cf);
          g_free(cf);
          i++;
        }
      g_strfreev(dirs);
    }
  if (process)
    {
      return cfg_lexer_start_next_include(self);
    }
  else
    {
      self->include_depth--;
      return TRUE;
    }
}

gboolean
cfg_lexer_include_file(CfgLexer *self, const gchar *filename_)
{
  struct stat st;
  gchar *filename;

  if (self->include_depth >= MAX_INCLUDE_DEPTH - 1)
    {
      msg_error("Include file depth is too deep, increase MAX_INCLUDE_DEPTH and recompile",
                evt_tag_str("filename", filename_),
                evt_tag_int("depth", self->include_depth));
      return FALSE;
    }

  filename = find_file_in_path(cfg_args_get(self->globals, "include-path"), filename_, G_FILE_TEST_EXISTS);
  if (!filename || stat(filename, &st) < 0)
    {
      if (cfg_lexer_include_file_glob(self, filename_))
        return TRUE;

      msg_error("Include file/directory not found",
                evt_tag_str("filename", filename_),
                evt_tag_str("include-path", cfg_args_get(self->globals, "include-path")),
                evt_tag_errno("error", errno));
      return FALSE;
    }
  else
    {
      gboolean result;

      result = cfg_lexer_include_file_simple(self, filename);
      g_free(filename);
      return result;
    }
}

gboolean
cfg_lexer_include_buffer_without_backtick_substitution(CfgLexer *self, const gchar *name, const gchar *buffer, gsize length)
{
  CfgIncludeLevel *level;
  gchar *lexer_buffer;
  gsize lexer_buffer_len;
  
  g_assert(length >= 0);

  if (self->include_depth >= MAX_INCLUDE_DEPTH - 1)
    {
      msg_error("Include file depth is too deep, increase MAX_INCLUDE_DEPTH and recompile",
                evt_tag_str("buffer", name),
                evt_tag_int("depth", self->include_depth));
      return FALSE;
    }

  /* lex requires two NUL characters at the end of the input */
  lexer_buffer_len = length + 2;
  lexer_buffer = g_malloc(lexer_buffer_len);
  memcpy(lexer_buffer, buffer, length);
  lexer_buffer[length] = 0;
  lexer_buffer[length + 1] = 0;

  self->include_depth++;
  level = &self->include_stack[self->include_depth];

  level->include_type = CFGI_BUFFER;
  level->buffer.content = lexer_buffer;
  level->buffer.content_length = lexer_buffer_len;
  level->name = g_strdup(name);

  return cfg_lexer_start_next_include(self);
}

/* NOTE: if length is negative, it indicates zero-terminated buffer and
 * length should be determined based on that */
gboolean
cfg_lexer_include_buffer(CfgLexer *self, const gchar *name, const gchar *buffer, gssize length)
{
  gchar *substituted_buffer;
  gsize substituted_length = 0;
  GError *error = NULL;
  gboolean result = FALSE;

  substituted_buffer = cfg_lexer_subst_args(self->globals, NULL, NULL, buffer, length, &substituted_length, &error);
  if (!substituted_buffer)
    {
      msg_error("Error resolving backtick references in block or buffer",
                evt_tag_str("buffer", name),
                evt_tag_str("error", error->message));
      g_clear_error(&error);
      return FALSE;
    }

  result = cfg_lexer_include_buffer_without_backtick_substitution(self, name, substituted_buffer, substituted_length);
  g_free(substituted_buffer);
  return result;
}

void
cfg_lexer_inject_token_block(CfgLexer *self, CfgTokenBlock *block)
{
  self->token_blocks = g_list_append(self->token_blocks, block);
}

static CfgBlockGenerator *
cfg_lexer_find_generator(CfgLexer *self, gint context, const gchar *name)
{
  GList *l;

  for (l = self->generators; l; l = l->next)
    {
      CfgBlockGenerator *gen = (CfgBlockGenerator *) l->data;

      if ((gen->context == 0 || gen->context == context) && strcmp(gen->name, name) == 0)
        {
          return gen;
        }
    }
  return NULL;
}

gboolean
cfg_lexer_register_block_generator(CfgLexer *self, gint context, const gchar *name, CfgBlockGeneratorFunc generator, gpointer generator_data, GDestroyNotify generator_data_free)
{
  CfgBlockGenerator *gen;
  gboolean res = FALSE;

  gen = cfg_lexer_find_generator(self, context, name);
  if (gen)
    {
      gen->generator_data_free(gen->generator_data);
      g_free(gen->name);
    }
  else
    {
      gen = g_new0(CfgBlockGenerator, 1);
      self->generators = g_list_append(self->generators, gen);
      res = TRUE;
    }

  gen->context = context;
  gen->name = g_strdup(name);
  gen->generator = generator;
  gen->generator_data = generator_data;
  gen->generator_data_free = generator_data_free;
  return res;
}

static gboolean
cfg_lexer_generate_block(CfgLexer *self, gint context, const gchar *name, CfgBlockGenerator *gen, CfgArgs *args)
{
  return gen->generator(self, context, name, args, gen->generator_data);
}

static YYSTYPE
cfg_lexer_copy_token(const YYSTYPE *original)
{
  YYSTYPE dest;
  int type = original->type;
  dest.type = type;

  if (type == LL_TOKEN)
    {
      dest.token = original->token;
    }
  else if (type == LL_IDENTIFIER ||
          type == LL_STRING ||
          type == LL_BLOCK)
    {
      dest.cptr = strdup(original->cptr);
    }
  else if (type == LL_NUMBER)
    {
      dest.num = original->num;
    }
  else if (type == LL_FLOAT)
    {
      dest.fnum = original->fnum;
    }

  return dest;
}

void
cfg_lexer_unput_token(CfgLexer *self, YYSTYPE *yylval)
{
  CfgTokenBlock *block;

  block = cfg_token_block_new();
  cfg_token_block_add_token(block, yylval);
  cfg_lexer_inject_token_block(self, block);
}

/*
 * NOTE: the caller is expected to manage the YYSTYPE instance itself (as
 * this is the way it is defined by the lexer), this function only frees its
 * contents.
 */
void
cfg_lexer_free_token(YYSTYPE *token)
{
  if (token->type == LL_STRING || token->type == LL_IDENTIFIER || token->type == LL_BLOCK)
    free(token->cptr);
}

static int
_invoke__cfg_lexer_lex(CfgLexer *self, YYSTYPE *yylval, YYLTYPE *yylloc)
{
  if (setjmp(self->fatal_error))
    {
      YYLTYPE *cur_lloc = &self->include_stack[self->include_depth].lloc;

      *yylloc = *cur_lloc;
      return LL_ERROR;
    }
  return _cfg_lexer_lex(yylval, yylloc, self->state);
}

int
cfg_lexer_lex(CfgLexer *self, YYSTYPE *yylval, YYLTYPE *yylloc)
{
  CfgBlockGenerator *gen;
  CfgTokenBlock *block;
  YYSTYPE *token;
  gint tok;
  gboolean injected;

 relex:

  injected = FALSE;
  while (self->token_blocks)
    {
      block = self->token_blocks->data;
      token = cfg_token_block_get_token(block);

      if (token)
        {
          *yylval = *token;
          *yylloc = self->include_stack[self->include_depth].lloc;
          tok = token->type;
          if (token->type == LL_TOKEN)
            {
              tok = token->token;
              injected = TRUE;
            }

          goto exit;
        }
      else
        {
          self->token_blocks = g_list_delete_link(self->token_blocks, self->token_blocks);
          cfg_token_block_free(block);
        }
    }

  if (cfg_lexer_get_context_type(self) == LL_CONTEXT_BLOCK_CONTENT)
    cfg_lexer_start_block_state(self, "{}");
  else if (cfg_lexer_get_context_type(self) == LL_CONTEXT_BLOCK_ARG)
    cfg_lexer_start_block_state(self, "()");

  yylval->type = 0;

  g_string_truncate(self->token_text, 0);
  g_string_truncate(self->token_pretext, 0);

  tok = _invoke__cfg_lexer_lex(self, yylval, yylloc);
  if (yylval->type == 0)
    yylval->type = tok;

  if (self->preprocess_output)
    g_string_append_printf(self->preprocess_output, "%s", self->token_pretext->str);
 exit:

  if (self->ignore_pragma)
    {
      /* only process @pragma/@include tokens in case pragma allowed is set */
      ;
    }
  else if (tok == LL_PRAGMA)
    {
      gpointer dummy;

      if (self->preprocess_output)
        g_string_append_printf(self->preprocess_output, "@");
      if (!cfg_parser_parse(&pragma_parser, self, &dummy, NULL))
        {
          return LL_ERROR;
        }
      goto relex;
    }
  else if (tok == KW_INCLUDE && cfg_lexer_get_context_type(self) != LL_CONTEXT_PRAGMA)
    {
      gchar *include_file;

      self->preprocess_suppress_tokens++;
      tok = cfg_lexer_lex(self, yylval, yylloc);
      if (tok != LL_STRING && tok != LL_IDENTIFIER)
        {
          self->preprocess_suppress_tokens--;
          return LL_ERROR;
        }

      include_file = g_strdup(yylval->cptr);
      free(yylval->cptr);

      tok = cfg_lexer_lex(self, yylval, yylloc);
      if (tok != ';')
        {
          self->preprocess_suppress_tokens--;
          return LL_ERROR;
        }

      if (!cfg_lexer_include_file(self, include_file))
        {
          self->preprocess_suppress_tokens--;
          return LL_ERROR;
        }
      self->preprocess_suppress_tokens--;
      goto relex;
    }
  else if (tok == LL_IDENTIFIER && (gen = cfg_lexer_find_generator(self, cfg_lexer_get_context_type(self), yylval->cptr)))
    {
      CfgArgs *args;

      self->preprocess_suppress_tokens++;
      if (cfg_parser_parse(&block_ref_parser, self, (gpointer *) &args, NULL))
        {
          gboolean success;

          self->preprocess_suppress_tokens--;
          success = cfg_lexer_generate_block(self, cfg_lexer_get_context_type(self), yylval->cptr, gen, args);
          cfg_args_unref(args);
          if (success)
            {
              goto relex;
            }
        }
      else
        {
          self->preprocess_suppress_tokens--;
        }
      return LL_ERROR;
    }
  else if (configuration->user_version == 0 && configuration->parsed_version != 0)
    {
      cfg_set_version(configuration, configuration->parsed_version);
    }
  else if (cfg_lexer_get_context_type(self) != LL_CONTEXT_PRAGMA && !self->non_pragma_seen)
    {
      /* first non-pragma token */

      if (configuration->user_version == 0 && configuration->parsed_version == 0)
        {
          /* no version selected yet, and we have a non-pragma token, this
           * means that the configuration is meant for syslog-ng 2.1 */
          msg_warning("WARNING: Configuration file has no version number, assuming syslog-ng 2.1 format. Please add @version: maj.min to the beginning of the file to indicate this explicitly");
          cfg_set_version(configuration, 0x0201);
        }
      cfg_load_candidate_modules(configuration);
      self->non_pragma_seen = TRUE;
    }

  if (!injected)
    {
      if (self->preprocess_suppress_tokens == 0 && self->preprocess_output)
        {
          g_string_append_printf(self->preprocess_output, "%s", self->token_text->str);
        }
    }
  return tok;
}

static void
cfg_lexer_init(CfgLexer *self)
{
  self->globals = cfg_args_new();
  CfgIncludeLevel *level;

  _cfg_lexer_lex_init_extra(self, &self->state);
  self->string_buffer = g_string_sized_new(32);
  self->token_text = g_string_sized_new(32);
  self->token_pretext = g_string_sized_new(32);

  level = &self->include_stack[0];
  level->lloc.first_line = level->lloc.last_line = 1;
  level->lloc.first_column = level->lloc.last_column = 1;
  level->lloc.level = level;
}

CfgLexer *
cfg_lexer_new(FILE *file, const gchar *filename, GString *preprocess_output)
{
  CfgLexer *self;
  CfgIncludeLevel *level;

  self = g_new0(CfgLexer, 1);
  cfg_lexer_init(self);
  self->preprocess_output = preprocess_output;

  level = &self->include_stack[0];
  level->include_type = CFGI_FILE;
  level->name = g_strdup(filename);
  level->yybuf = _cfg_lexer__create_buffer(file, YY_BUF_SIZE, self->state);
  _cfg_lexer__switch_to_buffer(level->yybuf, self->state);

  return self;
}

CfgLexer *
cfg_lexer_new_buffer(const gchar *buffer, gsize length)
{
  CfgLexer *self;
  CfgIncludeLevel *level;

  self = g_new0(CfgLexer, 1);
  cfg_lexer_init(self);
  self->ignore_pragma = TRUE;

  level = &self->include_stack[0];
  level->include_type = CFGI_BUFFER;
  level->buffer.content = g_malloc(length + 2);
  memcpy(level->buffer.content, buffer, length);
  level->buffer.content[length] = 0;
  level->buffer.content[length + 1] = 0;
  level->buffer.content_length = length + 2;
  level->name = g_strdup("<string>");
  level->yybuf = _cfg_lexer__scan_buffer(level->buffer.content, level->buffer.content_length, self->state);
  _cfg_lexer__switch_to_buffer(level->yybuf, self->state);

  return self;
}

void
cfg_lexer_free(CfgLexer *self)
{
  gint i;

  for (i = 0; i <= self->include_depth; i++)
    {
      CfgIncludeLevel *level = &self->include_stack[i];

      g_free(level->name);
      if (level->yybuf)
        _cfg_lexer__delete_buffer(level->yybuf, self->state);

      if (level->include_type == CFGI_FILE)
        {
          if (level->file.include_file)
            fclose(level->file.include_file);
          g_slist_foreach(level->file.files, (GFunc) g_free, NULL);
          g_slist_free(level->file.files);
        }
      else if (level->include_type == CFGI_BUFFER)
        {
          g_free(level->buffer.content);
        }
    }
  self->include_depth = 0;
  _cfg_lexer_lex_destroy(self->state);
  g_string_free(self->string_buffer, TRUE);
  if (self->token_text)
    g_string_free(self->token_text, TRUE);
  if (self->token_pretext)
    g_string_free(self->token_pretext, TRUE);

  while (self->context_stack)
    cfg_lexer_pop_context(self);
  while (self->generators)
    {
      CfgBlockGenerator *gen = self->generators->data;

      if (gen->generator_data && gen->generator_data_free)
        gen->generator_data_free(gen->generator_data);
      g_free(gen->name);
      g_free(gen);
      self->generators = g_list_delete_link(self->generators, self->generators);
    }
  cfg_args_unref(self->globals);
  g_list_foreach(self->token_blocks, (GFunc) cfg_token_block_free, NULL);
  g_list_free(self->token_blocks);
  g_free(self);
}

static const gchar *lexer_contexts[] =
{
  [LL_CONTEXT_ROOT] = "root",
  [LL_CONTEXT_DESTINATION] = "destination",
  [LL_CONTEXT_SOURCE] = "source",
  [LL_CONTEXT_PARSER] = "parser",
  [LL_CONTEXT_REWRITE] = "rewrite",
  [LL_CONTEXT_FILTER] = "filter",
  [LL_CONTEXT_LOG] = "log",
  [LL_CONTEXT_BLOCK_DEF] = "block-def",
  [LL_CONTEXT_BLOCK_REF] = "block-ref",
  [LL_CONTEXT_BLOCK_CONTENT] = "block-content",
  [LL_CONTEXT_PRAGMA] = "pragma",
  [LL_CONTEXT_FORMAT] = "format",
  [LL_CONTEXT_TEMPLATE_FUNC] = "template-func",
  [LL_CONTEXT_INNER_DEST] = "inner-dest",
  [LL_CONTEXT_INNER_SRC] = "inner-src",
  [LL_CONTEXT_CLIENT_PROTO] = "client-proto",
  [LL_CONTEXT_SERVER_PROTO] = "server-proto",
};

gint
cfg_lexer_lookup_context_type_by_name(const gchar *name)
{
  gint i;

  for (i = 0; i < G_N_ELEMENTS(lexer_contexts); i++)
    {
      if (lexer_contexts[i] && strcmp(lexer_contexts[i], name) == 0)
        return i;
    }
  return 0;
}

const gchar *
cfg_lexer_lookup_context_name_by_type(gint type)
{
  g_assert(type < G_N_ELEMENTS(lexer_contexts));
  return lexer_contexts[type];
}

/* token blocks */

void
cfg_token_block_add_and_consume_token(CfgTokenBlock *self, YYSTYPE *token)
{
  g_assert(self->pos == 0);
  g_array_append_val(self->tokens, *token);
}

void
cfg_token_block_add_token(CfgTokenBlock *self, YYSTYPE *token)
{
  YYSTYPE copied_token = cfg_lexer_copy_token(token);
  cfg_token_block_add_and_consume_token(self, &copied_token);
}

YYSTYPE *
cfg_token_block_get_token(CfgTokenBlock *self)
{
  if (self->pos < self->tokens->len)
    {
      YYSTYPE *result;

      result = &g_array_index(self->tokens, YYSTYPE, self->pos);
      self->pos++;
      return result;
    }
  return NULL;
}

CfgTokenBlock *
cfg_token_block_new()
{
  CfgTokenBlock *self = g_new0(CfgTokenBlock, 1);

  self->tokens = g_array_new(FALSE, TRUE, sizeof(YYSTYPE));
  return self;
}

void
cfg_token_block_free(CfgTokenBlock *self)
{
  if (self->pos < self->tokens->len)
    {
      for (gint i = self->pos; i < self->tokens->len; i++)
        {
          YYSTYPE *token = &g_array_index(self->tokens, YYSTYPE, i);

          cfg_lexer_free_token(token);
        }
    }

  g_array_free(self->tokens, TRUE);
  g_free(self);
}

/* user defined blocks */

/*
 * This class encapsulates a configuration block that the user defined
 * via the configuration file. It behaves like a macro, e.g. when
 * referenced the content of the block is expanded.
 *
 * Each block is identified by its name and the context (source,
 * destination, etc.) where it is meant to be used.
 *
 * A block has a set of name-value pairs to allow expansion to be
 * parameterized. The set of allowed NV pairs is defined at block
 * definition time
 */
struct _CfgBlock
{
  gchar *content;
  CfgArgs *arg_defs;
};

static void
_resolve_unknown_blockargs_as_varargs(gpointer key, gpointer value, gpointer user_data)
{
  CfgArgs *defs = ((gpointer *) user_data)[0];
  GString *varargs = ((gpointer *) user_data)[1];

  if (cfg_args_get(defs, key) == NULL)
    {
      g_string_append_printf(varargs, "%s(%s) ", (gchar *)key, (gchar *)value);
    }
}

static void
_fill_varargs(CfgBlock *block, CfgArgs *args)
{
  GString *varargs = g_string_new("");
  gpointer user_data[] = { block->arg_defs, varargs };

  cfg_args_foreach(args, _resolve_unknown_blockargs_as_varargs, user_data);
  cfg_args_set(args, "__VARARGS__", varargs->str);
  g_string_free(varargs, TRUE);
}

/*
 * cfg_block_generate:
 *
 * This is a CfgBlockGeneratorFunc, which takes a CfgBlock defined by
 * the user, substitutes backtick values and generates input tokens
 * for the lexer.
 */
gboolean
cfg_block_generate(CfgLexer *lexer, gint context, const gchar *name, CfgArgs *args, gpointer user_data)
{
  CfgBlock *block = (CfgBlock *) user_data;
  gchar *value;
  gchar buf[256];
  gsize length;
  GError *error = NULL;
  gboolean result;

  g_snprintf(buf, sizeof(buf), "%s block %s", cfg_lexer_lookup_context_name_by_type(context), name);
  _fill_varargs(block, args);

  value = cfg_lexer_subst_args(lexer->globals, block->arg_defs, args, block->content, -1, &length, &error);

  if (!value)
    {
      msg_warning("Syntax error while resolving backtick references in block",
                  evt_tag_str("context", cfg_lexer_lookup_context_name_by_type(context)),
                  evt_tag_str("block", name),
                  evt_tag_str("error", error->message));
      g_clear_error(&error);
      return FALSE;
    }

  result = cfg_lexer_include_buffer_without_backtick_substitution(lexer, buf, value, length);
  g_free(value);
  return result;
}

/*
 * Construct a user defined block.
 */
CfgBlock *
cfg_block_new(const gchar *content, CfgArgs *arg_defs)
{
  CfgBlock *self = g_new0(CfgBlock, 1);

  self->content = g_strdup(content);
  self->arg_defs = arg_defs;
  return self;
}

/*
 * Free a user defined block.
 */
void
cfg_block_free(CfgBlock *self)
{
  g_free(self->content);
  cfg_args_unref(self->arg_defs);
  g_free(self);
}

GQuark
cfg_lexer_error_quark(void)
{
  return g_quark_from_static_string("cfg-lexer-error-quark");
}
