/*******************************************************************************
 *  (C) Copyright 2009 STYL Solutions Co., Ltd. , All rights reserved          *
 *                                                                             *
 *  This source code and any compilation or derivative thereof is the sole     *
 *  property of STYL Solutions Co., Ltd. and is provided pursuant to a         *
 *  Software License Agreement.  This code is the proprietary information      *
 *  of STYL Solutions Co., Ltd and is confidential in nature.  Its use and     *
 *  dissemination by any party other than STYL Solutions Co., Ltd is           *
 *  strictly limited by the confidential information provisions of the         *
 *  Agreement referenced above.                                                *
 ******************************************************************************/
/**
 * @file    mlsAgpsNM.c
 * @brief   C code - Implement NetworkManager processing of A-GPS feature.
 *
 * Long description.
 * @date    10/10/2017
 * @author  Alvin Nguyen - alvin.nguyen@styl.solutions
 */

#ifdef __cplusplus
extern "C"
{
#endif

/********** Include section ***************************************************/
#include "mlsAgpsUtils.h"
#include "mlsAgpsNM.h"

/********** Local Constant and compile switch definition section **************/
/********** Local Type definition section *************************************/
/********** Local Macro definition section ************************************/
/********** Local (static) variable definition ********************************/
GMainLoop *loop = NULL;

/********** Local (static) function declaration section ***********************/
static void styl_agps_nm_free_ap_list_fnc(gpointer data);
static void styl_agps_nm_device_wifi_request_scan_simple_callback (NMDeviceWifi *device,
                                                                    GError *error,
                                                                    gpointer user_data);

/********** Local function definition section *********************************/
static void styl_agps_nm_free_ap_list_fnc(gpointer data)
{
    g_free((gchar *) data);
}

static void styl_agps_nm_device_wifi_request_scan_simple_callback (NMDeviceWifi *device,
                                                                    GError *error,
                                                                    gpointer user_data)
{
    STYL_DEBUG("Scanning callback work !");
    if (error)
    {
        const char *text = "failed to scan";
        char *err_text = g_strdup_printf ("(%d) %s", error->code,
                                          error->message ? error->message : "Unknown error");

        STYL_DEBUG ("%s: %s", text, err_text);
        g_free (err_text);
    }
    else
    {
        STYL_DEBUG("Scanning completed.");
    }

    g_main_loop_quit (loop);
}

/********** Global function definition section ********************************/
void styl_agps_nm_free_all(GObject *nm_client)
{
    g_object_unref (nm_client);
}


NMClient * styl_agps_nm_get_nm_client()
{
    NMClient * nm_client = NULL;

    nm_client = nm_client_new ();
    STYL_DEBUG("New nm_client: %p", nm_client);

    return nm_client;
}

GSList * styl_agps_nm_get_ap_list(GObject * nm_client)
{
    const GPtrArray *devices;
    const GPtrArray *access_points;
    GSList          * access_point_list     = NULL;
    NMDevice        * nm_device             = NULL;
    NMDevice        * tmp                   = NULL;

    devices = nm_client_get_devices (NM_CLIENT(nm_client));

    /* Go through the array and process Wi-Fi devices */
    for (gint i = 0; devices && (i < devices->len); i++)
    {
        tmp = g_ptr_array_index (devices, i);
        if (NM_IS_DEVICE_WIFI (tmp))
        {
            nm_device = tmp;
            break;
        }
    }
    if(nm_device!=NULL)
    {
        nm_device_wifi_request_scan_simple(NM_DEVICE_WIFI (nm_device),
                                           styl_agps_nm_device_wifi_request_scan_simple_callback, NULL);
        loop = g_main_loop_new (NULL, FALSE);  /* Create main loop */
        g_main_loop_run (loop);                /* Run main loop until scan done! */
        g_main_loop_unref (loop);

        access_points = nm_device_wifi_get_access_points (NM_DEVICE_WIFI(nm_device));
        /* Print AP details */
        for (gint j = 0; access_points && (j < access_points->len); j++)
        {
            NMAccessPoint *access_point = g_ptr_array_index (access_points, j);
            gchar *access_point_info = NULL;
            if(j==0)
            {
                access_point_info = g_strdup_printf("    { \"macAddress\": \"%s\",\"signalStrength\": %d }",
                                          nm_access_point_get_bssid (access_point),
                                          ((guint)nm_access_point_get_strength (access_point))-110);
            }
            else
            {
                access_point_info = g_strdup_printf(",    { \"macAddress\": \"%s\",\"signalStrength\": %d }",
                                          nm_access_point_get_bssid (access_point),
                                          ((guint)nm_access_point_get_strength (access_point))-110);
            }
            access_point_list = g_slist_append(access_point_list, (gpointer)access_point_info);
        }
    }

    return access_point_list;
}

void styl_agps_nm_free_ap_list(GSList * access_point_list)
{
    g_slist_free_full(access_point_list, styl_agps_nm_free_ap_list_fnc);
}

#ifdef __cplusplus
}
#endif
/*@}*/

