#include <mongo.h>

#include <string.h>
#include <stdio.h>

int
main (void)
{
  bson *b_new, *b_builder, *b_builder_full;
  bson *page1, *page2, *pages;

  page1 = bson_new ();
  bson_append_string (page1, "title", "BSON tutorial", -1);
  bson_append_string (page1, "content", "...", -1);
  bson_append_int32 (page1, "importance", 1);
  bson_finish (page1);

  page2 = bson_new ();
  bson_append_string (page2, "title", "Some other thing", -1);
  bson_append_string (page2, "content", "...", -1);
  bson_append_int32 (page2, "importance", 0);
  bson_finish (page2);

  pages = bson_new ();
  bson_append_document (pages, "1", page1);
  bson_append_document (pages, "2", page2);
  bson_finish (pages);

  b_new = bson_new ();
  bson_append_string (b_new, "author", "Gergely Nagy", -1);
  bson_append_array (b_new, "pages", pages);
  bson_append_boolean (b_new, "inline", TRUE);
  bson_finish (b_new);

  b_builder = bson_build (BSON_TYPE_STRING, "author", "Gergely Nagy", -1,
                          BSON_TYPE_ARRAY, "pages", pages,
                          BSON_TYPE_BOOLEAN, "inline", TRUE,
                          BSON_TYPE_NONE);
  bson_finish (b_builder);

  b_builder_full = bson_build_full
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
  bson_finish (b_builder_full);

  if (bson_size (b_new) != bson_size (b_builder) ||
      bson_size (b_new) != bson_size (b_builder_full))
    {
      fprintf (stderr, "There's something fishy: the three BSON objects have different sizes");
      return 1;
    }

  if (memcmp (bson_data (b_new), bson_data (b_builder), bson_size (b_new)) != 0 ||
      memcmp (bson_data (b_new), bson_data (b_builder_full), bson_size (b_new)) != 0)
    {
      fprintf (stderr, "The BSON objects do not match. Something smells.");
      return 1;
    }

  bson_free (b_builder_full);
  bson_free (b_builder);
  bson_free (b_new);
  bson_free (pages);
  bson_free (page2);
  bson_free (page1);

  return 0;
}
