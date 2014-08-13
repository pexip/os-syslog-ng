#include <mongo.h>

#include <errno.h>
#include <stdio.h>

static void
print_coll_info (bson *info)
{
  bson_cursor *c = NULL;
  bson *options = NULL;

  const gchar *name;
  gboolean capped = FALSE;
  gint64 size = -1;
  gint64 max = -1;

  c = bson_find (info, "name");
  bson_cursor_get_string (c, &name);
  bson_cursor_find (c, "options");

  bson_cursor_get_document (c, &options);

  printf ("Options for %s:\n", name);

  bson_cursor_free (c);
  bson_free (info);

  c = bson_find (options, "capped");
  bson_cursor_get_boolean (c, &capped);
  bson_cursor_free (c);

  c = bson_find (options, "size");
  bson_cursor_get_int64 (c, &size);
  bson_cursor_free (c);

  c = bson_find (options, "max");
  bson_cursor_get_int64 (c, &max);
  bson_cursor_free (c);

  bson_free (options);

  printf ("\tCapped: %s\n", (capped) ? "yes" : "no");
  if (size > 0)
    printf ("\tSize  : %lu\n", size);
  if (max > 0)
    printf ("\tMax   : %lu\n", max);
  printf ("\n");
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

  mongo_sync_cmd_create (conn, "lmc", "cmd_create", MONGO_COLLECTION_DEFAULTS);
  print_coll_info (mongo_sync_cmd_exists (conn, "lmc", "cmd_create"));

  mongo_sync_cmd_create (conn, "lmc", "cmd_create_capped",
                         MONGO_COLLECTION_CAPPED, 655360);
  print_coll_info (mongo_sync_cmd_exists (conn, "lmc", "cmd_create_capped"));

  mongo_sync_cmd_create (conn, "lmc", "cmd_create_capped_max",
                         MONGO_COLLECTION_CAPPED | MONGO_COLLECTION_CAPPED_MAX,
                         655360, 100);
  print_coll_info (mongo_sync_cmd_exists (conn, "lmc",
                                          "cmd_create_capped_max"));

  mongo_sync_cmd_create (conn, "lmc", "cmd_create_sized",
                         MONGO_COLLECTION_SIZED, 655360);
  print_coll_info (mongo_sync_cmd_exists (conn, "lmc", "cmd_create_sized"));

  mongo_sync_disconnect (conn);

  return 0;
}
