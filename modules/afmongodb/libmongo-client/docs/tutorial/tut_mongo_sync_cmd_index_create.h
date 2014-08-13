/** @page tut_mongo_sync_cmd_index_create Creating indexes
 *
 * This example will show how to properly create indexes, how to
 * verify its success, and will also give hints on how to prepare the
 * BSON used to create the index.
 *
 * @dontinclude tut_mongo_sync_cmd_index_create.c
 * @until stdio.h
 *
 * We will be creating and verifying multiple indexes, so lets create
 * a function that takes a connection, a prepared index, and does the
 * create and verify magic.
 *
 * @line static void
 * @until }
 * @until }
 *
 * This will create the index, and if it succeeds, write that to
 * stdout. If it fails, it will try to query the last error, and print
 * that to stderr.
 *
 * All we have to do past this point, is to build a few index
 * specifications in BSON, and see what happens:
 *
 * @line int
 * @until bson
 *
 * @line invalid
 * @until bson_finish
 *
 * The first index spec we create will have a single index field, @a
 * name, where we set the value to an empty string. However - as we
 * will soon see - this is not a valid specification, as MongoDB does
 * not accept string-typed fields in the index spec.
 *
 * @line index
 * @until bson_finish
 *
 * Armed with the knowledge that strings are not going to work, we
 * turn to our trusty old integers. Integers (32-bit integers at that,
 * there really is no need to use a 64-bit value here) are the best
 * fit for the type of an index field, because one can tell MongoDB
 * the sort order (with negative or positive numbers) with them easily.
 *
 * @line conn =
 * @until }
 *
 * We now have two index specs in BSON, and an established connection,
 * lets see what happens!
 *
 * @line create_and_verify
 * @until conn, index
 *
 * The first will - as explained above - fail, the second will
 * succeed.
 *
 * And that is all it takes to create simple indexes! We now free up
 * our BSON objects and disconnect, and the tutorial program is all
 * done and finished.
 *
 * @line bson_free
 * @until disconnect
 *
 * @line return
 * @until }
 */
