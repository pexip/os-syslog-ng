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
import logging

import psutil

from src.driver_io.file.file import File
from src.executors.command_executor import prepare_executable_command
from src.executors.command_executor import prepare_printable_command
from src.executors.command_executor import prepare_std_outputs

logger = logging.getLogger(__name__)


class ProcessExecutor(object):
    def __init__(self):
        self.__file_ref = File
        self.process = None

    def start(self, command, stdout_path, stderr_path):
        printable_command = prepare_printable_command(command)
        executable_command = prepare_executable_command(command)
        stdout, stderr = prepare_std_outputs(self.__file_ref, stdout_path, stderr_path)
        logger.info("Following process will be started:\n{}\n".format(printable_command))
        self.process = psutil.Popen(
            executable_command, stdout=stdout.open_file(mode="a"), stderr=stderr.open_file(mode="a"),
        )
        return self.process
