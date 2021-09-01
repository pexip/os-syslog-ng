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
import time

DEFAULT_TIMEOUT = 20  # 20 sec
POLL_FREQ = 0.001  # 1 millisecond


def wait_until_true(func, *args):
    return wait_until_true_custom(func, args)


def wait_until_true_custom(func, args=(), timeout=DEFAULT_TIMEOUT):
    # Python 2 compatibility note: time.monotonic() is missing
    t_end = time.time() + timeout
    while time.time() <= t_end:
        result = func(*args)
        if result:
            return result
        time.sleep(POLL_FREQ)
    return result


def wait_until_false(func, *args):
    return wait_until_false_custom(func, args)


def wait_until_false_custom(func, args=(), timeout=DEFAULT_TIMEOUT):
    def negate(func, args):
        return not func(*args)
    return wait_until_true_custom(negate, (func, args), timeout=timeout)
