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
 * @file    mlsAgpsParam.c
 * @brief   C code - Implement parameter processing of A-GPS feature.
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
#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <string.h>

#include "mlsAgpsParam.h"
#include "mlsAgpsUtils.h"

/********** Local Constant and compile switch definition section **************/
/********** Local Type definition section *************************************/
/********** Local Macro definition section ************************************/
/********** Local (static) variable definition ********************************/
/********** Local (static) function declaration section ***********************/
static void mlsAgpsParam_Print_core(gpointer key, gpointer value, gpointer userdata);
static void mlsAgpsParam_Free_core(gpointer key, gpointer value, gpointer userdata);

/********** Local function definition section *********************************/
static void mlsAgpsParam_Print_core(gpointer key, gpointer value, gpointer userdata)
{
    g_message("\n   Key: %s\n   Value: %s\n", (gchar *)key, (gchar *)value);
}

static void mlsAgpsParam_Free_core(gpointer key, gpointer value, gpointer userdata)
{
    g_free((gchar *)key);
    g_free((gchar *)value);
    key=NULL;
    value=NULL;
}

/********** Global function definition section ********************************/
GHashTable * mlsAgpsParam_New(const gchar* filename)
{
    FILE *fp = NULL;
    gchar buffer[255];

    g_return_val_if_fail(filename, NULL);

    STYL_DEBUG("Parameter file: %s", filename);

    GHashTable * param_table = NULL;
    param_table = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, NULL);

    fp = fopen(filename, "r");
    if(!fp)
        return NULL;

    for(gint i=0; i<PARAM_NUMBER; i++)
    {
        if(!feof(fp))
        {
            gchar ** token = NULL;
            memset(buffer, 0, 255);
            gint tmp = fscanf(fp, "%s", buffer);
            token = g_strsplit_set (buffer,"=",-1);
            if(g_strv_length(token)==2)
            {
                g_hash_table_insert(param_table, (gpointer )g_strdup(token[0]),(gpointer)g_strdup(token[1]));
            }
            g_strfreev(token);
        }
    }
    fclose(fp);
    fp=NULL;

    return param_table;
}

void mlsAgpsParam_Free(GHashTable * param_table)
{
    if(param_table)
    {
        g_hash_table_foreach(param_table, mlsAgpsParam_Free_core, NULL);
        g_hash_table_remove_all(param_table);
    }
}

void mlsAgpsParam_Print(GHashTable * param_table)
{
    if(param_table)
        g_hash_table_foreach(param_table, mlsAgpsParam_Print_core, NULL);
    else
        g_error("\nParameter is null.");
}

gchar * mlsAgpsParam_Key2Value(GHashTable * param_table, gchar * keyword)
{
    gchar * value = NULL;
    if(g_hash_table_lookup_extended(param_table, (gconstpointer)keyword, NULL, (gpointer)&value))
    {
        return value;
    }
    return NULL;
}

#ifdef __cplusplus
}
#endif
/*@}*/
