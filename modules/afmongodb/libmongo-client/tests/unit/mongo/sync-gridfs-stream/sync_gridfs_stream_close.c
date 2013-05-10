#include "test.h"
#include "mongo.h"

#include "libmongo-private.h"

void
test_mongo_sync_gridfs_stream_close (void)
{
  mongo_sync_connection *conn;
  mongo_sync_gridfs *gfs;
  mongo_sync_gridfs_stream *stream;

  mongo_util_oid_init (0);

  ok (mongo_sync_gridfs_stream_close (NULL) == FALSE,
      "mongo_sync_gridfs_stream_close() fails with a NULL stream");

  begin_network_tests (3);

  conn = mongo_sync_connect (config.primary_host, config.primary_port, FALSE);
  gfs = mongo_sync_gridfs_new (conn, config.gfs_prefix);

  stream = mongo_sync_gridfs_stream_new (gfs, NULL);
  ok (mongo_sync_gridfs_stream_close (stream) == TRUE,
      "mongo_sync_gridfs_stream_close() works with a write stream");

  stream = mongo_sync_gridfs_stream_new (gfs, NULL);
  stream->file.type = LMC_GRIDFS_FILE_CHUNKED;
  ok (mongo_sync_gridfs_stream_close (stream) == FALSE,
      "mongo_sync_gridfs_stream_close() should fail with a chunked file");

  stream->file.type = LMC_GRIDFS_FILE_STREAM_READER;
  ok (mongo_sync_gridfs_stream_close (stream) == TRUE,
      "mongo_sync_gridfs_stream_close() works with a read stream");

  mongo_sync_gridfs_free (gfs, TRUE);

  end_network_tests ();
}

RUN_TEST (4, mongo_sync_gridfs_stream_close);
