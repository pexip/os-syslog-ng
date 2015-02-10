#include "test.h"
#include "mongo.h"

#define FILE_SIZE 1024 * 1024 + 12345

static guint8 noname_oid[12];
static guint8 named_oid[12];
static guint8 binsub_oid[12];

void
test_func_sync_gridfs_put (void)
{
  mongo_sync_connection *conn;
  mongo_sync_gridfs *gfs;
  mongo_sync_gridfs_chunked_file *gfile;
  bson *meta;
  guint8 *data, *oid;
  gchar *oid_s;

  conn = mongo_sync_connect (config.primary_host, config.primary_port, FALSE);
  gfs = mongo_sync_gridfs_new (conn, config.gfs_prefix);
  oid = mongo_util_oid_new (1);
  meta = bson_build (BSON_TYPE_STRING, "filename", "libmongo-test", -1,
                     BSON_TYPE_OID, "_id", oid,
                     BSON_TYPE_NONE);
  g_free (oid);
  bson_finish (meta);

  data = g_malloc (FILE_SIZE);
  memset (data, 'x', FILE_SIZE);

  gfile = mongo_sync_gridfs_chunked_file_new_from_buffer (gfs, meta,
                                                          data, FILE_SIZE);
  ok (gfile != NULL,
      "GridFS file upload (with metadata) works!");
  memcpy (named_oid, mongo_sync_gridfs_file_get_id (gfile), 12);
  oid_s = mongo_util_oid_as_string (named_oid);
  note ("Named file ID : %s\n", oid_s);
  g_free (oid_s);
  mongo_sync_gridfs_chunked_file_free (gfile);

  gfile = mongo_sync_gridfs_chunked_file_new_from_buffer (gfs, NULL,
                                                          data, FILE_SIZE);
  ok (gfile != NULL,
      "GridFS file upload (w/o metadata) works!");
  memcpy (noname_oid, mongo_sync_gridfs_file_get_id (gfile), 12);
  oid_s = mongo_util_oid_as_string (noname_oid);
  note ("Noname file ID: %s\n", oid_s);
  g_free (oid_s);
  mongo_sync_gridfs_chunked_file_free (gfile);

  g_free (data);
  bson_free (meta);
  mongo_sync_gridfs_free (gfs, TRUE);
}

void
test_func_sync_gridfs_put_invalid (void)
{
  mongo_sync_connection *conn;
  bson *meta;
  gchar *ns;

  conn = mongo_sync_connect (config.primary_host, config.primary_port, FALSE);
  ns = g_strconcat (config.gfs_prefix, ".files", NULL);

  /* Insert metadata without any of the required fields but ID. */
  meta = bson_build (BSON_TYPE_STRING, "my-id", "id-only", -1,
                     BSON_TYPE_NONE);
  bson_finish (meta);

  mongo_sync_cmd_insert (conn, ns, meta, NULL);
  bson_free (meta);

  /* Insert metadata with an ID that's not an ObjectID. */
  meta = bson_build (BSON_TYPE_STRING, "_id", "I'm a teapot", -1,
                     BSON_TYPE_STRING, "my-id", "string-id", -1,
                     BSON_TYPE_NONE);
  bson_finish (meta);

  mongo_sync_cmd_insert (conn, ns, meta, NULL);
  bson_free (meta);

  /* Insert metadata with invalid length type. */
  meta = bson_build (BSON_TYPE_DOUBLE, "length", 1.0,
                     BSON_TYPE_STRING, "my-id", "invalid-length", -1,
                     BSON_TYPE_NONE);
  bson_finish (meta);

  mongo_sync_cmd_insert (conn, ns, meta, NULL);
  bson_free (meta);

  /* Insert metadata with invalid chunkSize type. */
  meta = bson_build (BSON_TYPE_INT32, "length", 10,
                     BSON_TYPE_DOUBLE, "chunkSize", 12.5,
                     BSON_TYPE_STRING, "my-id", "invalid-chunkSize", -1,
                     BSON_TYPE_NONE);
  bson_finish (meta);

  mongo_sync_cmd_insert (conn, ns, meta, NULL);
  bson_free (meta);

  /* Insert metadata with invalid uploadDate type. */
  meta = bson_build (BSON_TYPE_INT32, "length", 10,
                     BSON_TYPE_INT32, "chunkSize", 12,
                     BSON_TYPE_STRING, "my-id", "invalid-date", -1,
                     BSON_TYPE_INT32, "uploadDate", 1234,
                     BSON_TYPE_NONE);
  bson_finish (meta);

  mongo_sync_cmd_insert (conn, ns, meta, NULL);
  bson_free (meta);

  /* Insert metadata with invalid md5 type. */
  meta = bson_build (BSON_TYPE_INT32, "length", 32,
                     BSON_TYPE_INT32, "chunkSize", 12,
                     BSON_TYPE_UTC_DATETIME, "uploadDate", (gint64)1234,
                     BSON_TYPE_INT32, "md5", 0,
                     BSON_TYPE_STRING, "my-id", "invalid-md5", -1,
                     BSON_TYPE_NONE);
  bson_finish (meta);

  mongo_sync_cmd_insert (conn, ns, meta, NULL);
  bson_free (meta);

  /* Insert a valid metadata, without chunks. */
  meta = bson_build (BSON_TYPE_INT32, "length", 32,
                     BSON_TYPE_INT32, "chunkSize", 12,
                     BSON_TYPE_UTC_DATETIME, "uploadDate", (gint64)1234,
                     BSON_TYPE_STRING, "md5", "deadbeef", -1,
                     BSON_TYPE_STRING, "my-id", "no-chunks", -1,
                     BSON_TYPE_NONE);
  bson_finish (meta);

  mongo_sync_cmd_insert (conn, ns, meta, NULL);
  bson_free (meta);

  g_free (ns);
  mongo_sync_disconnect (conn);
}

void
validate_file (mongo_sync_gridfs *gfs, const bson *query, guint8 *oid,
               gboolean validate_md5)
{
  mongo_sync_gridfs_chunked_file *f;
  mongo_sync_cursor *cursor;
  gint64 n = 0, tsize = 0;
  const bson *meta;
  gchar *oid_s;

  f = mongo_sync_gridfs_chunked_find (gfs, query);

  ok (f != NULL,
      "File not found");
  ok (memcmp (mongo_sync_gridfs_file_get_id (f), oid, 12) == 0,
      "File _id matches");
  cmp_ok (mongo_sync_gridfs_file_get_length (f), "==", FILE_SIZE,
          "File length matches");
  cmp_ok (mongo_sync_gridfs_file_get_chunk_size (f), "==",
          mongo_sync_gridfs_get_chunk_size (gfs),
          "File chunk size matches");

  oid_s = mongo_util_oid_as_string (mongo_sync_gridfs_file_get_id (f));
  note ("File info:\n\tid = %s; length = %" G_GINT64_FORMAT "; "
        "chunk_size = %d; date = %" G_GINT64_FORMAT "; "
        "md5 = %s; n = %" G_GINT64_FORMAT "\n",

        oid_s,
        mongo_sync_gridfs_file_get_length (f),
        mongo_sync_gridfs_file_get_chunk_size (f),
        mongo_sync_gridfs_file_get_date (f),
        mongo_sync_gridfs_file_get_md5 (f),
        mongo_sync_gridfs_file_get_chunks (f));
  g_free (oid_s);
  meta = mongo_sync_gridfs_file_get_metadata (f);
  ok (meta != NULL,
      "mongo_sync_gridfs_file_get_metadata() works");

  cursor = mongo_sync_gridfs_chunked_file_cursor_new (f, 0, 0);
  while (mongo_sync_cursor_next (cursor))
    {
      gint32 size;
      guint8 *data;

      data = mongo_sync_gridfs_chunked_file_cursor_get_chunk (cursor, &size);
      g_free (data);

      tsize += size;
      n++;
    }
  mongo_sync_cursor_free (cursor);

  if (validate_md5)
    cmp_ok (mongo_sync_gridfs_file_get_length (f), "==", tsize,
            "File size matches the sum of its chunks");
  cmp_ok (mongo_sync_gridfs_file_get_chunks (f), "==", n,
          "Number of chunks matches the expected number");

  mongo_sync_gridfs_chunked_file_free (f);
}

void
test_func_sync_gridfs_get (void)
{
  mongo_sync_connection *conn;
  mongo_sync_gridfs *gfs;
  bson *query;

  conn = mongo_sync_connect (config.primary_host, config.primary_port, TRUE);
  gfs = mongo_sync_gridfs_new (conn, config.gfs_prefix);

  query = bson_build (BSON_TYPE_STRING, "filename", "libmongo-test", -1,
                      BSON_TYPE_NONE);
  bson_finish (query);
  validate_file (gfs, query, named_oid, TRUE);
  bson_free (query);

  query = bson_build (BSON_TYPE_OID, "_id", noname_oid,
                      BSON_TYPE_NONE);
  bson_finish (query);
  validate_file (gfs, query, noname_oid, TRUE);
  bson_free (query);

  mongo_sync_gridfs_free (gfs, TRUE);
}

void
test_get_invalid (mongo_sync_gridfs *gfs, gchar *name, gchar *msg)
{
  bson *query;

  query = bson_build (BSON_TYPE_STRING, "my-id", name, -1,
                      BSON_TYPE_NONE);
  bson_finish (query);
  ok (mongo_sync_gridfs_chunked_find (gfs, query) == NULL, msg);
  bson_free (query);
}

void
test_func_sync_gridfs_get_invalid (void)
{
  mongo_sync_connection *conn;
  mongo_sync_gridfs *gfs;
  mongo_sync_cursor *cursor;
  bson *query;
  gchar *ns;

  conn = mongo_sync_connect (config.primary_host, config.primary_port, TRUE);
  gfs = mongo_sync_gridfs_new (conn, config.gfs_prefix);

  test_get_invalid (gfs, "unknown",
                    "mongo_sync_gridfs_chunked_find() should fail when no file "
                    "is found");
  test_get_invalid (gfs, "id-only",
                    "mongo_sync_gridfs_chunked__find() should fail if the metadata "
                    "is incomplete");
  test_get_invalid (gfs, "string-id",
                    "mongo_sync_gridfs_chunked__find() should fail if the _id is "
                    "not an ObjectID");
  test_get_invalid (gfs, "invalid-length",
                    "mongo_sync_gridfs_chunked__find() should fail if length is "
                    "of inappropriate type");
  test_get_invalid (gfs, "invalid-chunkSize",
                    "mongo_sync_gridfs_chunked__find() should fail if chunkSize is "
                    "of inappropriate type");
  test_get_invalid (gfs, "invalid-date",
                    "mongo_sync_gridfs_chunked__find() should fail if uploadDate is "
                    "of inappropriate type");
  test_get_invalid (gfs, "invalid-md5",
                    "mongo_sync_gridfs_chunked__find() should fail if md5 is of "
                    "inappropriate type");

  ns = g_strconcat (config.gfs_prefix, ".files", NULL);
  query = bson_build (BSON_TYPE_STRING, "my-id", "id-only", -1,
                      BSON_TYPE_NONE);
  bson_finish (query);

  cursor = mongo_sync_cursor_new (conn, ns,
                                  mongo_sync_cmd_query (conn, ns, 0, 0, 0,
                                                        query, NULL));
  bson_free (query);
  mongo_sync_cursor_next (cursor);
  ok (mongo_sync_gridfs_chunked_file_cursor_get_chunk (cursor, NULL) == NULL,
      "mongo_sync_gridfs_chunked_file_cursor_get_chunk() should fail with "
      "invalid data");

  mongo_sync_gridfs_free (gfs, TRUE);
}

void
test_func_sync_gridfs_list (void)
{
  mongo_sync_gridfs *gfs;
  bson *query, *data;
  mongo_sync_cursor *cursor;
  bson_cursor *c;
  const gchar *str;
  gboolean found_named = FALSE, found_noname = FALSE;
  const guint8 *oid;

  gfs = mongo_sync_gridfs_new
    (mongo_sync_connect (config.primary_host, config.primary_port, TRUE),
     config.gfs_prefix);

  /* Test list with an invalid query */
  query = bson_build (BSON_TYPE_STRING, "no-such-field",
                      "You're not seeing this field.", -1,
                      BSON_TYPE_NONE);
  bson_finish (query);

  cursor = mongo_sync_gridfs_list (gfs, query);
  ok (cursor == NULL,
      "mongo_sync_gridfs_list() should fail if there query "
      "does not match anything");
  bson_free (query);

  /* Test list with a query */
  query = bson_build (BSON_TYPE_OID, "_id", named_oid,
                      BSON_TYPE_NONE);
  bson_finish (query);

  cursor = mongo_sync_gridfs_list (gfs, query);
  ok (cursor != NULL,
      "mongo_sync_gridfs_list() correctly finds files by query");

  mongo_sync_cursor_next (cursor);
  data = mongo_sync_cursor_get_data (cursor);
  c = bson_find (data, "filename");
  bson_cursor_get_string (c, &str);
  bson_cursor_free (c);

  is (str, "libmongo-test",
      "The listed file is named correctly");
  bson_free (data);
  mongo_sync_cursor_free (cursor);

  bson_free (query);

  /* Test list without a query */
  cursor = mongo_sync_gridfs_list (gfs, NULL);
  while (mongo_sync_cursor_next (cursor))
    {
      data = mongo_sync_cursor_get_data (cursor);

      c = bson_find (data, "_id");
      bson_cursor_get_oid (c, (const guint8 **)&oid);
      bson_cursor_free (c);

      if (memcmp (oid, named_oid, 12) == 0)
        found_named = TRUE;
      if (memcmp (oid, noname_oid, 12) == 0)
        found_noname = TRUE;

      bson_free (data);
    }
  mongo_sync_cursor_free (cursor);

  ok (found_named == TRUE && found_noname == TRUE,
      "mongo_sync_gridfs_list() finds both uploaded files without a query");

  mongo_sync_gridfs_free (gfs, TRUE);
}

void
test_fync_sync_gridfs_remove (void)
{
  mongo_sync_gridfs *gfs;
  bson *query;

  gfs = mongo_sync_gridfs_new
    (mongo_sync_connect (config.primary_host, config.primary_port, TRUE),
     config.gfs_prefix);

  /* Test with a non-matching query */
  query = bson_build (BSON_TYPE_STRING, "no-such-field",
                      "You're not seeing this field.", -1,
                      BSON_TYPE_NONE);
  bson_finish (query);

  ok (mongo_sync_gridfs_remove (gfs, query) == FALSE,
      "mongo_sync_gridfs_remove() should fail if there's nothing to delete.");
  bson_free (query);

  /* Test with a non-string id */
  query = bson_build (BSON_TYPE_STRING, "my-id", "string-id", -1,
                      BSON_TYPE_NONE);
  bson_finish (query);

  ok (mongo_sync_gridfs_remove (gfs, query) == FALSE,
      "mongo_sync_gridfs_remove() should fail if the file id is not "
      "an ObjectId");
  bson_free (query);

  /* Test with a working query */
  query = bson_build (BSON_TYPE_OID, "_id", named_oid,
                      BSON_TYPE_NONE);
  bson_finish (query);

  ok (mongo_sync_gridfs_remove (gfs, query) == TRUE,
      "mongo_sync_gridfs_remove() works");
  bson_finish (query);

  mongo_sync_gridfs_free (gfs, TRUE);
}

void
test_func_sync_gridfs_put_binary_subtype (void)
{
  mongo_sync_connection *conn;
  mongo_sync_gridfs *gfs;
  mongo_sync_gridfs_chunked_file *gfile;
  bson *meta, *query, *update;
  guint8 *data;
  gchar *chunk_ns;
  guint32 size = GINT32_TO_LE(FILE_SIZE);

  conn = mongo_sync_connect (config.primary_host, config.primary_port, FALSE);
  gfs = mongo_sync_gridfs_new (conn, config.gfs_prefix);
  meta = bson_build (BSON_TYPE_STRING, "filename", "binsub-libmongo-test", -1,
                     BSON_TYPE_NONE);
  bson_finish (meta);

  data = g_malloc (FILE_SIZE + 4);
  memcpy (data, &size, 4);
  memset (data + 4, 'x', FILE_SIZE);

  gfile = mongo_sync_gridfs_chunked_file_new_from_buffer (gfs, meta,
                                                          data + 4, FILE_SIZE);
  memcpy (binsub_oid, mongo_sync_gridfs_file_get_id (gfile), 12);

  query = bson_build (BSON_TYPE_OID, "files_id",
                      mongo_sync_gridfs_file_get_id (gfile),
                      BSON_TYPE_NONE);
  bson_finish (query);

  mongo_sync_gridfs_chunked_file_free (gfile);
  bson_free (meta);

  update = bson_build_full (BSON_TYPE_DOCUMENT, "$set", TRUE,
                            bson_build (BSON_TYPE_BINARY, "data",
                                        BSON_BINARY_SUBTYPE_BINARY,
                                        data, FILE_SIZE + 4,
                                        BSON_TYPE_NONE),
                            BSON_TYPE_NONE);
  bson_finish (update);
  g_free (data);

  chunk_ns = g_strconcat (config.gfs_prefix, ".chunks", NULL);
  mongo_sync_cmd_update (conn, chunk_ns, MONGO_WIRE_FLAG_UPDATE_UPSERT,
                         query, update);

  bson_free (query);
  bson_free (update);
  g_free (chunk_ns);

  mongo_sync_gridfs_free (gfs, TRUE);
}

void
test_func_sync_gridfs_get_binary_subtype (void)
{
  mongo_sync_connection *conn;
  mongo_sync_gridfs *gfs;
  bson *query;

  conn = mongo_sync_connect (config.primary_host, config.primary_port, TRUE);
  gfs = mongo_sync_gridfs_new (conn, config.gfs_prefix);

  query = bson_build (BSON_TYPE_STRING, "filename", "binsub-libmongo-test", -1,
                      BSON_TYPE_NONE);
  bson_finish (query);
  validate_file (gfs, query, binsub_oid, FALSE);
  bson_free (query);

  mongo_sync_gridfs_free (gfs, TRUE);
}

void
test_func_sync_gridfs_chunk (void)
{
  mongo_util_oid_init (0);

  test_func_sync_gridfs_put ();
  test_func_sync_gridfs_get ();
  test_func_sync_gridfs_list ();

  sleep (2);

  test_func_sync_gridfs_put_binary_subtype ();
  test_func_sync_gridfs_get_binary_subtype ();

  test_func_sync_gridfs_put_invalid ();
  test_func_sync_gridfs_get_invalid ();

  test_fync_sync_gridfs_remove ();
}

RUN_NET_TEST (37, func_sync_gridfs_chunk);
