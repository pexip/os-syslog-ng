/*
 * ivykis, an event handling library
 * Copyright (C) 2002, 2003 Lennert Buytenhek
 * Dedicated to Marija Kulikova.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version
 * 2.1 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License version 2.1 for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License version 2.1 along with this program; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street - Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include <stdio.h>
#include <stdlib.h>
#include <iv.h>
#include <netinet/in.h>
#include <string.h>

struct connector {
	struct iv_fd fd;
	struct sockaddr_in addr;
};

static void create_connector(struct connector *conn, struct sockaddr_in *addr);

static void connected(void *c)
{
	struct connector *conn = (struct connector *)c;
	int ret;

	ret = connect(conn->fd.fd, (struct sockaddr *)&conn->addr,
		      sizeof(conn->addr));
	if (ret == -1) {
		if (errno == EALREADY || errno == EINPROGRESS)
			return;
		fprintf(stderr, "blah: %s\n", strerror(errno));
	}

#if 0
	fprintf(stderr, ".");
#endif

	iv_fd_unregister(&conn->fd);
	close(conn->fd.fd);
	create_connector(conn, &conn->addr);
}

static void create_connector(struct connector *conn, struct sockaddr_in *addr)
{
	int fd;

	fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd < 0) {
		perror("socket");
		exit(1);
	}

	IV_FD_INIT(&conn->fd);
	conn->fd.fd = fd;
	conn->fd.cookie = (void *)conn;
	conn->fd.handler_in = connected;
	conn->fd.handler_out = NULL;
	iv_fd_register(&conn->fd);

	conn->addr.sin_family = addr->sin_family;
	conn->addr.sin_addr = addr->sin_addr;
	conn->addr.sin_port = addr->sin_port;

	connected((void *)conn);
}

int main()
{
	struct sockaddr_in addr;
	struct connector c[1000];
	int i;

	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(0x7f000001);

	iv_init();

	for (i = 0; i < sizeof(c) / sizeof(c[0]); i++) {
		addr.sin_port = htons(20000 + i);
		create_connector(&c[i], &addr);
	}

	iv_main();

	iv_deinit();

	return 0;
}
