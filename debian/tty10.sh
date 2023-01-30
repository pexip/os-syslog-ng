#/bin/sh

if [ -c /dev/tty10 ]
then
  echo 'file("/dev/tty10")'
elif [ -c /dev/ttyva ]
then
  echo 'file("/dev/ttyva")'
else
  echo 'file("/dev/null")'
fi
