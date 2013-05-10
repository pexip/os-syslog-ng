#include "test.h"
#include "mongo.h"

#include <string.h>

void
test_bson_cursor_find_next (void)
{
  bson *b;
  bson_cursor *c;

  b = test_bson_generate_full ();
  c = bson_find (b, "TRUE");

  ok (bson_cursor_find_next (c, NULL) == FALSE,
      "bson_cursor_find_next() should fail with a NULL key");
  ok (bson_cursor_find_next (NULL, "int32") == FALSE,
      "bson_cursor_find_next() should fail with a NULL cursor");

  ok (bson_cursor_find_next (c, "sex") == TRUE,
      "bson_cursor_find_next() works");

  ok (bson_cursor_find_next (c, "str") == FALSE,
      "bson_cursor_find_next() should fail when the key is not found");

  ok (bson_cursor_find_next (c, "int64") == TRUE,
      "bson_cursor_find_next() works, even after a previous failure");

  bson_cursor_free (c);
  bson_free (b);
}

RUN_TEST (5, bson_cursor_find_next);
