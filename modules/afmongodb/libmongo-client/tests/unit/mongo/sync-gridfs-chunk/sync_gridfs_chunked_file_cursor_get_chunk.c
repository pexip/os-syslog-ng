#include "test.h"
#include "mongo.h"

#include "libmongo-private.h"

void
test_mongo_sync_gridfs_chunked_file_cursor_get_chunk (void)
{
  gint32 size;

  ok (mongo_sync_gridfs_chunked_file_cursor_get_chunk (NULL, &size) == NULL,
      "mongo_sync_gridfs_file_cursor_get_chunk() fails with a NULL cursor");
}

RUN_TEST (1, mongo_sync_gridfs_chunked_file_cursor_get_chunk);
