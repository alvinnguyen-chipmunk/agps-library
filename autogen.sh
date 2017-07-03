#!/bin/sh
# Run this to generate all the initial makefiles, etc.

srcdir=`dirname $0`
test -z "$srcdir" && srcdir=.

DIE=0

(test -f $srcdir/configure.ac) || {
	echo "**Error**: Directory "\`$srcdir\'" does not look like the top-level package directory"
	exit 1
}

(autoconf --version) < /dev/null > /dev/null 2>&1 || {
	echo
	echo "**Error**: You must have \`autoconf' installed."
	echo "Download the appropriate package for your distribution,"
	echo "or get the source tarball at ftp://ftp.gnu.org/pub/gnu/"
	DIE=1
}

(libtoolize --version) < /dev/null > /dev/null 2>&1 || {
     (glibtoolize --version) < /dev/null > /dev/null 2>&1 || {
         echo
         echo "**Error**: You must have \`libtool' installed."
         echo "You can get it from:"
         echo "  http://www.gnu.org/software/libtool/"
         DIE=1
     }
}

(pkg-config --version) < /dev/null > /dev/null 2>&1 || {
        echo
        echo "You must have pkg-config installed to compile $package."
        echo "Download the appropriate package for your distribution."
               result="no"
        DIE=1
}

(automake --version) < /dev/null > /dev/null 2>&1 || {
	echo
	echo "**Error**: You must have \`automake' (1.7 or later) installed."
	echo "You can get it from: ftp://ftp.gnu.org/pub/gnu/"
	DIE=1
	NO_AUTOMAKE=yes
}


# if no automake, don't bother testing for aclocal
test -n "$NO_AUTOMAKE" || (aclocal --version) < /dev/null > /dev/null 2>&1 || {
	echo
	echo "**Error**: Missing \`aclocal'.  The version of \`automake'"
	echo "installed doesn't appear recent enough."
	echo "You can get automake from ftp://ftp.gnu.org/pub/gnu/"
	DIE=1
}

if test "$DIE" -eq 1; then
	echo "Miss some tool ... exited."
	exit 1
fi

if test -z "$*"; then
	echo "**Warning**: I am going to run \`configure' with no arguments."
	echo "If you wish to pass any to it, please specify them on the"
	echo \`$0\'" command line."
	echo
fi

echo "=============== configure.ac =============="

NOCONFIGURE=1

echo "Processing libtoolize --copy --force || glibtoolize --copy --force"
libtoolize --copy --force || glibtoolize --copy --force
echo "Processing aclocal"
aclocal
echo "Processing automake --add-missing --copy --gnu"
automake --add-missing --copy --gnu
echo "Processing autoconf"
autoconf

if [ "$NOCONFIGURE" = 1 ]; then
    echo "Done. configure skipped."
    exit 0;
else
    echo "Error, configure removed."
    rm configure
    exit 1;
fi

