/*
 * Copyright (c) 2018 Balabit
 * Copyright (c) 2018 László Várady <laszlo.varady@balabit.com>
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

#ifndef SNG_PYTHON_FETCHER_H
#define SNG_PYTHON_FETCHER_H

#include "python-module.h"
#include "driver.h"

LogDriver *python_fetcher_new(GlobalConfig *cfg);
void python_fetcher_set_loaders(LogDriver *d, GList *loaders);
void python_fetcher_set_class(LogDriver *d, gchar *class_name);
void python_fetcher_set_option(LogDriver *d, gchar *key, gchar *value);

void py_log_fetcher_init(void);

#endif
