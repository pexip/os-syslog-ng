/** @page tut_hl_client A full-blown application
 *
 * As the next step of our tutorial, we will write a full blown
 * application. While it does not solve any real-life problems, and
 * what it does is entirely pointless, it nevertheless is a good
 * example to showcase certain patterns one is likely to run into
 * while developing with libmongo-client.
 *
 * @dontinclude tut_hl_client.c
 * @until string.h
 *
 * Our first task is to add a handful of items to our test
 * collection. We'll have two static keys, and one that's different
 * for each key.
 * @until gint i
 *
 * First, we'll build a base BSON object:
 * @until bson_finish
 *
 * Then, we create a copy, append a counter element to the object,
 * insert it, and do this a thousand times over.
 * @until bson_free
 * @until }
 *
 * This was pretty simple, wasn't it? And we even have error handling!
 * Lets finish this function up, and move on.
 *
 * @until }
 *
 * Next up comes the interesting part: doing queries. We will use the
 * @ref mongo_sync_cursor "cursor API" to iterate over all our
 * results, hiding the gory details of database access behind its
 * convenience layer.
 *
 * @until {
 *
 * We'll need a couple of things: a cursor, a query, and a string to
 * store error messages in, if any.
 *
 * @until error
 *
 * Before we can query the database, we must build a query object:
 * @until bson_finish
 *
 * Once that is done, we create a cursor, cleverly embedding the
 * mongo_sync_cmd_query() call into the constructor:
 * @until bson_free
 *
 * Again, we properly handle errors. It is very important to not just
 * blindly assume things will work. While the library tries its best
 * to handle invalid data gracefully, it's easy to get lost between
 * the layers when one forgets to handle error cases at the
 * appropriate level.
 *
 * But I digress, lets get back to our program!
 *
 * We have a nice little query cursor, it's time to loop through the
 * database, extract the counter from the current BSON object, and
 * move on:
 * @until }
 *
 * At this point, we have the current document in the @a b variable,
 * handled the error case, and as such, we're ready to dig deep into
 * the BSON object!
 * @until printf
 *
 * And once we're done working with the BSON object, we free the
 * cursor, and the object, and continue the loop.
 * @until }
 *
 * And in the end, we emit a newline, and free the cursor to wrap up
 * our query routine.
 * @until }
 *
 * All that is left now, is the glue that holds this together, and
 * connects to MongoDB:
 * @until }
 * @until }
 *
 * I believe that does not need any further explanation.
 *
 * As an exercise, one can add another feature: dropping the temporary
 * collection on error. Or perhaps, count the number of documents
 * returned, and see if and how the count changes between subsequent
 * runs of the test program.
 */
