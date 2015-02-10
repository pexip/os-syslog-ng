#include "test.h"
#include "mongo.h"

void
test_mongo_sync_gridfs_get_set_chunk_size (void)
{
  mongo_sync_gridfs *gfs;

  ok (mongo_sync_gridfs_get_chunk_size (NULL) == -1,
      "mongo_sync_gridfs_get_chunk_size() fails with a NULL gfs");
  ok (mongo_sync_gridfs_set_chunk_size (NULL, 16 * 1024) == FALSE,
      "mongo_sync_gridfs_set_chunk_size() fails with a NULL gfs");

  begin_network_tests (3);

  gfs = mongo_sync_gridfs_new (mongo_sync_connect (config.primary_host,
                                                   config.primary_port,
                                                   FALSE),
                               config.gfs_prefix);

  ok (mongo_sync_gridfs_set_chunk_size (gfs, -1) == FALSE,
      "mongo_sync_gridfs_set_chunk_size() fails if the size is invalid");
  ok (mongo_sync_gridfs_set_chunk_size (gfs, 12345),
      "mongo_sync_gridfs_set_chunk_size() works");
  cmp_ok (mongo_sync_gridfs_get_chunk_size (gfs), "==", 12345,
          "mongo_sync_gridfs_get_chunk_size() works");

  mongo_sync_gridfs_free (gfs, TRUE);

  end_network_tests ();
}

RUN_TEST (5, mongo_sync_gridfs_get_set_chunk_size);
