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

#include "apphook.h"
#include "messages.h"
#include "children.h"
#include "dnscache.h"
#include "alarms.h"
#include "stats/stats-registry.h"
#include "logmsg/logmsg.h"
#include "timeutils.h"
#include "logsource.h"
#include "logwriter.h"
#include "afinter.h"
#include "template/templates.h"
#include "hostname.h"
#include "scratch-buffers.h"
#include "mainloop-call.h"
#include "service-management.h"
#include "crypto.h"
#include "value-pairs/value-pairs.h"

#include <iv.h>
#include <iv_work.h>
#include <resolv.h>

typedef struct _ApplicationHookEntry
{
  gint type;
  ApplicationHookFunc func;
  gpointer user_data;
} ApplicationHookEntry;

static GList *application_hooks = NULL;
static gint current_state = AH_STARTUP;

void 
register_application_hook(gint type, ApplicationHookFunc func, gpointer user_data)
{
  if (current_state < type)
    {
      ApplicationHookEntry *entry = g_new0(ApplicationHookEntry, 1);
      
      entry->type = type;
      entry->func = func;
      entry->user_data = user_data;
      
      application_hooks = g_list_append(application_hooks, entry);
    }
  else
    {
      /* the requested hook has already passed, call the requested function immediately */
      msg_debug("Application hook registered after the given point passed", 
                evt_tag_int("current", current_state), 
                evt_tag_int("hook", type));
      func(type, user_data);
    }
}

static void
run_application_hook(gint type)
{
  GList *l, *l_next;
  
  g_assert(current_state <= type);
  
  msg_debug("Running application hooks", evt_tag_int("hook", type));
  current_state = type;
  for (l = application_hooks; l; l = l_next)
    {
      ApplicationHookEntry *e = l->data;
      
      if (e->type == type)
        {
          l_next = l->next;
          application_hooks = g_list_remove_link(application_hooks, l);
          e->func(type, e->user_data);
          g_free(e);
          g_list_free_1(l);
        }
      else
        {
          l_next = l->next;
        }
    }

}

static void
app_fatal(const char *msg)
{
  fprintf(stderr, "%s\n", msg);
}

void 
app_startup(void)
{
  msg_init(FALSE);
  iv_set_fatal_msg_handler(app_fatal);
  iv_init();
  g_thread_init(NULL);
  crypto_init();
  hostname_global_init();
  dns_caching_global_init();
  dns_caching_thread_init();
  afinter_global_init();
  child_manager_init();
  alarm_init();
  stats_init();
  tzset();
  log_msg_global_init();
  log_tags_global_init();
  log_source_global_init();
  log_template_global_init();
  value_pairs_global_init();
  service_management_init();
}

void
app_post_daemonized(void)
{
  run_application_hook(AH_POST_DAEMONIZED);
}

void
app_pre_config_loaded(void)
{
  current_state = AH_PRE_CONFIG_LOADED;
}

void
app_post_config_loaded(void)
{
  run_application_hook(AH_POST_CONFIG_LOADED);
  res_init();
}

void 
app_shutdown(void)
{
  run_application_hook(AH_SHUTDOWN);
  value_pairs_global_deinit();
  log_template_global_deinit();
  log_tags_global_deinit();
  log_msg_global_deinit();

  stats_destroy();
  child_manager_deinit();
  g_list_foreach(application_hooks, (GFunc) g_free, NULL);
  g_list_free(application_hooks);
  dns_caching_thread_deinit();
  dns_caching_global_deinit();
  hostname_global_deinit();
  crypto_deinit();
  msg_deinit();

  
  /* NOTE: the iv_deinit() call should come here, but there's some exit
   * synchronization issue in libivykis that causes use-after-free with the
   * thread-local-state for the main thread and iv_work_pool worker threads. 
   * I've dropped a mail to Lennert about the issue, but I'm commenting this
   * out for now to avoid it biting someone. Bazsi, 2013/12/23.
   *
   *

    iv_deinit();

   */
}

void
app_thread_start(void)
{
  scratch_buffers_init();
  dns_caching_thread_init();
  main_loop_call_thread_init();
}

void
app_thread_stop(void)
{
  dns_caching_thread_deinit();
  scratch_buffers_free();
  main_loop_call_thread_deinit();
}
