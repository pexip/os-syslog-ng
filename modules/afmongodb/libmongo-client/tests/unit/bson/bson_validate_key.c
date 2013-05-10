#include "tap.h"
#include "test.h"

#include <errno.h>
#include <bson.h>
#include <string.h>

void
test_bson_validate_key (void)
{
  gboolean valid;

  valid = bson_validate_key (NULL, FALSE, FALSE);
  ok (valid == FALSE && errno == EINVAL,
      "bson_validate_key() sets errno when the key is NULL");

  valid = bson_validate_key ("$foo.bar", FALSE, FALSE);
  ok (valid == TRUE,
      "bson_validate_key() returns success if both checks are off");

  valid = bson_validate_key ("$foo.bar", FALSE, TRUE);
  ok (valid == FALSE,
      "bson_validate_key() returns failiure if the key starts with a $");
  valid = bson_validate_key ("foo.bar$", FALSE, TRUE);
  ok (valid == TRUE,
      "bson_validate_key() returns success if the key does not start with a $");

  valid = bson_validate_key ("foo.bar", TRUE, TRUE);
  ok (valid == FALSE,
      "bson_validate_key() returns failiure if the key contains a dot");
  valid = bson_validate_key ("foobar", TRUE, TRUE);
  ok (valid == TRUE,
      "bson_validate_key() returns success if the key does not contain a dot");
}

RUN_TEST (6, bson_validate_key)
