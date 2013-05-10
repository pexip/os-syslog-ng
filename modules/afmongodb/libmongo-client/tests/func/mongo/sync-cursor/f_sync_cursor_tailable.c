#include "test.h"
#include <mongo.h>

#include <errno.h>
#include <string.h>

void
test_func_mongo_sync_cursor_tailable (void)
{
  mongo_sync_connection *conn;
  bson *query, *data;
  mongo_sync_cursor *sc, *tc;
  mongo_packet *p;
  gint i;
  gchar *capped_ns, *capped_coll;

  bson_cursor *c;
  gboolean tailed = FALSE;

  conn = mongo_sync_connect (config.primary_host, config.primary_port, FALSE);

  query = bson_new ();
  bson_finish (query);

  p = mongo_sync_cmd_query (conn, config.ns,
			    MONGO_WIRE_FLAG_QUERY_TAILABLE_CURSOR |
			    MONGO_WIRE_FLAG_QUERY_NO_CURSOR_TIMEOUT,
			    0, 3, query, NULL);
  ok (p == NULL,
      "Tailable cursors should not work on non-capped collections");

  capped_coll = g_strconcat (config.coll, ".capped", NULL);
  capped_ns = g_strconcat (config.ns, ".capped", NULL);

  query = bson_build (BSON_TYPE_STRING, "create", capped_coll, -1,
		      BSON_TYPE_BOOLEAN, "capped", TRUE,
		      BSON_TYPE_INT32, "size", 64 * 1024 * 10,
		      BSON_TYPE_NONE);
  bson_finish (query);

  mongo_sync_cmd_drop (conn, config.db, capped_coll);
  p = mongo_sync_cmd_custom (conn, config.db, query);
  bson_free (query);

  ok (p != NULL,
      "Creating a capped collection works");
  mongo_wire_packet_free (p);

  for (i = 0; i < 10; i++)
    {
      data = bson_new ();
      bson_append_boolean (data, "f_sync_cursor_tailable", TRUE);
      bson_append_int32 (data, "i32", 42 * 1000 + i);
      bson_finish (data);

      mongo_sync_cmd_insert (conn, capped_ns, data, NULL);
      bson_free (data);
    }

  query = bson_new ();
  bson_append_boolean (query, "f_sync_cursor_tailable", TRUE);
  bson_finish (query);

  tc = mongo_sync_cursor_new (conn, capped_ns,
			      mongo_sync_cmd_query (conn, capped_ns,
						    MONGO_WIRE_FLAG_QUERY_TAILABLE_CURSOR |
						    MONGO_WIRE_FLAG_QUERY_NO_CURSOR_TIMEOUT,
						    0, 3, query, NULL));

  sc = mongo_sync_cursor_new (conn, capped_ns,
			      mongo_sync_cmd_query (conn, capped_ns,
						    0,
						    0, 3, query, NULL));

  bson_free (query);

  /* Exhaust both queries */
  for (i = 0; i < 10; i++)
    {
      mongo_sync_cursor_next (tc);
      mongo_sync_cursor_next (sc);
    }

  data = bson_new ();
  bson_append_boolean (data, "f_sync_cursor_tailable", TRUE);
  bson_append_boolean (data, "tailed", TRUE);
  bson_finish (data);

  mongo_sync_cmd_insert (conn, capped_ns, data, NULL);
  bson_free (data);

  ok (mongo_sync_cursor_next (tc) == TRUE,
      "mongo_sync_cursor_next() works after a tailable cursor got new data");
  ok (mongo_sync_cursor_next (sc) == FALSE,
      "mongo_sync_cursor_next() fails on a non-tailable cursor");

  data = mongo_sync_cursor_get_data (tc);
  ok (data != NULL,
      "mongo_sync_cursor_get_data() works on a tailable cursor");
  c = bson_find (data, "tailed");
  bson_cursor_get_boolean (c, &tailed);
  ok (tailed == TRUE,
      "We got the appropriate data back!");
  bson_cursor_free (c);

  mongo_sync_cursor_free (sc);
  mongo_sync_cursor_free (tc);

  mongo_sync_cmd_drop (conn, config.db, capped_coll);
  g_free (capped_ns);
  g_free (capped_coll);
  mongo_sync_disconnect (conn);
}

RUN_NET_TEST (6, func_mongo_sync_cursor_tailable);
