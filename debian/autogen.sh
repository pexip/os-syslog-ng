#! /bin/sh

TOPDIR=`pwd`

cd lib/ivykis/
libtoolize --force --copy --automake
aclocal -I m4 --install
autoheader
automake --foreign --add-missing --copy
autoconf
cd $TOPDIR

cd modules/afmongodb/libmongo-client/
libtoolize --force --copy --automake
aclocal -I m4 --install
autoheader
automake --foreign --add-missing --copy
autoconf
cd $TOPDIR

libtoolize --force --copy --automake
aclocal -I m4 --install
autoheader
automake --foreign --add-missing --copy
autoconf
