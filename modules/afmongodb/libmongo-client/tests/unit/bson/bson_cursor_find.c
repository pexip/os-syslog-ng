#include "test.h"
#include "mongo.h"

#include <string.h>

void
test_bson_cursor_find (void)
{
  bson *b;
  bson_cursor *c;

  b = test_bson_generate_full ();
  c = bson_find (b, "TRUE");

  ok (bson_cursor_find (c, NULL) == FALSE,
      "bson_cursor_find() should fail with a NULL key");
  ok (bson_cursor_find (NULL, "int32") == FALSE,
      "bson_cursor_find() should fail with a NULL cursor");

  ok (bson_cursor_find (c, "sex") == TRUE,
      "bson_cursor_find() works");

  ok (bson_cursor_find (c, "str") == TRUE,
      "bson_cursor_find() should wrap over if neccessary");

  ok (bson_cursor_find (c, "-invalid-key-") == FALSE,
      "bson_cursor_find() should fail when the key is not found");

  ok (bson_cursor_find (c, "int64") == TRUE,
      "bson_cursor_find() works, even after a previous failure");

  bson_cursor_free (c);
  bson_free (b);
}

RUN_TEST (6, bson_cursor_find);
