#define __STRICT_ANSI__ 1

#include <bson.h>
#include <json.h>

#include <stdio.h>
#include <unistd.h>
#include <glib.h>

static bson *json_to_bson (struct json_object *json);

static void
json_key_to_bson_key (bson *b, void *val,
		      const gchar *key)
{
  switch (json_object_get_type (val))
    {
    case json_type_boolean:
      bson_append_boolean (b, key, json_object_get_boolean (val));
      break;
    case json_type_double:
      bson_append_double (b, key, json_object_get_double (val));
      break;
    case json_type_int:
      bson_append_int32 (b, key, json_object_get_int (val));
      break;
    case json_type_string:
      bson_append_string (b, key, json_object_get_string (val), -1);
      break;
    case json_type_object:
      {
	bson *sub;

	sub = json_to_bson (val);
	bson_append_document (b, key, sub);
	bson_free (sub);
	break;
      }
    case json_type_array:
      {
	gint pos;
	bson *sub;

	sub = bson_new ();

	for (pos = 0; pos < json_object_array_length (val); pos++)
	  {
	    gchar *nk = g_strdup_printf ("%d", pos);

	    json_key_to_bson_key (sub, json_object_array_get_idx (val, pos),
				  nk);
	    g_free (nk);
	  }
	bson_finish (sub);

	bson_append_array (b, key, sub);
	bson_free (sub);
	break;
      }
    default:
      break;
    }
}

static void
json_to_bson_foreach (bson *b, struct json_object *json)
{
  json_object_object_foreach (json, key, val)
    {
      json_key_to_bson_key (b, val, key);
    }
}

static bson *
json_to_bson (struct json_object *json)
{
  bson *b;

  b = bson_new ();
  json_to_bson_foreach (b, json);
  bson_finish (b);

  return b;
}

int
main (int argc, char **argv)
{
  GIOChannel *input;
  GString *json_str;
  GError *error = NULL;
  struct json_tokener *tokener;

  input = g_io_channel_unix_new (0);

  json_str = g_string_new (NULL);
  tokener = json_tokener_new ();

  while (g_io_channel_read_line_string (input, json_str,
					NULL, &error) == G_IO_STATUS_NORMAL)
    {
      struct json_object *json;
      bson *bson;

      json_tokener_reset (tokener);

      json = json_tokener_parse_ex (tokener, json_str->str, json_str->len);
      if (!json)
	{
	  fprintf (stderr, "Error parsing json: %s\n", json_str->str);
	  break;
	}

      if (json_object_get_type (json) != json_type_object)
	{
	  fprintf (stderr,
		   "Error: json's top-level object is not object: %s\n",
		   json_str->str);
	  json_object_put (json);
	  break;
	}

      bson = json_to_bson (json);
      json_object_put (json);

      write (1, bson_data (bson), bson_size (bson));

      bson_free (bson);
    }

  return 0;
}
