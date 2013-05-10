#include "test.h"
#include "mongo.h"

#define BIG_PACKET_SIZE 2 * 1024 * 1024

void
test_func_client_big_packet (void)
{
  mongo_connection *conn;
  mongo_packet *p;

  guint8 *data;
  bson *b;
  gint32 exp_size;

  conn = mongo_connect (config.primary_host, config.primary_port);

  b = bson_new_sized (BIG_PACKET_SIZE + 1024);
  data = g_malloc (BIG_PACKET_SIZE);
  memset (data, 'z', BIG_PACKET_SIZE);
  bson_append_boolean (b, "big_packet_size", TRUE);
  bson_append_binary (b, "bighead", BSON_BINARY_SUBTYPE_GENERIC,
		      data, BIG_PACKET_SIZE);
  bson_finish (b);
  exp_size = bson_size (b);

  p = mongo_wire_cmd_insert (1, config.ns, b, NULL);
  mongo_packet_send (conn, p);
  bson_free (b);
  mongo_wire_packet_free (p);

  b = bson_new ();
  bson_append_boolean (b, "big_packet_size", TRUE);
  bson_finish (b);

  p = mongo_wire_cmd_query (2, config.ns, 0, 0, 1, b, NULL);
  mongo_packet_send (conn, p);
  mongo_wire_packet_free (p);
  bson_free (b);

  p = mongo_packet_recv (conn);
  ok (p != NULL,
      "mongo_packet_recv() works with a huge packet");

  mongo_wire_reply_packet_get_nth_document (p, 1, &b);
  bson_finish (b);
  mongo_wire_packet_free (p);

  cmp_ok (exp_size + 17, "==", bson_size (b), /* +17: _id + value */
	  "Huge packet receiving works, and returns a same sized packet");

  bson_free (b);

  mongo_disconnect (conn);
}

RUN_NET_TEST (2, func_client_big_packet);
