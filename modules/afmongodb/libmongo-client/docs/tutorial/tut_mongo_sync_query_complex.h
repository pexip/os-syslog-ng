/** @page tut_mongo_sync_query_complex Querying documents, part two
 *
 * We learned how to make simple queries in the previous section,
 * we'll be brave and do something much more advanced this time: we'll
 * limit the query to documents that have their @c "yes?" field set to
 * @a FALSE, and sort the results by the @c "n" field, in ascending
 * order.
 *
 * @dontinclude tut_mongo_sync.c
 * @skip tut_sync_query_simple
 * @skip }
 * @skip void
 * @until {
 *
 * @until gint i
 *
 * @until }
 *
 * After our routine connect, we build the query and select BSON
 * objects:
 *
 * @until bson_finish (select)
 *
 * Then we launch the query:
 * @until bson_free (select)
 *
 * And make a cursor, just like last time:
 * @until }
 *
 * And that's pretty much the bulk of what we wanted to do: we just
 * constructed our query and select BSON objects appropriately, and
 * mongo_sync_cmd_query() does the rest.
 *
 * But just to make sure our results are sane, we iterate over the
 * returned documents, and print the fields we're interested in:
 *
 * @until i++
 * @until }
 *
 * And when that is done, all that is left, is to clean up after
 * ourselves:
 * @until }
 */
