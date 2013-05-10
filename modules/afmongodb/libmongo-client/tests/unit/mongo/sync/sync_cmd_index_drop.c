#include "test.h"
#include "mongo.h"

void
test_mongo_sync_cmd_index_drop (void)
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

  ok (mongo_sync_cmd_index_drop (NULL, "test.ns", indexes) == FALSE,
      "mongo_sync_cmd_index_drop() fails with a NULL connection");
  ok (mongo_sync_cmd_index_drop (c, NULL, indexes) == FALSE,
      "mongo_sync_cmd_index_drop() fails with a NULL namespace");
  ok (mongo_sync_cmd_index_drop (c, "test.ns", NULL) == FALSE,
      "mongo_sync_cmd_index_drop() fails with NULL indexes");
  ok (mongo_sync_cmd_index_drop (c, "bogus", indexes) == FALSE,
      "mongo_sync_cmd_index_drop() fails with a bogus namespace");
  ok (mongo_sync_cmd_index_drop (c, "test.ns", indexes) == FALSE,
      "mongo_sync_cmd_index_drop() fails with a bogus FD");

  mongo_sync_disconnect (c);

  begin_network_tests (1);

  c = mongo_sync_connect (config.primary_host, config.primary_port,
			  TRUE);
  mongo_sync_cmd_insert (c, config.ns, doc, NULL);

  mongo_sync_cmd_index_create (c, config.ns, indexes, 0);

  ok (mongo_sync_cmd_index_drop (c, config.ns, indexes) == TRUE,
      "mongo_sync_cmd_index_drop() works");

  mongo_sync_disconnect (c);

  bson_free (doc);
  bson_free (indexes);

  end_network_tests ();
}

RUN_TEST (6, mongo_sync_cmd_index_drop);
