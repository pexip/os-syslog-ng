#include "syslog-ng.h"
#include "template_lib.h"

#include "logmsg.h"
#include "template/templates.h"
#include "misc.h"
#include "apphook.h"
#include "cfg.h"
#include "timeutils.h"
#include "plugin.h"

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

GCond *thread_ping;
GMutex *thread_lock;
gboolean thread_start;

static gpointer
format_template_thread(gpointer s)
{
  gpointer *args = (gpointer *) s;
  LogMessage *msg = args[0];
  LogTemplate *templ = args[1];
  const gchar *expected = args[2];
  GString *result;
  gint i;

  g_mutex_lock(thread_lock);
  while (!thread_start)
    g_cond_wait(thread_ping, thread_lock);
  g_mutex_unlock(thread_lock);

  result = g_string_sized_new(0);
  for (i = 0; i < 10000; i++)
    {
      log_template_format(templ, msg, NULL, LTZ_SEND, 5555, NULL, result);
      assert_string(result->str, expected, "multi-threaded formatting yielded invalid result (iteration: %d)", i);
    }
  g_string_free(result, TRUE);
  return NULL;
}

static void
assert_template_format_multi_thread(const gchar *template, const gchar *expected)
{
  LogTemplate *templ;
  LogMessage *msg;
  gpointer args[3];
  GThread *threads[16];
  gint i;

  msg = create_sample_message();
  templ = compile_template(template, FALSE);
  args[0] = msg;
  args[1] = templ;
  args[2] = (gpointer) expected;

  thread_start = FALSE;
  thread_ping = g_cond_new();
  thread_lock = g_mutex_new();
  args[1] = templ;
  for (i = 0; i < 16; i++)
    {
      threads[i] = g_thread_create(format_template_thread, args, TRUE, NULL);
    }

  thread_start = TRUE;
  g_mutex_lock(thread_lock);
  g_cond_broadcast(thread_ping);
  g_mutex_unlock(thread_lock);
  for (i = 0; i < 16; i++)
    {
      g_thread_join(threads[i]);
    }
  g_cond_free(thread_ping);
  g_mutex_free(thread_lock);
  log_template_unref(templ);
  log_msg_unref(msg);
}

static void
test_macros(void)
{
  /* pri 3, fac 19 == local3 */

  assert_template_format("$FACILITY", "local3");
  assert_template_format("$FACILITY_NUM", "19");
  assert_template_format("$PRIORITY", "err");
  assert_template_format("$LEVEL", "err");
  assert_template_format("$LEVEL_NUM", "3");
  assert_template_format("$TAG", "9b");
  assert_template_format("$TAGS", "alma,korte,citrom");
  assert_template_format("$PRI", "155");
  assert_template_format("$DATE", "Feb 11 10:34:56.000");
  assert_template_format("$FULLDATE", "2006 Feb 11 10:34:56.000");
  assert_template_format("$ISODATE", "2006-02-11T10:34:56.000+01:00");
  assert_template_format("$STAMP", "Feb 11 10:34:56.000");
  assert_template_format("$YEAR", "2006");
  assert_template_format("$YEAR_DAY", "042");
  assert_template_format("$MONTH", "02");
  assert_template_format("$MONTH_WEEK", "1");
  assert_template_format("$MONTH_ABBREV", "Feb");
  assert_template_format("$MONTH_NAME", "February");
  assert_template_format("$DAY", "11");
  assert_template_format("$HOUR", "10");
  assert_template_format("$MIN", "34");
  assert_template_format("$SEC", "56");
  assert_template_format("$WEEKDAY", "Sat");
  assert_template_format("$WEEK_DAY", "7");
  assert_template_format("$WEEK_DAY_NAME", "Saturday");
  assert_template_format("$WEEK_DAY_ABBREV", "Sat");
  assert_template_format("$WEEK", "06");
  assert_template_format("$UNIXTIME", "1139650496.000");
  assert_template_format("$TZOFFSET", "+01:00");
  assert_template_format("$TZ", "+01:00");
  assert_template_format("$R_DATE", "Feb 11 19:58:35.639");
  assert_template_format("$R_FULLDATE", "2006 Feb 11 19:58:35.639");
  assert_template_format("$R_ISODATE", "2006-02-11T19:58:35.639+01:00");
  assert_template_format("$R_STAMP", "Feb 11 19:58:35.639");
  assert_template_format("$R_YEAR", "2006");
  assert_template_format("$R_YEAR_DAY", "042");
  assert_template_format("$R_MONTH", "02");
  assert_template_format("$R_MONTH_WEEK", "1");
  assert_template_format("$R_MONTH_ABBREV", "Feb");
  assert_template_format("$R_MONTH_NAME", "February");
  assert_template_format("$R_DAY", "11");
  assert_template_format("$R_HOUR", "19");
  assert_template_format("$R_MIN", "58");
  assert_template_format("$R_SEC", "35");
  assert_template_format("$R_WEEKDAY", "Sat");
  assert_template_format("$R_WEEK_DAY", "7");
  assert_template_format("$R_WEEK_DAY_NAME", "Saturday");
  assert_template_format("$R_WEEK_DAY_ABBREV", "Sat");
  assert_template_format("$R_WEEK", "06");
  assert_template_format("$R_UNIXTIME", "1139684315.639");
  assert_template_format("$R_TZOFFSET", "+01:00");
  assert_template_format("$R_TZ", "+01:00");
  assert_template_format("$S_DATE", "Feb 11 10:34:56.000");
  assert_template_format("$S_FULLDATE", "2006 Feb 11 10:34:56.000");
  assert_template_format("$S_ISODATE", "2006-02-11T10:34:56.000+01:00");
  assert_template_format("$S_STAMP", "Feb 11 10:34:56.000");
  assert_template_format("$S_YEAR", "2006");
  assert_template_format("$S_YEAR_DAY", "042");
  assert_template_format("$S_MONTH", "02");
  assert_template_format("$S_MONTH_WEEK", "1");
  assert_template_format("$S_MONTH_ABBREV", "Feb");
  assert_template_format("$S_MONTH_NAME", "February");
  assert_template_format("$S_DAY", "11");
  assert_template_format("$S_HOUR", "10");
  assert_template_format("$S_MIN", "34");
  assert_template_format("$S_SEC", "56");
  assert_template_format("$S_WEEKDAY", "Sat");
  assert_template_format("$S_WEEK_DAY", "7");
  assert_template_format("$S_WEEK_DAY_NAME", "Saturday");
  assert_template_format("$S_WEEK_DAY_ABBREV", "Sat");
  assert_template_format("$S_WEEK", "06");
  assert_template_format("$S_UNIXTIME", "1139650496.000");
  assert_template_format("$S_TZOFFSET", "+01:00");
  assert_template_format("$S_TZ", "+01:00");
  assert_template_format("$HOST_FROM", "kismacska");
  assert_template_format("$FULLHOST_FROM", "kismacska");
  assert_template_format("$HOST", "bzorp");
  assert_template_format("$FULLHOST", "bzorp");
  assert_template_format("$PROGRAM", "syslog-ng");
  assert_template_format("$PID", "23323");
  assert_template_format("$MSGHDR", "syslog-ng[23323]:");
  assert_template_format("$MSG", "árvíztűrőtükörfúrógép");
  assert_template_format("$MESSAGE", "árvíztűrőtükörfúrógép");
  assert_template_format("$SOURCEIP", "10.11.12.13");

  assert_template_format("$SEQNUM", "999");
  assert_template_format("$CONTEXT_ID", "test-context-id");
}

static void
test_nvpairs(void)
{
  assert_template_format("$PROGRAM/var/log/messages/$HOST/$HOST_FROM/$MONTH$DAY${QQQQQ}valami", "syslog-ng/var/log/messages/bzorp/kismacska/0211valami");
  assert_template_format("${APP.VALUE}", "value");
  assert_template_format("${APP.VALUE:-ures}", "value");
  assert_template_format("${APP.VALUE2:-ures}", "ures");
  assert_template_format("${1}", "first-match");
  assert_template_format("$1", "first-match");
  assert_template_format("$$$1$$", "$first-match$");
}

static void
test_template_functions(void)
{
  /* template functions */
  assert_template_format("$(echo $HOST $PID)", "bzorp 23323");
  assert_template_format("$(echo \"$(echo $HOST)\" $PID)", "bzorp 23323");
  assert_template_format("$(echo \"$(echo '$(echo $HOST)')\" $PID)", "bzorp 23323");
  assert_template_format("$(echo \"$(echo '$(echo $HOST)')\" $PID)", "bzorp 23323");
  assert_template_format("$(echo '\"$(echo $(echo $HOST))\"' $PID)", "\"bzorp\" 23323");
}

static void
test_message_refs(void)
{
  /* message refs */
  assert_template_format_with_context("$(echo ${HOST}@0 ${PID}@1)", "bzorp 23323");
  assert_template_format_with_context("$(echo $HOST $PID)@0", "bzorp 23323");
}

static void
test_syntax_errors(void)
{
  /* template syntax errors */
  assert_template_failure("${unbalanced_brace", "'}' is missing");
  assert_template_format("$unbalanced_brace}", "}");
  assert_template_format("$}", "$}");
  assert_template_failure("$(unbalanced_paren", "missing function name or inbalanced '('");
  assert_template_format("$unbalanced_paren)", ")");
}

static void
test_compat(void)
{
  gint old_version;

  old_version = configuration->user_version;
  /* old version for various macros */
  configuration->user_version = 0x0201;

  start_grabbing_messages();
  assert_template_format("$MSGHDR", "syslog-ng[23323]:");
  assert_grabbed_messages_contain("the default value for template-escape has changed to 'no' from syslog-ng 3.0", NULL);
  reset_grabbed_messages();
  assert_template_format("$MSG", "syslog-ng[23323]:árvíztűrőtükörfúrógép");
  assert_grabbed_messages_contain("the meaning of the $MSG/$MESSAGE macros has changed from syslog-ng 3.0", NULL);
  stop_grabbing_messages();
  assert_template_format("$MSGONLY", "árvíztűrőtükörfúrógép");
  assert_template_format("$MESSAGE", "syslog-ng[23323]:árvíztűrőtükörfúrógép");

  configuration->user_version = old_version;
}

static void
test_multi_thread(void)
{
  /* name-value pair */
  assert_template_format_multi_thread("alma $HOST bela", "alma bzorp bela");
  assert_template_format_multi_thread("kukac $DATE mukac", "kukac Feb 11 10:34:56.000 mukac");
  assert_template_format_multi_thread("dani $(echo $HOST $DATE $(echo huha)) balint", "dani bzorp Feb 11 10:34:56.000 huha balint");
}

static void
test_escaping(void)
{
  assert_template_format_with_escaping("${APP.QVALUE}", FALSE, "\"value\"");
  assert_template_format_with_escaping("${APP.QVALUE}", TRUE, "\\\"value\\\"");
  assert_template_format_with_escaping("$(if (\"${APP.VALUE}\" == \"value\") \"${APP.QVALUE}\" \"${APP.QVALUE}\")",
                                       FALSE, "\"value\"");
  assert_template_format_with_escaping("$(if (\"${APP.VALUE}\" == \"value\") \"${APP.QVALUE}\" \"${APP.QVALUE}\")",
                                       TRUE, "\\\"value\\\"");
}

int
main(int argc G_GNUC_UNUSED, char *argv[] G_GNUC_UNUSED)
{
  app_startup();

  init_template_tests();
  plugin_load_module("basicfuncs", configuration, NULL);
  configuration->template_options.frac_digits = 3;
  configuration->template_options.time_zone_info[LTZ_LOCAL] = time_zone_info_new(NULL);


  putenv("TZ=MET-1METDST");
  tzset();

  test_macros();
  test_nvpairs();
  test_template_functions();
  test_message_refs();
  test_syntax_errors();
  test_compat();
  test_multi_thread();
  test_escaping();

  /* multi-threaded expansion */


  deinit_template_tests();
  app_shutdown();

  return 0;
}
