/** @page tut_mongo_sync_insert Inserting documents into MongoDB
 *
 * Now that we know how to connect, it is time to take another step
 * forward, and put something into our database. We already learned
 * how to build BSON objects in @ref tut_bson_build, so lets put that
 * knowledge together, and insert a document!
 *
 * @dontinclude tut_mongo_sync.c
 * @skip tut_sync_connect_replica
 * @skip }
 * @skip void
 * @until {
 *
 * First, we define a couple of variables, a connection, and three documents:
 *
 * @until bson
 *
 * Then we do our routine connect:
 * @until }
 *
 * And then build a BSON object, as we've learned earlier:
 * @until bson_finish
 *
 * Now we have a connection, and we have a document, it's time to get
 * dirty, and insert:
 *
 * @until }
 *
 * One might wonder what that @c NULL is at the end of
 * mongo_sync_cmd_insert()'s argument list: it's the @a sentinel. The
 * value that marks the end of the documents we want to insert. It is
 * needed, because the insert command can take any number of
 * documents, and it will try to insert them in bulk.
 *
 * Lets try that, and build two more documents:
 * @until bson_finish (doc3)
 *
 * Then we insert the two new documents into the same collection, at
 * the same time:
 * @until }
 *
 * And we're done! It's that straightforward. All we have left is
 * cleaning up!
 *
 * @until }
 */
