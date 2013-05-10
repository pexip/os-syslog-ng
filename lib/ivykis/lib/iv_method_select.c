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

#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <sys/types.h>
#ifdef HAVE_SYS_SELECT_H
#include <sys/select.h>
#endif
#include <sys/time.h>
#include "iv_private.h"
#include "iv_thr.h"

TLS_BLOCK_START
{
	struct iv_avl_tree	fds;
	int			setsize;
	int			fd_max;
	fd_set			*readfds_master;
	fd_set			*writefds_master;
	fd_set			*readfds;
	fd_set			*writefds;
}
TLS_BLOCK_END;

#define fds                   __tls_deref(fds)
#define setsize               __tls_deref(setsize)
#define fd_max                __tls_deref(fd_max)
#define readfds_master        __tls_deref(readfds_master)
#define writefds_master       __tls_deref(writefds_master)
#define readfds               __tls_deref(readfds)
#define writefds              __tls_deref(writefds)

static struct iv_fd_ *find_fd(int fd)
{
	struct iv_avl_node *an;

	an = fds.root;
	while (an != NULL) {
		struct iv_fd_ *p;

		p = container_of(an, struct iv_fd_, avl_node);
		if (fd == p->fd)
			return p;

		if (fd < p->fd)
			an = an->left;
		else
			an = an->right;
	}

	return NULL;
}

static int fd_compare(struct iv_avl_node *_a, struct iv_avl_node *_b)
{
	struct iv_fd_ *a = container_of(_a, struct iv_fd_, avl_node);
	struct iv_fd_ *b = container_of(_b, struct iv_fd_, avl_node);

	if (a->fd < b->fd)
		return -1;
	if (a->fd > b->fd)
		return 1;
	return 0;
}


/* interface ****************************************************************/
static int iv_select_init(int maxfd)
{
	unsigned char *fdsets;

	INIT_IV_AVL_TREE(&fds, fd_compare);

	setsize = (maxfd + 7) / 8;

	fdsets = malloc(4 * setsize);
	if (fdsets == NULL)
		return -1;

	fprintf(stderr, "warning: using select(2), POLLERR delivery broken\n");

	readfds_master = (fd_set *)fdsets;
	writefds_master = (fd_set *)(fdsets + setsize);
	readfds = (fd_set *)(fdsets + 2 * setsize);
	writefds = (fd_set *)(fdsets + 3 * setsize);

	fd_max = 0;
	memset(readfds_master, 0, 2*setsize);

	return 0;
}

static void iv_select_poll(int numfds, struct list_head *active, int msec)
{
	struct timeval to;
	int ret;
	int i;

	/*
	 * @@@ This is ugly and dependent on clock tick granularity.
	 */
	if (msec)
		msec += (1000/100) - 1;

	memcpy(readfds, readfds_master, (fd_max / 8) + 1);
	memcpy(writefds, writefds_master, (fd_max / 8) + 1);

	to.tv_sec = msec / 1000;
	to.tv_usec = 1000 * (msec % 1000);

	ret = select(fd_max + 1, readfds, writefds, NULL, &to);
	if (ret < 0) {
		if (errno == EINTR)
			return;

		fprintf(stderr, "iv_select_poll: got error %d[%s]", errno,
		       strerror(errno));
		abort();
	}

	for (i = 0; i <= fd_max; i++) {
		int pollin;
		int pollout;

		pollin = !!FD_ISSET(i, readfds);
		pollout = !!FD_ISSET(i, writefds);
		if (pollin || pollout) {
			struct iv_fd_ *fd;

			fd = find_fd(i);
			if (fd == NULL) {
				fprintf(stderr, "iv_select_poll: just puked "
						 "on myself... eeeeeeeeeeew");
				abort();
			}

			if (pollin)
				iv_fd_make_ready(active, fd, MASKIN);

			if (pollout)
				iv_fd_make_ready(active, fd, MASKOUT);
		}
	}
}

static void iv_select_register_fd(struct iv_fd_ *fd)
{
	int ret;

	ret = iv_avl_tree_insert(&fds, &fd->avl_node);
	if (ret) {
		fprintf(stderr, "iv_select_register_fd: got error %d[%s]",
		       ret, strerror(ret));
		abort();
	}

	if (fd->fd > fd_max)
		fd_max = fd->fd;
}

static void iv_select_unregister_fd(struct iv_fd_ *fd)
{
	iv_avl_tree_delete(&fds, &fd->avl_node);

	if (fd->fd == fd_max) {
		struct iv_avl_node *an;

		an = iv_avl_tree_max(&fds);
		if (an != NULL)
			fd_max = container_of(an, struct iv_fd_, avl_node)->fd;
		else
			fd_max = 0;
	}
}

static void iv_select_notify_fd(struct iv_fd_ *fd, int wanted)
{
	if (wanted & MASKIN)
		FD_SET(fd->fd, readfds_master);
	else
		FD_CLR(fd->fd, readfds_master);

	if (wanted & MASKOUT)
		FD_SET(fd->fd, writefds_master);
	else
		FD_CLR(fd->fd, writefds_master);

	fd->registered_bands = wanted;
}

static void iv_select_deinit(void)
{
	free(readfds_master);
}


struct iv_poll_method iv_method_select = {
	.name		= "select",
	.init		= iv_select_init,
	.poll		= iv_select_poll,
	.register_fd	= iv_select_register_fd,
	.unregister_fd	= iv_select_unregister_fd,
	.notify_fd	= iv_select_notify_fd,
	.deinit		= iv_select_deinit,
};
