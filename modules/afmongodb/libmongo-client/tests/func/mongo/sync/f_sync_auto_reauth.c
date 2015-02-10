#include "test.h"
#include <mongo.h>

#include <errno.h>
#include <sys/socket.h>

#include "libmongo-private.h"


/*
 * This test requires that the "lmcUser" user (password "lmcPass") has
 * RW access to the test db. It must be set up prior to running this
 * test.
 */
void
test_func_mongo_sync_auto_reauth (void)
{
  mongo_sync_connection *conn;
  bson *b;

  b = bson_new ();
  bson_append_int32 (b, "f_sync_auto_reauth", 1);
  bson_finish (b);

  conn = mongo_sync_connect (config.primary_host, config.primary_port,
                             TRUE);

  mongo_sync_conn_set_safe_mode (conn, TRUE);

  skip (mongo_sync_cmd_insert (conn, config.ns, b, NULL) == TRUE, 3,
        "Authentication not configured.");

  skip (mongo_sync_cmd_authenticate (conn, config.db, "lmcUser", "lmcPass")== FALSE, 3,
        "Authentication environment not set up for testing.");

  ok (mongo_sync_cmd_insert (conn, config.ns, b, NULL) == TRUE,
      "Inserting works after authentication.");

  shutdown (conn->super.fd, SHUT_RDWR);
  sleep (1);

  ok (mongo_sync_cmd_insert (conn, config.ns, b, NULL) == FALSE,
      "Inserting fails with auto-reconnect turned off, and a broken "
      "connection");

  mongo_sync_conn_set_auto_reconnect (conn, TRUE);

  ok (mongo_sync_cmd_insert (conn, config.ns, b, NULL) == TRUE,
      "Inserting works with auto-reconnect turned on, and auto-auth, "
      "and a broken connection.");

  endskip;
  endskip;

  mongo_sync_disconnect (conn);
}

RUN_NET_TEST (3, func_mongo_sync_auto_reauth);
