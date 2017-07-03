#ifndef STYL_AGPS_JSON_H_INCLUDED
#define STYL_AGPS_JSON_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <nm-device.h>
#include <nm-device-wifi.h>

gchar *styl_agps_json_new(GObject * nm_client);

#endif // STYL_AGPS_JSON_H_INCLUDED
