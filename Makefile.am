lib_LTLIBRARIES = libstylagps.la
ACLOCAL_AMFLAGS = -I m4
AM_CFLAGS = -std=c99
AM_LDFLAGS= -lcurl -ljson-c
libstylagps_la_SOURCES = stylagps.c
include_HEADERS = stylagps.h

# Reference application
bin_PROGRAMS = stylagps_demo
stylagps_demo_SOURCES = examples/main.cpp
stylagps_demo_LDADD = libstylagps.la

extradir = $(prefix)/etc/stylagps
extra_DATA = stylagps.conf scripts/SnipWireless.sh

