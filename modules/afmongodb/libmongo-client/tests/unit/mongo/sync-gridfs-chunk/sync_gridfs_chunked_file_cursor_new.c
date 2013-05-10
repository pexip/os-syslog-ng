#include "test.h"
#include "mongo.h"

#include "libmongo-private.h"

void
test_mongo_sync_gridfs_chunked_file_cursor_new (void)
{
  mongo_sync_gridfs_chunked_file f;

  ok (mongo_sync_gridfs_chunked_file_cursor_new (NULL, 0, 0) == NULL,
      "mongo_sync_gridfs_file_cursor_new() fails with a NULL file");
  ok (mongo_sync_gridfs_chunked_file_cursor_new (&f, -1, 0) == NULL,
      "mongo_sync_gridfs_file_cursor_new() fails with an invalid start position");
  ok (mongo_sync_gridfs_chunked_file_cursor_new (&f, 0, -1) == NULL,
      "mongo_sync_gridfs_file_cursor_new() fails with an invalid max number");
}

RUN_TEST (3, mongo_sync_gridfs_chunked_file_cursor_new);
