/* -*- Mode: C; tab-width: 4; indent-tabs-mode: t; c-basic-offset: 4 -*- */
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 *(at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Copyright 2010 Red Hat, Inc.
 */

/*
 * The example shows how to get info about APs visible by Wi-Fi devices using
 * libnm.
 *
 * Compile with:
 *   gcc -Wall `pkg-config --libs --cflags glib-2.0 libnm` get-ap-info-libnm.c -o get-ap-info-libnm
 */

#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <NetworkManager.h>
#include "stylAgpsUtils.h"

static int strength_to_dbm(int strength)
{
        /* Scale:
         * -10 dbm 	: 100% strength
         * -110 dbm :   0% strength
         */

        return(int) (strength +(-110));
}

int CreateJsonStringListAP(char *jsonString, int jsonStringLen)
{
        const GPtrArray *apArr;
        const GPtrArray *deviceArr;
        char tempString[1000];
        const char *debug = getenv("STYL_DEBUG");
        int tempStringLen = 0;
        int ret = EXIT_SUCCESS;
        int foundWifiDevice = 0;
        NMClient *client;
        NMDevice *wifiDevice;
        GError *error = NULL;

#if !GLIB_CHECK_VERSION(2, 35, 0)
        /* Initialize GType system */
        g_type_init();
#endif

        /* Get NMClient object */
        client = nm_client_new(NULL, &error);
        if(!client)
        {
                g_message("Error: Could not create NMClient: %s.", error->message);
                g_error_free(error);
                ret = EXIT_FAILURE;
                goto EXIT;
        }

        /* Get all devices managed by NetworkManager */
        deviceArr = nm_client_get_devices(client);

        /* Go through the array and process Wi-Fi devices */
        for(int i = 0; i < deviceArr->len; i++)
        {
                wifiDevice = g_ptr_array_index(deviceArr, i);
                if(NM_IS_DEVICE_WIFI(wifiDevice))
                {
                        foundWifiDevice = 1;
                        break;
                }
        }

        if(! foundWifiDevice)
        {
                printf("ERROR: WiFi device is not found\n");
                goto EXIT;
        }

        /* Create json string root, wifiAccessPoints */
        memset(jsonString, '\0', jsonStringLen);
        strcpy(tempString, "{\n \"wifiAccessPoints\":\n [\n");
        tempStringLen = strlen(tempString);
        if(tempStringLen < jsonStringLen)
        {
                strncpy(jsonString, tempString, tempStringLen);
        }

        /* Get all APs of the Wi-Fi device */
        apArr = nm_device_wifi_get_access_points(NM_DEVICE_WIFI(wifiDevice));

        /* Print AP details */
        for(int i = 0; i < apArr->len; i++)
        {
                NMAccessPoint *ap = g_ptr_array_index(apArr, i);

                unsigned char strength;
                int dbm = 0;
                const char *hwaddr;

                hwaddr = nm_access_point_get_bssid(ap);
                strength = nm_access_point_get_strength(ap);
                dbm = strength_to_dbm(strength);

                sprintf(tempString, "    { \"macAddress\": \"%s\",\"signalStrength\": %d }", hwaddr, dbm);
                tempStringLen = strlen(tempString);

                if( jsonStringLen >(tempStringLen + 4) )
                {
                        strncat(jsonString, tempString, tempStringLen);
                }
                else
                {
                        printf("Insufficient memory to add more AP\n");
                        ret = EXIT_FAILURE;
                        goto EXIT;
                }

                if(apArr->len-1 != i)
                {
                        strncat(jsonString, ",\n", 2);
                }
                else
                {
                        strncat(jsonString, "\n", 1);
                }
        }

        strncat(jsonString, " ]\n}", 4);

        if(NULL != debug)
        {
                printf("jsonString:\n%s\n", jsonString);
        }

EXIT:
        g_object_unref(client);
        return ret;
}
