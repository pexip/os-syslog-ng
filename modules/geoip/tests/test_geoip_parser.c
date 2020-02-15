/*
 * Copyright (c) 2016 Balabit
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
 */
#include "testutils.h"
#include "geoip-parser.h"
#include "apphook.h"
#include "msg_parse_lib.h"

#define geoip_parser_testcase_begin(func, args)             \
  do                                                            \
    {                                                           \
      testcase_begin("%s(%s)", func, args);                     \
      geoip_parser = geoip_parser_new(configuration);     \
    }                                                           \
  while (0)

#define geoip_parser_testcase_end()                           \
  do                                                            \
    {                                                           \
      log_pipe_deinit(&geoip_parser->super);      \
      log_pipe_unref(&geoip_parser->super);                     \
      testcase_end();                                           \
    }                                                           \
  while (0)

#define KV_PARSER_TESTCASE(x, ...) \
  do {                                                          \
      geoip_parser_testcase_begin(#x, #__VA_ARGS__);      \
      x(__VA_ARGS__);                                           \
      geoip_parser_testcase_end();                              \
  } while(0)

LogParser *geoip_parser;

static LogMessage *
parse_geoip_into_log_message_no_check(const gchar *input)
{
  LogMessage *msg;
  LogPathOptions path_options = LOG_PATH_OPTIONS_INIT;
  LogParser *cloned_parser;
  gboolean success;

  cloned_parser = (LogParser *) log_pipe_clone(&geoip_parser->super);
  log_pipe_init(&cloned_parser->super);
  msg = log_msg_new_empty();
  log_msg_set_value(msg, LM_V_MESSAGE, input, -1);
  success = log_parser_process_message(cloned_parser, &msg, &path_options);
  if (!success)
    {
      log_msg_unref(msg);
      msg = NULL;
    }
  log_pipe_deinit(&cloned_parser->super);
  log_pipe_unref(&cloned_parser->super);
  return msg;
}

static LogMessage *
parse_geoip_into_log_message(const gchar *input)
{
  LogMessage *msg;

  msg = parse_geoip_into_log_message_no_check(input);
  assert_not_null(msg, "expected geoip-parser success and it returned failure, input=%s", input);
  return msg;
}

static void
test_geoip_parser_basics(void)
{
  LogMessage *msg;

  msg = parse_geoip_into_log_message("217.20.130.99");
  assert_log_message_value(msg, log_msg_get_value_handle(".geoip.country_code"), "HU");
  log_msg_unref(msg);

  geoip_parser_set_prefix(geoip_parser, ".prefix.");
  msg = parse_geoip_into_log_message("217.20.130.99");
  assert_log_message_value(msg, log_msg_get_value_handle(".prefix.country_code"), "HU");
  log_msg_unref(msg);
}

static void
test_geoip_parser_uses_template_to_parse_input(void)
{
  LogMessage *msg;
  LogTemplate *template;

  template = log_template_new(NULL, NULL);
  log_template_compile(template, "217.20.130.99", NULL);
  log_parser_set_template(geoip_parser, template);
  msg = parse_geoip_into_log_message("8.8.8.8");
  assert_log_message_value(msg, log_msg_get_value_handle(".geoip.country_code"), "HU");
  log_msg_unref(msg);
}

static void
test_geoip_parser(void)
{
  KV_PARSER_TESTCASE(test_geoip_parser_basics);
  KV_PARSER_TESTCASE(test_geoip_parser_uses_template_to_parse_input);
}

int
main(int argc G_GNUC_UNUSED, char *argv[] G_GNUC_UNUSED)
{
  app_startup();

  test_geoip_parser();
  app_shutdown();
  return 0;
}
