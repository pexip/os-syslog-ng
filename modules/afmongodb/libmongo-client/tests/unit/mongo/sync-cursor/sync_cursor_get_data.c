#include "test.h"
#include "mongo.h"
#include "config.h"

#include "libmongo-private.h"

#include <errno.h>

void
test_mongo_sync_cursor_get_data (void)
{
  mongo_sync_connection *conn;
  mongo_packet *p;
  bson *b;
  mongo_sync_cursor *c;

  test_env_setup ();

  p = test_mongo_wire_generate_reply (TRUE, 4, TRUE);
  conn = test_make_fake_sync_conn (-1, FALSE);

  c = mongo_sync_cursor_new (conn, config.ns, p);

  errno = 0;
  b = mongo_sync_cursor_get_data (NULL);
  ok (b == NULL && errno == EINVAL,
      "mongo_sync_cursor_get_data(NULL) should fail");

  b = mongo_sync_cursor_get_data (c);
  ok (b == NULL,
      "mongo_sync_cursor_get_data() should fail without _cursor_next()");

  mongo_sync_cursor_next (c);
  b = mongo_sync_cursor_get_data (c);
  ok (b != NULL,
      "mongo_sync_cursor_get_data() works");

  c->offset = 5;

  errno = 0;
  b = mongo_sync_cursor_get_data (c);
  ok (b == NULL && errno == ERANGE,
      "mongo_sync_cursor_get_data() should fail if the cursor is "
      "out of range");

  mongo_sync_cursor_free (c);
  mongo_sync_disconnect (conn);
  test_env_free ();
}

RUN_TEST (4, mongo_sync_cursor_get_data);
