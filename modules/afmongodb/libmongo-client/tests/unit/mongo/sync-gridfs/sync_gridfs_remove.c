#include "test.h"
#include "mongo.h"

void
test_mongo_sync_gridfs_remove (void)
{
  mongo_sync_gridfs *gfs;
  bson *query;

  query = bson_build (BSON_TYPE_STRING, "bogus-key", "bogus-value", -1,
		      BSON_TYPE_NONE);
  bson_finish (query);

  ok (mongo_sync_gridfs_remove (NULL, NULL) == FALSE,
      "mongo_sync_gridfs_remove() fails with a NULL GridFS");

  begin_network_tests (1);

  gfs = mongo_sync_gridfs_new
    (mongo_sync_connect (config.primary_host, config.primary_port, FALSE),
     config.gfs_prefix);

  ok (mongo_sync_gridfs_remove (gfs, query) == FALSE,
      "mongo_sync_gridfs_remove() fails with a query that does not match "
      "anything");

  mongo_sync_gridfs_free (gfs, TRUE);

  end_network_tests ();

  bson_free (query);
}

RUN_TEST (2, mongo_sync_gridfs_remove);
