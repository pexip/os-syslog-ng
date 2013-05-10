/*
 * ivykis, an event handling library
 * Copyright (C) 2002, 2003, 2009 Lennert Buytenhek
 * Dedicated to Marija Kulikova.
 *
 * This library is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version
 * 2.1 as published by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License version 2.1 for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License version 2.1 along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street - Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>
#include "iv_private.h"
#include "iv_thr.h"

TLS_BLOCK_START
{
	struct list_head	tasks;
}
TLS_BLOCK_END;

#define tasks         __tls_deref(tasks)

void iv_task_init(void)
{
	INIT_LIST_HEAD(&tasks);
}

int iv_pending_tasks(void)
{
	return !list_empty(&tasks);
}

void iv_run_tasks(void)
{
	struct list_head current_tasks;

	if (list_empty(&tasks))
		return;

        current_tasks = tasks;
        tasks.prev->next = &current_tasks;
        tasks.next->prev = &current_tasks;
	INIT_LIST_HEAD(&tasks);
	while (!list_empty(&current_tasks)) {
		struct iv_task_ *t;

		t = list_entry(current_tasks.next, struct iv_task_, list);
		list_del_init(&t->list);

		t->handler(t->cookie);
	}
}

void IV_TASK_INIT(struct iv_task *_t)
{
	struct iv_task_ *t = (struct iv_task_ *)_t;

	INIT_LIST_HEAD(&t->list);
}

void iv_task_register(struct iv_task *_t)
{
	struct iv_task_ *t = (struct iv_task_ *)_t;

	if (!list_empty(&t->list)) {
		fprintf(stderr, "iv_task_register: called with task still "
				 "on a list");
		abort();
	}

	list_add_tail(&t->list, &tasks);
}

void iv_task_unregister(struct iv_task *_t)
{
	struct iv_task_ *t = (struct iv_task_ *)_t;

	if (list_empty(&t->list)) {
		fprintf(stderr, "iv_task_unregister: called with task not "
				 "on a list");
		abort();
	}

	list_del_init(&t->list);
}

int iv_task_registered(struct iv_task *_t)
{
	struct iv_task_ *t = (struct iv_task_ *)_t;

	return !list_empty(&t->list);
}
