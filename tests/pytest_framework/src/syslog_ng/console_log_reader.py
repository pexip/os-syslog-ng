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

from src.message_reader.message_reader import MessageReader
from src.driver_io.file.file_io import FileIO
from src.message_reader.single_line_parser import SingleLineParser


class ConsoleLogReader(object):
    def __init__(self, logger_factory, instance_paths):
        self.__logger = logger_factory.create_logger("ConsoleLogReader")
        self.__stderr_io = FileIO(logger_factory, instance_paths.get_stderr_path())
        self.__message_reader = MessageReader(logger_factory, self.__stderr_io.read, SingleLineParser(logger_factory))

    def wait_for_start_message(self):
        syslog_ng_start_message = ["syslog-ng starting up;"]
        return self.__wait_for_messages_in_console_log(syslog_ng_start_message)

    def wait_for_stop_message(self):
        syslog_ng_stop_message = ["syslog-ng shutting down"]
        return self.__wait_for_messages_in_console_log(syslog_ng_stop_message)

    def wait_for_reload_message(self):
        syslog_ng_reload_messages = [
            "New configuration initialized",
            "Configuration reload request received, reloading configuration",
            "Configuration reload finished",
        ]
        return self.__wait_for_messages_in_console_log(syslog_ng_reload_messages)

    def __wait_for_messages_in_console_log(self, expected_messages):
        if not self.__stderr_io.wait_for_creation():
            raise Exception

        console_log_messages = self.__message_reader.pop_messages(counter=0)
        console_log_content = "".join(console_log_messages)

        result = []
        for expected_message in expected_messages:
            result.append(expected_message in console_log_content)
        return all(result)

    def check_for_unexpected_messages(self, unexpected_messages):
        unexpected_patterns = ["Plugin module not found"]
        console_log_messages = self.__message_reader.peek_messages(counter=0)
        if unexpected_messages is not None:
            unexpected_patterns.append(unexpected_messages)
        for unexpected_pattern in unexpected_patterns:
            for console_log_message in console_log_messages:
                if unexpected_pattern in console_log_message:
                    self.__logger.error("Found unexpected message in console log: {}".format(console_log_message))
                    assert False

    def dump_stderr(self, last_n_lines=10):
        console_log_messages = self.__message_reader.peek_messages(counter=0)
        self.__logger.info("".join(console_log_messages[-last_n_lines:]))
