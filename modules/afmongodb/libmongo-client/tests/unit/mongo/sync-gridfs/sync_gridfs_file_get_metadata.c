#include "test.h"
#include "mongo.h"

void
test_mongo_sync_gridfs_file_get_metadata (void)
{
  ok (mongo_sync_gridfs_file_get_id (NULL) == NULL,
      "mongo_sync_gridfs_file_get_id() fails with a NULL file");
  ok (mongo_sync_gridfs_file_get_length (NULL) == -1,
      "mongo_sync_gridfs_file_get_length() fails with a NULL file");
  ok (mongo_sync_gridfs_file_get_chunk_size (NULL) == -1,
      "mongo_sync_gridfs_file_get_chunk_size() fails with a NULL file");
  ok (mongo_sync_gridfs_file_get_md5 (NULL) == NULL,
      "mongo_sync_gridfs_file_get_md5() fails with a NULL file");
  ok (mongo_sync_gridfs_file_get_date (NULL) == -1,
      "mongo_sync_gridfs_file_get_date() fails with a NULL file");
  ok (mongo_sync_gridfs_file_get_metadata (NULL) == NULL,
      "mongo_sync_gridfs_file_get_metadata() fails with a NULL file");
  ok (mongo_sync_gridfs_file_get_chunks (NULL) == -1,
      "mongo_sync_gridfs_file_get_chunks() fails with a NULL file");
}

RUN_TEST (7, mongo_sync_gridfs_file_get_metadata);
