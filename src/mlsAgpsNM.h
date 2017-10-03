#ifndef STYL_AGPS_NM_H_INCLUDED
#define STYL_AGPS_NM_H_INCLUDED

#include <dbus/dbus-glib.h>
#include <nm-client.h>
#include <nm-device.h>
#include <nm-device-wifi.h>


NMClient *      styl_agps_nm_get_nm_client();

GSList *        styl_agps_nm_get_ap_list(GObject * nm_client);

void            styl_agps_nm_free_ap_list(GSList * access_point_list);

void styl_agps_nm_free_all(GObject *nm_client);

#endif // STYL_AGPS_NM_H_INCLUDED
