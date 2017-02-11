AC_INIT([libstylagps], [1.0], [luck.hoang@styl.solutions])

dnl Must come before AM_INIT_AUTOMAKE.
AC_CONFIG_AUX_DIR([build-aux])

AM_INIT_AUTOMAKE([-Wall subdir-objects])
AC_CONFIG_MACRO_DIR([m4])

AC_ENABLE_SHARED

AC_PROG_CC
AC_PROG_CXX
AM_PROG_AR
AC_PROG_LIBTOOL

LT_INIT

PKG_CHECK_MODULES([LIBNM], [libnm > 1.0])
PKG_CHECK_MODULES([GLIB], [glib-2.0])
PKG_CHECK_MODULES([CURL], [libcurl])
PKG_CHECK_MODULES([JSON], [json-c])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
