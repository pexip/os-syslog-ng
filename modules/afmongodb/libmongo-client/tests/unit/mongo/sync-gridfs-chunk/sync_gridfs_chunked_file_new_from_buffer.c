#include "test.h"
#include "mongo.h"

#define BUFFER_SIZE 256 * 1024 + 42

void
test_mongo_sync_gridfs_chunked_file_new_from_buffer (void)
{
  mongo_sync_connection *conn;
  mongo_sync_gridfs *gfs;
  bson *metadata;
  guint8 *buffer;
  mongo_sync_gridfs_chunked_file *gfile;

  buffer = g_malloc (BUFFER_SIZE);
  memset (buffer, 'a', BUFFER_SIZE);

  conn = test_make_fake_sync_conn (4, TRUE);
  gfs = mongo_sync_gridfs_new (conn, config.gfs_prefix);

  metadata = bson_build (BSON_TYPE_STRING, "filename",
			 "gridfs_file_new_from_buffer", -1,
			 BSON_TYPE_NONE);
  bson_finish (metadata);

  ok (mongo_sync_gridfs_chunked_file_new_from_buffer (NULL, metadata,
						      buffer, BUFFER_SIZE) == FALSE,
      "mongo_sync_gridfs_chunked_file_new_from_buffer() fails with a NULL GridFS");

  mongo_sync_gridfs_free (gfs, TRUE);

  begin_network_tests (5);

  conn = mongo_sync_connect (config.primary_host, config.primary_port, FALSE);
  gfs = mongo_sync_gridfs_new (conn, config.gfs_prefix);

  ok (mongo_sync_gridfs_chunked_file_new_from_buffer (gfs, metadata,
						      NULL, BUFFER_SIZE) == FALSE,
      "mongo_sync_gridfs_chunked_file_new_from_buffer() fails with NULL data");

  ok (mongo_sync_gridfs_chunked_file_new_from_buffer (gfs, metadata,
						      buffer, 0) == FALSE,
      "mongo_sync_gridfs_chunked_file_new_from_buffer() fails with an invalid data size");

  ok (mongo_sync_gridfs_chunked_file_new_from_buffer (gfs, metadata, buffer,
						      BUFFER_SIZE) == FALSE,
      "mongo_sync_gridfs_chunked_file_new_from_buffer() fails with uninitialized OID");

  mongo_util_oid_init (0);

  gfile = mongo_sync_gridfs_chunked_file_new_from_buffer (gfs, metadata,
							  buffer, BUFFER_SIZE);
  ok (gfile != NULL,
      "mongo_sync_gridfs_chunked_file_new_from_buffer() works with metadata");
  mongo_sync_gridfs_chunked_file_free (gfile);

  gfile = mongo_sync_gridfs_chunked_file_new_from_buffer (gfs, NULL,
							  buffer, BUFFER_SIZE);
  ok (gfile != NULL,
      "mongo_sync_gridfs_chunked_file_new_from_buffer() works without metadata");
  mongo_sync_gridfs_chunked_file_free (gfile);

  mongo_sync_gridfs_free (gfs, TRUE);

  end_network_tests ();

  bson_free (metadata);
  g_free (buffer);
}

RUN_TEST (6, mongo_sync_gridfs_chunked_file_new_from_buffer);
