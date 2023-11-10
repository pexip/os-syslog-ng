#!/usr/bin/env python
#############################################################################
# Copyright (c) 2020 One Identity
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
import pytest
from pathlib2 import Path

from src.common.file import copy_file
from src.executors.command_executor import CommandExecutor
from src.syslog_ng.syslog_ng_paths import SyslogNgPaths


class SecureLogging():
    def __init__(self, testcase_parameters):
        self.instance_paths = SyslogNgPaths(testcase_parameters).set_syslog_ng_paths("server")
        self.master_key = None
        self.derived_key = None
        self.decryption_key = None
        self.slogkey = self.instance_paths.get_slogkey_bin()
        self.slogverify = self.instance_paths.get_slogverify_bin()

        self.create_master_key()
        self.create_derived_key()
        self.create_decryption_key()

    def create_master_key(self):
        slogkey_stdout = Path("slogkey_stdout_master")
        slogkey_stderr = Path("slogkey_stderr_master")

        self.master_key = Path("master.key")

        CommandExecutor().run(
            [self.slogkey, "-m", self.master_key],
            slogkey_stdout,
            slogkey_stderr,
        )

    def create_derived_key(self):
        slogkey_stdout = Path("slogkey_stdout_derived")
        slogkey_stderr = Path("slogkey_stderr_derived")

        self.derived_key = Path("derived.key")
        self.cmac = Path("cmac")

        CommandExecutor().run(
            [self.slogkey, "-d", self.master_key, "foo", "bar", self.derived_key],
            slogkey_stdout,
            slogkey_stderr,
        )

    def create_decryption_key(self):
        self.decryption_key = Path("decryption.key")
        copy_file(self.derived_key, self.decryption_key)

    def decrypt(self, input_file):
        slogverify_stdout = Path("slogverify_stdout")
        slogverify_stderr = Path("slogverify_stderr")
        encrypted = Path(input_file)
        decrypted = Path("decrypted.txt")

        CommandExecutor().run(
            [
                self.slogverify,
                "-k", self.decryption_key,
                "-m", self.cmac,
                encrypted, decrypted,
            ],
            slogverify_stdout,
            slogverify_stderr,
        )
        return decrypted.read_text().rstrip("\n").split("\n")


@pytest.fixture
def slog(testcase_parameters):
    yield SecureLogging(testcase_parameters)
