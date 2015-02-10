#include "test.h"
#include "mongo.h"

void
test_mongo_sync_gridfs_stream_new (void)
{
  mongo_sync_connection *conn;
  mongo_sync_gridfs *gfs;
  mongo_sync_gridfs_stream *stream;
  bson *meta;

  mongo_util_oid_init (0);

  meta = bson_build (BSON_TYPE_STRING, "my-id", "sync_gridfs_stream_new", -1,
                     BSON_TYPE_NONE);
  bson_finish (meta);

  ok (mongo_sync_gridfs_stream_new (NULL, meta) == FALSE,
      "mongo_sync_gridfs_stream_new() should fail with a NULL connection");

  begin_network_tests (2);

  conn = mongo_sync_connect (config.primary_host, config.primary_port, FALSE);
  gfs = mongo_sync_gridfs_new (conn, config.gfs_prefix);

  stream = mongo_sync_gridfs_stream_new (gfs, NULL);
  ok (stream != NULL,
      "mongo_sync_gridfs_stream_new() works with NULL metadata");
  mongo_sync_gridfs_stream_close (stream);

  stream = mongo_sync_gridfs_stream_new (gfs, meta);
  ok (stream != NULL,
      "mongo_sync_gridfs_stream_new() works with metadata");
  mongo_sync_gridfs_stream_close (stream);

  mongo_sync_gridfs_free (gfs, TRUE);

  end_network_tests ();

  bson_free (meta);
}

RUN_TEST (3, mongo_sync_gridfs_stream_new);
