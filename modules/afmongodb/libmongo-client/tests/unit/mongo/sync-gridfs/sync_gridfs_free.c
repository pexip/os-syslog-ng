#include "test.h"
#include "mongo.h"

#include <errno.h>

void
test_mongo_sync_gridfs_free (void)
{
  mongo_sync_connection *conn;
  mongo_sync_gridfs *gfs;

  errno = 0;
  mongo_sync_gridfs_free (NULL, FALSE);
  cmp_ok (errno, "==", ENOTCONN,
	  "mongo_sync_gridfs_free() with a NULL connection shall set errno");

  begin_network_tests (2);

  conn = mongo_sync_connect (config.primary_host, config.primary_port, FALSE);
  gfs = mongo_sync_gridfs_new (conn, config.gfs_prefix);

  mongo_sync_gridfs_free (gfs, FALSE);
  cmp_ok (errno, "==", 0,
	  "mongo_sync_gridfs_free() should clear errno on success");

  gfs = mongo_sync_gridfs_new (conn, config.gfs_prefix);
  mongo_sync_gridfs_free (gfs, TRUE);
  cmp_ok (errno, "==", 0,
	  "mongo_sync_gridfs_free() works when asked to free the "
	  "connection too");

  end_network_tests ();
}

RUN_TEST (3, mongo_sync_gridfs_free);
