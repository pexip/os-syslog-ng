/*
 * Copyright (c) 2002-2014 Balabit
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
  
#include "cfg.h"
#include "module-config.h"
#include "cfg-tree.h"
#include "messages.h"
#include "template/templates.h"
#include "userdb.h"
#include "logmsg/logmsg.h"
#include "dnscache.h"
#include "serialize.h"
#include "plugin.h"
#include "cfg-parser.h"
#include "stats/stats-registry.h"
#include "logproto/logproto-builtins.h"
#include "reloc.h"
#include "hostname.h"
#include "rcptid.h"
#include "resolved-configurable-paths.h"

#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iv_work.h>

/* PersistConfig */

struct _PersistConfig
{
  GHashTable *keys;
};

typedef struct _PersistConfigEntry
{
  gpointer value;
  GDestroyNotify destroy;
} PersistConfigEntry;

static void
persist_config_entry_free(PersistConfigEntry *self)
{
  if (self->destroy)
    {
      self->destroy(self->value);
    }
  g_free(self);
}

PersistConfig *
persist_config_new(void)
{
  PersistConfig *self = g_new0(PersistConfig, 1);

  self->keys = g_hash_table_new_full(g_str_hash, g_str_equal, (GDestroyNotify) g_free, (GDestroyNotify) persist_config_entry_free);
  return self;
}

void
persist_config_free(PersistConfig *self)
{
  g_hash_table_destroy(self->keys);
  g_free(self);
}

gint
cfg_ts_format_value(gchar *format)
{
  if (strcmp(format, "rfc3164") == 0 || strcmp(format, "bsd") == 0)
    return TS_FMT_BSD;
  else if (strcmp(format, "rfc3339") == 0 || strcmp(format, "iso") == 0)
    return TS_FMT_ISO;
  else if (strcmp(format, "full") == 0)
    return TS_FMT_FULL;
  else if (strcmp(format, "unix") == 0 || strcmp(format, "utc") == 0)
    return TS_FMT_UNIX;
  else
    {
      msg_error("Invalid ts_format() value",
                evt_tag_str("value", format));
      return TS_FMT_BSD;
    }
}

void
cfg_bad_hostname_set(GlobalConfig *self, gchar *bad_hostname_re)
{
  if (self->bad_hostname_re)
    g_free(self->bad_hostname_re);
  self->bad_hostname_re = g_strdup(bad_hostname_re);  
}

gint
cfg_lookup_mark_mode(gchar *mark_mode)
{
  if (!strcmp(mark_mode, "internal"))
    return MM_INTERNAL;
  if (!strcmp(mark_mode, "dst_idle") || !strcmp(mark_mode, "dst-idle"))
    return MM_DST_IDLE;
  if (!strcmp(mark_mode, "host_idle") || !strcmp(mark_mode, "host-idle"))
    return MM_HOST_IDLE;
  if (!strcmp(mark_mode, "periodical"))
    return MM_PERIODICAL;
  if (!strcmp(mark_mode, "none"))
    return MM_NONE;
  if (!strcmp(mark_mode, "global"))
    return MM_GLOBAL;

  return -1;
}

void
cfg_set_mark_mode(GlobalConfig *self, gchar *mark_mode)
{
  self->mark_mode = cfg_lookup_mark_mode(mark_mode);
}

static void
_invoke_module_init(gchar *key, ModuleConfig *mc, gpointer *args)
{
  GlobalConfig *cfg = (GlobalConfig *) args[0];
  gboolean *result = (gboolean *) args[1];

  if (!module_config_init(mc, cfg))
    *result = FALSE;
}

static void
_invoke_module_deinit(gchar *key, ModuleConfig *mc, gpointer user_data)
{
  GlobalConfig *cfg = (GlobalConfig *) user_data;

  module_config_deinit(mc, cfg);
}

static gboolean
cfg_init_modules(GlobalConfig *cfg)
{
  gboolean result = TRUE;
  gpointer args[] = { cfg, &result };
  g_hash_table_foreach(cfg->module_config, (GHFunc) _invoke_module_init, args);

  return result;
}

static void
cfg_deinit_modules(GlobalConfig *cfg)
{
  g_hash_table_foreach(cfg->module_config, (GHFunc) _invoke_module_deinit, cfg);
}

gboolean
cfg_init(GlobalConfig *cfg)
{
  gint regerr;
  
  if (cfg->file_template_name && !(cfg->file_template = cfg_tree_lookup_template(&cfg->tree, cfg->file_template_name)))
    msg_error("Error resolving file template",
               evt_tag_str("name", cfg->file_template_name));
  if (cfg->proto_template_name && !(cfg->proto_template = cfg_tree_lookup_template(&cfg->tree, cfg->proto_template_name)))
    msg_error("Error resolving protocol template",
               evt_tag_str("name", cfg->proto_template_name));

  if (cfg->bad_hostname_re)
    {
      if ((regerr = regcomp(&cfg->bad_hostname, cfg->bad_hostname_re, REG_NOSUB | REG_EXTENDED)) != 0)
        {
          gchar buf[256];
          
          regerror(regerr, &cfg->bad_hostname, buf, sizeof(buf));
          msg_error("Error compiling bad_hostname regexp",
                    evt_tag_str("error", buf));
        }
      else
        { 
          cfg->bad_hostname_compiled = TRUE;
        }
    }

  if (!rcptid_init(cfg->state, cfg->use_uniqid))
    return FALSE;

  stats_reinit(&cfg->stats_options);
  log_tags_reinit_stats(cfg);

  dns_caching_update_options(&cfg->dns_cache_options);
  hostname_reinit(cfg->custom_domain);
  host_resolve_options_init(&cfg->host_resolve_options, cfg);
  log_template_options_init(&cfg->template_options, cfg);
  if (!cfg_init_modules(cfg))
    return FALSE;
  return cfg_tree_start(&cfg->tree);
}

gboolean
cfg_deinit(GlobalConfig *cfg)
{
  cfg_deinit_modules(cfg);
  rcptid_deinit();
  return cfg_tree_stop(&cfg->tree);
}

void
cfg_set_version(GlobalConfig *self, gint version)
{
  self->user_version = version;
  if (cfg_is_config_version_older(self, VERSION_VALUE))
    {
      msg_warning("WARNING: Configuration file format is too old, syslog-ng is running in compatibility mode "
                  "Please update it to use the " VERSION_CURRENT " format at your time of convenience, "
                  "compatibility mode can operate less efficiently in some cases. "
                  "To upgrade the configuration, please review the warnings about incompatible changes printed "
                  "by syslog-ng, and once completed change the @version header at the top of the configuration "
                  "file.");
    }
  else if (version_convert_from_user(self->user_version) > VERSION_VALUE)
    {
      msg_warning("WARNING: Configuration file format is newer than the current version, please specify the "
                  "current version number ("  VERSION_CURRENT_VER_ONLY ") in the @version directive. "
                  "syslog-ng will operate at its highest supported version in this mode");
      self->user_version = VERSION_VALUE;
    }

  if (cfg_is_config_version_older(self, 0x0300))
    {
      msg_warning("WARNING: global: the default value of chain_hostnames is changing to 'no' in " VERSION_3_0 ", please update your configuration accordingly");
      self->chain_hostnames = TRUE;
    }
  if (cfg_is_config_version_older(self, 0x0303))
    {
      msg_warning("WARNING: global: the default value of log_fifo_size() has changed to 10000 in " VERSION_3_3 " to reflect log_iw_size() changes for tcp()/udp() window size changes");
    }

}

gboolean
cfg_allow_config_dups(GlobalConfig *self)
{
  const gchar *s;

  if (cfg_is_config_version_older(self, 0x0303))
    return TRUE;

  s = cfg_args_get(self->lexer->globals, "allow-config-dups");
  if (s && atoi(s))
    {
      return TRUE;
    }
  else
    {
      /* duplicate found, but allow-config-dups is not enabled, hint the user that he might want to use allow-config-dups */
      msg_warning_once("WARNING: Duplicate configuration objects (sources, destinations, ...) are not allowed by default starting with syslog-ng 3.3, add \"@define allow-config-dups 1\" to your configuration to re-enable");
      return FALSE;
    }
}

static void
cfg_register_builtin_plugins(GlobalConfig *self)
{
  log_proto_register_builtin_plugins(self);
}

GlobalConfig *
cfg_new(gint version)
{
  GlobalConfig *self = g_new0(GlobalConfig, 1);

  self->module_config = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, (GDestroyNotify) module_config_free);
  self->user_version = version;

  self->flush_lines = 100;
  self->flush_timeout = 10000;  /* 10 seconds */
  self->mark_freq = 1200;	/* 20 minutes */
  self->mark_mode = MM_HOST_IDLE;
  self->chain_hostnames = 0;
  self->time_reopen = 60;
  self->time_reap = 60;

  self->log_fifo_size = 10000;
  self->log_msg_size = 8192;

  file_perm_options_global_defaults(&self->file_perm_options);

  dns_cache_options_defaults(&self->dns_cache_options);
  self->threaded = TRUE;
  self->pass_unix_credentials = TRUE;
  
  log_template_options_defaults(&self->template_options);
  self->template_options.ts_format = TS_FMT_BSD;
  self->template_options.frac_digits = 0;
  self->template_options.on_error = ON_ERROR_DROP_MESSAGE;

  host_resolve_options_defaults(&self->host_resolve_options);
  self->host_resolve_options.use_fqdn = FALSE;
  self->host_resolve_options.use_dns = TRUE;
  self->host_resolve_options.use_dns_cache = TRUE;
  self->host_resolve_options.normalize_hostnames = FALSE;

  self->recv_time_zone = NULL;
  self->keep_timestamp = TRUE;

  self->use_uniqid = FALSE;
  
  stats_options_defaults(&self->stats_options);

  cfg_tree_init_instance(&self->tree, self);
  cfg_register_builtin_plugins(self);
  return self;
}

void
cfg_set_global_paths(GlobalConfig *self)
{
  gchar *include_path;

  cfg_args_set(self->lexer->globals, "syslog-ng-root", get_installation_path_for(SYSLOG_NG_PATH_PREFIX));
  cfg_args_set(self->lexer->globals, "syslog-ng-data", get_installation_path_for(SYSLOG_NG_PATH_DATADIR));
  cfg_args_set(self->lexer->globals, "syslog-ng-include", get_installation_path_for(SYSLOG_NG_PATH_CONFIG_INCLUDEDIR));
  cfg_args_set(self->lexer->globals, "scl-root", get_installation_path_for(SYSLOG_NG_PATH_SCLDIR));
  cfg_args_set(self->lexer->globals, "module-path", resolvedConfigurablePaths.initial_module_path);
  cfg_args_set(self->lexer->globals, "autoload-compiled-modules", "1");

  include_path = g_strdup_printf("%s:%s",
                                 get_installation_path_for(SYSLOG_NG_PATH_SYSCONFDIR),
                                 get_installation_path_for(SYSLOG_NG_PATH_CONFIG_INCLUDEDIR));
  cfg_args_set(self->lexer->globals, "include-path", include_path);
  g_free(include_path);
}

gboolean
cfg_run_parser(GlobalConfig *self, CfgLexer *lexer, CfgParser *parser, gpointer *result, gpointer arg)
{
  gboolean res;
  GlobalConfig *old_cfg;
  CfgLexer *old_lexer;

  old_cfg = configuration;
  configuration = self;
  old_lexer = self->lexer;
  self->lexer = lexer;

  cfg_set_global_paths(self);

  res = cfg_parser_parse(parser, lexer, result, arg);

  cfg_lexer_free(lexer);
  self->lexer = NULL;
  self->lexer = old_lexer;
  configuration = old_cfg;
  return res;
}

void
cfg_load_candidate_modules(GlobalConfig *self)
{
  /* we enable autoload for pre-3.1 configs or when the user requested
   * auto-load (the default) */

  if ((cfg_is_config_version_older(self, 0x0302) ||
      atoi(cfg_args_get(self->lexer->globals, "autoload-compiled-modules"))) && !self->candidate_plugins)
    {
      plugin_load_candidate_modules(self);
    }
}

static void
cfg_dump_processed_config(GString *preprocess_output, gchar *output_filename)
{
  FILE *output_file;

  output_file = fopen(output_filename,"w+");
  if (output_file)
    {
      fprintf(output_file, "%s", preprocess_output->str);
      fclose(output_file);
    }
}

gboolean
cfg_load_config(GlobalConfig *self, gchar *config_string, gboolean syntax_only, gchar *preprocess_into)
{
  gint res;
  CfgLexer *lexer;
  GString *preprocess_output = g_string_sized_new(8192);

  lexer = cfg_lexer_new_buffer(config_string, strlen(config_string));
  lexer->preprocess_output = preprocess_output;

  res = cfg_run_parser(self, lexer, &main_parser, (gpointer *) &self, NULL);
  if (preprocess_into)
    {
      cfg_dump_processed_config(preprocess_output, preprocess_into);
    }
  g_string_free(preprocess_output, TRUE);
  if (res)
    {
      return TRUE;
    }
  return FALSE;
}

gboolean
cfg_read_config(GlobalConfig *self, const gchar *fname, gboolean syntax_only, gchar *preprocess_into)
{
  FILE *cfg_file;
  gint res;

  self->filename = fname;

  if ((cfg_file = fopen(fname, "r")) != NULL)
    {
      CfgLexer *lexer;
      GString *preprocess_output = g_string_sized_new(8192);

      lexer = cfg_lexer_new(cfg_file, fname, preprocess_output);
      res = cfg_run_parser(self, lexer, &main_parser, (gpointer *) &self, NULL);
      fclose(cfg_file);
      if (preprocess_into)
        {
          cfg_dump_processed_config(preprocess_output, preprocess_into);
        }
      g_string_free(preprocess_output, TRUE);
      if (res)
        {
          /* successfully parsed */
          return TRUE;
        }
    }
  else
    {
      msg_error("Error opening configuration file",
                evt_tag_str(EVT_TAG_FILENAME, fname),
                evt_tag_errno(EVT_TAG_OSERROR, errno));
    }
  
  return FALSE;
}

void
cfg_free(GlobalConfig *self)
{
  g_assert(self->persist == NULL);
  if (self->state)
    persist_state_free(self->state);

  g_free(self->file_template_name);
  g_free(self->proto_template_name);  
  log_template_unref(self->file_template);
  log_template_unref(self->proto_template);
  log_template_options_destroy(&self->template_options);
  host_resolve_options_destroy(&self->host_resolve_options);

  if (self->bad_hostname_compiled)
    regfree(&self->bad_hostname);
  g_free(self->bad_hostname_re);
  dns_cache_options_destroy(&self->dns_cache_options);
  g_free(self->custom_domain);
  plugin_free_plugins(self);
  plugin_free_candidate_modules(self);
  cfg_tree_free_instance(&self->tree);
  g_hash_table_unref(self->module_config);
  g_free(self);
}

void
cfg_persist_config_move(GlobalConfig *src, GlobalConfig *dest)
{
  if (dest->persist != NULL)
    persist_config_free(dest->persist);
  dest->persist = src->persist;
  dest->state = src->state;
  src->persist = NULL;
  src->state = NULL;
}

void
cfg_persist_config_add(GlobalConfig *cfg, const gchar *name, gpointer value, GDestroyNotify destroy,
                       gboolean force)
{
  PersistConfigEntry *p;
  
  if (cfg->persist && value)
    {
      if (g_hash_table_lookup(cfg->persist->keys, name))
        {
          if (!force)
            {
              msg_error("Internal error, duplicate configuration elements refer to the same persistent config", 
                        evt_tag_str("name", name));
              if (destroy)
                destroy(value);
              return;
            }
        }
  
      p = g_new0(PersistConfigEntry, 1);
  
      p->value = value;
      p->destroy = destroy;
      g_hash_table_insert(cfg->persist->keys, g_strdup(name), p);
      return;
    }
  else if (destroy && value)
    {
      destroy(value);
    }
  return;
}

gpointer
cfg_persist_config_fetch(GlobalConfig *cfg, const gchar *name)
{
  gpointer res = NULL;
  gchar *orig_key;
  PersistConfigEntry *p;
  gpointer tmp1, tmp2;

  if (cfg->persist && g_hash_table_lookup_extended(cfg->persist->keys, name, &tmp1, &tmp2))
    {
      orig_key = (gchar *) tmp1;
      p = (PersistConfigEntry *) tmp2;

      res = p->value;

      g_hash_table_steal(cfg->persist->keys, name);
      g_free(orig_key);
      g_free(p);
    }
  return res;
}

gint
cfg_get_user_version(const GlobalConfig *cfg)
{
  return cfg->user_version;
}

gint
cfg_get_parsed_version(const GlobalConfig *cfg)
{
  return cfg->parsed_version;
}

const gchar*
cfg_get_filename(const GlobalConfig *cfg)
{
  return cfg->filename;
}

