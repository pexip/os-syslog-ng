/*
 * Copyright (c) 2017 Balabit
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * As an additional exemption you are allowed to compile & link against the
 * OpenSSL libraries as published by the OpenSSL project. See the file
 * COPYING for details.
 *
 */

#include "compat-python.h"
#include "python-helpers.h"

#include <datetime.h>

void
py_init_argv(void)
{
  static char *argv[] = {"syslog-ng"};
  PySys_SetArgvEx(1, argv, 0);
}

PyObject *
int_as_pyobject(gint num)
{
  return PyInt_FromLong(num);
};

void
py_datetime_init(void)
{
  PyDateTime_IMPORT;
}

gboolean
py_datetime_to_logstamp(PyObject *py_timestamp, LogStamp *logstamp)
{
  if (!PyDateTime_Check(py_timestamp))
    {
      PyErr_Format(PyExc_TypeError, "datetime expected in the first parameter");
      return FALSE;
    }

  PyObject *py_epoch = PyDateTime_FromDateAndTime(1970, 1, 1, 0, 0, 0, 0);
  PyObject *py_delta = _py_invoke_method_by_name(py_timestamp, "__sub__", py_epoch,
                                                 "PyDateTime", "py_datetime_to_logstamp");
  if (!py_delta)
    {
      Py_XDECREF(py_epoch);
      PyErr_Format(PyExc_ValueError, "Error calculating POSIX timestamp");
      return FALSE;
    }

  PyObject *py_posix_timestamp = _py_invoke_method_by_name(py_delta, "total_seconds", NULL,
                                                           "PyDateTime", "py_datetime_to_logstamp");
  gdouble posix_timestamp = PyFloat_AsDouble(py_posix_timestamp);

  Py_XDECREF(py_posix_timestamp);
  Py_XDECREF(py_delta);
  Py_XDECREF(py_epoch);

  logstamp->tv_sec = (time_t) posix_timestamp;
  logstamp->tv_usec = posix_timestamp * 10e5 - logstamp->tv_sec * 10e5;
  logstamp->zone_offset = 0;

  return TRUE;
}
