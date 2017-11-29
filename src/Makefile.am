######################### STYL AGPS COMMON VARIABLE ############################
if DEBUG
DEBUG_CFLAGS = -g -ggdb
else
DEBUG_CFLAGS = 
endif

stylagps_datadir = /etc/stylagps
STYLAGPS_includedir = $(includedir)/styl
STYLAGPS_SOURCES =                                 \
                mlsAgpsUtils.h  mlsAgpsUtils.c     \
                mlsAgpsJson.h   mlsAgpsJson.c      \
                mlsAgpsParam.h  mlsAgpsParam.c     \
                mlsAgpsQuery.h  mlsAgpsQuery.c     \
                mlsAgpsNM.h     mlsAgpsNM.c        \
                mlsAgps.h       mlsAgps.c

STYLAGPS_include_HEADERS = mlsAgps.h

STYLAGPS_CFLAGS = -D__DATADIR__=\""$(stylagps_datadir)"\" 	\
		-std=c99 -D_BSD_SOURCE -D_DEFAULT_SOURCE	\
		$(DEBUG_CFLAGS) $(DBUS_GLIB_1_CFLAGS) 		\
		$(LIBNM_GLIB_CFLAGS) $(GLIB_CFLAGS)		\
		$(CURL_CFLAGS)

STYLAGPS_LDFLAGS = $(DBUS_GLIB_1_LIBS) $(LIBNM_GLIB_LIBS) \
		$(GLIB_LIBS) $(CURL_LIBS) -version-info @STYL_VERSION_INFO@


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

