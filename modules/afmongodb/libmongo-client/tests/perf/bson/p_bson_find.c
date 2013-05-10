#include "tap.h"
#include "test.h"

#include <mongo.h>

#define MAX_KEYS 10000

void
test_p_bson_find (void)
{
  bson *b;
  bson_cursor *c;
  gint i;
  gchar **keys;
  gboolean ret = TRUE;

  keys = g_new(gchar *, MAX_KEYS);

  b = bson_new ();
  for (i = 0; i < MAX_KEYS; i++)
    {
      keys[i] = g_strdup_printf ("tmp_key_%d", i);
      bson_append_int32 (b, keys[i], i);
    }
  bson_finish (b);

  for (i = 1; i <= MAX_KEYS; i++)
    {
      c = bson_find (b, keys[i - 1]);
      if (!c)
	ret = FALSE;
      bson_cursor_free (c);
      g_free (keys[i - 1]);
    }

  bson_free (b);
  g_free (keys);

  ok (ret == TRUE,
      "bson_find() performance test ok");
}

RUN_TEST (1, p_bson_find);
