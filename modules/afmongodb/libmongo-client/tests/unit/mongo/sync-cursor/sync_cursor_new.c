#include "test.h"
#include "mongo.h"
#include "config.h"

#include "libmongo-private.h"

#include <errno.h>

void
test_mongo_sync_cursor_new (void)
{
  mongo_sync_connection *conn;
  mongo_packet *p;
  mongo_sync_cursor *c;

  test_env_setup ();

  p = mongo_wire_packet_new ();
  conn = test_make_fake_sync_conn (-1, FALSE);

  c = mongo_sync_cursor_new (conn, config.ns, NULL);
  ok (c == NULL,
      "mongo_sync_cursor_new() fails with a NULL packet");
  c = mongo_sync_cursor_new (conn, NULL, p);
  ok (c == NULL,
      "mongo_sync_cursor_new() fails with a NULL namespace");
  c = mongo_sync_cursor_new (NULL, config.ns, p);
  ok (c == NULL,
      "mongo_sync_cursor_new() fails with a NULL connection");

  c = mongo_sync_cursor_new (conn, config.ns, p);
  ok (c != NULL,
      "mongo_sync_cursor_new() works");

  mongo_sync_cursor_free (c);
  mongo_sync_disconnect (conn);
  test_env_free ();
}

RUN_TEST (4, mongo_sync_cursor_new);
