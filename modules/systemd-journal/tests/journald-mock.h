/*
 * Copyright (c) 2010-2014 Balabit
 * Copyright (c) 2010-2014 Viktor Juhasz <viktor.juhasz@balabit.com>
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

#ifndef JOURNALD_MOCK_H_
#define JOURNALD_MOCK_H_

#include "journald-subsystem.h"

typedef struct _MockEntry MockEntry;

Journald *journald_mock_new(void);

MockEntry *mock_entry_new(const gchar *cursor);

void mock_entry_add_data(MockEntry *self, gchar *data);

void journald_mock_add_entry(Journald *self, MockEntry *entry);


#endif /* JOURNALD_MOCK_H_ */
