#include "test.h"
#include "mongo.h"
#include "config.h"

#include "libmongo-private.h"

#include <errno.h>

void
test_mongo_sync_cursor_free (void)
{
  mongo_sync_connection *conn;
  mongo_packet *p;
  mongo_sync_cursor *c;

  test_env_setup ();

  p = mongo_wire_packet_new ();
  conn = test_make_fake_sync_conn (-1, FALSE);

  c = mongo_sync_cursor_new (conn, config.ns, p);

  errno = 0;
  mongo_sync_cursor_free (NULL);
  ok (errno == ENOTCONN,
      "mongo_sync_cursor_free(NULL) sets errno to ENOTCONN");
  mongo_sync_cursor_free (c);
  pass ("mongo_sync_cursor_free() works");

  mongo_sync_disconnect (conn);
  test_env_free ();
}

RUN_TEST (2, mongo_sync_cursor_free);
