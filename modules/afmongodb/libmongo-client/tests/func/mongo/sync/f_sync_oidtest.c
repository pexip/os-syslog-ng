#include "test.h"
#include <mongo.h>

#include <string.h>

void
test_func_mongo_sync_oidtest (void)
{
  mongo_sync_connection *conn;
  bson *boid, *reply = NULL;
  bson_cursor *c;
  mongo_packet *p;
  guint8 *oid;
  const guint8 *noid;

  mongo_util_oid_init (0);

  oid = mongo_util_oid_new (1);
  boid = bson_new ();
  bson_append_oid (boid, "driverOIDTest", oid);
  bson_finish (boid);

  conn = mongo_sync_connect (config.primary_host, config.primary_port,
			     FALSE);

  p = mongo_sync_cmd_custom (conn, config.db, boid);
  ok (p != NULL,
      "driverOIDTest(OID) custom command works");
  mongo_wire_reply_packet_get_nth_document (p, 1, &reply);
  bson_finish (reply);

  c = bson_find (reply, "oid");
  bson_cursor_get_oid (c, &noid);
  ok (memcmp (oid, noid, 12) == 0,
      "driverOIDTest(OID) returns the same OID");
  bson_cursor_free (c);

  mongo_sync_disconnect (conn);
  mongo_wire_packet_free (p);
  bson_free (boid);
  bson_free (reply);
}

RUN_NET_TEST (2, func_mongo_sync_oidtest);
