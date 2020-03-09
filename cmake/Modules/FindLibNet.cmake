#############################################################################
# Copyright (c) 2016 Balabit
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
#
# As an additional exemption you are allowed to compile & link against the
# OpenSSL libraries as published by the OpenSSL project. See the file
# COPYING for details.
#
#############################################################################

# - Try to find the libnet library
# Once done this will define
#
#  LIBNET_FOUND - system has the libnet library
#  LIBNET_CONFIG
#  LIBNET_LIBRARIES - The libraries needed to use libnet
#
# Based on FindESMTP.cmake
# Distributed under the BSD license.

if (LIBNET_LIBRARIES)
  # Already in cache, be silent
  set(LIBNET_FIND_QUIETLY TRUE)
endif (LIBNET_LIBRARIES)

FIND_PROGRAM(LIBNET_CONFIG libnet-config)

IF (LIBNET_CONFIG)
  EXEC_PROGRAM(${LIBNET_CONFIG} ARGS --libs OUTPUT_VARIABLE _LIBNET_LIBRARIES)
  EXEC_PROGRAM(${LIBNET_CONFIG} ARGS --defines OUTPUT_VARIABLE _LIBNET_DEFINES)
  string(REGEX REPLACE "[\r\n]" " " _LIBNET_LIBRARIES "${_LIBNET_LIBRARIES}")
  string(REGEX REPLACE "[\r\n]" " " _LIBNET_DEFINES "${_LIBNET_DEFINES}")
  set (LIBNET_LIBRARIES ${_LIBNET_LIBRARIES} CACHE STRING "The libraries needed for LIBNET")
  set (LIBNET_DEFINES ${_LIBNET_DEFINES} CACHE STRING "The #defines needed for LIBNET")
  set (LIBNET_FOUND TRUE CACHE BOOL "LibNet is found")
ELSE(LIBNET_CONFIG)
  set (LIBNET_FOUND FALSE CACHE BOOL "LibNet is found")
ENDIF()

include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(LIBNET DEFAULT_MSG LIBNET_LIBRARIES LIBNET_DEFINES LIBNET_FOUND)

MARK_AS_ADVANCED(LIBNET_LIBRARIES)
