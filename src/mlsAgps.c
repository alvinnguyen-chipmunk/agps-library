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
 * @file    mlsAgps.c
 * @brief   C code - Implement A-GPS feature.
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
#include "mlsAgps.h"
#include "mlsAgpsJson.h"
#include "mlsAgpsUtils.h"
#include "mlsAgpsQuery.h"
#include "mlsAgpsParam.h"
#include "mlsAgpsNM.h"

/********** Local Constant and compile switch definition section **************/
/********** Local Type definition section *************************************/
/********** Local Macro definition section ************************************/
/********** Local (static) variable definition ********************************/
static gchar * DATA_FILE = NULL;

/********** Local (static) function declaration section ***********************/
/********** Local function definition section *********************************/
/********** Global function definition section ********************************/
gint mlsAgps_GetLocation(GObject * nm_client, gdouble *latitude, gdouble *longitude, gdouble *accuracy)
{
    gchar       *json_string    = NULL;
    GHashTable  *param_table    = NULL;
    gchar       *http_data      = NULL;
    gint        ret             = EXIT_FAILURE;

    g_return_val_if_fail(nm_client, EXIT_FAILURE);

    /* **************************** Read and parse configure file ********************************* */
    param_table = mlsAgpsParam_New(DATA_FILE);
    if(param_table)
    {
        //mlsAgpsParam_Print(param_table);
        STYL_DEBUG("Parameter pares was success!");

        /* ================== Create J-son String consist list Access Point ======================= */
        json_string = mlsAgpsJson_New(nm_client);

        if(json_string)
        {
            STYL_DEBUG("Create a json_string was success!");
            //DEBUG_1("Json String: %s", json_string);
            /* ---------------------------- Query location from Google API ------------------------ */
            http_data = mlsAgpsQuery_Execute(json_string, param_table);
            STYL_DEBUG("\n************** http_data:\n%s", http_data);
            if(http_data)
            {
                STYL_DEBUG("Query location was success!");
                ret = mlsAgpsUtils_ParseData(http_data, &latitude, &longitude, &accuracy);
            }
            /* ------------------------------------------------------------------------------------ */
        }
        /* ======================================================================================== */
    }
    /* ******************************************************************************************** */

    /* ========================================= Free memory =================================== */
    mlsAgpsParam_Free(param_table);
    g_free(json_string);
    g_free(http_data);
    /* ======================================================================================== */

    return ret;
}

GObject * mlsAgps_Init()
{
    if(__DATADIR__)
        DATA_FILE = g_strdup_printf("%s/%s", __DATADIR__, DATA_NAME);

    if(DATA_FILE==NULL)
        return NULL;

    NMClient *  nm_client = mlsAgpsNM_GetNMClient();
    return (GObject *)(nm_client);
}

void mlsAgps_Finalize(GObject * nm_client)
{
    g_free(DATA_FILE);
    mlsAgpsNM_FreeAll(nm_client);
}

const gchar * mlsAgps_GetVersion(void)
{
        return (const gchar*) VERSION;
}

#ifdef __cplusplus
}
#endif
/*@}*/
