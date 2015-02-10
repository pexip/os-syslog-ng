#include <mongo.h>

#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int
main (void)
{
  mongo_sync_connection *conn;
  mongo_packet *p;
  mongo_sync_cursor *cursor;
  bson *eval;

  conn = mongo_sync_connect ("localhost", 27017, FALSE);
  if (!conn)
    {
      perror ("mongo_sync_connect()");
      exit (1);
    }

  eval = bson_build_full (BSON_TYPE_JS_CODE, "$eval", FALSE,
                          "function(x){return x + 4.2;}", -1,
                          BSON_TYPE_ARRAY, "args", TRUE,
                          bson_build (BSON_TYPE_INT32, "0", 1,
                                      BSON_TYPE_NONE),
                          BSON_TYPE_NONE);
  bson_finish (eval);

  p = mongo_sync_cmd_custom (conn, "test", eval);

  if (!p)
    {
      gchar *error = NULL;

      mongo_sync_cmd_get_last_error (conn, "test", &error);
      fprintf (stderr, "Can't run db.eval: %s\n", error);
      g_free (error);

      exit (1);
    }

  cursor = mongo_sync_cursor_new (conn, "test", p);

  if (!cursor)
    {
      perror ("mongo_sync_cursor_new()");
      exit (1);
    }

  while (mongo_sync_cursor_next (cursor))
    {
      bson *result;
      bson_cursor *c;
      gdouble r;

      result = mongo_sync_cursor_get_data (cursor);
      if (!result)
        {
          perror ("mongo_sync_cursor_get_data()");
          exit (1);
        }

      c = bson_find (result, "retval");
      if (!bson_cursor_get_double (c, &r))
        {
          perror ("bson_cursor_get_double()");
          exit (1);
        }
      bson_cursor_free (c);
      bson_free (result);

      printf ("Result: %2.1f\n", r);
    }

  mongo_sync_cursor_free (cursor);
  mongo_sync_disconnect (conn);

  return 0;
}
