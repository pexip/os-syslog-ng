#include "test.h"
#include "mongo.h"

#include <errno.h>

void
test_mongo_sync_gridfs_chunked_file_free (void)
{
  errno = 0;
  mongo_sync_gridfs_chunked_file_free (NULL);

  cmp_ok (errno, "==", ENOTCONN,
	  "mongo_sync_gridfs_chunked_file_free() fails with a NULL file");
}

RUN_TEST (1, mongo_sync_gridfs_chunked_file_free);
