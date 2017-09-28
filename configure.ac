AC_INIT([stylagps library], [2.0.0], [alvin.nguyen@styl.solutions])
AC_CONFIG_SRCDIR([configure.ac])

# Version information
STYL_MAJOR_VERSION=2
STYL_MINOR_VERSION=0
STYL_MICRO_VERSION=0
STYL_MICRO_VERSION_SUFFIX=
STYL_VERSION=$STYL_MAJOR_VERSION.$STYL_MINOR_VERSION.$STYL_MICRO_VERSION$STYL_MICRO_VERSION_SUFFIX
STYL_VERSION_INFO=`expr $STYL_MAJOR_VERSION + $STYL_MINOR_VERSION`:$STYL_MICRO_VERSION:$STYL_MINOR_VERSION
STYL_VERSION_NUMBER=`expr $STYL_MAJOR_VERSION \* 10000 + $STYL_MINOR_VERSION \* 100 + $STYL_MICRO_VERSION`

AC_SUBST(STYL_MAJOR_VERSION)
AC_SUBST(STYL_MINOR_VERSION)
AC_SUBST(STYL_MICRO_VERSION)
AC_SUBST(STYL_VERSION)
AC_SUBST(STYL_VERSION_INFO)
AC_SUBST(STYL_VERSION_NUMBER)
AC_SUBST(STYL_VERSION_EXTRA)

VERSION=${STYL_VERSION}

dnl Must come before AM_INIT_AUTOMAKE.

# Auxiliary files go "build-aux" directory
AC_CONFIG_AUX_DIR([build-aux])

AM_INIT_AUTOMAKE([-Wall subdir-objects])
AC_CONFIG_MACRO_DIR([m4])

AC_ENABLE_SHARED
AC_ENABLE_STATIC

AC_PROG_CC
AM_PROG_CC_C_O
AM_PROG_AR
AC_PROG_LIBTOOL
AC_PROG_INSTALL
AC_PROG_LN_S

dnl ================================================================

LT_INIT

# Configure for libtool
AM_PROG_LIBTOOL
LIBTOOL="$LIBTOOL --silent"

dnl ================================================================

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_OFF_T
AC_TYPE_SIZE_T
AC_STRUCT_TM

dnl ================================================================

# GTHREAD checks
gthread_modules="gthread-2.0"
PKG_CHECK_MODULES(GTHREAD, [$gthread_modules])
AC_SUBST(GTHREAD_CFLAGS)
AC_SUBST(GTHREAD_LIBS)
GTHREAD_VERSION=`$PKG_CONFIG --modversion ${gthread_modules}`

libnm_glib_modules="libnm-glib"
PKG_CHECK_MODULES([LIBNM_GLIB], [$libnm_glib_modules])
AC_SUBST(LIBNM_GLIB_CFLAGS)
AC_SUBST(LIBNM_GLIB_LIBS)
LIBNM_GLIB_VERSION=`$PKG_CONFIG --modversion ${libnm_glib_modules}`

glib_modules="glib-2.0"
PKG_CHECK_MODULES([GLIB], [$glib_modules])
AC_SUBST(GLIB_CFLAGS)
AC_SUBST(GLIB_LIBS)
GLIB_VERSION=`$PKG_CONFIG --modversion ${glib_modules}`

libcurl_modules="libcurl"
PKG_CHECK_MODULES([CURL], [$libcurl_modules])
AC_SUBST(CURL_CFLAGS)
AC_SUBST(CURL_LIBS)
LIBCURL_VERSION=`$PKG_CONFIG --modversion ${libcurl_modules}`

dbus_glib_1_modules="dbus-glib-1"
PKG_CHECK_MODULES([DBUS_GLIB_1], [$dbus_glib_1_modules])
AC_SUBST(DBUS_GLIB_1CFLAGS)
AC_SUBST(DBUS_GLIB_1_LIBS)
DBUS_GLIB_1_VERSION=`$PKG_CONFIG --modversion ${dbus_glib_1_modules}`


dnl ================================================================
AC_ARG_ENABLE([yocto],
[  --enable-yocto        navigation for stylagps.conf via recipe in yocto],
[case "${enableval}" in
  yes) yocto=true ;;
  no)  yocto=false ;;
  *) AC_MSG_ERROR([bad value ${enableval} for --enable-debug]) ;;
esac],[yocto=false])

AM_CONDITIONAL([YOCTO], [test x$yocto = xtrue])

AC_ARG_ENABLE([debug],
[  --enable-debug        enable print debug information to console],
[case "${enableval}" in
  yes) debug=true ;;
  no)  debug=false ;;
  *) AC_MSG_ERROR([bad value ${enableval} for --enable-debug]) ;;
esac],[debug=false])

AM_CONDITIONAL([DEBUG], [test x$debug = xtrue])

AC_CONFIG_FILES([ Makefile src/Makefile examples/Makefile])

AC_OUTPUT([ stylagps.pc data/stylagps.conf])

dnl ================================================================

echo "----------------------------------------------------------------"
echo "----------------------------------------------------------------"
echo ""
echo "Install STYL AGPS in           : ${prefix}"
echo "Using GTHREAD version          : ${GTHREAD_VERSION}"
echo "Using LIBNM_GLIB version       : ${LIBNM_GLIB_VERSION}"
echo "Using GLIB version             : ${GLIB_VERSION}"
echo "Using LIBCURL version          : ${LIBCURL_VERSION}"
echo "Using DBUS_GLIB_1 version      : ${DBUS_GLIB_1_VERSION}"

echo ""
echo "Configuration is done OK."
echo ""
