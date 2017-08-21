######################### STYL AGPS COMMON VARIABLE ############################
if DEBUG
DEBUG_CFLAGS = -g -ggdb
else
DEBUG_CFLAGS = -D__RELEASE__
endif

stylagps_datadir = /etc/stylagps
STYLAGPS_includedir = $(includedir)/styl
STYLAGPS_SOURCES = 					\
                styl_agps_utils.h styl_agps_utils.c     \
                styl_agps_json.h styl_agps_json.c       \
                styl_agps_param.h styl_agps_param.c     \
                styl_agps_query.h styl_agps_query.c     \
                styl_agps_nm.h styl_agps_nm.c           \
                stylagps.h stylagps.c

STYLAGPS_include_HEADERS = stylagps.h

STYLAGPS_CFLAGS = -D__DATADIR__=\""$(stylagps_datadir)"\" 	\
		$(DEBUG_CFLAGS) -std=c99 $(DBUS_GLIB_1_CFLAGS) 	\
		$(LIBNM_GLIB_CFLAGS) $(GLIB_CFLAGS)		\
		$(CURL_CFLAGS)

STYLAGPS_LDFLAGS = $(DBUS_GLIB_1_LIBS) $(LIBNM_GLIB_LIBS) \
		$(GLIB_LIBS) $(CURL_LIBS)


######################### STYL AGPS LIBTOOL LIBRARY ############################

lib_LTLIBRARIES = libstylagps.la

libstylagps_la_includedir = $(STYLAGPS_includedir)

libstylagps_la_SOURCES = $(STYLAGPS_SOURCES)

libstylagps_la_include_HEADERS = $(STYLAGPS_include_HEADERS)

libstylagps_la_CFLAGS = $(STYLAGPS_CFLAGS)

libstylagps_la_LDFLAGS = $(STYLAGPS_LDFLAGS)

######################### STYL AGPS STATIC LIBRARY #############################

lib_LIBRARIES = libstylagps.a

libstylagps_a_includedir = $(STYLAGPS_includedir)

libstylagps_a_SOURCES = $(STYLAGPS_SOURCES)

libstylagps_a_include_HEADERS = $(STYLAGPS_include_HEADERS)

libstylagps_a_CFLAGS = $(STYLAGPS_CFLAGS)

libstylagps_a_LIBADD =

