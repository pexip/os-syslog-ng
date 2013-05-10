/** @page tut_bson_build Building BSON objects
 *
 * Our first task will be to build a BSON document, which we can later
 * insert into MongoDB. For this example, we want something more
 * complex than a simple "Hello World"-style object, so we can
 * showcase all the interesting functions of the BSON API.
 *
 * Lets build a document that would look like this, if we were writing
 * JSON:
 * @verbinclude tut_bson_build.json
 *
 * @dontinclude tut_bson_build.c
 *
 * First we start by including the main libmongo-client header. It's
 * convenient to include the whole lot instead of including the used
 * headers one by one, unless one's embedding only parts of the
 * library.
 * @until mongo.h
 *
 * @until {
 *
 * We'll be building the same BSON object in various different ways,
 * so we declare a few more variables than we'd normally need.
 * @until pages
 *
 * Next, we create the two pages:
 * @until bson_finish (page2)
 *
 * Then we construct the "pages" array. Do note how we set the key to
 * "1" and "2", and how pages is just a document! This is because in
 * BSON, an array is a document that has a special type, and where
 * keys are numbers.
 * @until bson_finish (pages)
 *
 * Finally, now that we have all the subdocuments ready, we build up
 * our main object:
 * @until bson_finish (b_new)
 *
 * And that's about it! But surely, there is an easier way to do
 * this... And indeed, there is, using bson_build():
 * @until bson_finish (b_builder)
 *
 * Much cleaner, but still, we had to create the pages array in three
 * steps beforehand. Couldn't we do it in one gigantic function call
 * instead?
 * @until bson_finish (b_builder_full)
 *
 * Wonderful! We have three BSON objects created now, in three
 * different ways! But are they the same? That's really easy to figure
 * out. As a quick check, we can compare their sizes: if they do not
 * match, we can bail out fast:
 * @until }
 *
 * Or, we can do a more expensive comparsion, and compare the data:
 * @until }
 *
 * And now that we are done, we free up the resources we allocated.
 * @until bson_free (page1)
 *
 *
 * @until }
 */
