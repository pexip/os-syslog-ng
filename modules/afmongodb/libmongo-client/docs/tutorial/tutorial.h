/** @page tutorial Tutorial
 *
 * These pages will attempt to guide one through the libmongo-client
 * library, starting from the basic BSON building blocks, through the
 * low level wire protocol API, until the highest level synchronous
 * API.
 *
 * The documentation assumes a reasonable amount of C knowledge, and
 * basic familiarity with MongoDB concepts.
 *
 * The example programs can be found in the @c docs/tut/examples
 * directory in the source tree, along with a Makefile. Would one want
 * to compile the examples, or modified versions of them by hand, then
 * the following command should work:
 *
 * @verbatim
$ cc $(pkg-config --cflags --libs libmongo-client) tut_bson_build.c -o tut_bson_build
@endverbatim
 *
 * Contents:
 *   - @subpage tut_bson
 *     - @ref tut_bson_build
 *     - @ref tut_bson_traverse
 *   - @subpage tut_mongo_sync
 *     - @ref tut_mongo_sync_connect
 *     - @ref tut_mongo_sync_insert
 *     - @ref tut_mongo_sync_query
 *     - @ref tut_mongo_sync_query_complex
 *     - @ref tut_mongo_sync_cmd_create
 *   - @subpage tut_hl_client
 *   - @subpage tut_json2bson
 */
