#!/bin/sh

autoheader &&
libtoolize &&
aclocal && 
automake --add-missing --copy
autoreconf && 
./configure && 
make
