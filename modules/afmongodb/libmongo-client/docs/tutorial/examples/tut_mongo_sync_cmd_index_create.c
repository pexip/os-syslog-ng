#include <mongo.h>

#include <errno.h>
#include <stdio.h>

static void
create_and_verify_index(mongo_sync_connection *conn,
                        bson *index)
{
  if (!mongo_sync_cmd_index_create (conn, "lmc.indexed", index,
                                    MONGO_INDEX_UNIQUE | MONGO_INDEX_DROP_DUPS |
                                    MONGO_INDEX_SPARSE))
    {
      gchar *error = NULL;
      int e = errno;

      mongo_sync_cmd_get_last_error (conn, "lmc.indexed", &error);
      fprintf (stderr, "Can't create indexes: %s\n", error ? error : strerror (e));
      g_free (error);
    }
  else
    printf ("Index successfully created!\n");
}

int
main (void)
{
  mongo_sync_connection *conn;
  bson *invalid_index, *index;

  invalid_index = bson_build (BSON_TYPE_STRING, "name", "", -1,
                              BSON_TYPE_NONE);
  bson_finish (invalid_index);

  index = bson_build (BSON_TYPE_INT32, "name", 1,
                      BSON_TYPE_NONE);
  bson_finish (index);

  conn = mongo_sync_connect ("localhost", 27017, FALSE);
  if (!conn)
    {
      fprintf (stderr, "Connection failed: %s\n", strerror (errno));
      return 1;
    }

  create_and_verify_index (conn, invalid_index);
  create_and_verify_index (conn, index);

  bson_free (invalid_index);
  bson_free (index);
  mongo_sync_disconnect (conn);

  return 0;
}
