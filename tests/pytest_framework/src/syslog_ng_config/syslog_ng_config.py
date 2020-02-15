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

from src.driver_io.file.file_io import FileIO
from src.syslog_ng_config.renderer import ConfigRenderer
from src.syslog_ng_config.statements.logpath.logpath import LogPath
from src.syslog_ng_config.statements.sources.file_source import FileSource
from src.syslog_ng_config.statements.destinations.file_destination import FileDestination
from src.syslog_ng_config.config_group import ConfigGroup


class SyslogNgConfig(object):
    def __init__(self, logger_factory, instance_paths, syslog_ng_version):
        self.__instance_paths = instance_paths
        self.__config_path = instance_paths.get_config_path()
        self.__logger_factory = logger_factory
        self.__logger = logger_factory.create_logger("SyslogNgConfig")
        self.__syslog_ng_config = {"version": syslog_ng_version, "sources": {}, "destinations": {}, "logpaths": {}}

    def write_config_content(self):
        rendered_config = ConfigRenderer(self.__syslog_ng_config, self.__instance_paths).get_rendered_config()
        self.__logger.info(
            "Used config \
        \n->Content:[{}]".format(
                rendered_config
            )
        )
        FileIO(self.__logger_factory, self.__config_path).rewrite(rendered_config)

    def create_file_source(self, **kwargs):
        return FileSource(self.__logger_factory, self.__instance_paths, **kwargs)

    def create_file_destination(self, **kwargs):
        return FileDestination(self.__logger_factory, self.__instance_paths, **kwargs)

    def create_source_group(self, drivers):
        config_group = ConfigGroup(group_type="source")
        config_group.update_group_node(drivers)
        self.__syslog_ng_config["sources"].update(config_group.full_group_node)
        return config_group

    def create_destination_group(self, drivers):
        config_group = ConfigGroup(group_type="destination")
        config_group.update_group_node(drivers)
        self.__syslog_ng_config["destinations"].update(config_group.full_group_node)
        return config_group

    def create_logpath(self, sources, destinations):
        logpath = LogPath()
        logpath.add_source_groups(sources)
        logpath.add_destination_groups(destinations)
        self.__syslog_ng_config["logpaths"].update(logpath.full_logpath_node)
        return logpath
