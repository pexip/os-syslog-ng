#include "test.h"
#include <mongo.h>
#include <errno.h>

void
test_func_mongo_sync_invalid_getlasterror (void)
{
  mongo_sync_connection *conn;
  gchar *error = NULL;
  gboolean res;

  conn = mongo_sync_connect (config.primary_host, config.primary_port,
                             TRUE);

  res = mongo_sync_cmd_get_last_error
    (conn, "1234567890123456789012345678901234567890123456789012345678901234567890",
     &error);

  ok (res == FALSE,
      "Trying to get the last error from an invalid DB results in an error.");
  ok (error == NULL,
      "When getLastError() fails, error remains NULL");

  mongo_sync_disconnect (conn);
}

RUN_NET_TEST (2, func_mongo_sync_invalid_getlasterror);
