/*
 * Copyright (c) 2002-2016 Balabit
 * Copyright (c) 2016 Viktor Juhasz <viktor.juhasz@balabit.com>
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

#ifndef QUEUE_UTILS_LIB_H
#define QUEUE_UTILS_LIB_H 1

#include "logqueue.h"
#include "logpipe.h"

extern int acked_messages;
extern int fed_messages;

void test_ack(LogMessage *msg, AckType ack_type);
void feed_some_messages(LogQueue *q, int n, MsgFormatOptions *po);

void send_some_messages(LogQueue *q, gint n);

void app_rewind_some_messages(LogQueue *q, guint n);

void app_ack_some_messages(LogQueue *q, guint n);

void rewind_messages(LogQueue *q);

#endif
