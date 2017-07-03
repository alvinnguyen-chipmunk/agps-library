######################### STYL AGPS library ############################

DEBUG_CFLAGS = -g -ggdb
PM_CONFIG_DIR = .libstylagps

lib_LTLIBRARIES = libstylagps.la

libstylagps_la_includedir = $(includedir)/libstylagps

libstylagps_la_SOURCES = \
		styl_agps_utils.h styl_agps_utils.c	\
		styl_agps_json.h styl_agps_json.c	\
		styl_agps_param.h styl_agps_param.c	\
		styl_agps_query.h styl_agps_query.c	\
		styl_agps_nm.h styl_agps_nm.c		\
		stylagps.h stylagps.c

libstylagps_la_include_HEADERS = stylagps.h

libstylagps_la_CFLAGS = $(DEBUG_CFLAGS) -std=c99 $(DBUS_GLIB_1_CFLAGS) \
			$(LIBNM_GLIB_CFLAGS) $(GLIB_CFLAGS)	\
			$(CURL_CFLAGS)

libstylagps_la_LDFLAGS= $(DBUS_GLIB_1_LIBS) $(LIBNM_GLIB_LIBS)	\
			$(GLIB_LIBS) $(CURL_LIBS)
