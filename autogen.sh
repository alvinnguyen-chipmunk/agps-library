#!/bin/sh

echo "Generating configure files... may take a while."

libtoolize && aclocal && autoconf && automake --add-missing --copy
