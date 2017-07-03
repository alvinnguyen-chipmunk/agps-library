/*******************************************************************************
 (C) Copyright 2009 Styl Solutions Co., Ltd. , All rights reserved *
 *
 This source code and any compilation or derivative thereof is the sole *
 property of Styl Solutions Co., Ltd. and is provided pursuant to a *
 Software License Agreement. This code is the proprietary information *
 of Styl Solutions Co., Ltd and is confidential in nature. Its use and *
 dissemination by any party other than Styl Solutions Co., Ltd is *
 strictly limited by the confidential information provisions of the *
 Agreement referenced above. *
 ******************************************************************************/

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#include "stylagps.h"
#include "styl_agps_json.h"
#include "styl_agps_utils.h"
#include "styl_agps_query.h"
#include "styl_agps_param.h"
#include "styl_agps_nm.h"

#ifndef STYL_SW_VERSION
#define STYL_SW_VERSION     "1.3"
#endif

static gchar * DATA_FILE = NULL;

gint StylAgpsGetLocation(GObject * nm_device, gdouble *latitude, gdouble *longitude, gdouble *accuracy)
{
    gchar       *json_string    = NULL;
    GHashTable  *param_table    = NULL;
    gchar       *http_data      = NULL;
    gint        ret             = EXIT_FAILURE;

    g_return_val_if_fail(nm_device, EXIT_FAILURE);

    /* **************************** Read and parse configure file ********************************* */
    param_table = styl_agps_param_new(DATA_FILE);
    if(param_table)
    {
        //styl_agps_param_print(param_table);

        /* ================== Create J-son String consist list Access Point ======================= */
        json_string = styl_agps_json_new(NM_CLIENT(nm_device));

//        json_string = g_strdup("{                     						           \
//                                 \"wifiAccessPoints\":						           \
//                                [								           \
//                                    { \"macAddress\": \"B4:75:0E:C5:36:C3\",\"signalStrength\": -35 }      \
//                                ,    { \"macAddress\": \"78:44:76:61:12:CC\",\"signalStrength\": -33 }     \
//                                ,    { \"macAddress\": \"48:F8:B3:2E:EA:78\",\"signalStrength\": -36 }     \
//                                ,    { \"macAddress\": \"B4:75:0E:C5:36:C4\",\"signalStrength\": -45 }     \
//                                ,    { \"macAddress\": \"48:F8:B3:2E:EA:3D\",\"signalStrength\": -45 }     \
//                                ,    { \"macAddress\": \"60:E3:27:3F:60:9E\",\"signalStrength\": -46 }     \
//                                ,    { \"macAddress\": \"14:91:82:7D:66:C7\",\"signalStrength\": -66 }     \
//                                ,    { \"macAddress\": \"48:F8:B3:2E:EA:79\",\"signalStrength\": -75 }     \
//                                ,    { \"macAddress\": \"DC:FB:02:D3:54:AC\",\"signalStrength\": -10 }     \
//                                ,    { \"macAddress\": \"9C:AD:97:C5:E5:46\",\"signalStrength\": -18 }     \
//                                ,    { \"macAddress\": \"48:F8:B3:2E:EA:3C\",\"signalStrength\": -45 }     \
//                                ,    { \"macAddress\": \"00:23:F8:5D:57:39\",\"signalStrength\": -23 }     \
//                                ,    { \"macAddress\": \"98:DE:D0:E5:EF:7E\",\"signalStrength\": -46 }     \
//                                ,    { \"macAddress\": \"EE:0E:C4:51:07:BC\",\"signalStrength\": -63 }     \
//                                ,    { \"macAddress\": \"C8:3A:35:5F:11:80\",\"signalStrength\": -60 }     \
//                                ,    { \"macAddress\": \"EC:08:6B:37:A7:7D\",\"signalStrength\": -66 }     \
//                                ,    { \"macAddress\": \"B4:75:0E:16:58:A2\",\"signalStrength\": -76 }     \
//                                ,    { \"macAddress\": \"A4:2B:B0:D1:F5:44\",\"signalStrength\": -81 }     \
//                                ,    { \"macAddress\": \"EC:22:80:D1:F9:C2\",\"signalStrength\": -81 }     \
//                                 ] 									   \
//                                }     									   \
//                                ");
        if(json_string)
        {
            //DEBUG_1("Json String: %s", json_string);
            /* ---------------------------- Query location from Google API ------------------------ */
            http_data = styl_agps_query_exec(json_string, param_table);
            DEBUG_1("\n************** http_data:\n%s", http_data);
            if(http_data)
            {
                ret = styl_agps_utils_data_parse(http_data, &latitude, &longitude, &accuracy);
            }
            /* ------------------------------------------------------------------------------------ */
        }
        /* ======================================================================================== */
    }
    /* ******************************************************************************************** */

    /* ========================================= Free memory =================================== */
    styl_agps_param_free(param_table);
    g_free(json_string);
    g_free(http_data);
    /* ======================================================================================== */

    return ret;
}

GObject * StylAgpsInit()
{
    DEBUG_0();

    DATA_FILE = g_strdup_printf("%s/%s", __DATADIR__, DATA_NAME);

    if(DATA_FILE==NULL)
        return NULL;

    NMClient *  nm_client = styl_agps_nm_get_nm_client();
    return (GObject *)(nm_client);
}

void StylAgpsFinalize(GObject * nm_device)
{
    styl_agps_nm_free_all(nm_device);
}

#ifdef __cplusplus
}
#endif /* __cplusplus */
