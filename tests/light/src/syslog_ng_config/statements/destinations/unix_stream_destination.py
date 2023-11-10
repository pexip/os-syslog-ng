#!/usr/bin/env python
#############################################################################
# Copyright (c) 2022 One Identity
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
import atexit

from pathlib2 import Path

from src.common.asynchronous import BackgroundEventLoop
from src.common.blocking import DEFAULT_TIMEOUT
from src.common.network import SingleConnectionUnixStreamServer
from src.driver_io import message_readers
from src.syslog_ng_config.statements.destinations.destination_driver import DestinationDriver


class UnixStreamDestination(DestinationDriver):
    def __init__(self, file_name, **options):
        self.driver_name = "unix-stream"
        self.path = Path(file_name)

        self.__server = None
        self.__message_reader = None

        atexit.register(self.stop_listener)
        super(UnixStreamDestination, self).__init__([self.path], options)

    def start_listener(self):
        self.__server = SingleConnectionUnixStreamServer(self.path)
        self.__message_reader = message_readers.SingleLineStreamReader(self.__server)
        BackgroundEventLoop().wait_async_result(self.__server.start(), timeout=DEFAULT_TIMEOUT)

    def stop_listener(self):
        if self.__message_reader is not None:
            BackgroundEventLoop().wait_async_result(self.__server.stop(), timeout=DEFAULT_TIMEOUT)
            self.__message_reader = None
            self.__server = None

    def read_log(self, timeout=DEFAULT_TIMEOUT):
        return self.read_logs(1, timeout)[0]

    def read_logs(self, counter, timeout=DEFAULT_TIMEOUT):
        return self.__message_reader.wait_for_number_of_messages(counter, timeout)

    def read_until_logs(self, logs, timeout=DEFAULT_TIMEOUT):
        return self.__message_reader.wait_for_messages(logs, timeout)
