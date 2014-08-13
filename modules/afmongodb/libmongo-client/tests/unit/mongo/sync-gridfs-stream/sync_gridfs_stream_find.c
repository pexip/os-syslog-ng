#include "test.h"
#include "mongo.h"

void
test_mongo_sync_gridfs_stream_find (void)
{
  mongo_sync_connection *conn;
  mongo_sync_gridfs *gfs;
  bson *query;

  query = bson_build (BSON_TYPE_STRING, "filename", "bogus-fn", -1,
                      BSON_TYPE_NONE);
  bson_finish (query);

  ok (mongo_sync_gridfs_stream_find (NULL, query) == NULL,
      "mongo_sync_gridfs_stream_find() should fail with a NULL connection");

  begin_network_tests (2);

  conn = mongo_sync_connect (config.primary_host, config.primary_port, FALSE);
  gfs = mongo_sync_gridfs_new (conn, config.gfs_prefix);

  ok (mongo_sync_gridfs_stream_find (gfs, NULL) == NULL,
      "mongo_sync_gridfs_stream_find() fails with a NULL query");

  ok (mongo_sync_gridfs_stream_find (gfs, query) == NULL,
      "mongo_sync_gridfs_stream_find() fails if the file is not found");

  mongo_sync_gridfs_free (gfs, TRUE);

  end_network_tests ();

  bson_free (query);
}

RUN_TEST (3, mongo_sync_gridfs_stream_find);
