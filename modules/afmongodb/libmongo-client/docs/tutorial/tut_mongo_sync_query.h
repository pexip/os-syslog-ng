/** @page tut_mongo_sync_query Querying documents
 *
 * We can connect, insert, and we still vaguely remember how to build
 * BSON objects: how about we go out and query the database this time?
 *
 * @dontinclude tut_mongo_sync.c
 * @skip tut_sync_insert
 * @skip }
 * @skip void
 * @until {
 *
 * First, we define a couple of variables: a connection, a packet, a
 * cursor, a BSON object and a counter:
 *
 * @until gint i
 *
 * We'll use the packet as an intermediate step between querying and
 * making a cursor. We'll see why later. The query will be used to
 * limit the documents queried, and the counter is just for pretty
 * printing.
 *
 * Then we do our routine connect:
 * @until }
 *
 * And then build a BSON object, an empty one, because an empty query
 * means we're interested in all of the documents!
 * @until bson_finish
 *
 * Now we have a connection, and we have a query, lets tell MongoDB
 * what we want:
 *
 * @until bson_free
 *
 * The first two parameters are obvious. The third is a set of flags -
 * but we don't use any right now. Then comes the number of documents
 * to skip, and the number of documents to return, followed by a
 * query, and an optional field selector, which we just left empty
 * (meaning we want all fields returned).
 *
 * There's more than one way to figure out the data returned by a
 * query: we can either use the returned packet as-is, and extract
 * data from it using the low-level mongo_wire family of functions. Or
 * we can make a cursor out of this packet, and iterate over the
 * elements:
 *
 * @until }
 *
 * @until }
 *
 * The first thing we do inside of the loop is to get the data from
 * the cursor - or bail out with an error if we can't.
 *
 * @until printf
 *
 * Then we proceed to make a BSON cursor, and print all the keys that
 * belong to the document.
 *
 * Once that's done, we free the resources we used, and continue along
 * the loop, until our cursor signals the end of the query.
 *
 * @until printf
 *
 * @until }
 *
 * Then we clean up and go home:
 * @until }
 */
