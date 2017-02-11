lib_LTLIBRARIES = libstylagps.la
ACLOCAL_AMFLAGS = -I m4
AM_CFLAGS = -std=c99 $(LIBNM_CFLAGS) $(GLIB_CFLAGS) $(JSON_CFLAGS) $(CURL_CFLAGS)
AM_LDFLAGS= $(LIBNM_LIBS) $(GLIB_LIBS) $(JSON_LIBS) $(CURL_LIBS)
libstylagps_la_SOURCES = stylagps.c get-ap-info-libnm.c
include_HEADERS = stylagps.h get-ap-info-libnm.h

# Reference application
bin_PROGRAMS = stylagps_demo
stylagps_demo_SOURCES = examples/main.c
stylagps_demo_LDADD = libstylagps.la

extradir = /etc/stylagps
extra_DATA = stylagps.conf
