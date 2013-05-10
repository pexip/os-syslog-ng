#include <mongo.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void
tut_sync_connect (void)
{
  mongo_sync_connection *conn;

  conn = mongo_sync_connect ("localhost", 27017, TRUE);
  if (!conn)
    {
      perror ("mongo_sync_connect()");
      exit (1);
    }
  mongo_sync_disconnect (conn);
}

void
tut_sync_connect_replica (void)
{
  mongo_sync_connection *conn;

  conn = mongo_sync_connect ("mongo-master", 27017, TRUE);
  if (!conn)
    {
      perror ("mongo_sync_connect()");
      return;
    }

  if (!mongo_sync_conn_set_auto_reconnect (conn, TRUE))
    {
      perror ("mongo_sync_conn_set_auto_reconnect()");
      return;
    }

  if (!mongo_sync_conn_seed_add (conn, "mongo-replica", 27017))
    {
      perror ("mongo_sync_conn_seed_add()");
      return;
    }
  if (!mongo_sync_conn_seed_add (conn, "mongo-replica-2", 27017))
    {
      perror ("mongo_sync_conn_seed_add()");
      return;
    }

  mongo_sync_disconnect (conn);
}

void
tut_sync_insert (void)
{
  mongo_sync_connection *conn;
  bson *doc1, *doc2, *doc3;

  conn = mongo_sync_connect ("localhost", 27017, FALSE);
  if (!conn)
    {
      perror ("mongo_sync_connect()");
      exit (1);
    }

  doc1 = bson_build (BSON_TYPE_STRING, "hello", "world", -1,
		     BSON_TYPE_INT32, "the_final_answer", 42,
		     BSON_TYPE_BOOLEAN, "yes?", FALSE,
		     BSON_TYPE_INT32, "n", 1,
		     BSON_TYPE_NONE);
  bson_finish (doc1);

  if (!mongo_sync_cmd_insert (conn, "tutorial.docs", doc1, NULL))
    {
      perror ("mongo_sync_cmd_insert()");
      exit (1);
    }

  doc2 = bson_build (BSON_TYPE_INT32, "n", 2,
		     BSON_TYPE_BOOLEAN, "yes?", FALSE,
		     BSON_TYPE_STRING, "hello", "dolly", -1,
		     BSON_TYPE_NONE);
  bson_finish (doc2);

  doc3 = bson_build (BSON_TYPE_INT32, "n", 3,
		     BSON_TYPE_STRING, "hello", "nurse", -1,
		     BSON_TYPE_BOOLEAN, "yes?", TRUE,
		     BSON_TYPE_NONE);
  bson_finish (doc3);

  if (!mongo_sync_cmd_insert (conn, "tutorial.docs", doc2, doc3, NULL))
    {
      perror ("mongo_sync_cmd_insert()");
      exit (1);
    }

  bson_free (doc3);
  bson_free (doc2);
  bson_free (doc1);

  mongo_sync_disconnect (conn);
}

void
tut_sync_query_simple (void)
{
  mongo_sync_connection *conn;
  mongo_packet *p;
  mongo_sync_cursor *cursor;
  bson *query;
  gint i = 0;

  conn = mongo_sync_connect ("localhost", 27017, FALSE);
  if (!conn)
    {
      perror ("mongo_sync_connect()");
      exit (1);
    }

  query = bson_new ();
  bson_finish (query);

  p = mongo_sync_cmd_query (conn, "tutorial.docs", 0,
			    0, 10, query, NULL);
  if (!p)
    {
      perror ("mongo_sync_cmd_query()");
      exit (1);
    }
  bson_free (query);

  cursor = mongo_sync_cursor_new (conn, "tutorial.docs", p);
  if (!cursor)
    {
      perror ("mongo_sync_cursor_new()");
      exit (1);
    }

  while (mongo_sync_cursor_next (cursor))
    {
      bson *result = mongo_sync_cursor_get_data (cursor);
      bson_cursor *c;

      if (!result)
	{
	  perror ("mongo_sync_cursor_get_data()");
	  exit (1);
	}

      printf ("Keys in document #%d:\n", i);
      c = bson_cursor_new (result);
      while (bson_cursor_next (c))
	printf ("\t%s\n", bson_cursor_key (c));

      i++;
      bson_cursor_free (c);
      bson_free (result);
    }

  mongo_sync_cursor_free (cursor);
  mongo_sync_disconnect (conn);
}

void
tut_sync_query_complex (void)
{
  mongo_sync_connection *conn;
  mongo_packet *p;
  mongo_sync_cursor *cursor;
  bson *query, *select;
  gint i = 0;

  conn = mongo_sync_connect ("localhost", 27017, FALSE);
  if (!conn)
    {
      perror ("mongo_sync_connect()");
      exit (1);
    }

  query = bson_build_full (BSON_TYPE_DOCUMENT, "$query", TRUE,
			   bson_build (BSON_TYPE_BOOLEAN, "yes?", FALSE,
				       BSON_TYPE_NONE),
			   BSON_TYPE_DOCUMENT, "$orderby", TRUE,
			   bson_build (BSON_TYPE_INT32, "n", 1,
				       BSON_TYPE_NONE),
			   BSON_TYPE_NONE);
  bson_finish (query);

  select = bson_build (BSON_TYPE_INT32, "hello", 1,
		       BSON_TYPE_INT32, "n", 1,
		       BSON_TYPE_INT32, "yes?", 1,
		       BSON_TYPE_NONE);
  bson_finish (select);

  p = mongo_sync_cmd_query (conn, "tutorial.docs", 0,
			    0, 10, query, select);
  if (!p)
    {
      perror ("mongo_sync_cmd_query()");
      exit (1);
    }
  bson_free (query);
  bson_free (select);

  cursor = mongo_sync_cursor_new (conn, "tutorial.docs", p);
  if (!cursor)
    {
      perror ("mongo_sync_cursor_new()");
      exit (1);
    }

  while (mongo_sync_cursor_next (cursor))
    {
      const char *hello;
      gint32 n;
      gboolean yes;

      bson *result;
      bson_cursor *c;

      result = mongo_sync_cursor_get_data (cursor);
      if (!result)
	{
	  perror ("mongo_sync_cursor_get_data()");
	  exit (1);
	}

      c = bson_find (result, "hello");
      if (!bson_cursor_get_string (c, &hello))
	{
	  perror ("bson_cursor_get_string()");
	  exit (1);
	}
      bson_cursor_free (c);

      c = bson_find (result, "n");
      if (!bson_cursor_get_int32 (c, &n))
	{
	  perror ("bson_cursor_get_int32()");
	  exit (1);
	}
      bson_cursor_free (c);

      c = bson_find (result, "yes?");
      if (!bson_cursor_get_boolean (c, &yes))
	{
	  perror ("bson_cursor_get_boolean()");
	  exit (1);
	}
      bson_cursor_free (c);

      printf ("Document #%d: hello=%s; n=%d; yes?=%s\n",
	      i, hello, n, (yes) ? "TRUE" : "FALSE");

      bson_free (result);
      i++;
    }

  mongo_sync_cursor_free (cursor);
  mongo_sync_disconnect (conn);
}

int
main (int argc, char *argv[])
{
  tut_sync_connect ();
  tut_sync_connect_replica ();
  tut_sync_insert ();
  tut_sync_query_simple ();
  tut_sync_query_complex ();

  return 0;
}
