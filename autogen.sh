#!/bin/sh

echo "Generating configure files... may take a while."

aclocal && autoconf && automake --add-missing --copy
