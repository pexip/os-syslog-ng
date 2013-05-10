#include "test.h"
#include <mongo.h>

int
main (void)
{
  mongo_sync_connection *conn;
  gchar *c;

  if (!test_env_setup ())
    return 0;

  conn = mongo_sync_connect (config.primary_host, config.primary_port, FALSE);
  mongo_sync_cmd_drop (conn, config.db, config.coll);

  c = g_strconcat (config.coll, ".grid.files", NULL);
  mongo_sync_cmd_drop (conn, config.db, c);
  g_free (c);

  c = g_strconcat (config.coll, ".grid.chunks", NULL);
  mongo_sync_cmd_drop (conn, config.db, c);
  g_free (c);

  c = g_strconcat (config.coll, ".capped", NULL);
  mongo_sync_cmd_drop (conn, config.db, c);
  g_free (c);

  test_env_free ();

  return 0;
}
