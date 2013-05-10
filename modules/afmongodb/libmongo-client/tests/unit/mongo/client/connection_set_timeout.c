#include "test.h"
#include "mongo.h"

#include "libmongo-private.h"

void
test_mongo_connection_set_timeout (void)
{
  mongo_connection c, *conn;

  c.fd = -1;

  ok (mongo_connection_set_timeout (NULL, 100) == FALSE,
      "mongo_connection_set_timeout() should fail with a NULL connection");
  ok (mongo_connection_set_timeout (&c, -1) == FALSE,
      "mongo_connection_set_timeout() should fail with a negative timeout");
  ok (mongo_connection_set_timeout (&c, 100) == FALSE,
      "mongo_connection_set_timeout() should fail with an invalid FD");

  begin_network_tests (0);

  conn = mongo_connect (config.primary_host, config.primary_port);

  /* No verification here, as some systems may or may not support
     this, thus, failing in a test is not fatal. */
  mongo_connection_set_timeout (conn, 100);

  mongo_disconnect (conn);

  end_network_tests ();
}

RUN_TEST (3, mongo_connection_set_timeout);
