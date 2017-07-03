#ifndef STYL_AGPS_TMP_H_INCLUDED
#define STYL_AGPS_TMP_H_INCLUDED

// File: connect-wifi.c
// Last Updated: Galen                23 Apr 2013
//
//
// Commentary: using nm_device_wifi_request_scan_simple() to scan wifi networks
// Since: NetworkManager-0.9.8
/*
 * Compile with:
 *  gcc -Wall `pkg-config --libs --cflags glib-2.0 dbus-glib-1 libnm-glib libnm-util` wifi-scan.c -o wifi-scan
 */

#include <stdio.h>
#include <stdlib.h>

#include <glib.h>
#include <nm-client.h>
#include <nm-device.h>
#include <nm-device-wifi.h>

GObject * tmp_init();
gint tmp_execute(GObject * nm_client);
void tmp_free(GObject * nm_client);

#endif // STYL_AGPS_TMP_H_INCLUDED
