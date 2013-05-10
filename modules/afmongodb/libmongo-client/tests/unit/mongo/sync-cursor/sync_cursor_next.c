#include "test.h"
#include "mongo.h"
#include "config.h"

#include "libmongo-private.h"

#include <errno.h>

void
test_mongo_sync_cursor_next (void)
{
  mongo_sync_connection *conn;
  mongo_packet *p;
  mongo_sync_cursor *c;
  gboolean r = TRUE;
  gint i;

  test_env_setup ();

  p = test_mongo_wire_generate_reply (TRUE, 2, TRUE);
  conn = test_make_fake_sync_conn (-1, FALSE);

  c = mongo_sync_cursor_new (conn, config.ns, p);

  ok (mongo_sync_cursor_next (NULL) == FALSE,
      "mongo_sync_cursor_next() should fail with a NULL cursor");
  for (i = 0; i < 2; i++)
    r &= mongo_sync_cursor_next (c);
  
  ok (r == TRUE,
      "mongo_sync_cursor_next() works");
  ok (mongo_sync_cursor_next (c) == FALSE,
      "mongo_sync_cursor_next() should fail past the end of the resultset");

  mongo_sync_cursor_free (c);
  mongo_sync_disconnect (conn);
  test_env_free ();
}

RUN_TEST (3, mongo_sync_cursor_next);
