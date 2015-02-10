libmongo-client
===============

[![Build Status](https://travis-ci.org/algernon/libmongo-client.png?branch=master)](https://travis-ci.org/algernon/libmongo-client)

This is an alternative C driver for [MongoDB][mongodb], with slightly
different goals than the official one:

libmongo-client is meant to be a stable (API, ABI and quality alike),
clean, well documented and well tested shared library, that strives to
make the most common use cases as convenient as possible.

Features
--------

The main purpose of this library is to provide a well maintained
implementation, that suits a wider range of needs than the original:

* Well documented, easy, clean and stable API.
* Comprehensive test suite, with over 90% code coverage, and
  increasing.
* Ability to easily construct mongodb commands, to be sent at a later
  time (comes in handy when one is trying to write from a separate
  thread).
* ReplicaSet support, with support for automatic reconnecting and
  discovery.
* Safe-mode support, to optionally enable extra safety checks on
  writes, that make sure the server accepted the write.
* Convenient APIs to work with BSON objects and MongoDB documents.
* Connection pooling.

Apart from these, the library is meant to be used as a shared library,
therefore API and ABI compatibility will be maintained, and only
broken when absolutely neccessary - in which case, a sufficiently
bumped version will be branched off.

Requirements
------------

Apart from [glib][glib] (with header files - usually found in a
development package - installed), there are no other hard
dependencies. Though, one will need [Perl][perl] (with a suitable
version of Test::Harness, along with the prove utility) to run the
test suite.

To build the documentation, [Doxygen][doxygen] will be needed too.

Installation
------------

The library follows the usual autotools way of installation (one will
need libtool 2.2+ to build from git!):

     $ git clone git://github.com/algernon/libmongo-client.git
     $ cd libmongo-client
     $ autoreconf -i
     $ ./configure && make && make install

License
-------

Although the code is not based on any other driver, it is released
under the same Apache License, version 2.0 (included as the file
LICENSE).

 [mongodb]: http://www.mongodb.org/
 [glib]: http://developer.gnome.org/glib/
 [perl]: http://www.perl.org/
 [doxygen]: http://www.stack.nl/~dimitri/doxygen/
