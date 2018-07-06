/*
 * Copyright (c) 2002-2014 Balabit
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
#include "testutils.h"
#include "type-hinting.h"
#include "apphook.h"

#include <stdio.h>
#include <string.h>
#include <math.h>

#define assert_type_hint(hint,expected)                                 \
  do                                                                    \
    {                                                                   \
      TypeHint t;                                                       \
      GError *e = NULL;                                                 \
                                                                        \
      assert_true(type_hint_parse(hint, &t, &e),                        \
                  "Parsing '%s' as type hint", hint);                   \
                                                                        \
      assert_gint(t, expected,                                          \
                  "Parsing '%s' as type hint results in correct type", hint); \
    } while(0)                                                          \

static void
assert_error(GError *error, gint code, const gchar *expected_message)
{
  assert_not_null(error, "GError expected to be non-NULL");

  assert_gint(error->code, code, "GError error code is as expected");
  if (expected_message)
    assert_string(error->message, expected_message, "GError error message is as expected");
}

static void
test_type_hint_parse(void)
{
  testcase_begin("Testing type hint parsing");

  assert_type_hint(NULL, TYPE_HINT_STRING);
  assert_type_hint("string", TYPE_HINT_STRING);
  assert_type_hint("literal", TYPE_HINT_LITERAL);
  assert_type_hint("boolean", TYPE_HINT_BOOLEAN);
  assert_type_hint("int", TYPE_HINT_INT32);
  assert_type_hint("int32", TYPE_HINT_INT32);
  assert_type_hint("int64", TYPE_HINT_INT64);
  assert_type_hint("double", TYPE_HINT_DOUBLE);
  assert_type_hint("datetime", TYPE_HINT_DATETIME);
  assert_type_hint("default", TYPE_HINT_DEFAULT);

  TypeHint t;
  GError *e = NULL;
  assert_false(type_hint_parse("invalid-hint", &t, &e),
               "Parsing an invalid hint results in an error.");

  assert_error(e, TYPE_HINTING_INVALID_TYPE, "Unknown type specified in type hinting: invalid-hint");

  testcase_end();
}

#define assert_type_cast(target,value,out)                              \
  do                                                                    \
    {                                                                   \
      assert_true(type_cast_to_##target(value, out, &error),            \
                  "Casting '%s' to %s works", value, #target);          \
      assert_no_error(error, "Successful casting returns no error");    \
    } while(0)

#define assert_type_cast_fail(target,value,out)                 \
  do                                                            \
    {                                                           \
      assert_false(type_cast_to_##target(value, out, &error),   \
                   "Casting '%s' to %s fails", value, #target); \
      assert_error(error, TYPE_HINTING_INVALID_CAST, NULL);     \
      error = NULL;                                             \
    } while(0)

#define assert_bool_cast(value,expected)                                \
  do                                                                    \
    {                                                                   \
      gboolean ob;                                                      \
      assert_type_cast(boolean, value, &ob);                            \
      assert_gboolean(ob, expected, "'%s' casted to boolean is %s",     \
                      value, #expected);                                \
    } while(0)

#define assert_double_cast(value,expected)                              \
  do                                                                    \
    {                                                                   \
      gdouble od;                                                       \
      assert_type_cast(double, value, &od);                             \
      assert_gdouble(od, expected, "'%s' casted to double is %s",       \
                      value, #expected);                                \
    } while(0)

#define assert_int_cast(value,width,expected)                           \
  do                                                                    \
    {                                                                   \
      gint##width i;                                                    \
      assert_type_cast(int##width, value, &i);                          \
      assert_gint##width(i, expected, "'%s' casted to int%s is %u",     \
                         value, expected);                              \
    } while(0) \

static void
test_type_cast(void)
{
  GError *error = NULL;
  gint32 i32;
  gint64 i64;
  guint64 dt;
  gdouble d;

  testcase_begin("Testing type casting");

  /* Boolean */

  assert_bool_cast("True", TRUE);
  assert_bool_cast("true", TRUE);
  assert_bool_cast("1", TRUE);
  assert_bool_cast("totally true", TRUE);
  assert_bool_cast("False", FALSE);
  assert_bool_cast("false", FALSE);
  assert_bool_cast("0", FALSE);
  assert_bool_cast("fatally false", FALSE);

  {
    gboolean ob;
    assert_type_cast_fail(boolean, "booyah", &ob);
  }

  /* int32 */
  assert_int_cast("12345", 32, 12345);
  assert_type_cast_fail(int32, "12345a", &i32);

  /* int64 */
  assert_int_cast("12345", 64, 12345);
  assert_type_cast_fail(int64, "12345a", &i64);

  /* double */
  assert_double_cast("1.0", 1.0);
  assert_type_cast_fail(double, "2.0bad", &d);
  assert_type_cast_fail(double, "bad", &d);
  assert_type_cast_fail(double, "", &d);
  assert_type_cast_fail(double, "1e1000000", &d);
  assert_type_cast_fail(double, "-1e1000000", &d);
  assert_double_cast("1e-100000000", 0.0);
#ifdef INFINITY
  assert_double_cast("INF", INFINITY);
#endif

  /* datetime */
  assert_type_cast(datetime_int, "12345", &dt);
  assert_guint64(dt, 12345000, "Casting '12345' to datetime works");
  assert_type_cast(datetime_int, "12345.5", &dt);
  assert_guint64(dt, 12345500, "Casting '12345.5' to datetime works");
  assert_type_cast(datetime_int, "12345.54", &dt);
  assert_guint64(dt, 12345540, "Casting '12345.54' to datetime works");
  assert_type_cast(datetime_int, "12345.543", &dt);
  assert_guint64(dt, 12345543, "Casting '12345.543' to datetime works");
  assert_type_cast(datetime_int, "12345.54321", &dt);
  assert_guint64(dt, 12345543, "Casting '12345.54321' to datetime works");

  assert_type_cast_fail(datetime_int, "invalid", &dt);

  testcase_end();
}

int
main (void)
{
  app_startup();

  test_type_hint_parse();
  test_type_cast();

  app_shutdown();

  return 0;
}
