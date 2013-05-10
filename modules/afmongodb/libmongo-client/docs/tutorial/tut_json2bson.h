/** @page tut_json2bson JSON to BSON converter
 *
 * Now that we have a basic grasp of the library, we'll write a
 * solution to a real life problem: converting JSON to BSON.
 *
 * Our program will expect correctly formatted JSON, in condensed
 * one-line format, and will output a BSON document for each line of
 * JSON received.
 *
 * @dontinclude tut_json2bson.c
 * @until glib.h
 *
 * First, we forward declare the json_to_bson() function, because
 * we'll recursively use it later on:
 * @until json_to_bson
 *
 * Next, we create the heart of the program, a function that takes a
 * BSON object, a value and a key, and appends the key-value pair to
 * the bson object, with the correct type.
 * @until {
 *
 * We do this by checking the JSON object's type, and acting up on it:
 * @until switch
 * @until {
 *
 * The boolean, double, integer and string types are easy: we just use
 * the appropriate bson_append_*() function:
 * @until break
 * @until break
 * @until break
 * @until break
 *
 * Converting a JSON object to BSON is a bit more complicated, yet,
 * straightforward nevertheless:
 * @until }
 *
 * This is one of the reasons we needed to forward-declare
 * json_to_bson(): we're using it to turn the JSON value into BSON,
 * and append it as a subdocument.
 *
 * Next up: arrays! This is even trickier than sub-documents, as we
 * need to iterate over the elements, and append each
 * individually. But, trickier as it may be, it's still
 * straightforward;
 * @until }
 * @until }
 *
 * Anything else, we ignore:
 * @until break
 *
 * @until }
 *
 * @until }
 *
 * And to bind this together with JSON-C's API, we need two more
 * functions. The first one will simply iterate over a JSON object,
 * and call the function we wrote above:
 * @until }
 * @until }
 *
 * The next one is another wrapper around this former: it creates a
 * BSON document, calls the foreach method, then finishes the BSON
 * object and we're done:
 * @until }
 *
 * We're almost done! All that is left is writing our program's entry
 * point: something that will read the input, turn it into BSON, and
 * write it out:
 *
 * @until json_tokener
 *
 * We do some setting up, creating a new IO channel, and a JSON
 * tokenizer:
 * @until tokener =
 *
 * Then, until we have something to read...
 * @until {
 * @until bson
 *
 * We reset the tokenizer before parsing another line, then parse the
 * JSON we received:
 * @until }
 *
 * If we received something other than a JSON object, we can't turn
 * that into BSON, so we write an error to STDERR, and skip this line:
 * @until }
 *
 * Otherwise, we turn it into BSON, and write it to STDOUT:
 * @until bson_free
 *
 * @until }
 *
 * And that was our program, a very simple application that turns each
 * line of JSON into BSON.
 *
 * @until }
 */
