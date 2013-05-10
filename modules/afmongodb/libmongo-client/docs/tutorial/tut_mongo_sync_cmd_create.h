/** @page tut_mongo_sync_cmd_create Creating collections
 *
 * In this simple example we'll learn how to explicitly create
 * collections with the library, be those normal collections, capped
 * ones or simply preallocated.
 *
 * Our application will attempt to create a normal collection, a
 * capped one, a capped one that's also capped on the number of
 * entries, and a pre-allocated (but uncapped) collection.
 *
 * It will print these properties of the collections aswell, so that
 * we can verify that the creation did indeed work.
 *
 * @dontinclude tut_mongo_sync_cmd_create.c
 * @until stdio.h
 *
 * First of all, we need a function that prints the collection
 * properties. Because we're lazy, it will take a BSON object, as
 * returned by mongo_sync_cmd_exists().
 *
 * The output of said command is a BSON object that has a @a name
 * field, which is the full name of the collection, the database part
 * included; and an @a options subdocument, which lists various
 * options specified during creating, such as cappedness, size and
 * maximum number of elements.
 *
 * Our very simple function will extract all these and print what's
 * appropriate. It will also free the BSON object it was given, so
 * that we don't leak memory.
 * @until printf ("\n")
 * @until }
 *
 * With that done, lets get down to business, and create the
 * collections, after connecting to the server, of course.
 * @until }
 *
 * First we create a completely normal collection, with the default
 * settings:
 * @until print_coll_info
 *
 * Then a capped collection:
 * @until print_coll_info
 *
 * Followed by another capped collection, one that is also capped by
 * the number of elements, not only by size:
 * @until print_coll_info
 *
 * And finally, we create a pre-allocated collection:
 * @until print_coll_info
 *
 * And that's about it, really.
 * @until }
 */
