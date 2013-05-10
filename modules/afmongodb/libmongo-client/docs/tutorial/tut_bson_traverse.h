/** @page tut_bson_traverse Traversing BSON objects
 *
 * Now that we can build BSON objects (see the @ref tut_bson_build
 * "previous section"), it is time that we learn how to find things in
 * them!
 *
 * We will use the same JSON structure as in the previous example.
 *
 * @dontinclude tut_bson_traverse.c
 * First, we include our stuff, and create a function that gives us a
 * BSON object to work with:
 * @until return b
 * @line }
 *
 * @until {
 * First, we need a variable to hold our BSON object, and a cursor,
 * with which we can find the keys we're looking for.
 * @until bson_cursor
 *
 * Then we need a few variables to store the retrieved information
 * in. Extracting data out of a BSON object involves storing them in a
 * variable of our own.
 * @until v_str
 *
 * @until doc = tut_bson
 *
 * In order to find something in a BSON object, we must know the keys
 * name. There's two ways to find information within a BSON object:
 * bson_find() and bson_cursor_next() and its friends.
 *
 * The first takes a BSON object, and returns a cursor that points to
 * the key we wanted to find (or to NULL, if it was not found, of
 * course). We can then extract that value, and either close the
 * cursor, or use bson_cursor_next() to iterate over the rest of the
 * keys.
 *
 * The advantage of bson_find() is that we can jump to a specific key
 * easily, but at the cost of having to use a new cursor every time,
 * which in turn will start searching from the beginning of a BSON
 * document.
 *
 * On the other hand, bson_cursor_next() remembers its position, and
 * jumping to the next key is straightforward. It can also be used in
 * conjunction with bson_find() to locate the first key we're
 * interested in, and move on to the next until we're done.
 *
 * For our first traversal example, lets say we want to see who the
 * author of our BSON object is! We can extract that information by
 * locating the "author" key, and retrieving the string contents:
 * @until printf
 *
 * Now, if we also want to know whether the 'inline' key is set to
 * true or false, we have two options: if we know the exact order of
 * keys, we can use the appropriate amount of bson_cursor_next()
 * calls:
 * @until printf
 *
 * But this is not only ugly, it's very sensitive to the order of the
 * keys, and it's hard to understand aswell, without being familiar
 * with the document's structure.
 *
 * So, while it is a little more inconvenient, it's better to find the
 * key in some other way. But first, let's close our cursor, as we'll
 * need to start again anyway...
 * @until bson_cursor_free
 *
 * First, we'll go the easy route, and use bson_find():
 * @until printf
 *
 * Now, the downside of this, is that we ran through the BSON object
 * twice. Well, once and a little, since the "author" key was the
 * first. But using bson_find() this way has the potential of
 * traversing through a document multiple times.
 *
 * Now, if we know the one key always comes after another, then we can
 * use bson_cursor_next() to help us find it, without having to
 * restart from the beginning. We do this by extracting the key name
 * from the cursor, and comparing it to whatever we're searching for:
 * @until printf
 *
 * Now the above is still picky about key order, but it's at least
 * more flexible: we can put any number of keys between author and
 * inline, and it will work. In most cases, that's good enough. In
 * every other case, where we have no idea about key ordering,
 * bson_find() is still there for us.
 *
 * Even better, the library itself provides a function that does
 * something similar: it takes a cursor and a key name, and attempts
 * to find the key past the cursor's current position. So if we
 * already have the author, we can use this function to find the next
 * inline key aswell:
 * @until printf
 *
 * However, if we suspect that a key might come after the current
 * position, but we're not sure, and still want to find the key with
 * as little code as possible, we shall not despair! The
 * bson_cursor_find() function does just that: it will try to find the
 * key starting from the current position, and wrap over once if it
 * can't.
 *
 * Lets see how it works! First, we find a key in the middle:
 * @until bson_find
 *
 * Now that we have a key in the middle, lets find a key after it:
 * @until get_boolean
 *
 * And once we have that - and we're at the end of our BSON object -,
 * lets try finding the author key aswell:
 * @until get_string
 *
 * That works, just like that! To verify, we go ahead and print the
 * results, which should be the same as it was in the previous
 * examples:
 *
 * @until cursor_free
 *
 * @until printf
 *
 * One thing we did not explore yet, is bson_cursor_new(): this will
 * create a new cursor, and point to to the very beginning of our BSON
 * object, just before the first key. Thus, the first
 * bson_cursor_next() done afterwards will yield the first key.
 * @until bson_cursor_free
 *
 * Very well! But what if we want to see the title of the second page
 * within the pages array? Unfortunately, that is a bit more work to
 * accomplish: we'll need to extract the pages array from our
 * document, and then extract its second element, and then we can find
 * stuff in that:
 * @until printf
 *
 * And that concludes our BSON traversing tutorial!
 *
 * @until }
 */
