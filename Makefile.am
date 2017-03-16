lib_LTLIBRARIES = libstylagps.la
ACLOCAL_AMFLAGS = -I m4
AM_CFLAGS = -std=c99 $(LIBNM_CFLAGS) $(GLIB_CFLAGS) $(JSON_CFLAGS) $(CURL_CFLAGS)
AM_LDFLAGS= $(LIBNM_LIBS) $(GLIB_LIBS) $(JSON_LIBS) $(CURL_LIBS)
libstylagps_la_SOURCES = stylagps.c stylAgpsUtils.c
include_HEADERS = stylagps.h stylAgpsUtils.h

# Reference application
bin_PROGRAMS = stylagps_demo stylagps_send stylagps_receive stylagps_mqSend stylagps_mqReceive
stylagps_demo_SOURCES = examples/main.c
stylagps_demo_LDADD = libstylagps.la
stylagps_send_SOURCES = examples/stylAgpsSend.c
stylagps_send_LDADD = libstylagps.la
stylagps_receive_SOURCES = examples/stylAgpsReceive.c
stylagps_receive_LDADD = libstylagps.la
stylagps_mqSend_SOURCES = examples/stylAgpsMQSend.c
stylagps_mqSend_LDADD = libstylagps.la
stylagps_mqReceive_SOURCES = examples/stylAgpsMQReceive.c
stylagps_mqReceive_LDADD = libstylagps.la

extradir = /etc/stylagps
extra_DATA = stylagps.conf
