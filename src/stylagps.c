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
        STYL_DEBUG("Parameter pares was success!");

        /* ================== Create J-son String consist list Access Point ======================= */
        json_string = styl_agps_json_new(nm_device);

        if(json_string)
        {
            STYL_DEBUG("Create a json_string was success!");
            //DEBUG_1("Json String: %s", json_string);
            /* ---------------------------- Query location from Google API ------------------------ */
            http_data = styl_agps_query_exec(json_string, param_table);
            STYL_DEBUG("\n************** http_data:\n%s", http_data);
            if(http_data)
            {
                STYL_DEBUG("Query location was success!");
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
    if(__DATADIR__)
        DATA_FILE = g_strdup_printf("%s/%s", __DATADIR__, DATA_NAME);

    if(DATA_FILE==NULL)
        return NULL;

    NMClient *  nm_client = styl_agps_nm_get_nm_client();
    return (GObject *)(nm_client);
}

void StylAgpsFinalize(GObject * nm_device)
{
    g_free(DATA_FILE);
    styl_agps_nm_free_all(nm_device);
}

gchar * StylAgpsGetVersion(void)
{
        return VERSION;
}
#ifdef __cplusplus
}
#endif /* __cplusplus */
