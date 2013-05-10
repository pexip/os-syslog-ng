/** @page tut_mongo_sync_connect Connecting to MongoDB
 *
 * The next step in our journey is to connect to MongoDB: to a single
 * server and to a replicaset alike.
 *
 * Our first task is to connect to a MongoDB server, listening
 * on localhost's 27017 port. And we don't care whether it is a master
 * or a secondary, so we set the slave_ok argument to TRUE:
 *
 * @dontinclude tut_mongo_sync.c
 * @skip void
 * @until mongo_sync_disconnect
 * @until }
 *
 * It's fairly straightforward: error handling is done using errno
 * values, because that saves us from inventing our own statuses:
 * POSIX provides us with plenty, and the C library uses errno
 * extensively well. So does libmongo-client!
 *
 * Next up, is connecting to a replicaset:
 *
 * @until return;
 * @until }
 *
 * Wait a minute! Does this look familiar? Isn't it @b exactly the
 * same as in the former example (apart from the host name)? It sure
 * is! There really is no difference between connecting to a single
 * server and to a replica set when using the Sync API. It hides all
 * the boring things from the user.
 *
 * However, if the server is a replicaset, we can add seeds: seeds are
 * hosts that are not listed in the replicaset's public config
 * (meaning they're hidden), but we still want to be able to use them,
 * if so need be.
 *
 * It's not neccessary to add seeds, if the replica set itself
 * advertises secondaries: the library will discover those, and
 * reconnect to them, if automatic reconnection is turned on. Lets
 * just do that!
 *
 * @until }
 *
 * Then we can add the seeds:
 * @until }
 * @until }
 *
 * And that's about it! We wrap up our function, and we're done!
 * @until }
 */
