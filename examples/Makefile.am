###################### STYL AGPS Example #######################
if DEBUG
DEBUG_CFLAGS = -g -ggdb
else
DEBUG_CFLAGS = -D__RELEASE__
endif

AM_CFLAGS = $(DEBUG_CFLAGS) -std=c99 

AM_LDFLAGS = 

######################### simple EXAMPLE ########################

bin_PROGRAMS = stylagps_demo

stylagps_demo_SOURCES = main.c

stylagps_demo_CFLAGS = $(AM_CFLAGS) $(GLIB_CFLAGS) -I$(top_srcdir)/src

stylagps_demo_LDFLAGS = $(AM_LDFLAGS) $(GLIB_LIBS)  -lstylagps -L./../src


##################### Send/Receive EXAMPLE ######################

bin_PROGRAMS += stylagps_send stylagps_receive

stylagps_send_SOURCES = stylAgpsSend.c common.h

stylagps_send_CFLAGS = $(AM_CFLAGS) $(GLIB_CFLAGS) -I$(top_srcdir)/src -I.

stylagps_send_LDFLAGS = $(AM_LDFLAGS) $(GLIB_LIBS)  -lstylagps -L./../src

stylagps_receive_SOURCES = stylAgpsReceive.c common.h

stylagps_receive_CFLAGS = $(AM_CFLAGS) -I.

stylagps_receive_LDFLAGS = $(AM_LDFLAGS)

############## Message queue Send/Receive EXAMPLE ################

bin_PROGRAMS += stylagps_mqSend stylagps_mqReceive

stylagps_mqSend_SOURCES = stylAgpsMQSend.c common.h

stylagps_mqSend_CFLAGS = $(AM_CFLAGS) $(GLIB_CFLAGS) -I$(top_srcdir)/src -I.

stylagps_mqSend_LDFLAGS = $(AM_LDFLAGS) $(GLIB_LIBS)  -lstylagps -L./../src -lrt

stylagps_mqReceive_SOURCES = stylAgpsMQReceive.c common.h

stylagps_mqReceive_CFLAGS = $(AM_CFLAGS) -I.

stylagps_mqReceive_LDFLAGS = $(AM_LDFLAGS) -lrt


