#include "test.h"
#include "mongo.h"

#include <sys/socket.h>
#include "libmongo-private.h"

void
test_mongo_sync_cmd_create_net (void)
{
  mongo_sync_connection *conn;
  gchar *cc;

  begin_network_tests (5);

  conn = mongo_sync_connect (config.primary_host, config.primary_port, FALSE);

  cc = g_strconcat (config.coll, ".capped", NULL);

  mongo_sync_cmd_drop (conn, config.db, config.coll);
  mongo_sync_cmd_drop (conn, config.db, cc);

  ok (mongo_sync_cmd_create (conn, config.db, config.coll,
                             MONGO_COLLECTION_DEFAULTS) == TRUE,
      "mongo_sync_cmd_create() can create normal collections");
  mongo_sync_cmd_drop (conn, config.db, config.coll);

  ok (mongo_sync_cmd_create (conn, config.db, config.coll,
                             MONGO_COLLECTION_SIZED,
                             (gint64) 64 * 1024 * 10) == TRUE,
      "mongo_sync_cmd_create() can create pre-allocated collections");

  ok (mongo_sync_cmd_create (conn, config.db, cc,
                             MONGO_COLLECTION_CAPPED, (gint64) -1) == FALSE,
      "mongo_sync_cmd_create() fails when trying to create a capped "
      "collection with an invalid size");
  ok (mongo_sync_cmd_create (conn, config.db, cc,
                             MONGO_COLLECTION_CAPPED_MAX,
                             (gint64) (64 * 1024 * 10), (gint64) -1) == FALSE,
      "mongo_sync_cmd_create() fails when trying to create a capped "
      "collection with invalid max.");
  ok (mongo_sync_cmd_create (conn, config.db, cc,
                             MONGO_COLLECTION_CAPPED_MAX |
                             MONGO_COLLECTION_AUTO_INDEX_ID,
                             (gint64)(64 * 1024 * 10), (gint64) 10) == TRUE,
      "mongo_sync_cmd_create() can create capped collections");

  mongo_sync_cmd_drop (conn, config.db, cc);

  g_free (cc);
  mongo_sync_disconnect (conn);

  end_network_tests ();
}

void
test_mongo_sync_cmd_create (void)
{
  mongo_sync_connection *c;

  c = test_make_fake_sync_conn (-1, FALSE);

  ok (mongo_sync_cmd_create (NULL, "test", "db",
                             MONGO_COLLECTION_DEFAULTS) == FALSE,
      "mongo_sync_cmd_create() fails with a NULL connection");

  ok (mongo_sync_cmd_create (c, NULL, "db",
                             MONGO_COLLECTION_DEFAULTS) == FALSE,
      "mongo_sync_cmd_create() fails with a NULL db");
  ok (mongo_sync_cmd_create (c, "test", NULL,
                             MONGO_COLLECTION_DEFAULTS) == FALSE,
      "mongo_sync_cmd_create() fails with a NULL collection");

  mongo_sync_disconnect (c);

  test_mongo_sync_cmd_create_net ();
}

RUN_TEST (8, mongo_sync_cmd_create);
