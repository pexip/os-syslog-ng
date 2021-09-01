/*
 * Copyright (c) 2019 Balabit
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published
 * by the Free Software Foundation, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * As an additional exemption you are allowed to compile & link against the
 * OpenSSL libraries as published by the OpenSSL project. See the file
 * COPYING for details.
 *
 */

#ifndef SNG_PYTHON_PERSIST_H_INCLUDED
#define SNG_PYTHON_PERSIST_H_INCLUDED

#include "python-module.h"
#include "logpipe.h"

typedef struct
{
  PyObject_HEAD
  PersistState *persist_state;
  gchar *persist_name;
} PyPersist;

extern PyTypeObject py_persist_type;

typedef struct
{
  PyObject *generate_persist_name_method;
  GHashTable *options;
  const gchar *class;
  const gchar *id;
} PythonPersistMembers;

void py_persist_init(void);
const gchar *python_format_stats_instance(LogPipe *p, const gchar *module, PythonPersistMembers *options);
const gchar *python_format_persist_name(const LogPipe *p, const gchar *module, PythonPersistMembers *options);

#endif
