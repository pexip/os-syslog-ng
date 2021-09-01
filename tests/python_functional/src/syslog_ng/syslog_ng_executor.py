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
from src.common.random_id import get_unique_id
from src.executors.command_executor import CommandExecutor
from src.executors.process_executor import ProcessExecutor


class SyslogNgExecutor(object):
    def __init__(self, instance_paths):
        self.__instance_paths = instance_paths
        self.__process_executor = ProcessExecutor()
        self.__command_executor = CommandExecutor()

    def run_process(self):
        return self.__process_executor.start(
            command=self.__construct_syslog_ng_process(),
            stdout_path=self.__instance_paths.get_stdout_path(),
            stderr_path=self.__instance_paths.get_stderr_path(),
        )

    def run_process_with_external_tool(self, external_tool):
        self.__instance_paths.register_external_tool_output_path(external_tool)
        if external_tool == "valgrind":
            return self.run_process_with_valgrind()
        elif external_tool == "strace":
            return self.run_process_with_strace()
        else:
            raise Exception("Unknown external tool was selected: {}".format(external_tool))

    def run_process_with_valgrind(self):
        valgrind_command_args = [
            "valgrind",
            "--show-leak-kinds=all",
            "--track-origins=yes",
            "--tool=memcheck",
            "--leak-check=full",
            "--keep-stacktraces=alloc-and-free",
            "--read-var-info=yes",
            "--error-limit=no",
            "--num-callers=40",
            "--verbose",
            "--log-file={}".format(self.__instance_paths.get_external_tool_output_path("valgrind")),
        ]
        full_command_args = valgrind_command_args + self.__construct_syslog_ng_process()
        return self.__process_executor.start(
            command=full_command_args,
            stdout_path=self.__instance_paths.get_stdout_path(),
            stderr_path=self.__instance_paths.get_stderr_path(),
        )

    def run_process_with_strace(self):
        strace_command_args = [
            "strace",
            "-s",
            "4096",
            "-tt",
            "-T",
            "-ff",
            "-o",
            self.__instance_paths.get_external_tool_output_path("strace"),
        ]
        full_command_args = strace_command_args + self.__construct_syslog_ng_process()
        return self.__process_executor.start(
            command=full_command_args,
            stdout_path=self.__instance_paths.get_stdout_path(),
            stderr_path=self.__instance_paths.get_stderr_path(),
        )

    def run_command(self, command_short_name, command):
        return self.__command_executor.run(
            command=self.__construct_syslog_ng_command(command),
            stdout_path=self.__instance_paths.get_stdout_path_with_postfix(postfix=command_short_name),
            stderr_path=self.__instance_paths.get_stderr_path_with_postfix(postfix=command_short_name),
        )

    def get_backtrace_from_core(self, core_file):
        gdb_command_args = [
            "gdb",
            "-ex",
            "bt full",
            "--batch",
            self.__instance_paths.get_syslog_ng_bin(),
            "--core",
            core_file,
        ]
        core_postfix = "gdb_core_{}".format(get_unique_id())
        return self.__command_executor.run(
            command=gdb_command_args,
            stdout_path=self.__instance_paths.get_stdout_path_with_postfix(postfix=core_postfix),
            stderr_path=self.__instance_paths.get_stderr_path_with_postfix(postfix=core_postfix),
        )

    def __construct_syslog_ng_process(
        self,
        stderr=True,
        debug=True,
        trace=True,
        verbose=True,
        startup_debug=True,
        no_caps=True,
        config_path=None,
        persist_path=None,
        pid_path=None,
        control_socket_path=None,
    ):
        syslog_ng_process_args = [self.__instance_paths.get_syslog_ng_bin()]
        syslog_ng_process_args += ["--foreground", "--enable-core"]
        if stderr:
            syslog_ng_process_args += ["--stderr"]
        if debug:
            syslog_ng_process_args += ["--debug"]
        if trace:
            syslog_ng_process_args += ["--trace"]
        if verbose:
            syslog_ng_process_args += ["--verbose"]
        if startup_debug:
            syslog_ng_process_args += ["--startup-debug"]
        if no_caps:
            syslog_ng_process_args += ["--no-caps"]
        if config_path is None:
            config_path = self.__instance_paths.get_config_path()
        syslog_ng_process_args += ["--cfgfile={}".format(config_path)]
        if persist_path is None:
            persist_path = self.__instance_paths.get_persist_path()
        syslog_ng_process_args += ["--persist-file={}".format(persist_path)]
        if pid_path is None:
            pid_path = self.__instance_paths.get_pid_path()
        syslog_ng_process_args += ["--pidfile={}".format(pid_path)]
        if control_socket_path is None:
            control_socket_path = self.__instance_paths.get_control_socket_path()
        syslog_ng_process_args += ["--control={}".format(control_socket_path)]
        return syslog_ng_process_args

    def __construct_syslog_ng_command(self, command):
        syslog_ng_command_args = [self.__instance_paths.get_syslog_ng_bin()]
        syslog_ng_command_args += command
        return syslog_ng_command_args
