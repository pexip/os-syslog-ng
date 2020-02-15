#!/usr/bin/env python
#############################################################################
# Copyright (c) 2015-2018 Balabit
#
# This program is free software; you can redistribute it and/or modify it
# under the terms of the GNU General Public License version 2 as published
# by the Free Software Foundation, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
#
# As an additional exemption you are allowed to compile & link against the
# OpenSSL libraries as published by the OpenSSL project. See the file
# COPYING for details.
#
#############################################################################

from src.message_reader.single_line_parser import SingleLineParser


def test_single_line_parser(tc_unittest):
    single_line_parser = SingleLineParser(tc_unittest.get_fake_logger_factory())
    input_buffer = """test message 1
test message 2
test message 3
"""
    single_line_parser.parse_buffer(content_buffer=input_buffer)
    assert single_line_parser.msg_list == ["test message 1\n", "test message 2\n", "test message 3\n"]


def test_single_line_parser_no_line_end(tc_unittest):
    single_line_parser = SingleLineParser(tc_unittest.get_fake_logger_factory())
    input_buffer = "test message 1"
    single_line_parser.parse_buffer(content_buffer=input_buffer)
    assert single_line_parser.msg_list == []


def test_single_line_parser_parsing_multiple_times(tc_unittest):
    single_line_parser = SingleLineParser(tc_unittest.get_fake_logger_factory())
    input_buffer = """test message 1
"""
    single_line_parser.parse_buffer(content_buffer=input_buffer)
    input_buffer2 = """test message 2
"""
    single_line_parser.parse_buffer(content_buffer=input_buffer2)
    assert single_line_parser.msg_list == ["test message 1\n", "test message 2\n"]
