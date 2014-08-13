/* mongo-dump.c - MongoDB database dumper; example application.
 * Copyright 2011, 2012 Gergely Nagy <algernon@balabit.hu>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <mongo.h>

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

typedef struct
{
  gchar *addr;
  gint port;
  gchar *db;
  gchar *coll;
  gchar *output;
  gchar *ns;
  gboolean verbose;
  gboolean slaveok;
  gboolean master_sync;
} config_t;

#define VLOG(...) { if (config->verbose) fprintf (stderr, __VA_ARGS__); }

void
mongo_dump (config_t *config)
{
  mongo_sync_connection *conn;
  mongo_sync_cursor *cursor;
  bson *b;
  int fd;

  glong cnt, pos = 0;

  gchar *error = NULL;
  int e;

  if (config->port == MONGO_CONN_LOCAL)
    {
      VLOG ("Connecting to %s/%s.%s...\n", config->addr, config->db,
            config->coll);
    }
  else
    {
      VLOG ("Connecting to %s:%d/%s.%s...\n", config->addr, config->port,
            config->db, config->coll);
    }
  conn = mongo_sync_connect (config->addr, config->port, config->slaveok);

  if (!conn)
    {
      e = errno;

      mongo_sync_cmd_get_last_error (conn, config->db, &error);
      fprintf (stderr, "Error connecting to %s:%d: %s\n", config->addr,
               config->port, (error) ? error : strerror (e));
      g_free (error);
      exit (1);
    }

  if (config->master_sync)
    {
      VLOG ("Syncing to master...\n");
      conn = mongo_sync_reconnect (conn, TRUE);
      if (!conn)
        {
          e = errno;

          mongo_sync_cmd_get_last_error (conn, config->db, &error);
          fprintf (stderr, "Error reconnecting to the master of %s:%d: %s\n",
                   config->addr, config->port, (error) ? error : strerror (e));
          exit (1);
        }
    }

  VLOG ("Counting documents...\n");
  cnt = mongo_sync_cmd_count (conn, config->db, config->coll, NULL);
  if (cnt < 0)
    {
      e = errno;

      mongo_sync_cmd_get_last_error (conn, config->db, &error);
      fprintf (stderr, "Error counting documents in %s.%s: %s\n",
               config->db, config->coll, (error) ? error : strerror (e));
      mongo_sync_disconnect (conn);
      exit (1);
    }

  VLOG ("Opening output file '%s'...\n", config->output);
  if (strcmp (config->output, "-") == 0)
    fd = 1;
  else
    {
      fd = open (config->output, O_RDWR | O_CREAT | O_TRUNC, 0600);
      if (fd == -1)
        {
          fprintf (stderr, "Error opening output file '%s': %s\n",
                   config->output, strerror (errno));
          mongo_sync_disconnect (conn);
          exit (1);
        }
    }

  VLOG ("Launching initial query...\n");
  b = bson_new ();
  bson_finish (b);
  cursor = mongo_sync_cursor_new (conn, config->ns,
                                  mongo_sync_cmd_query (conn, config->ns,
                                                        MONGO_WIRE_FLAG_QUERY_NO_CURSOR_TIMEOUT,
                                                        0, 10, b, NULL));
  bson_free (b);

  while ((pos < cnt) && mongo_sync_cursor_next (cursor))
    {
      bson *b = mongo_sync_cursor_get_data (cursor);
      pos++;

      if (!b)
        {
          e = errno;

          mongo_sync_cmd_get_last_error (conn, config->db, &error);
          fprintf (stderr, "Error advancing the cursor: %s\n",
                   (error) ? error : strerror (e));
          mongo_sync_disconnect (conn);
          exit (1);
        }

      if (pos % 10 == 0)
        VLOG ("\rDumping... %03.2f%%", (pos * 1.0) / (cnt * 1.0) * 100);

      if (write (fd, bson_data (b), bson_size (b)) != bson_size (b))
        {
          perror ("write()");
          exit (1);
        }
      bson_free (b);
    }
  VLOG ("\rDumping... %03.2f%%\n", (double)((pos / cnt) * 100));

  mongo_sync_cursor_free (cursor);

  close (fd);
  mongo_sync_disconnect (conn);
}

int
main (int argc, char *argv[])
{
  GError *error = NULL;
  GOptionContext *context;
  config_t config = {
    NULL, 27017, NULL, NULL, NULL, NULL, FALSE, FALSE, FALSE
  };

  GOptionEntry entries[] =
    {
      { "addr", 'a', 0, G_OPTION_ARG_STRING, &config.addr,
        "Address to connect to", "ADDRESS" },
      { "port", 'p', 0, G_OPTION_ARG_INT, &config.port, "Port", "PORT" },
      { "db", 'd', 0, G_OPTION_ARG_STRING, &config.db, "Database", "DB" },
      { "collection", 'c', 0, G_OPTION_ARG_STRING, &config.coll, "Collection",
        "COLL" },
      { "verbose", 'v', 0, G_OPTION_ARG_NONE, &config.verbose,
        "Be verbose", NULL },
      { "output", 'o', 0, G_OPTION_ARG_STRING, &config.output,
        "Output", "FILENAME" },
      { "slave-ok", 's', 0, G_OPTION_ARG_NONE, &config.slaveok,
        "Connecting to slaves is ok", NULL },
      { "master-sync", 'm', 0, G_OPTION_ARG_NONE, &config.master_sync,
        "Reconnect to the replica master", NULL },
      { NULL, 0, 0, 0, NULL, NULL, NULL }
    };

  context = g_option_context_new ("- dump a complete mongo collection");
  g_option_context_add_main_entries (context, entries, "mongo-dump");
  if (!g_option_context_parse (context, &argc, &argv, &error))
    {
      g_print ("option parsing failed: %s\n", error->message);
      exit (1);
    }

  if (!((config.addr && config.port)) || !config.db ||
      !config.coll || !config.output)
    {
      gchar **nargv;
      argc = 2;

      nargv = g_new (gchar *, 3);
      nargv[0] = argv[0];
      nargv[1] = "--help";
      nargv[2] = NULL;

      g_option_context_parse (context, &argc, (gchar ***)&nargv, &error);

      exit (1);
    }

  config.ns = g_strdup_printf ("%s.%s", config.db, config.coll);
  mongo_dump (&config);

  g_free (config.ns);
  g_option_context_free (context);

  return 0;
}
