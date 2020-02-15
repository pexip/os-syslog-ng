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

from src.common.random_id import RandomId


class ConfigGroup(object):
    def __init__(self, group_type):
        self.group_id = "%sid_%s" % (group_type, RandomId(use_static_seed=False).get_unique_id())
        self.full_group_node = {self.group_id: {}}
        self.group_node = self.full_group_node[self.group_id]

    def update_group_node(self, drivers):
        if isinstance(drivers, list):
            for driver in drivers:
                self.group_node.update(driver.get_driver_node())
        else:
            driver = drivers
            self.group_node.update(driver.get_driver_node())
