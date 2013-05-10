#include "test.h"
#include "mongo.h"

#include "libmongo-private.h"

void
test_mongo_sync_gridfs_stream_read (void)
{
  mongo_sync_connection *conn;
  mongo_sync_gridfs *gfs;
  mongo_sync_gridfs_stream *stream;
  guint8 buffer[4096];

  mongo_util_oid_init (0);

  ok (mongo_sync_gridfs_stream_read (NULL, buffer, sizeof (buffer)) == -1,
      "mongo_sync_gridfs_stream_read() should fail with a NULL connection");

  begin_network_tests (3);

  conn = mongo_sync_connect (config.primary_host, config.primary_port, FALSE);
  gfs = mongo_sync_gridfs_new (conn, config.gfs_prefix);

  stream = mongo_sync_gridfs_stream_new (gfs, NULL);

  ok (mongo_sync_gridfs_stream_read (stream, buffer, sizeof (buffer)) == -1,
      "mongo-sync_gridfs_stream_read() should fail when the stream is "
      "write-only");

  stream->file.type = LMC_GRIDFS_FILE_STREAM_READER;

  ok (mongo_sync_gridfs_stream_read (stream, NULL, sizeof (buffer)) == -1,
      "mongo_sync_gridfs_stream_read() should fail with a NULL buffer");
  ok (mongo_sync_gridfs_stream_read (stream, buffer, 0) == -1,
      "mongo_sync_gridfs_stream_read() should fail with a 0 size");

  mongo_sync_gridfs_stream_close (stream);

  mongo_sync_gridfs_free (gfs, TRUE);

  end_network_tests ();
}

RUN_TEST (4, mongo_sync_gridfs_stream_read);
