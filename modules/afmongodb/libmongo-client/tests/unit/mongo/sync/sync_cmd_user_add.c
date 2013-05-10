#include "test.h"
#include "mongo.h"
#include "config.h"

#include <errno.h>
#include <sys/socket.h>
#include "libmongo-private.h"

void
test_mongo_sync_cmd_user_add_net_secondary (void)
{
  mongo_sync_connection *c;
  gboolean ret;

  skip (!config.secondary_host, 1,
	"Secondary server not configured");

  c = mongo_sync_connect (config.secondary_host, config.secondary_port, TRUE);
  mongo_sync_conn_set_auto_reconnect (c, TRUE);

  ret = mongo_sync_cmd_user_add (c, config.db, "test", "s3kr1+");
  ok (ret && mongo_sync_cmd_is_master (c),
      "mongo_sync_cmd_user_add() automatically reconnects to master");

  mongo_sync_disconnect (c);

  endskip;
}

void
test_mongo_sync_cmd_user_add_net (void)
{
  mongo_sync_connection *c;

  begin_network_tests (3);

  c = mongo_sync_connect (config.primary_host, config.primary_port, TRUE);
  mongo_sync_conn_set_auto_reconnect (c, TRUE);

  ok (mongo_sync_cmd_user_add (c, config.db, "test", "s3kr1+") == TRUE,
      "mongo_sync_cmd_user_add() works");

  shutdown (c->super.fd, SHUT_RDWR);
  sleep (3);

  ok (mongo_sync_cmd_user_add (c, config.db, "test", "s3kr1+") == TRUE,
      "mongo_sync_cmd_user_add() automatically reconnects");

  mongo_sync_disconnect (c);

  test_mongo_sync_cmd_user_add_net_secondary ();

  end_network_tests ();
}

void
test_mongo_sync_cmd_user_add (void)
{
  mongo_sync_connection *c;

  c = test_make_fake_sync_conn (-1, FALSE);

  errno = 0;
  ok (mongo_sync_cmd_user_add (NULL, "test", "test", "s3kr1+") == FALSE,
      "mongo_sync_cmd_user_add() fails with a NULL connection");
  cmp_ok (errno, "==", ENOTCONN,
	  "errno is set to ENOTCONN");

  errno = 0;
  ok (mongo_sync_cmd_user_add (c, NULL, "test", "s3kr1+") == FALSE,
      "mongo_sync_cmd_user_add() fails with a NULL db");
  cmp_ok (errno, "==", EINVAL,
	  "errno is set to EINVAL");

  errno = 0;
  ok (mongo_sync_cmd_user_add (c, "test", NULL, "s3kr1+") == FALSE,
      "mongo_sync_cmd_user_add() fails with a NULL user");
  cmp_ok (errno, "==", EINVAL,
	  "errno is set to EINVAL");

  errno = 0;
  ok (mongo_sync_cmd_user_add (c, "test", "test", NULL) == FALSE,
      "mongo_sync_cmd_user_add() fails with a NULL password");
  cmp_ok (errno, "==", EINVAL,
	  "errno is set to EINVAL");

  ok (mongo_sync_cmd_user_add (c, "test", "test", "s3kr1+") == FALSE,
      "mongo_sync_cmd_user_add() fails with a bogus FD");

  mongo_sync_disconnect (c);

  test_mongo_sync_cmd_user_add_net ();
}

RUN_TEST (12, mongo_sync_cmd_user_add);
