/*
 * Copyright (c) 2017 Balabit
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


#include <criterion/criterion.h>
#include <criterion/parameterized.h>
#include "xml.h"
#include "scanner/xml-scanner/xml-scanner.h"
#include "apphook.h"
#include "scratch-buffers.h"

void
setup(void)
{
  configuration = cfg_new_snippet();
  app_startup();
}

void
teardown(void)
{
  scratch_buffers_explicit_gc();
  app_shutdown();
  cfg_free(configuration);
}

typedef struct
{
  gboolean forward_invalid;
  gboolean strip_whitespaces;
  gboolean *create_lists;
  GList *exclude_tags;
  const gchar *prefix;
} XMLParserTestOptions;

static LogParser *
_construct_xml_parser(XMLParserTestOptions options)
{
  LogParser *xml_parser = xml_parser_new(configuration);
  xml_parser_set_forward_invalid(xml_parser, options.forward_invalid);
  if (options.create_lists != NULL)
    xml_parser_allow_create_lists(xml_parser, *options.create_lists);
  if (options.strip_whitespaces)
    xml_scanner_options_set_strip_whitespaces(xml_parser_get_scanner_options(xml_parser), options.strip_whitespaces);
  if (options.exclude_tags)
    xml_scanner_options_set_and_compile_exclude_tags(xml_parser_get_scanner_options(xml_parser), options.exclude_tags);
  if (options.prefix)
    xml_parser_set_prefix(xml_parser, options.prefix);

  LogPipe *cloned = xml_parser_clone(&xml_parser->super);
  log_pipe_init(cloned);
  log_pipe_unref(&xml_parser->super);
  return (LogParser *)cloned;
}

TestSuite(xmlparser, .init = setup, .fini = teardown);

typedef struct
{
  const gchar *input;
} XMLFailTestCase;

ParameterizedTestParameters(xmlparser, invalid_inputs)
{
  static XMLFailTestCase test_cases[] =
  {
    {"simple string"},
    {"<tag></missingtag>"},
    {"<tag></tag></extraclosetag>"},
    {"<tag><tag></tag>"},
    {"<tag1><tag2>closewrongorder</tag1></tag2>"},
    {"<tag id=\"missingquote></tag>"},
    {"<tag id='missingquote></tag>"},
    {"<tag id=missingquote\"></tag>"},
    {"<tag id=missingquote'></tag>"},
    {"<space in tag/>"},
    {"</>"},
    {"<tag></tag>>"},
  };

  return cr_make_param_array(XMLFailTestCase, test_cases, sizeof(test_cases) / sizeof(test_cases[0]));
}

ParameterizedTest(XMLFailTestCase *test_case, xmlparser, invalid_inputs)
{
  LogParser *xml_parser = _construct_xml_parser((XMLParserTestOptions) {});

  LogMessage *msg = log_msg_new_empty();
  log_msg_set_value(msg, LM_V_MESSAGE, test_case->input, -1);

  LogPathOptions path_options = LOG_PATH_OPTIONS_INIT;
  cr_assert_not(log_parser_process_message(xml_parser, &msg, &path_options));

  log_pipe_deinit((LogPipe *)xml_parser);
  log_pipe_unref((LogPipe *)xml_parser);
  log_msg_unref(msg);
}

typedef struct
{
  const gchar *input;
  const gchar *key;
  const gchar *value;
} ValidXMLTestCase;

ParameterizedTestParameters(xmlparser, valid_inputs)
{
  static ValidXMLTestCase test_cases[] =
  {
    {"<tag1>value1</tag1>", ".xml.tag1", "value1"},
    {"<tag1 attr='attr_value'>value1</tag1>", ".xml.tag1._attr", "attr_value"},
    {"<tag1><tag2>value2</tag2></tag1>", ".xml.tag1.tag2", "value2"},
    {"<tag1>part1<tag2>value2</tag2>part2</tag1>", ".xml.tag1", "part1part2"},
    {"<tag1><tag11></tag11><tag12><tag121>value</tag121></tag12></tag1>", ".xml.tag1.tag12.tag121", "value"},
    {"<tag1><tag11></tag11><tag12><tag121 attr1='1' attr2='2'>value</tag121></tag12></tag1>", ".xml.tag1.tag12.tag121._attr1", "1"},
    {"<tag1><tag11></tag11><tag12><tag121 attr1='1' attr2='2'>value</tag121></tag12></tag1>", ".xml.tag1.tag12.tag121._attr2", "2"},
    {"<tag1><tag1>t11.1</tag1><tag1>t11.2</tag1></tag1>", ".xml.tag1.tag1", "t11.1,t11.2"},
  };

  return cr_make_param_array(ValidXMLTestCase, test_cases, sizeof(test_cases) / sizeof(test_cases[0]));
}

ParameterizedTest(ValidXMLTestCase *test_cases, xmlparser, valid_inputs)
{
  LogParser *xml_parser = _construct_xml_parser((XMLParserTestOptions) {});

  LogMessage *msg = log_msg_new_empty();
  log_msg_set_value(msg, LM_V_MESSAGE, test_cases->input, -1);

  LogPathOptions path_options = LOG_PATH_OPTIONS_INIT;
  log_parser_process_message(xml_parser, &msg, &path_options);

  const gchar *value = log_msg_get_value_by_name(msg, test_cases->key, NULL);

  cr_assert_str_eq(value, test_cases->value, "key: %s | value: %s != %s (expected)", test_cases->key, value,
                   test_cases->value);

  log_pipe_deinit((LogPipe *)xml_parser);
  log_pipe_unref((LogPipe *)xml_parser);
  log_msg_unref(msg);
}

typedef struct
{
  const gchar *input;
  gboolean create_lists;
  const gchar *key;
  const gchar *value;
} ListCreateTestCase;

ParameterizedTestParameters(xmlparser, list_quoting_array_elements)
{
  static ListCreateTestCase test_cases[] =
  {
    {
      "<tag1><simple_namevalue> value,2 </simple_namevalue></tag1>", .create_lists = FALSE,
      ".xml.tag1.simple_namevalue", " value,2 "
    },
    {
      "<tag1><simple_namevalue> value,2 </simple_namevalue></tag1>", .create_lists = TRUE,
      ".xml.tag1.simple_namevalue", "\" value,2 \""
    },
    {
      "<events><data>1</data><data> 2 </data></events>", .create_lists = TRUE,
      ".xml.events.data", "1,\" 2 \""
    },
    {
      "<events><data>1</data><data> 2 </data><data>3,</data><data>4</data></events>", .create_lists = TRUE,
      ".xml.events.data", "1,\" 2 \",\"3,\",4"
    },
    {
      "<noquotes><data>one</data><data>two</data><data>three</data></noquotes>", .create_lists = TRUE,
      ".xml.noquotes.data", "one,two,three"
    },
    {
      "<array><data>,first element</data><data>second element</data><data>Third element</data></array>",
      .create_lists = TRUE,
      ".xml.array.data", "\",first element\",\"second element\",\"Third element\""
    },
    {
      "<array><data>\"Quoted elements escaped with single-quote\"</data><data>unquoted with double-quotes</data></array>",
      .create_lists = TRUE,
      ".xml.array.data", "'\"Quoted elements escaped with single-quote\"',\"unquoted with double-quotes\""
    },
    {
      "<array><data>\'Single quoted becomes quoted\'</data><data>simple</data></array>", .create_lists = TRUE,
      ".xml.array.data", "\"'Single quoted becomes quoted'\",simple"
    },
    {
      "<events><data>first</data><data>second</data></events>", .create_lists = FALSE,
      ".xml.events.data", "firstsecond"
    },
    {
      "<events><data>first</data><data>second, long entry</data></events>", .create_lists = FALSE,
      ".xml.events.data", "firstsecond, long entry"
    },
  };

  return cr_make_param_array(ListCreateTestCase, test_cases, sizeof(test_cases) / sizeof(test_cases[0]));
}

ParameterizedTest(ListCreateTestCase *test_cases, xmlparser, list_quoting_array_elements)
{
  LogParser *xml_parser = _construct_xml_parser((XMLParserTestOptions)
  {
    .create_lists = &test_cases->create_lists
  });

  LogMessage *msg = log_msg_new_empty();
  log_msg_set_value(msg, LM_V_MESSAGE, test_cases->input, -1);

  LogPathOptions path_options = LOG_PATH_OPTIONS_INIT;
  log_parser_process_message(xml_parser, &msg, &path_options);

  const gchar *value = log_msg_get_value_by_name(msg, test_cases->key, NULL);

  cr_assert_str_eq(value, test_cases->value, "key: %s | value: %s != %s (expected)", test_cases->key, value,
                   test_cases->value);

  log_pipe_deinit((LogPipe *)xml_parser);
  log_pipe_unref((LogPipe *)xml_parser);
  log_msg_unref(msg);
}

Test(xmlparser, test_drop_invalid)
{
  LogParser *xml_parser = _construct_xml_parser((XMLParserTestOptions) {});

  LogMessage *msg = log_msg_new_empty();
  log_msg_set_value(msg, LM_V_MESSAGE, "<tag>", -1);

  LogPathOptions path_options = LOG_PATH_OPTIONS_INIT;
  xml_parser_set_forward_invalid(xml_parser, FALSE);
  cr_assert_not(log_parser_process_message(xml_parser, &msg, &path_options));

  xml_parser_set_forward_invalid(xml_parser, TRUE);
  cr_assert(log_parser_process_message(xml_parser, &msg, &path_options));

  log_pipe_deinit((LogPipe *)xml_parser);
  log_pipe_unref((LogPipe *)xml_parser);
  log_msg_unref(msg);
}

typedef struct
{
  const gchar *input;
  gchar *pattern;
  const gchar *key;
  const gchar *value;
} SingleExcludeTagTestCase;

ParameterizedTestParameters(xmlparser, single_exclude_tags)
{
  static SingleExcludeTagTestCase test_cases[] =
  {
    /* Negative */
    {"<longtag>Text</longtag>", "longtag", ".xml.longtag", ""},
    {"<longtag>Text</longtag>", "longt?g", ".xml.longtag", ""},
    {"<longtag>Text</longtag>", "?ongtag", ".xml.longtag", ""},
    {"<longtag>Text</longtag>", "longta?", ".xml.longtag", ""},
    {"<longtag>Text</longtag>", "lon?ta?", ".xml.longtag", ""},
    {"<longtag>Text</longtag>", "longt*", ".xml.longtag", ""},
    {"<longtag>Text</longtag>", "*tag", ".xml.longtag", ""},
    {"<longtag>Text</longtag>", "lo*gtag", ".xml.longtag", ""},
    {"<longtag>Text</longtag>", "long*ag", ".xml.longtag", ""},
    {"<longtag>Text</longtag>", "*", ".xml.longtag", ""},
    /* Positive */
    {"<longtag>Text</longtag>", "longtag_break", ".xml.longtag", "Text"},
    {"<longtag>Text</longtag>", "longt?g_break", ".xml.longtag", "Text"},
    {"<longtag>Text</longtag>", "?ongtag_break", ".xml.longtag", "Text"},
    {"<longtag>Text</longtag>", "longta?_break", ".xml.longtag", "Text"},
    {"<longtag>Text</longtag>", "lon?ta?_break", ".xml.longtag", "Text"},
    {"<longtag>Text</longtag>", "break_longt*", ".xml.longtag", "Text"},
    {"<longtag>Text</longtag>", "lo*gtag_break", ".xml.longtag", "Text"},
    {"<longtag>Text</longtag>", "break_long*ag", ".xml.longtag", "Text"},
    {"<longtag>Text</longtag>", "*tag_break", ".xml.longtag", "Text"},
    /* Complex */
    {"<longtag>Outer<inner>Inner</inner></longtag>", "inner", ".xml.longtag", "Outer"},
    {"<longtag>Outer<inner>Inner</inner></longtag>", "inner", ".xml.longtag.inner", ""},
    {
      "<exclude>excude1Text</exclude><notexclude>notexcludeText<exclude>excude2Text</exclude></notexclude>",
      "exclude", ".xml.exclude", ""
    },
    {
      "<exclude>excude1Text</exclude><notexclude>notexcludeText<exclude>excude2Text</exclude></notexclude>",
      "exclude", ".xml.exclude", ""
    },
    {
      "<exclude>excude1Text</exclude><notexclude>notexcludeText<exclude>excude2Text</exclude></notexclude>",
      "exclude", ".xml.notexclude.exclude", ""
    },
    {
      "<exclude>excude1Text</exclude><notexclude>notexcludeText<exclude>excude2Text</exclude></notexclude>",
      "exclude", ".xml.notexclude", "notexcludeText"
    },
  };

  return cr_make_param_array(SingleExcludeTagTestCase, test_cases, sizeof(test_cases) / sizeof(test_cases[0]));
}

ParameterizedTest(SingleExcludeTagTestCase *test_cases, xmlparser, single_exclude_tags)
{
  GList *exclude_tags = NULL;
  exclude_tags = g_list_append(exclude_tags, test_cases->pattern);

  LogParser *xml_parser = _construct_xml_parser((XMLParserTestOptions)
  {
    .exclude_tags = exclude_tags
  });

  LogMessage *msg = log_msg_new_empty();
  log_msg_set_value(msg, LM_V_MESSAGE, test_cases->input, -1);

  LogPathOptions path_options = LOG_PATH_OPTIONS_INIT;
  log_parser_process_message(xml_parser, &msg, &path_options);

  const gchar *value = log_msg_get_value_by_name(msg, test_cases->key, NULL);
  cr_assert_str_eq(value, test_cases->value, "key: %s | value: %s, should be %s", test_cases->key, value,
                   test_cases->value);

  log_pipe_deinit((LogPipe *)xml_parser);
  log_pipe_unref((LogPipe *)xml_parser);
  log_msg_unref(msg);

  g_list_free(exclude_tags);
}

Test(xmlparser, test_multiple_exclude_tags)
{
  GList *exclude_tags = NULL;
  exclude_tags = g_list_append(exclude_tags, "tag1");
  exclude_tags = g_list_append(exclude_tags, "tag2");
  exclude_tags = g_list_append(exclude_tags, "inner*");

  LogParser *xml_parser = _construct_xml_parser((XMLParserTestOptions)
  {
    .exclude_tags = exclude_tags
  });

  LogMessage *msg = log_msg_new_empty();
  log_msg_set_value(msg, LM_V_MESSAGE,
                    "<tag1>Text1</tag1><tag2>Text2</tag2><tag3>Text3<innertag>TextInner</innertag></tag3>", -1);

  const gchar *value;
  LogPathOptions path_options = LOG_PATH_OPTIONS_INIT;
  log_parser_process_message(xml_parser, &msg, &path_options);

  value = log_msg_get_value_by_name(msg, ".xml.tag1", NULL);
  cr_assert_str_eq(value, "");
  value = log_msg_get_value_by_name(msg, ".xml.tag2", NULL);
  cr_assert_str_eq(value, "");
  value = log_msg_get_value_by_name(msg, ".xml.tag3", NULL);
  cr_assert_str_eq(value, "Text3");
  value = log_msg_get_value_by_name(msg, ".xml.tag3.innertag", NULL);
  cr_assert_str_eq(value, "");

  log_pipe_deinit((LogPipe *)xml_parser);
  log_pipe_unref((LogPipe *)xml_parser);
  log_msg_unref(msg);

  g_list_free(exclude_tags);
}

Test(xmlparser, test_strip_whitespaces)
{
  LogParser *xml_parser = _construct_xml_parser((XMLParserTestOptions)
  {
    .strip_whitespaces = TRUE
  });

  LogMessage *msg = log_msg_new_empty();
  log_msg_set_value(msg, LM_V_MESSAGE,
                    "<tag> \n\t part1 <tag2/> part2 \n\n</tag>", -1);

  const gchar *value;
  LogPathOptions path_options = LOG_PATH_OPTIONS_INIT;
  log_parser_process_message(xml_parser, &msg, &path_options);

  value = log_msg_get_value_by_name(msg, ".xml.tag", NULL);
  cr_assert_str_eq(value, "part1part2");

  log_pipe_deinit((LogPipe *)xml_parser);
  log_pipe_unref((LogPipe *)xml_parser);
  log_msg_unref(msg);
}

typedef struct
{
  const gchar *input;
  const gchar *prefix;
  const gchar *key;
  const gchar *value;
} PrefixTestCase;

ParameterizedTestParameters(xmlparser, test_prefix)
{
  static PrefixTestCase test_cases[] =
  {
    {"<tag>default_prefix</tag>", NULL, ".xml.tag", "default_prefix"},
    {"<tag>foo</tag>", "", "tag", "foo"},
    {"<tag>foobar</tag>", ".xmlparser", ".xmlparser.tag", "foobar"},
    {"<tag>baz</tag>", ".meta.", ".meta.tag", "baz"},
    {"<top><t1>asd</t1><t2>jkl</t2></top>", "", "top.t2", "jkl"},
    {"<top><t1>1</t1><t2><t3>3</t3></t2></top>", "", "top.t2.t3", "3"},
    {"<top><t1>1</t1><t2><t3>3</t3></t2><misc>value</misc></top>", "", "top.misc", "value"},
  };
  return cr_make_param_array(PrefixTestCase, test_cases, sizeof(test_cases)/sizeof(test_cases[0]));
}

ParameterizedTest(PrefixTestCase *test_cases, xmlparser, test_prefix)
{
  LogParser *xml_parser = _construct_xml_parser((XMLParserTestOptions)
  {
    .prefix = test_cases->prefix
  });

  LogMessage *msg = log_msg_new_empty();
  log_msg_set_value(msg, LM_V_MESSAGE, test_cases->input, -1);

  LogPathOptions path_options = LOG_PATH_OPTIONS_INIT;
  log_parser_process_message(xml_parser, &msg, &path_options);

  const gchar *value = log_msg_get_value_by_name(msg, test_cases->key, NULL);
  cr_assert_str_eq(value, test_cases->value);

  log_pipe_deinit((LogPipe *)xml_parser);
  log_pipe_unref((LogPipe *)xml_parser);
  log_msg_unref(msg);
}
