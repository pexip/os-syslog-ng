#include "test.h"
#include "mongo.h"

void
test_mongo_utils_oid_as_string (void)
{
  guint8 *oid;
  gchar *oid_str;

  mongo_util_oid_init (0);

  oid = mongo_util_oid_new (1);

  ok (mongo_util_oid_as_string (NULL) == NULL,
      "mongo_util_oid_as_string() should fail with a NULL oid");

  oid_str = mongo_util_oid_as_string (oid);

  ok (oid_str != NULL,
      "mongo_util_oid_as_string() works");

  g_free (oid_str);
  g_free (oid);
}

RUN_TEST (2, mongo_utils_oid_as_string);
