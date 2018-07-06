/*
 * Copyright (c) 2010-2014 Balabit
 * Copyright (c) 2010-2014 Balázs Scheidler <balazs.scheidler@balabit.com>
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

gboolean fail = FALSE;
gboolean verbose = FALSE;

#define test_fail(fmt, args...) \
do {\
  printf(fmt, ##args); \
  fail = TRUE; \
} while (0);

#define test_msg(fmt, args...) \
do { \
  if (verbose) printf(fmt, ##args); \
} while (0);



gchar *pdb_parser_skeleton_prefix ="<?xml version='1.0' encoding='UTF-8'?>\
<patterndb version='4' pub_date='2010-02-22'>\
  <ruleset name='test1_program' id='480de478-d4a6-4a7f-bea4-0c0245d361e1'>\
    <patterns>\
      <pattern>test</pattern>\
    </patterns>\
    <rules>\
      <rule id='1' class='test1' provider='my'>\
        <patterns>\
          <pattern>" /* HERE COMES THE GENERATED PATTERN */ ;

gchar *pdb_parser_skeleton_postfix =  /* HERE IS THE GENERATED PATTERN */ "</pattern>\
        </patterns>\
      </rule>\
    </rules>\
  </ruleset>\
</patterndb>";


void
test_pattern(const gchar *pattern, const gchar *rule, gboolean match)
{
  gboolean result;
  LogMessage *msg = log_msg_new_empty();

  log_msg_set_value(msg, LM_V_HOST, MYHOST, strlen(MYHOST));
  log_msg_set_value(msg, LM_V_PROGRAM, "test", strlen(MYHOST));
  log_msg_set_value(msg, LM_V_MESSAGE, pattern, strlen(pattern));

  result = pattern_db_process(patterndb, msg);

  if (match)
    {
      assert_true(result, "Value '%s' is not matching for pattern '%s'\n", rule, pattern);
    }
  else
    {
      assert_false(result, "Value '%s' is matching for pattern '%s'\n", rule, pattern);
    }

  log_msg_unref(msg);
}

void
test_parser(gchar **test)
{
  GString *str;
  gsize i = 1;

  str = g_string_new(pdb_parser_skeleton_prefix);
  g_string_append(str, test[0]);
  g_string_append(str, pdb_parser_skeleton_postfix);

  _load_pattern_db_from_string(str->str);
  g_string_free(str, TRUE);
  while(test[i] != NULL)
    test_pattern(test[i++], test[0], TRUE);
  i++;
  while(test[i] != NULL)
    test_pattern(test[i++], test[0], FALSE);

  _destroy_pattern_db();
}

gchar * test1 [] = {
"@ANYSTRING:TEST@",
"ab ba ab",
"ab ba ab",
"1234ab",
"ab1234",
"1.2.3.4",
"ab  1234  ba",
"&lt;ab ba&gt;",
NULL,
NULL
};

gchar * test2 [] = {
"@DOUBLE:TEST@",
"1234",
"1234.567",
"1.2.3.4",
"1234ab",
NULL, // not match
"ab1234",NULL
};

gchar * test3 [] = {
"@ESTRING:TEST:endmark@",
"ab ba endmark",
NULL,
"ab ba",NULL
};

gchar * test4 [] = {
"@ESTRING:TEST:&gt;@",
"ab ba > ab",
NULL,
"ab ba",NULL
};

gchar * test5 [] = {
"@FLOAT:TEST@",
"1234",
"1234.567",
"1.2.3.4",
"1234ab",
NULL, // not match
"ab1234",NULL
};

gchar * test6 [] = {
"@SET:TEST: 	@",
" a ",
"  a ",
" 	a ",
" 	 a ",
NULL, // not match
"ab1234",NULL
};

gchar * test7 [] = {
"@IPv4:TEST@",
"1.2.3.4",
"0.0.0.0",
"255.255.255.255",
NULL,
"256.256.256.256",
"1234",
"ab1234",
"ab1.2.3.4",
"1,2,3,4",NULL
};

gchar * test8 [] = {
"@IPv6:TEST@",
"2001:0db8:0000:0000:0000:0000:1428:57ab",
"2001:0db8:0000:0000:0000::1428:57ab",
"2001:0db8:0:0:0:0:1428:57ab",
"2001:0db8:0:0::1428:57ab",
"2001:0db8::1428:57ab",
"2001:db8::1428:57ab",
NULL,
"2001:0db8::34d2::1428:57ab",NULL
};

gchar * test9 [] = {
"@IPvANY:TEST@",
"1.2.3.4",
"0.0.0.0",
"255.255.255.255",
"2001:0db8:0000:0000:0000:0000:1428:57ab",
"2001:0db8:0000:0000:0000::1428:57ab",
"2001:0db8:0:0:0:0:1428:57ab",
"2001:0db8:0:0::1428:57ab",
"2001:0db8::1428:57ab",
"2001:db8::1428:57ab",
NULL,
"256.256.256.256",
"1234",
"ab1234",
"ab1.2.3.4",
"1,2,3,4",
"2001:0db8::34d2::1428:57ab",NULL
};

gchar * test10 [] = {
"@NUMBER:TEST@",
"1234",
"1.2",
"1.2.3.4",
"1234ab",
NULL,
"ab1234",
NULL
};

gchar * test11 [] = {
"@QSTRING:TEST:&lt;&gt;@",
"<aa bb>",
"< aabb >",
NULL,
"aabb>",
"<aabb",NULL
};

gchar * test12 [] = {
"@STRING:TEST@",
"aabb",
"aa bb",
"1234",
"ab1234",
"1234bb",
"1.2.3.4",
NULL,NULL
};

gchar **parsers[] = {test1, test2, test3, test4, test5, test6, test7, test8, test9, test10, test11, test12, NULL};

void
test_patterndb_parsers()
{
  gint i;

  for (i = 0; parsers[i]; i++)
    {
      test_parser(parsers[i]);
    }
}
