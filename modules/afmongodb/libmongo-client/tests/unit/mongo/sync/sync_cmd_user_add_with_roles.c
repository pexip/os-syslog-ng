#include "test.h"
#include "mongo.h"
#include "config.h"

#include <errno.h>
#include <sys/socket.h>
#include "libmongo-private.h"

void
test_mongo_sync_cmd_user_add_with_roles_net (const bson *roles)
{
  mongo_sync_connection *c;

  begin_network_tests (2);

  c = mongo_sync_connect (config.primary_host, config.primary_port, TRUE);
  mongo_sync_conn_set_auto_reconnect (c, TRUE);

  ok (mongo_sync_cmd_user_add_with_roles (c, config.db,
                                          "test", "s3kr1+", roles) == TRUE,
      "mongo_sync_cmd_user_add_with_roles() works");

  shutdown (c->super.fd, SHUT_RDWR);
  sleep (3);

  ok (mongo_sync_cmd_user_add_with_roles (c, config.db,
                                          "test", "s3kr1+", roles) == TRUE,
      "mongo_sync_cmd_user_add_with_roles() automatically reconnects");

  mongo_sync_disconnect (c);

  end_network_tests ();
}

void
test_mongo_sync_cmd_user_add_with_roles (void)
{
  mongo_sync_connection *c;
  bson *roles = bson_build (BSON_TYPE_STRING, "0", "readWrite", -1,
                            BSON_TYPE_NONE);

  bson_finish (roles);

  c = test_make_fake_sync_conn (-1, FALSE);

  errno = 0;
  ok (mongo_sync_cmd_user_add_with_roles (NULL, "test",
                                          "test", "s3kr1+", roles) == FALSE,
      "mongo_sync_cmd_user_add_with_roles() fails with a NULL connection");
  cmp_ok (errno, "==", ENOTCONN,
          "errno is set to ENOTCONN");

  errno = 0;
  ok (mongo_sync_cmd_user_add_with_roles (c, NULL,
                                          "test", "s3kr1+", roles) == FALSE,
      "mongo_sync_cmd_user_add_with_roles() fails with a NULL db");
  cmp_ok (errno, "==", EINVAL,
          "errno is set to EINVAL");

  errno = 0;
  ok (mongo_sync_cmd_user_add_with_roles (c, "test",
                                          NULL, "s3kr1+", roles) == FALSE,
      "mongo_sync_cmd_user_add_with_roles() fails with a NULL user");
  cmp_ok (errno, "==", EINVAL,
          "errno is set to EINVAL");

  errno = 0;
  ok (mongo_sync_cmd_user_add_with_roles (c, "test",
                                          "test", NULL, roles) == FALSE,
      "mongo_sync_cmd_user_add_with_roles() fails with a NULL password");
  cmp_ok (errno, "==", EINVAL,
          "errno is set to EINVAL");

  ok (mongo_sync_cmd_user_add_with_roles (c, "test",
                                          "test", "s3kr1+", NULL) == FALSE,
      "mongo_sync_cmd_user_add() fails with a bogus FD and empty roles");

  ok (mongo_sync_cmd_user_add_with_roles (c, "test",
                                          "test", "s3kr1+", roles) == FALSE,
      "mongo_sync_cmd_user_add() fails with a bogus FD");

  mongo_sync_disconnect (c);

  test_mongo_sync_cmd_user_add_with_roles_net (roles);

  bson_free (roles);
}

RUN_TEST (12, mongo_sync_cmd_user_add_with_roles);
