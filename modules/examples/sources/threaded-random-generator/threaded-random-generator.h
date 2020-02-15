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

#ifndef THREADED_RANDOM_GENERATOR_H
#define THREADED_RANDOM_GENERATOR_H

#include "syslog-ng.h"
#include "driver.h"
#include "logsource.h"

typedef struct ThreadedRandomGeneratorSourceDriver ThreadedRandomGeneratorSourceDriver;

LogDriver *threaded_random_generator_sd_new(GlobalConfig *cfg);

void threaded_random_generator_sd_set_freq(LogDriver *s, gdouble freq);
void threaded_random_generator_sd_set_bytes(LogDriver *s, guint bytes);
gboolean threaded_random_generator_sd_set_type(LogDriver *s, const gchar *type);

#endif
