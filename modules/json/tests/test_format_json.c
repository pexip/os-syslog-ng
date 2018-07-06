/*
 * Copyright (c) 2011-2013 Balabit
 * Copyright (c) 2011-2013 Gergely Nagy <algernon@balabit.hu>
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
#include "template_lib.h"
#include "apphook.h"
#include "plugin.h"
#include "cfg.h"

void
test_format_json(void)
{
  assert_template_format("$(format-json MSG=$MSG)", "{\"MSG\":\"árvíztűrőtükörfúrógép\"}");
  assert_template_format("$(format-json MSG=$escaping)", "{\"MSG\":\"binary stuff follows \\\"\\\\xad árvíztűrőtükörfúrógép\"}");
  assert_template_format("$(format-json MSG=$escaping2)", "{\"MSG\":\"\\\\xc3\"}");
  assert_template_format("$(format-json MSG=$null)", "{\"MSG\":\"binary\\u0000stuff\"}");
  assert_template_format_with_context("$(format-json MSG=$MSG)", "{\"MSG\":\"árvíztűrőtükörfúrógép\"}{\"MSG\":\"árvíztűrőtükörfúrógép\"}");
  assert_template_format("$(format-json --scope rfc3164)", "{\"PROGRAM\":\"syslog-ng\",\"PRIORITY\":\"err\",\"PID\":\"23323\",\"MESSAGE\":\"árvíztűrőtükörfúrógép\",\"HOST\":\"bzorp\",\"FACILITY\":\"local3\",\"DATE\":\"Feb 11 10:34:56\"}");
  assert_template_format("$(format-json msg.text=$MSG msg.id=42 host=bzorp)", "{\"msg\":{\"text\":\"árvíztűrőtükörfúrógép\",\"id\":\"42\"},\"host\":\"bzorp\"}");
  assert_template_format("$(format-json msg.text.str=$MSG msg.text.len=42 msg.id=42 host=bzorp)",
                         "{\"msg\":{\"text\":{\"str\":\"árvíztűrőtükörfúrógép\",\"len\":\"42\"},\"id\":\"42\"},\"host\":\"bzorp\"}");
  assert_template_format("$(format-json kernel.SUBSYSTEM=pci kernel.DEVICE.type=pci kernel.DEVICE.name=0000:02:00.0 MSGID=801 MESSAGE=test)",
                         "{\"kernel\":{\"SUBSYSTEM\":\"pci\",\"DEVICE\":{\"type\":\"pci\",\"name\":\"0000:02:00.0\"}},\"MSGID\":\"801\",\"MESSAGE\":\"test\"}");
  assert_template_format("$(format-json .foo=bar)", "{\"_foo\":\"bar\"}");
  assert_template_format("$(format-json --scope rfc3164,rfc3164)", "{\"PROGRAM\":\"syslog-ng\",\"PRIORITY\":\"err\",\"PID\":\"23323\",\"MESSAGE\":\"árvíztűrőtükörfúrógép\",\"HOST\":\"bzorp\",\"FACILITY\":\"local3\",\"DATE\":\"Feb 11 10:34:56\"}");
  assert_template_format("$(format-json sdata.win@18372.4.fruit=\"pear\" sdata.win@18372.4.taste=\"good\")",
                         "{\"sdata\":{\"win@18372.4\":{\"taste\":\"good\",\"fruit\":\"pear\"}}}");

  assert_template_format("$(format-json --scope selected_macros)", "{\"TAGS\":\"alma,korte,citrom\",\"SOURCEIP\":\"10.11.12.13\",\"SEQNUM\":\"999\",\"PROGRAM\":\"syslog-ng\",\"PRIORITY\":\"err\",\"PID\":\"23323\",\"MESSAGE\":\"árvíztűrőtükörfúrógép\",\"HOST\":\"bzorp\",\"FACILITY\":\"local3\",\"DATE\":\"Feb 11 10:34:56\"}");
  assert_template_format("$(format-json --scope rfc3164 --key *.*)",
                          "{\"_unix\":{\"uid\":\"1000\",\"gid\":\"1000\",\"cmd\":\"command\"},\"_json\":{\"sub\":{\"value2\":\"subvalue2\",\"value1\":\"subvalue1\"},\"foo\":\"bar\"},\"PROGRAM\":\"syslog-ng\",\"PRIORITY\":\"err\",\"PID\":\"23323\",\"MESSAGE\":\"árvíztűrőtükörfúrógép\",\"HOST\":\"bzorp\",\"FACILITY\":\"local3\",\"DATE\":\"Feb 11 10:34:56\",\"APP\":{\"VALUE\":\"value\",\"STRIP5\":\"\",\"STRIP4\":\"value\",\"STRIP3\":\"     value     \",\"STRIP2\":\"value     \",\"STRIP1\":\"     value\",\"QVALUE\":\"\\\"value\\\"\"}}");

  assert_template_format("$(format-json --scope syslog-proto)", "{\"PROGRAM\":\"syslog-ng\",\"PRIORITY\":\"err\",\"PID\":\"23323\",\"MESSAGE\":\"árvíztűrőtükörfúrógép\",\"HOST\":\"bzorp\",\"FACILITY\":\"local3\",\"DATE\":\"Feb 11 10:34:56\"}");

  assert_template_format("$(format-json @program=${PROGRAM})", "{\"@program\":\"syslog-ng\"}");
  assert_template_format("$(format-json @program.123=${PROGRAM})", "{\"@program\":{\"123\":\"syslog-ng\"}}");
  assert_template_format("$(format-json .@program.123=${PROGRAM})", "{\"_@program\":{\"123\":\"syslog-ng\"}}");
  assert_template_format("$(format-json @.program=${PROGRAM})", "{\"@\":{\"program\":\"syslog-ng\"}}");
  assert_template_format("$(format-json .program.n@me=${PROGRAM})", "{\"_program\":{\"n@me\":\"syslog-ng\"}}");
  assert_template_format("$(format-json .program.@name=${PROGRAM})", "{\"_program\":{\"@name\":\"syslog-ng\"}}");
}

void
test_format_json_key(void)
{
  assert_template_format("$(format-json --key PID)", "{\"PID\":\"23323\"}");
  assert_template_format("$(format-json --key HOST)", "{\"HOST\":\"bzorp\"}");
  assert_template_format("$(format-json --key MESSAGE)", "{\"MESSAGE\":\"árvíztűrőtükörfúrógép\"}");
  assert_template_format("$(format-json --key HOST --key MESSAGE)", "{\"MESSAGE\":\"árvíztűrőtükörfúrógép\",\"HOST\":\"bzorp\"}");

  assert_template_format("$(format-json --scope selected-macros --key MSG)", "{\"TAGS\":\"alma,korte,citrom\",\"SOURCEIP\":\"10.11.12.13\",\"SEQNUM\":\"999\",\"PROGRAM\":\"syslog-ng\",\"PRIORITY\":\"err\",\"PID\":\"23323\",\"MSG\":\"árvíztűrőtükörfúrógép\",\"MESSAGE\":\"árvíztűrőtükörfúrógép\",\"HOST\":\"bzorp\",\"FACILITY\":\"local3\",\"DATE\":\"Feb 11 10:34:56\"}");

  assert_template_format("$(format-json --key MSG)", "{\"MSG\":\"árvíztűrőtükörfúrógép\"}");
  assert_template_format("$(format-json --key DATE)", "{\"DATE\":\"Feb 11 10:34:56\"}");
  assert_template_format("$(format-json --key PRI)", "{\"PRI\":\"155\"}");
}

void
test_format_json_rekey(void)
{
  assert_template_format("$(format-json .msg.text=dotted --rekey .* --shift 1 --add-prefix _)",
                         "{\"_msg\":{\"text\":\"dotted\"}}");
}

void
test_format_json_with_type_hints(void)
{
  assert_template_format("$(format-json i32=int32(1234))",
                         "{\"i32\":1234}");
  assert_template_format("$(format-json \"i=ifoo(\")",
                         "{\"i\":\"ifoo(\"}");
  assert_template_format("$(format-json b=boolean(TRUE))",
                         "{\"b\":true}");
}

void
test_format_json_on_error(void)
{
  configuration->template_options.on_error = ON_ERROR_DROP_MESSAGE | ON_ERROR_SILENT;
  assert_template_format("$(format-json x=y bad=boolean(blah) foo=bar)",
                         "");
  assert_template_format("$(format-json x=y bad=int32(blah) foo=bar)",
                         "");
  assert_template_format("$(format-json x=y bad=int64(blah) foo=bar)",
                         "");

  configuration->template_options.on_error = ON_ERROR_DROP_PROPERTY | ON_ERROR_SILENT;
  assert_template_format("$(format-json x=y bad=boolean(blah) foo=bar)",
                         "{\"x\":\"y\",\"foo\":\"bar\"}");
  assert_template_format("$(format-json x=y bad=boolean(blah))",
                         "{\"x\":\"y\"}");
  assert_template_format("$(format-json x=y bad=int32(blah))",
                         "{\"x\":\"y\"}");
  assert_template_format("$(format-json x=y bad=int64(blah))",
                         "{\"x\":\"y\"}");

  configuration->template_options.on_error = ON_ERROR_FALLBACK_TO_STRING | ON_ERROR_SILENT;
  assert_template_format("$(format-json x=y bad=boolean(blah) foo=bar)",
                         "{\"x\":\"y\",\"foo\":\"bar\",\"bad\":\"blah\"}");
  assert_template_format("$(format-json x=y bad=boolean(blah))",
                         "{\"x\":\"y\",\"bad\":\"blah\"}");
  assert_template_format("$(format-json x=y bad=int32(blah))",
                         "{\"x\":\"y\",\"bad\":\"blah\"}");
  assert_template_format("$(format-json x=y bad=int64(blah))",
                         "{\"x\":\"y\",\"bad\":\"blah\"}");

}

void
test_format_json_with_utf8(void)
{
  LogMessage *msg = create_empty_message();
  log_msg_set_value_by_name(msg, "UTF8-C2", "\xc2\xbf \xc2\xb6 \xc2\xa9 \xc2\xb1", -1); // ¿ ¶ © ±
  log_msg_set_value_by_name(msg, "UTF8-C3", "\xc3\x88 \xc3\x90", -1); // È Ð

  assert_template_format_msg("$(format-json MSG=\"${UTF8-C2}\")", "{\"MSG\":\"\xc2\xbf \xc2\xb6 \xc2\xa9 \xc2\xb1\"}", msg);
  assert_template_format_msg("$(format-json MSG=\"${UTF8-C3}\")", "{\"MSG\":\"\xc3\x88 \xc3\x90\"}", msg);

  log_msg_unref(msg);
}

int
main(int argc G_GNUC_UNUSED, char *argv[] G_GNUC_UNUSED)
{
  app_startup();
  putenv("TZ=UTC");
  tzset();
  init_template_tests();
  plugin_load_module("json-plugin", configuration, NULL);

  test_format_json();
  test_format_json_key();
  test_format_json_rekey();
  test_format_json_with_type_hints();
  test_format_json_on_error();
  test_format_json_with_utf8();

  deinit_template_tests();
  app_shutdown();
}
