#include "test.h"
#include "mongo.h"

#include "libmongo-private.h"

void
test_mongo_sync_cmd_exists_net (void)
{
  mongo_sync_connection *conn;
  gchar *cc, *ns;

  bson *r;
  bson_cursor *c;
  const gchar *str = NULL;
  gboolean capped = FALSE;

  begin_network_tests (4);

  conn = mongo_sync_connect (config.primary_host, config.primary_port, FALSE);

  cc = g_strconcat (config.coll, ".capped", NULL);

  mongo_sync_cmd_drop (conn, config.db, config.coll);
  mongo_sync_cmd_drop (conn, config.db, cc);

  mongo_sync_cmd_create (conn, config.db, config.coll,
			 MONGO_COLLECTION_DEFAULTS);
  mongo_sync_cmd_create (conn, config.db, cc,
			 MONGO_COLLECTION_CAPPED,
			 (gint64) 64 * 1024 * 10);

  r = mongo_sync_cmd_exists (conn, config.db, config.coll);
  c = bson_find (r, "name");
  bson_cursor_get_string (c, &str);
  is (str, config.ns,
      "mongo_sync_cmd_exists() works on normal collections");
  bson_cursor_find (c, "capped");
  bson_cursor_get_boolean (c, &capped);
  cmp_ok (capped, "==", FALSE,
	  "mongo_sync_cmd_exists() returned correct info");
  bson_cursor_free (c);
  bson_free (r);

  r = mongo_sync_cmd_exists (conn, config.db, cc);
  ns = g_strconcat (config.db, ".", cc, NULL);
  c = bson_find (r, "name");
  bson_cursor_get_string (c, &str);
  is (str, ns,
      "mongo_sync_cmd_exists() works on capped collections");
  bson_cursor_find (c, "capped");
  bson_cursor_get_boolean (c, &capped);
  cmp_ok (capped, "==", FALSE,
	  "mongo_sync_cmd_exists() returned correct info");
  bson_cursor_free (c);
  g_free (ns);
  bson_free (r);

  mongo_sync_cmd_drop (conn, config.db, cc);

  g_free (cc);
  mongo_sync_disconnect (conn);

  end_network_tests ();
}

void
test_mongo_sync_cmd_exists (void)
{
  mongo_sync_connection *c;

  c = test_make_fake_sync_conn (-1, FALSE);

  ok (mongo_sync_cmd_exists (NULL, "test", "db") == NULL,
      "mongo_sync_cmd_exists() fails with a NULL connection");
  ok (mongo_sync_cmd_exists (c, NULL, "db") == NULL,
      "mongo_sync_cmd_exists() fails with a NULL db");
  ok (mongo_sync_cmd_exists (c, "test", NULL) == NULL,
      "mongo_sync_cmd_exists() fails with a NULL collection");

  mongo_sync_disconnect (c);

  test_mongo_sync_cmd_exists_net ();
}

RUN_TEST (7, mongo_sync_cmd_exists);
