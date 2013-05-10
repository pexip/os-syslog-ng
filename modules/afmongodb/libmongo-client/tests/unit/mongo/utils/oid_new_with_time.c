#include "tap.h"
#include "test.h"
#include "mongo-utils.h"

#include <string.h>

void
test_mongo_utils_oid_new_with_time (void)
{
  guint8 *oid1, *oid2, *oid3;
  gchar *oid1_s, *oid2_s;

  ok (mongo_util_oid_new_with_time (0, 0) == NULL,
      "mongo_util_oid_new_with_time() should fail before mongo_util_oid_init()");

  mongo_util_oid_init (0);
  ok ((oid1 = mongo_util_oid_new_with_time (0, 1)) != NULL,
      "mongo_util_oid_new_with_time() works");
  cmp_ok (oid1[11], "==", 1,
	  "mongo_util_oid_new_with_time() returns an OID with the currect seq ID");

  oid2 = mongo_util_oid_new_with_time (0, 2);
  oid3 = mongo_util_oid_new_with_time (0, 2);

  ok (memcmp (oid2, oid1, 12) > 0,
      "OIDs with higher sequence ID sort higher");
  ok (memcmp (oid2, oid3, 12) == 0,
      "OIDs with the same sequence ID are equal (within a second)");
  g_free (oid2);
  g_free (oid3);

  oid2 = mongo_util_oid_new_with_time (1, 0);

  oid1_s = mongo_util_oid_as_string (oid1);
  oid2_s = mongo_util_oid_as_string (oid2);

  ok (memcmp (oid2, oid1, 12) > 0,
      "OIDs with the same sequence ID, a few seconds later sort higher; "
      "oid1=%s; oid2=%s", oid1_s, oid2_s);
  g_free (oid2_s);
  g_free (oid1_s);
  g_free (oid2);
  g_free (oid1);
}

RUN_TEST (6, mongo_utils_oid_new_with_time);
