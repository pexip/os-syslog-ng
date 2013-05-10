#include <mongo.h>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

static void
do_inserts (mongo_sync_connection *conn)
{
  bson *base;
  gint i;

  base = bson_build
    (BSON_TYPE_STRING, "tutorial-program", "tut_hl_client.c", -1,
     BSON_TYPE_INT32, "the answer to life, the universe and everything", 42,
     BSON_TYPE_NONE);
  bson_finish (base);

  for (i = 0; i < 1000; i++)
    {
      bson *n;

      n = bson_new_from_data (bson_data (base), bson_size (base) - 1);
      bson_append_int32 (n, "counter", i);
      bson_finish (n);

      if (!mongo_sync_cmd_insert (conn, "lmc.tutorial", n, NULL))
	{
	  fprintf (stderr, "Error inserting document %d: %s\n", i,
		   strerror (errno));
	  exit (1);
	}
      bson_free (n);
    }
  bson_free (base);
}

static void
do_query (mongo_sync_connection *conn)
{
  mongo_sync_cursor *c;
  bson *query;
  gchar *error = NULL;

  query = bson_build
    (BSON_TYPE_STRING, "tutorial-program", "tut_hl_client.c", -1,
     BSON_TYPE_NONE);
  bson_finish (query);

  c = mongo_sync_cursor_new (conn, "lmc.tutorial",
			     mongo_sync_cmd_query (conn, "lmc.tutorial", 0,
						   0, 10, query, NULL));
  if (!c)
    {
      fprintf (stderr, "Error creating the query cursor: %s\n",
	       strerror (errno));
      exit (1);
    }
  bson_free (query);

  while (mongo_sync_cursor_next (c))
    {
      bson *b = mongo_sync_cursor_get_data (c);
      bson_cursor *bc;
      gint32 cnt;

      if (!b)
	{
	  int e = errno;

	  mongo_sync_cmd_get_last_error (conn, "lmc", &error);
	  fprintf (stderr, "Error retrieving cursor data: %s\n",
		   (error) ? error : strerror (e));
	  exit (1);
	}

      bc = bson_find (b, "counter");
      bson_cursor_get_int32 (bc, &cnt);
      printf ("\rCounter: %d", cnt);

      bson_cursor_free (bc);
      bson_free (b);
    }
  printf ("\n");

  mongo_sync_cursor_free (c);
}

int
main (void)
{
  mongo_sync_connection *conn;

  conn = mongo_sync_connect ("localhost", 27017, FALSE);
  if (!conn)
    {
      fprintf (stderr, "Connection failed: %s\n", strerror (errno));
      return 1;
    }

  do_inserts (conn);
  do_query (conn);

  mongo_sync_disconnect (conn);
  return 0;
}
