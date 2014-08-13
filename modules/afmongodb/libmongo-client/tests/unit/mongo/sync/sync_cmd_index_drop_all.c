#include "test.h"
#include "mongo.h"

void
test_mongo_sync_cmd_index_drop_all (void)
{
  mongo_sync_connection *c;
  bson *doc, *indexes;

  c = test_make_fake_sync_conn (-1, FALSE);
  doc = test_bson_generate_full ();
  indexes = bson_build (BSON_TYPE_INT32, "sex", 1,
                        BSON_TYPE_DOUBLE, "double", 1.0,
                        BSON_TYPE_BOOLEAN, "TRUE", TRUE,
                        BSON_TYPE_INT64, "print", (gint64)-1,
                        BSON_TYPE_NONE);
  bson_finish (indexes);

  ok (mongo_sync_cmd_index_drop_all (NULL, "test.ns") == FALSE,
      "mongo_sync_cmd_index_drop_all() fails with a NULL connection");
  ok (mongo_sync_cmd_index_drop_all (c, NULL) == FALSE,
      "mongo_sync_cmd_index_drop_all() fails with a NULL namespace");
  ok (mongo_sync_cmd_index_drop_all (c, "bogus") == FALSE,
      "mongo_sync_cmd_index_drop_all() fails with a bogus namespace");
  ok (mongo_sync_cmd_index_drop_all (c, "test.ns") == FALSE,
      "mongo_sync_cmd_index_drop_all() fails with a bogus FD");

  mongo_sync_disconnect (c);

  begin_network_tests (1);

  c = mongo_sync_connect (config.primary_host, config.primary_port,
                          TRUE);
  mongo_sync_cmd_insert (c, config.ns, doc, NULL);

  mongo_sync_cmd_index_create (c, config.ns, indexes, 0);

  ok (mongo_sync_cmd_index_drop_all (c, config.ns) == TRUE,
      "mongo_sync_cmd_index_drop_all() works");

  mongo_sync_disconnect (c);

  bson_free (doc);
  bson_free (indexes);

  end_network_tests ();
}

RUN_TEST (5, mongo_sync_cmd_index_drop_all);
