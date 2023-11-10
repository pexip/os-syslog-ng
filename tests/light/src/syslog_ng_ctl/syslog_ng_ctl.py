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
from src.syslog_ng_ctl.syslog_ng_ctl_cli import SyslogNgCtlCli
from src.syslog_ng_ctl.syslog_ng_ctl_executor import QueryTypes


class SyslogNgCtl(object):
    def __init__(self, instance_paths):
        self.__syslog_ng_ctl_cli = SyslogNgCtlCli(instance_paths)

    def reload(self):
        return self.__syslog_ng_ctl_cli.reload()

    def stop(self):
        return self.__syslog_ng_ctl_cli.stop()

    def reopen(self):
        return self.__syslog_ng_ctl_cli.reopen()

    def stats(self, reset=False):
        return self.__syslog_ng_ctl_cli.stats(reset)

    def query(self, pattern="*", query_type=QueryTypes.QUERY_GET):
        return self.__syslog_ng_ctl_cli.query(pattern, query_type)

    def credentials_add(self, credential, secret):
        return self.__syslog_ng_ctl_cli.credentials_add(credential, secret)

    def is_control_socket_alive(self):
        return self.__syslog_ng_ctl_cli.is_control_socket_alive()
