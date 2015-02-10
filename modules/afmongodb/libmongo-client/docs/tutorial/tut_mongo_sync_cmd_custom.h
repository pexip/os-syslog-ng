/** @page tut_mongo_sync_cmd_custom Running custom commands
 *
 * Sometimes it is necessary to run custom commands against a
 * database, commands for which the library does not provide a
 * convenience wrapper for. In this tutorial, we will explore how to
 * run server-side evaluations, using the @a $eval command.
 *
 * @dontinclude tut_mongo_sync_cmd_custom.c
 * @until stdlib.h
 *
 * @until eval
 *
 * First, we connect to the database, and create a BSON object that
 * will hold our command, one that creates a function server side,
 * that takes one argument, and returns the argument plus 4.2. The
 * BSON object will also set up the arguments passed to this function,
 * which, in our case, will be the number @a 1.
 *
 * @line conn =
 * @until }
 *
 * @line eval =
 * @until bson_finish
 *
 * Once we have the connection and the query established, it is time
 * to send the command:
 *
 * @line p =
 * @until }
 *
 * We then create a cursor from the returned packet, and iterate over
 * it (in case there are multiple documents returned - which will not
 * be the case here):
 *
 * @line cursor =
 * @until }
 *
 * @until gdouble
 *
 * We want to retrieve each document, and find the @a retval key in
 * them, because that's where @a $eval returns the results to us.
 *
 * @line result =
 * @until }
 * @until }
 *
 * At this point, we have successfully extracted the data, so we can
 * free up the BSON and cursor objects.
 *
 * @line bson_cursor_free
 * @until bson_free
 *
 * And finally, print the result:
 *
 * @until printf
 *
 * @until }
 *
 * And that's it! We clean up, disconnect, and that's all there is to
 * running custom commands!
 *
 * @line mongo_sync_cursor_free
 * @until }
 */
