######################### STYL AGPS library ############################

DEBUG_CFLAGS = -g -ggdb

bin_PROGRAMS = stylagps_demo

stylagps_demo_SOURCES = main.c

stylagps_demo_CFLAGS = $(DEBUG_CFLAGS) -std=c99 $(GLIB_CFLAGS) -I$(top_srcdir)/src

stylagps_demo_LDFLAGS = $(GLIB_LIBS) -lstylagps -L./../src
