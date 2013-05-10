#include "test.h"
#include <mongo.h>

#include <errno.h>
#include <string.h>

void
test_func_mongo_sync_cursor_iterate (void)
{
  mongo_sync_connection *conn;
  bson *query, *result;
  mongo_sync_cursor *sc;
  bson_cursor *c;
  gint i;
  gint32 first_i32 = -1, last_i32 = -1, current_i32 = -1;
  gboolean early_break = FALSE, continous = TRUE;

  conn = mongo_sync_connect (config.primary_host, config.primary_port, FALSE);

  for (i = 0; i < 10; i++)
    {
      bson *data = bson_new ();
      bson_append_boolean (data, "f_sync_cursor_iterate", TRUE);
      bson_append_int32 (data, "i32", 42 * 100 + i);
      bson_finish (data);

      mongo_sync_cmd_insert (conn, config.ns, data, NULL);
      bson_free (data);
    }

  query = bson_new ();
  bson_append_boolean (query, "f_sync_cursor_iterate", TRUE);
  bson_finish (query);

  sc = mongo_sync_cursor_new (conn, config.ns,
			      mongo_sync_cmd_query (conn, config.ns, 0, 0, 3,
						    query, NULL));
  bson_free (query);

  ok (sc != NULL,
      "mongo_sync_cursor_new() works");

  result = mongo_sync_cursor_get_data (sc);
  ok (result == NULL,
      "mongo_sync_cursor_get_data() should fail without _cursor_next()");

  i = 0;
  while (mongo_sync_cursor_next (sc) && i < 10)
    {
      result = mongo_sync_cursor_get_data (sc);

      if (!result)
	{
	  early_break = TRUE;
	  break;
	}
      i++;
      c = bson_find (result, "i32");
      bson_cursor_get_int32 (c, &current_i32);
      bson_cursor_free (c);
      bson_free (result);

      if (first_i32 == -1)
	{
	  first_i32 = current_i32;
	  last_i32 = first_i32 - 1;
	}

      if (current_i32 != last_i32 + 1)
	continous = FALSE;
      last_i32 = current_i32;
    }

  ok (early_break == FALSE,
      "mongo_sync_cursor_next() can iterate over the whole stuff");
  ok (continous == TRUE,
      "mongo_sync_cursor_next() iterates over all elements");

  cmp_ok (first_i32, "!=", last_i32,
	  "Iteration returns different elements, as expected");
  cmp_ok (i, ">=", 10,
	  "Iteration really does return all documents");

  mongo_sync_cursor_free (sc);
  mongo_sync_disconnect (conn);
}

RUN_NET_TEST (6, func_mongo_sync_cursor_iterate);
