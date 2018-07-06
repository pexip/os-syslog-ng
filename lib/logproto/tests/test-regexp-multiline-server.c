/*
 * Copyright (c) 2013-2014 Balabit
 * Copyright (c) 2013-2014 Balázs Scheidler <balazs.scheidler@balabit.com>
 * Copyright (c) 2014 Viktor Tusa <viktor.tusa@balabit.com>
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

#include "mock-transport.h"
#include "proto_lib.h"
#include "msg_parse_lib.h"
#include "logproto/logproto-regexp-multiline-server.h"

/****************************************************************************************
 * LogProtoREMultiLineServer
 ****************************************************************************************/

static void
test_lines_separated_with_prefix(gboolean input_is_stream)
{
  LogProtoServer *proto;
  MultiLineRegexp *re;

  proto = log_proto_prefix_garbage_multiline_server_new(
            /* 32 bytes max line length, which means that the complete
             * multi-line block plus one additional line must fit into 32
             * bytes. */
            (input_is_stream ? log_transport_mock_stream_new : log_transport_mock_records_new)(
              "Foo First Line\n"
              "Foo Second Line\n"
              "Foo Third Line\n"
              "Foo Multiline\n"
              "multi\n"
              "Foo final\n", -1,
              LTM_PADDING,
              LTM_EOF),
            get_inited_proto_server_options(),
            re = multi_line_regexp_compile("^Foo", NULL), NULL);

  assert_proto_server_fetch(proto, "Foo First Line", -1);
  assert_proto_server_fetch(proto, "Foo Second Line", -1);
  assert_proto_server_fetch(proto, "Foo Third Line", -1);
  assert_proto_server_fetch(proto, "Foo Multiline\nmulti", -1);

  log_proto_server_free(proto);
  log_proto_server_options_destroy(&proto_server_options);
  multi_line_regexp_free(re);
}

static void
test_lines_separated_with_prefix_and_garbage(gboolean input_is_stream)
{
  LogProtoServer *proto;
  MultiLineRegexp *re1, *re2;

  proto = log_proto_prefix_garbage_multiline_server_new(
            /* 32 bytes max line length, which means that the complete
             * multi-line block plus one additional line must fit into 32
             * bytes. */
            (input_is_stream ? log_transport_mock_stream_new : log_transport_mock_records_new)(
              "Foo First Line Bar\n"
              "Foo Second Line Bar\n"
              "Foo Third Line Bar\n"
              "Foo Multiline\n"
              "multi Bar\n"
              "Foo final\n", -1,
              LTM_PADDING,
              LTM_EOF),
            get_inited_proto_server_options(),
            re1 = multi_line_regexp_compile("^Foo", NULL),
            re2 = multi_line_regexp_compile(" Bar$", NULL));

  assert_proto_server_fetch(proto, "Foo First Line", -1);
  assert_proto_server_fetch(proto, "Foo Second Line", -1);
  assert_proto_server_fetch(proto, "Foo Third Line", -1);
  assert_proto_server_fetch(proto, "Foo Multiline\nmulti", -1);

  log_proto_server_free(proto);
  log_proto_server_options_destroy(&proto_server_options);
  multi_line_regexp_free(re1);
  multi_line_regexp_free(re2);
}

static void
test_lines_separated_with_prefix_and_suffix(gboolean input_is_stream)
{
  LogProtoServer *proto;
  MultiLineRegexp *re1, *re2;

  proto = log_proto_prefix_suffix_multiline_server_new(
            /* 32 bytes max line length, which means that the complete
             * multi-line block plus one additional line must fit into 32
             * bytes. */
            (0 && input_is_stream ? log_transport_mock_stream_new : log_transport_mock_records_new)(
              "prefix first suffix garbage\n"
              "prefix multi\n"
              "suffix garbage\n"
              "prefix final\n", -1,
              LTM_PADDING,
              LTM_EOF),
            get_inited_proto_server_options(),
            re1 = multi_line_regexp_compile("^prefix", NULL),
            re2 = multi_line_regexp_compile("suffix", NULL));

  assert_proto_server_fetch(proto, "prefix first suffix", -1);
  assert_proto_server_fetch(proto, "prefix multi\nsuffix", -1);

  log_proto_server_free(proto);
  log_proto_server_options_destroy(&proto_server_options);
  multi_line_regexp_free(re1);
  multi_line_regexp_free(re2);
};


static void
test_lines_separated_with_garbage(gboolean input_is_stream)
{
  LogProtoServer *proto;
  MultiLineRegexp *re;

  proto = log_proto_prefix_garbage_multiline_server_new(
            /* 32 bytes max line length, which means that the complete
             * multi-line block plus one additional line must fit into 32
             * bytes. */
            (input_is_stream ? log_transport_mock_stream_new : log_transport_mock_records_new)(
              "Foo First Line Bar\n"
              "Foo Second Line Bar\n"
              "Foo Third Line Bar\n"
              "Foo Multiline\n"
              "multi Bar\n"
              "Foo final\n", -1,
              LTM_PADDING,
              LTM_EOF),
            get_inited_proto_server_options(),
            NULL,
            re = multi_line_regexp_compile(" Bar$", NULL));

  assert_proto_server_fetch(proto, "Foo First Line", -1);
  assert_proto_server_fetch(proto, "Foo Second Line", -1);
  assert_proto_server_fetch(proto, "Foo Third Line", -1);
  assert_proto_server_fetch(proto, "Foo Multiline\nmulti", -1);

  log_proto_server_free(proto);
  log_proto_server_options_destroy(&proto_server_options);
  multi_line_regexp_free(re);
}

static void
test_first_line_without_prefix(gboolean input_is_stream)
{
  LogProtoServer *proto;
  MultiLineRegexp *re;

  proto = log_proto_prefix_garbage_multiline_server_new(
            /* 32 bytes max line length, which means that the complete
             * multi-line block plus one additional line must fit into 32
             * bytes. */
            (input_is_stream ? log_transport_mock_stream_new : log_transport_mock_records_new)(
              "First Line\n"
              "Foo Second Line\n"
              "Foo Third Line\n"
              "Foo Multiline\n"
              "multi\n"
              "Foo final\n", -1,
              LTM_PADDING,
              LTM_EOF),
            get_inited_proto_server_options(),
            re = multi_line_regexp_compile("^Foo", NULL),
            NULL);

  assert_proto_server_fetch(proto, "First Line", -1);
  assert_proto_server_fetch(proto, "Foo Second Line", -1);
  assert_proto_server_fetch(proto, "Foo Third Line", -1);
  assert_proto_server_fetch(proto, "Foo Multiline\nmulti", -1);

  log_proto_server_free(proto);
  log_proto_server_options_destroy(&proto_server_options);
  multi_line_regexp_free(re);
}

void
test_log_proto_regexp_multiline_server(void)
{
  PROTO_TESTCASE(test_lines_separated_with_prefix, FALSE);
  PROTO_TESTCASE(test_lines_separated_with_prefix, TRUE);
  PROTO_TESTCASE(test_lines_separated_with_prefix_and_garbage, FALSE);
  PROTO_TESTCASE(test_lines_separated_with_prefix_and_garbage, TRUE);
  PROTO_TESTCASE(test_lines_separated_with_prefix_and_suffix, FALSE);
  PROTO_TESTCASE(test_lines_separated_with_prefix_and_suffix, TRUE);
  PROTO_TESTCASE(test_lines_separated_with_garbage, FALSE);
  PROTO_TESTCASE(test_lines_separated_with_garbage, TRUE);
  PROTO_TESTCASE(test_first_line_without_prefix, FALSE);
  PROTO_TESTCASE(test_first_line_without_prefix, TRUE);
}
