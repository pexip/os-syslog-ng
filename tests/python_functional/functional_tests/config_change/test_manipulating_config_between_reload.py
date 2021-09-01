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


def test_manipulating_config_between_reload(config, syslog_ng):
    file_source = config.create_file_source(file_name="input.log")
    file_destination = config.create_file_destination(file_name="output.log")
    destination_group = config.create_statement_group(file_destination)

    logpath = config.create_logpath(statements=[file_source, destination_group])

    syslog_ng.start(config)

    # update positional value of file source
    file_source.set_path("updated_input.log")

    # add new option to file source
    file_source.options["log_iw_size"] = "100"

    # create new file source and add to separate source group
    file_source2 = config.create_file_source(file_name="input2.log")
    source_group2 = config.create_statement_group(file_source2)

    # create new file destination and update first destination group
    file_destination2 = config.create_file_destination(file_name="output2.log")
    destination_group.append(file_destination2)

    # update first logpath group with new source group
    logpath.add_group(source_group2)

    syslog_ng.reload(config)

    # remove option from file source
    file_source.options.pop("log_iw_size")

    # remove file destination from destination group
    destination_group.remove(file_destination2)

    # remove second source group from logpath
    logpath.logpath.remove(source_group2)

    syslog_ng.reload(config)
