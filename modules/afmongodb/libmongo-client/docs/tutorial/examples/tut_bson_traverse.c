#include <mongo.h>

#include <string.h>
#include <stdio.h>

bson *
tut_bson (void)
{
  bson *b;

  b = bson_build_full
    (BSON_TYPE_STRING, "author", FALSE, "Gergely Nagy", -1,
     BSON_TYPE_ARRAY, "pages", TRUE,
       bson_build_full (BSON_TYPE_DOCUMENT, "1", TRUE,
			bson_build (BSON_TYPE_STRING, "title", "BSON tutorial", -1,
				    BSON_TYPE_STRING, "content", "...", -1,
				    BSON_TYPE_INT32, "importance", 1,
				    BSON_TYPE_NONE),
			BSON_TYPE_DOCUMENT, "2", TRUE,
			bson_build (BSON_TYPE_STRING, "title", "Some other thing", -1,
				    BSON_TYPE_STRING, "content", "...", -1,
				    BSON_TYPE_INT32, "importance", 0,
				    BSON_TYPE_NONE),
			BSON_TYPE_NONE),
     BSON_TYPE_BOOLEAN, "inline", FALSE, TRUE,
     BSON_TYPE_NONE);
  bson_finish (b);

  return b;
}

int
main (void)
{
  bson *doc;
  bson_cursor *c, *c_arr, *c_page;

  bson *v_doc, *v_array;
  gboolean v_bool;
  const gchar *v_str;

  doc = tut_bson ();

  c = bson_find (doc, "author");
  bson_cursor_get_string (c, &v_str);
  printf ("Author: %s\n", v_str);

  bson_cursor_next (c);
  bson_cursor_next (c);

  bson_cursor_get_boolean (c, &v_bool);
  printf ("inline: %s\n", (v_bool) ? "TRUE" : "FALSE");

  bson_cursor_free (c);

  c = bson_find (doc, "author");
  bson_cursor_get_string (c, &v_str);
  bson_cursor_free (c);
  c = bson_find (doc, "inline");
  bson_cursor_get_boolean (c, &v_bool);
  bson_cursor_free (c);

  printf ("Author: %s; inline: %s; (bson_find)\n",
	  v_str, (v_bool) ? "TRUE" : "FALSE");

  c = bson_find (doc, "author");
  bson_cursor_get_string (c, &v_str);
  while (bson_cursor_next (c))
    {
      if (strcmp (bson_cursor_key (c), "inline") == 0)
	{
	  bson_cursor_get_boolean (c, &v_bool);
	  break;
	}
    }
  bson_cursor_free (c);

  printf ("Author: %s; inline: %s; (bson_cursor_next)\n",
	  v_str, (v_bool) ? "TRUE" : "FALSE");

  c = bson_find (doc, "author");
  bson_cursor_get_string (c, &v_str);
  bson_cursor_find_next (c, "inline");
  bson_cursor_get_boolean (c, &v_bool);
  bson_cursor_free (c);

  printf ("Author: %s; inline: %s; (bson_cursor_find_next)\n",
	  v_str, (v_bool) ? "TRUE" : "FALSE");

  c = bson_find (doc, "pages");
  bson_cursor_find (c, "inline");
  bson_cursor_get_boolean (c, &v_bool);
  bson_cursor_find (c, "author");
  bson_cursor_get_string (c, &v_str);
  bson_cursor_free (c);

  printf ("Author: %s; inline: %s; (bson_cursor_find)\n",
	  v_str, (v_bool) ? "TRUE" : "FALSE");

  c = bson_cursor_new (doc);
  while (bson_cursor_next (c))
    {
      printf ("Key: %s; type=%s\n", bson_cursor_key (c),
	      bson_cursor_type_as_string (c));
    }
  bson_cursor_free (c);

  c = bson_find (doc, "pages");
  bson_cursor_get_array (c, &v_array);
  c_arr = bson_find (v_array, "2");
  bson_cursor_get_document (c_arr, &v_doc);
  c_page = bson_find (v_doc, "title");
  bson_cursor_get_string (c_page, &v_str);

  bson_cursor_free (c_page);
  bson_cursor_free (c_arr);
  bson_cursor_free (c);

  printf ("Title of the 2nd page in the pages array: %s\n", v_str);

  bson_free (doc);
  return 0;
}
