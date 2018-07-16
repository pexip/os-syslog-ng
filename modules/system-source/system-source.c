/*
 * Copyright (c) 2012-2014 Balabit
 * Copyright (c) 2012-2014 Gergely Nagy <algernon@balabit.hu>
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

#include "cfg.h"
#include "cfg-lexer.h"
#include "messages.h"
#include "plugin.h"
#include "plugin-types.h"

#include <fcntl.h>
#include <sys/utsname.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <iv.h>
#include "service-management.h"

#if __FreeBSD__
#include <sys/sysctl.h>
#include <inttypes.h>
#endif

static void
system_sysblock_add_unix_dgram_driver(GString *sysblock, const gchar *path,
                                      const gchar *perms, const gchar *recvbuf_size)
{
  g_string_append_printf(sysblock, "unix-dgram(\"%s\"", path);
  if (perms)
    g_string_append_printf(sysblock, " perm(%s)", perms);
  if (recvbuf_size)
    g_string_append_printf(sysblock, " so_rcvbuf(%s)", recvbuf_size);
  g_string_append(sysblock, ");\n");
}

static void
system_sysblock_add_unix_dgram(GString *sysblock, const gchar *path,
                               const gchar *perms, const gchar *recvbuf_size)
{
  GString *unix_driver = g_string_sized_new(0);
  
  system_sysblock_add_unix_dgram_driver(unix_driver, path, perms, recvbuf_size);

  g_string_append_printf(sysblock, 
"channel {\n"
"    source { %s };\n"
"    rewrite { set(\"${.unix.pid}\" value(\"PID\") condition(\"${.unix.pid}\" ne \"\")); };\n"
"};\n", unix_driver->str);

  g_string_free(unix_driver, TRUE);
}

static void
system_sysblock_add_file(GString *sysblock, const gchar *path,
                         gint follow_freq, const gchar *prg_override,
                         const gchar *flags, const gchar *format,
                         gboolean ignore_timestamp)
{
  g_string_append_printf(sysblock, "file(\"%s\"", path);
  if (follow_freq >= 0)
    g_string_append_printf(sysblock, " follow-freq(%d)", follow_freq);
  if (prg_override)
    g_string_append_printf(sysblock, " program-override(\"%s\")", prg_override);
  if (flags)
    g_string_append_printf(sysblock, " flags(%s)", flags);
  if (format)
    g_string_append_printf(sysblock, " format(%s)", format);
  if (ignore_timestamp)
    g_string_append_printf(sysblock, " keep-timestamp(no)");
  g_string_append(sysblock, ");\n");
}

static void
system_sysblock_add_module(GString *sysblock, const gchar *mod)
{
  g_string_append_printf(sysblock, "@module %s\n", mod);
}

static void
system_sysblock_add_sun_streams(GString *sysblock, const gchar *path,
                                const gchar *door)
{
  GString *solaris_driver = g_string_sized_new(0);



  g_string_append_printf(solaris_driver, "sun-streams(\"%s\"", path);
  if (door)
    g_string_append_printf(solaris_driver, " door(\"%s\")", door);
  g_string_append(solaris_driver, ");\n");


  g_string_append_printf(sysblock,
"channel {\n"
"    source { %s };\n"
"    parser { extract-solaris-msgid(); };\n"
"};\n", solaris_driver->str);
  g_string_free(solaris_driver, TRUE);
}

static void
system_sysblock_add_pipe(GString *sysblock, const gchar *path, gint pad_size)
{
  g_string_append_printf(sysblock, "pipe(\"%s\"", path);
  if (pad_size >= 0)
    g_string_append_printf(sysblock, " pad_size(%d)", pad_size);
  g_string_append(sysblock, ");\n");
}

#if __FreeBSD__
static gboolean
system_freebsd_is_jailed(void)
{
  int r;
  int32_t is_jailed;
  size_t len = 4;

  r = sysctlbyname("security.jail.jailed", &is_jailed, &len, NULL, 0);
  if (r != 0)
    return FALSE;
  return !!is_jailed;
}
#else
static gboolean
system_freebsd_is_jailed(void)
{
  return FALSE;
}
#endif

static void
system_sysblock_add_freebsd_klog(GString *sysblock, const gchar *release)
{
  /* /dev/klog on FreeBSD prior to 9.1-RC-something is not
     pollable with kqueue(), so use timers for it instead, by
     forcing follow-freq(1). */
  if (strncmp(release, "7.", 2) == 0 ||
      strncmp(release, "8.", 2) == 0 ||
      strncmp(release, "9.0", 3) == 0)
    system_sysblock_add_file(sysblock, "/dev/klog", 1, "kernel", "no-parse", NULL, FALSE);
  else
    system_sysblock_add_file(sysblock, "/dev/klog", 0, "kernel", "no-parse", NULL, FALSE);
}

static gboolean
_is_fd_pollable(gint fd)
{
  struct iv_fd check_fd;
  gboolean pollable;

  IV_FD_INIT(&check_fd);
  check_fd.fd = fd;
  check_fd.cookie = NULL;

  pollable = (iv_fd_register_try(&check_fd) == 0);
  if (pollable)
    iv_fd_unregister(&check_fd);
  return pollable;
}


static void
system_sysblock_add_systemd_source(GString *sysblock)
{
  g_string_append(sysblock, "systemd-journal();\n");
}

static void
system_sysblock_add_linux_kmsg(GString *sysblock)
{
  gchar *kmsg = "/proc/kmsg";
  int fd;
  gchar *format = NULL;

  if ((fd = open("/dev/kmsg", O_RDONLY)) != -1)
    {
      if ((lseek (fd, 0, SEEK_END) != -1) && _is_fd_pollable(fd))
        {
          kmsg = "/dev/kmsg";
          format = "linux-kmsg";
        }
      close (fd);
    }

  if (access(kmsg, R_OK) == -1)
    {
      msg_warning("system(): The kernel message buffer is not readable, "
                  "please check permissions if this is unintentional.",
                  evt_tag_str("device", kmsg),
                  evt_tag_errno("error", errno));
    }
  else
    system_sysblock_add_file(sysblock, kmsg, -1,
                             "kernel", "kernel", format, TRUE);
}

static gboolean
_is_running_in_linux_container(void)
{
  FILE *f;
  char line[2048];
  gboolean container = FALSE;

  f = fopen("/proc/1/cgroup", "r");
  if (!f)
    return FALSE;

  while (fgets(line, sizeof(line), f) != NULL)
    {
      if (line[strlen(line) - 2] != '/')
        {
          container = TRUE;
          break;
        }
    }

  fclose (f);

  return container;
}

static void
system_sysblock_add_linux(GString *sysblock)
{
  if (service_management_get_type() == SMT_SYSTEMD)
    system_sysblock_add_systemd_source(sysblock);
  else
    {
      system_sysblock_add_unix_dgram(sysblock, "/dev/log", NULL, "8192");
      if (!_is_running_in_linux_container())
        system_sysblock_add_linux_kmsg(sysblock);
    }
}

static gboolean
system_generate_system_transports(GString *sysblock)
{
  struct utsname u;

  if (uname(&u) < 0)
    {
      msg_error("system(): Cannot get information about the running kernel",
                evt_tag_errno("error", errno));
      return FALSE;
    }

  if (strcmp(u.sysname, "Linux") == 0)
    {
      system_sysblock_add_linux(sysblock);
    }
  else if (strcmp(u.sysname, "SunOS") == 0)
    {
      system_sysblock_add_module(sysblock, "afstreams");

      if (strcmp(u.release, "5.8") == 0)
        system_sysblock_add_sun_streams(sysblock, "/dev/log", NULL);
      else if (strcmp(u.release, "5.9") == 0)
        system_sysblock_add_sun_streams(sysblock, "/dev/log", "/etc/.syslog_door");
      else
        system_sysblock_add_sun_streams(sysblock, "/dev/log", "/var/run/syslog_door");
    }
  else if (strcmp(u.sysname, "FreeBSD") == 0)
    {
      system_sysblock_add_unix_dgram(sysblock, "/var/run/log", NULL, NULL);
      system_sysblock_add_unix_dgram(sysblock, "/var/run/logpriv", "0600", NULL);

      if (!system_freebsd_is_jailed())
        system_sysblock_add_freebsd_klog(sysblock, u.release);
    }
  else if (strcmp(u.sysname, "GNU/kFreeBSD") == 0)
    {
      system_sysblock_add_unix_dgram(sysblock, "/var/run/log", NULL, NULL);
      system_sysblock_add_freebsd_klog(sysblock, u.release);
    }
  else if (strcmp(u.sysname, "HP-UX") == 0)
    {
      system_sysblock_add_pipe(sysblock, "/dev/log", 2048);
    }
  else if (strcmp(u.sysname, "AIX") == 0 ||
           strcmp(u.sysname, "OSF1") == 0 ||
           strncmp(u.sysname, "CYGWIN", 6) == 0)
    {
      system_sysblock_add_unix_dgram(sysblock, "/dev/log", NULL, NULL);
    }
  else
    {
      msg_error("system(): Error detecting platform, unable to define the system() source. "
                "Please send your system information to the developers!",
                evt_tag_str("sysname", u.sysname),
                evt_tag_str("release", u.release));
      return FALSE;
    }
  g_string_append(sysblock, "\n");
  return TRUE;
}

static gboolean
_is_json_parser_available(GlobalConfig *cfg)
{
  return plugin_find(cfg, LL_CONTEXT_PARSER, "json-parser") != NULL;
}

static void
system_generate_cim_parser(GlobalConfig *cfg, GString *sysblock)
{
  if (cfg_is_config_version_older(cfg, 0x0306))
    {
      msg_warning_once("WARNING: Starting with " VERSION_3_6 ", the system() source performs JSON parsing of messages starting with the '@cim:' prefix. No additional action is needed");
      return;
    }

  if (!_is_json_parser_available(cfg))
    {
      msg_debug("system(): json-parser() is missing, skipping the automatic JSON parsing of messages submitted via syslog(3), Please install the json module");
      return;
    }

  g_string_append(sysblock,
                  "channel {\n"
                  "  channel {\n"
                  "    parser {\n"
                  "      json-parser(prefix('.cim.') marker('@cim:'));\n"
                  "    };\n"
                  "    flags(final);\n"
                  "  };\n"
                  "  channel { };\n"
                  "};\n");
}

static gboolean
system_generate_system(CfgLexer *lexer, gint type, const gchar *name,
                       CfgArgs *args, gpointer user_data)
{
  gchar buf[256];
  GString *sysblock;
  gboolean result = FALSE;
  GlobalConfig *cfg = (GlobalConfig *) user_data;

  g_snprintf(buf, sizeof(buf), "source confgen system");

  sysblock = g_string_sized_new(1024);

  g_string_append(sysblock,
                  "channel {\n"
                  "    source {\n");

  if (!system_generate_system_transports(sysblock))
    {
      goto exit;
    }

  g_string_append(sysblock, "    }; # source\n");

  system_generate_cim_parser(cfg, sysblock);

  g_string_append(sysblock, "}; # channel\n");
  result = cfg_lexer_include_buffer(lexer, buf, sysblock->str, sysblock->len);
 exit:
  g_string_free(sysblock, TRUE);
  return result;
}

gboolean
system_source_module_init(GlobalConfig *cfg, CfgArgs *args)
{
  cfg_lexer_register_block_generator(cfg->lexer,
                                     cfg_lexer_lookup_context_type_by_name("source"),
                                     "system", system_generate_system,
                                     cfg, NULL);

  return TRUE;
}

const ModuleInfo module_info =
{
  .canonical_name = "system-source",
  .version = SYSLOG_NG_VERSION,
  .description = "The system-source module provides support for determining the system log sources at run time.",
  .core_revision = SYSLOG_NG_SOURCE_REVISION,
  .plugins = NULL,
  .plugins_len = 0,
};
