#include "value-pairs.h"
#include "vptransform.h"
#include "logmsg.h"
#include "apphook.h"
#include "cfg.h"
#include "plugin.h"

#include <stdlib.h>

gboolean success = TRUE;

gboolean
vp_keys_foreach(const gchar  *name, TypeHint type, const gchar *value, gpointer user_data)
{
  gpointer *args = (gpointer *) user_data;
  GList **keys = (GList **) args[0];
  gboolean *test_key_found = (gboolean *) args[1];

  if (strcmp(name, "test.key") != 0)
    *keys = g_list_insert_sorted(*keys, g_strdup(name), (GCompareFunc) strcmp);
  else
    *test_key_found = TRUE;
  return FALSE;
}

void
cat_keys_foreach(const gchar *name, gpointer user_data)
{
  GString *res = (GString *) user_data;

  if (res->len > 0)
    g_string_append_c(res, ',');
  g_string_append(res, name);
}

MsgFormatOptions parse_options;
LogTemplateOptions template_options;

LogMessage *
create_message(void)
{
  LogMessage *msg;
  const gchar *text = "<134>1 2009-10-16T11:51:56+02:00 exchange.macartney.esbjerg MSExchange_ADAccess 20208 _MSGID_ [origin ip=\"exchange.macartney.esbjerg\"][meta sequenceId=\"191732\" sysUpTime=\"68807696\"][EventData@18372.4 Data=\"MSEXCHANGEOWAAPPPOOL.CONFIG\\\" -W \\\"\\\" -M 1 -AP \\\"MSEXCHANGEOWAAPPPOOL5244fileserver.macartney.esbjerg CDG 1 7 7 1 0 1 1 7 1 mail.macartney.esbjerg CDG 1 7 7 1 0 1 1 7 1 maindc.macartney.esbjerg CD- 1 6 6 0 0 1 1 6 1 \"][Keywords@18372.4 Keyword=\"Classic\"] ApplicationMSExchangeADAccess: message";

  msg = log_msg_new(text, strlen(text), NULL, &parse_options);
  log_msg_set_tag_by_name(msg, "almafa");
  return msg;
}

static LogTemplate *
create_template(const gchar *type_hint_string, const gchar *template_string)
{
  LogTemplate *template;

  template = log_template_new(configuration, NULL);
  log_template_compile(template, template_string, NULL);
  log_template_set_type_hint(template, type_hint_string, NULL);
  return template;
}

void
testcase(const gchar *scope, const gchar *exclude, const gchar *expected, GPtrArray *transformers)
{
  ValuePairs *vp;
  GList *vp_keys_list = NULL;
  GString *vp_keys;
  LogMessage *msg = create_message();
  gpointer args[2];
  gboolean test_key_found = FALSE;

  vp_keys = g_string_sized_new(0);

  vp = value_pairs_new();
  value_pairs_add_scope(vp, scope);
  if (exclude)
    value_pairs_add_glob_pattern(vp, exclude, FALSE);
  value_pairs_add_pair(vp, "test.key", create_template("string", "$MESSAGE"));

  if (transformers)
    {
      gint i;
      ValuePairsTransformSet *vpts = value_pairs_transform_set_new("*");

      for (i = 0; i < transformers->len; i++)
	value_pairs_transform_set_add_func(vpts, g_ptr_array_index(transformers, i));
      value_pairs_add_transforms(vp, (gpointer *)vpts);
    }

  args[0] = &vp_keys_list;
  args[1] = &test_key_found;
  value_pairs_foreach(vp, vp_keys_foreach, msg, 11, LTZ_LOCAL, &template_options, args);
  g_list_foreach(vp_keys_list, (GFunc) cat_keys_foreach, vp_keys);

  if (strcmp(vp_keys->str, expected) != 0)
    {
      fprintf(stderr, "Scope keys mismatch, scope=[%s], exclude=[%s], value=[%s], expected=[%s]\n", scope, exclude ? exclude : "(none)", vp_keys->str, expected);
      success = FALSE;
    }

  if (!test_key_found)
    {
      fprintf(stderr, "test.key is not found in the result set\n");
      success = FALSE;
    }
  g_list_foreach(vp_keys_list, (GFunc) g_free, NULL);
  g_list_free(vp_keys_list);
  g_string_free(vp_keys, TRUE);
  log_msg_unref(msg);
  value_pairs_free(vp);
}

int
main(int argc, char *argv[])
{
  GPtrArray *transformers;

  app_startup();
  putenv("TZ=MET-1METDST");
  tzset();

  configuration = cfg_new(0x0302);
  plugin_load_module("syslogformat", configuration, NULL);
  msg_format_options_defaults(&parse_options);
  msg_format_options_init(&parse_options, configuration);
  parse_options.flags |= LP_SYSLOG_PROTOCOL;

  testcase("rfc3164", NULL, "DATE,FACILITY,HOST,MESSAGE,PID,PRIORITY,PROGRAM", NULL);
  testcase("core", NULL, "DATE,FACILITY,HOST,MESSAGE,PID,PRIORITY,PROGRAM", NULL);
  testcase("base", NULL, "DATE,FACILITY,HOST,MESSAGE,PID,PRIORITY,PROGRAM", NULL);

  testcase("rfc5424", NULL, ".SDATA.EventData@18372.4.Data,.SDATA.Keywords@18372.4.Keyword,.SDATA.meta.sequenceId,.SDATA.meta.sysUpTime,.SDATA.origin.ip,DATE,FACILITY,HOST,MESSAGE,MSGID,PID,PRIORITY,PROGRAM", NULL);
  testcase("syslog-proto", NULL, ".SDATA.EventData@18372.4.Data,.SDATA.Keywords@18372.4.Keyword,.SDATA.meta.sequenceId,.SDATA.meta.sysUpTime,.SDATA.origin.ip,DATE,FACILITY,HOST,MESSAGE,MSGID,PID,PRIORITY,PROGRAM", NULL);

  testcase("selected-macros", NULL, "DATE,FACILITY,HOST,MESSAGE,PID,PRIORITY,PROGRAM,SEQNUM,SOURCEIP,TAGS", NULL);

  testcase("nv-pairs", NULL, "HOST,MESSAGE,MSGID,PID,PROGRAM", NULL);
  testcase("dot-nv-pairs", NULL, ".SDATA.EventData@18372.4.Data,.SDATA.Keywords@18372.4.Keyword,.SDATA.meta.sequenceId,.SDATA.meta.sysUpTime,.SDATA.origin.ip", NULL);

  testcase("sdata", NULL, ".SDATA.EventData@18372.4.Data,.SDATA.Keywords@18372.4.Keyword,.SDATA.meta.sequenceId,.SDATA.meta.sysUpTime,.SDATA.origin.ip", NULL);

  testcase("all-nv-pairs", NULL, ".SDATA.EventData@18372.4.Data,.SDATA.Keywords@18372.4.Keyword,.SDATA.meta.sequenceId,.SDATA.meta.sysUpTime,.SDATA.origin.ip,HOST,MESSAGE,MSGID,PID,PROGRAM", NULL);

  testcase("everything", NULL, ".SDATA.EventData@18372.4.Data,.SDATA.Keywords@18372.4.Keyword,.SDATA.meta.sequenceId,.SDATA.meta.sysUpTime,.SDATA.origin.ip,AMPM,BSDTAG,C_DATE,C_DAY,C_FULLDATE,C_HOUR,C_ISODATE,C_MIN,C_MONTH,C_MONTH_ABBREV,C_MONTH_NAME,C_MONTH_WEEK,C_SEC,C_STAMP,C_TZ,C_TZOFFSET,C_UNIXTIME,C_WEEK,C_WEEKDAY,C_WEEK_DAY,C_WEEK_DAY_ABBREV,C_WEEK_DAY_NAME,C_YEAR,C_YEAR_DAY,DATE,DAY,FACILITY,FACILITY_NUM,FULLDATE,HOST,HOUR,HOUR12,ISODATE,LEVEL,LEVEL_NUM,LOGHOST,MESSAGE,MIN,MONTH,MONTH_ABBREV,MONTH_NAME,MONTH_WEEK,MSEC,MSG,MSGHDR,MSGID,PID,PRI,PRIORITY,PROGRAM,R_AMPM,R_DATE,R_DAY,R_FULLDATE,R_HOUR,R_HOUR12,R_ISODATE,R_MIN,R_MONTH,R_MONTH_ABBREV,R_MONTH_NAME,R_MONTH_WEEK,R_MSEC,R_SEC,R_STAMP,R_TZ,R_TZOFFSET,R_UNIXTIME,R_USEC,R_WEEK,R_WEEKDAY,R_WEEK_DAY,R_WEEK_DAY_ABBREV,R_WEEK_DAY_NAME,R_YEAR,R_YEAR_DAY,SDATA,SEC,SEQNUM,SOURCEIP,STAMP,SYSUPTIME,S_AMPM,S_DATE,S_DAY,S_FULLDATE,S_HOUR,S_HOUR12,S_ISODATE,S_MIN,S_MONTH,S_MONTH_ABBREV,S_MONTH_NAME,S_MONTH_WEEK,S_MSEC,S_SEC,S_STAMP,S_TZ,S_TZOFFSET,S_UNIXTIME,S_USEC,S_WEEK,S_WEEKDAY,S_WEEK_DAY,S_WEEK_DAY_ABBREV,S_WEEK_DAY_NAME,S_YEAR,S_YEAR_DAY,TAG,TAGS,TZ,TZOFFSET,UNIXTIME,USEC,WEEK,WEEKDAY,WEEK_DAY,WEEK_DAY_ABBREV,WEEK_DAY_NAME,YEAR,YEAR_DAY", NULL);

  testcase("nv-pairs", ".SDATA.*", "HOST,MESSAGE,MSGID,PID,PROGRAM", NULL);

  /* tests that the exclude patterns do not affect explicitly added
   * keys. The testcase function adds a "test.key" and then checks if
   * it is indeed present. Even if it would be excluded it still has
   * to be in the result set. */
  testcase("rfc3164", "test.*", "DATE,FACILITY,HOST,MESSAGE,PID,PRIORITY,PROGRAM", NULL);

  /* tests that excluding works even when the key would be in the
   * default set. */
  testcase("nv-pairs", "MESSAGE", "HOST,MSGID,PID,PROGRAM", NULL);

  /* test the value-pair transformators */
  transformers = g_ptr_array_new();
  g_ptr_array_add(transformers, value_pairs_new_transform_add_prefix("__"));
  g_ptr_array_add(transformers, value_pairs_new_transform_shift(2));
  g_ptr_array_add(transformers, value_pairs_new_transform_replace_prefix("C_", "CC_"));

  testcase("everything", NULL, ".SDATA.EventData@18372.4.Data,.SDATA.Keywords@18372.4.Keyword,.SDATA.meta.sequenceId,.SDATA.meta.sysUpTime,.SDATA.origin.ip,AMPM,BSDTAG,CC_DATE,CC_DAY,CC_FULLDATE,CC_HOUR,CC_ISODATE,CC_MIN,CC_MONTH,CC_MONTH_ABBREV,CC_MONTH_NAME,CC_MONTH_WEEK,CC_SEC,CC_STAMP,CC_TZ,CC_TZOFFSET,CC_UNIXTIME,CC_WEEK,CC_WEEKDAY,CC_WEEK_DAY,CC_WEEK_DAY_ABBREV,CC_WEEK_DAY_NAME,CC_YEAR,CC_YEAR_DAY,DATE,DAY,FACILITY,FACILITY_NUM,FULLDATE,HOST,HOUR,HOUR12,ISODATE,LEVEL,LEVEL_NUM,LOGHOST,MESSAGE,MIN,MONTH,MONTH_ABBREV,MONTH_NAME,MONTH_WEEK,MSEC,MSG,MSGHDR,MSGID,PID,PRI,PRIORITY,PROGRAM,R_AMPM,R_DATE,R_DAY,R_FULLDATE,R_HOUR,R_HOUR12,R_ISODATE,R_MIN,R_MONTH,R_MONTH_ABBREV,R_MONTH_NAME,R_MONTH_WEEK,R_MSEC,R_SEC,R_STAMP,R_TZ,R_TZOFFSET,R_UNIXTIME,R_USEC,R_WEEK,R_WEEKDAY,R_WEEK_DAY,R_WEEK_DAY_ABBREV,R_WEEK_DAY_NAME,R_YEAR,R_YEAR_DAY,SDATA,SEC,SEQNUM,SOURCEIP,STAMP,SYSUPTIME,S_AMPM,S_DATE,S_DAY,S_FULLDATE,S_HOUR,S_HOUR12,S_ISODATE,S_MIN,S_MONTH,S_MONTH_ABBREV,S_MONTH_NAME,S_MONTH_WEEK,S_MSEC,S_SEC,S_STAMP,S_TZ,S_TZOFFSET,S_UNIXTIME,S_USEC,S_WEEK,S_WEEKDAY,S_WEEK_DAY,S_WEEK_DAY_ABBREV,S_WEEK_DAY_NAME,S_YEAR,S_YEAR_DAY,TAG,TAGS,TZ,TZOFFSET,UNIXTIME,USEC,WEEK,WEEKDAY,WEEK_DAY,WEEK_DAY_ABBREV,WEEK_DAY_NAME,YEAR,YEAR_DAY", transformers);
  g_ptr_array_free(transformers, TRUE);

  app_shutdown();
  if (success)
    return 0;
  return 1;
}
