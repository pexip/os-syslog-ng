/*
 * Copyright (c) 2002-2016 Balabit
 * Copyright (c) 2016 Viktor Juhasz <viktor.juhasz@balabit.com>
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

#ifndef LOGQUEUE_DISK_RELIABLE_H_
#define LOGQUEUE_DISK_RELIABLE_H_

#include "logqueue-disk.h"

typedef struct _LogQueueDiskReliable
{
  LogQueueDisk super;
  GQueue *qreliable;
  GQueue *qbacklog;
} LogQueueDiskReliable;

LogQueue *log_queue_disk_reliable_new(DiskQueueOptions *options, const gchar *persist_name);

#endif /* LOGQUEUE_DISK_RELIABLE_H_ */
