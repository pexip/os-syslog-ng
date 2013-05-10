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
#include <fcntl.h>
#include <string.h>
#include <syslog.h>
#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h>
#include "iv_thr.h"
#include "iv_private.h"

#define UPLOAD_QUEUE_SIZE	(1024)

TLS_BEGIN_BLOCK
{
	int		kqueue_fd;
	struct kevent	*upload_queue;
	int		upload_entries;
}
TLS_END_BLOCK;

#define kqueue_fd         __tls_deref(kqueue_fd)
#define upload_queue      __tls_deref(upload_queue)
#define upload_entries    __tls_deref(upload_entries)


static int iv_kqueue_init(int maxfd)
{
	int flags;

	kqueue_fd = kqueue();
	if (kqueue_fd < 0)
		return -1;

	flags = fcntl(kqueue_fd, F_GETFD);
	if (!(flags & FD_CLOEXEC)) {
		flags |= FD_CLOEXEC;
		fcntl(kqueue_fd, F_SETFD, flags);
	}

	upload_queue = malloc(UPLOAD_QUEUE_SIZE * sizeof(*upload_queue));
	if (upload_queue == NULL) {
		close(kqueue_fd);
		return -1;
	}

	fprintf(stderr, "warning: using kqueue(2), POLLERR delivery broken\n");

	upload_entries = 0;

	return 0;
}

static void iv_kqueue_poll(int numfds, struct list_head *active, int msec)
{
	struct timespec to;
	struct kevent batch[numfds ? : 1];
	int ret;
	int i;

	/*
	 * Valgrind 3.5.0 as supplied with FreeBSD 8.1-RELEASE ports
	 * doesn't understand that kevent(2) fills in kevent udata on
	 * return, and labels our subsequent use of it as "Conditional
	 * jump or move depends on uninitialised value(s)".  Zero the
	 * udata fields here as an ugly workaround.
	 */
	for (i = 0; i < (numfds ? : 1); i++)
		batch[i].udata = 0;

	to.tv_sec = msec / 1000;
	to.tv_nsec = 1000000 * (msec % 1000);

	ret = kevent(kqueue_fd, upload_queue, upload_entries,
		     batch, numfds ? : 1, &to);
	if (ret < 0) {
		if (errno == EINTR)
			return;

		fprintf(stderr, "iv_kqueue_poll: got error %d[%s]",
		       errno, strerror(errno));
		abort();
	}

	upload_entries = 0;

	for (i = 0; i < ret; i++) {
		struct iv_fd_ *fd;

		fd = batch[i].udata;
		if (batch[i].filter == EVFILT_READ) {
			iv_fd_make_ready(active, fd, MASKIN);
		} else if (batch[i].filter == EVFILT_WRITE) {
			iv_fd_make_ready(active, fd, MASKOUT);
		} else {
			fprintf(stderr, "iv_kqueue_poll: got message from "
					 "filter %d", batch[i].filter);
			abort();
		}
	}
}

static void flush_upload_queue(void)
{
	struct timespec to = { 0, 0 };
	int ret;

	do {
		ret = kevent(kqueue_fd, upload_queue,
			     upload_entries, NULL, 0, &to);
	} while (ret < 0 && errno == EINTR);

	if (ret < 0) {
		fprintf(stderr, "flush_upload_queue: got error %d[%s]",
		       errno, strerror(errno));
		abort();
	}

	upload_entries = 0;
}

static void iv_kqueue_unregister_fd(struct iv_fd_ *fd)
{
	flush_upload_queue();
}

static void queue(u_int ident, short filter, u_short flags,
		  u_int fflags, int data, void *udata)
{
	if (upload_entries == UPLOAD_QUEUE_SIZE)
		flush_upload_queue();

	EV_SET(&upload_queue[upload_entries], ident, filter, flags,
	       fflags, data, udata);
	upload_entries++;
}

static void iv_kqueue_notify_fd(struct iv_fd_ *fd, int wanted)
{
	if ((fd->registered_bands & MASKIN) && !(wanted & MASKIN)) {
		queue(fd->fd, EVFILT_READ, EV_DELETE, 0, 0, (void *)fd);
		fd->registered_bands &= ~MASKIN;
	} else if ((wanted & MASKIN) && !(fd->registered_bands & MASKIN)) {
		queue(fd->fd, EVFILT_READ, EV_ADD | EV_ENABLE,
		      0, 0, (void *)fd);
		fd->registered_bands |= MASKIN;
	}

	if ((fd->registered_bands & MASKOUT) && !(wanted & MASKOUT)) {
		queue(fd->fd, EVFILT_WRITE, EV_DELETE, 0, 0, (void *)fd);
		fd->registered_bands &= ~MASKOUT;
	} else if ((wanted & MASKOUT) && !(fd->registered_bands & MASKOUT)) {
		queue(fd->fd, EVFILT_WRITE, EV_ADD | EV_ENABLE,
		      0, 0, (void *)fd);
		fd->registered_bands |= MASKOUT;
	}
	if (wanted & MASKERR) {
	        /* NOTE: kqueue doesn't support POLLERR-like interface, but
	         * we need to set it here, as otherwise we run into a failed
	         * assertion later on in the ivykis core.
	         */

	        fd->registered_bands |= MASKERR;
	}
}

static void iv_kqueue_deinit(void)
{
	free(upload_queue);
	close(kqueue_fd);
}

static int iv_kqueue_pollable(int fd)
{
	struct timespec to = { 0, 0 };
	struct kevent kev;
        int ret;

	EV_SET(&kev, fd, EVFILT_READ, EV_ADD, 0, 0, &fd);

	do {
		ret = kevent(kqueue_fd, &kev, 1,
			     NULL, 0, &to);
	} while (ret < 0 && errno == EINTR);

	if (ret < 0 && errno == ENODEV)
		return 0;
        if (ret >= 0) {
	        EV_SET(&kev, fd, EVFILT_READ, EV_DELETE, 0, 0, &fd);

                do {
                        ret = kevent(kqueue_fd, &kev, 1,
                                     NULL, 0, &to);
                } while (ret < 0 && errno == EINTR);

		if (ret < 0) {
			fprintf(stderr, "iv_kqueue_pollable: got error %d[%s]",
			       errno, strerror(errno));
			abort();
		}
        }
	return 1;
}

struct iv_poll_method iv_method_kqueue = {
	.name		= "kqueue",
	.init		= iv_kqueue_init,
	.poll		= iv_kqueue_poll,
	.unregister_fd	= iv_kqueue_unregister_fd,
	.notify_fd	= iv_kqueue_notify_fd,
	.pollable	= iv_kqueue_pollable,
	.deinit		= iv_kqueue_deinit,
};
