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
 * @file    mlsAgpsJson.c
 * @brief   C code - Implement J-son string processing of A-GPS feature.
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
#include "mlsAgpsJson.h"
#include "mlsAgpsUtils.h"
#include "mlsAgpsNM.h"

/********** Local Constant and compile switch definition section **************/
/********** Local Type definition section *************************************/
/********** Local Macro definition section ************************************/
/********** Local (static) variable definition ********************************/
/********** Local (static) function declaration section ***********************/
static void styl_agps_json_append(gpointer data, gpointer userdata);

/********** Local function definition section *********************************/
static void styl_agps_json_append(gpointer data, gpointer userdata)
{
    gchar **json_string = (gchar **)userdata;
    gchar * str = (gchar *) data;
    gchar * buffer = NULL;
    buffer = g_strdup_printf("%s\n%s", *json_string, str);
    g_free(*json_string);
    *json_string=NULL;
    *json_string = buffer;
}

/********** Global function definition section ********************************/
gchar *styl_agps_json_new(GObject * nm_client)
{
    gchar * json_string = NULL;
    gchar * buffer      = NULL;

    GSList * access_point_list = styl_agps_nm_get_ap_list(nm_client);

    if(access_point_list)
    {
        json_string = g_strdup("{\n \"wifiAccessPoints\":\n [");
        g_slist_foreach(access_point_list, styl_agps_json_append, (gpointer)&json_string);
        buffer = g_strdup_printf("%s\n%s", json_string, " ]\n}");
        g_free(json_string);
        json_string = buffer;
    }
    styl_agps_nm_free_ap_list(access_point_list);

    return json_string;
}

#ifdef __cplusplus
}
#endif
/*@}*/

