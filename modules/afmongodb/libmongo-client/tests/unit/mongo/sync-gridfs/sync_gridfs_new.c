#include "test.h"
#include "mongo.h"

#include <errno.h>

void
test_mongo_sync_gridfs_new (void)
{
  mongo_sync_connection *conn;
  mongo_sync_gridfs *gfs;
  gchar *f, *c;

  conn = test_make_fake_sync_conn (4, TRUE);

  ok (mongo_sync_gridfs_new (NULL, "test.fs") == NULL,
      "mongo_sync_gridfs_new() should fail with a NULL connection");

  ok (mongo_sync_gridfs_new (conn, "test.fs") == NULL,
      "mongo_sync_gridfs_new() should fail with a bogus connection");

  ok (mongo_sync_gridfs_new (conn, NULL) == NULL,
      "mongo_sync_gridfs_new() should fail with a NULL ns prefix");

  ok (mongo_sync_gridfs_new (conn, "bogus") == NULL,
      "mongo_sync_gridfs_new() should fail with a bogus ns prefix");

  mongo_sync_disconnect (conn);

  begin_network_tests (4);

  f = g_strconcat (config.gfs_prefix, ".files", NULL);
  c = g_strconcat (config.gfs_prefix, ".chunks", NULL);

  conn = mongo_sync_connect (config.primary_host, config.primary_port, FALSE);

  gfs = mongo_sync_gridfs_new (conn, config.gfs_prefix);
  ok (gfs != NULL,
      "mongo_sync_gridfs_new() works");
  is (gfs->ns.prefix, config.gfs_prefix,
      "The namespace prefix is as specified");
  is (gfs->ns.files, f,
      "The files namespace is correct");
  is (gfs->ns.chunks, c,
      "The chunks namespace is correct");
  mongo_sync_gridfs_free (gfs, FALSE);

  mongo_sync_disconnect (conn);

  g_free (f);
  g_free (c);
  end_network_tests ();
}

RUN_TEST (8, mongo_sync_gridfs_new);
