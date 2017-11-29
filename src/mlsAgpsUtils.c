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
#include "mlsAgpsUtils.h"

/********** Local Constant and compile switch definition section **************/
/********** Local Type definition section *************************************/
/********** Local Macro definition section ************************************/
/********** Local (static) variable definition ********************************/
/********** Local (static) function declaration section ***********************/
static gboolean mlsAgpsUtils_ParseDataGet(gchar ** tokens, const gchar * keyword, gdouble *container);

/********** Local function definition section *********************************/
static gboolean mlsAgpsUtils_ParseDataGet(gchar ** tokens, const gchar * keyword, gdouble *container)
{
    gchar * buffer = NULL;
    for(gint i=0; i<g_strv_length(tokens); i++)
    {
        buffer = g_strrstr(tokens[i], keyword);
        if(buffer)
        {
            gchar tmp[128];
            gint end;
            if(sscanf(tokens[i], "%*[^0-9]%s", (char *)&tmp)==1)
            {
                end = strlen(tmp)-1;
                if(tmp[end]==',')
                    tmp[end]='\0';
                *container = g_ascii_strtod(tmp, NULL);
                return TRUE;
            }
        }
    }
    return FALSE;
}

/********** Global function definition section ********************************/
/*!
 * \brief mlsAgpsUtils_ParseData: Parse data of message response of location
 */
gint mlsAgpsUtils_ParseData(gchar *data,
                             gdouble **longitude,
                             gdouble **latitude,
                             gdouble **accuracy)

{
    gint ret = EXIT_FAILURE;
    gdouble tmp1 = 0, tmp2 = 0, tmp3 = 0;

    gchar ** tokens = NULL;
    tokens = g_strsplit_set (data,"\n",-1);

    if(mlsAgpsUtils_ParseDataGet(tokens, "\"lat\":", &tmp1) == TRUE)
        if(mlsAgpsUtils_ParseDataGet(tokens, "\"lng\":", &tmp2) == TRUE)
            if(mlsAgpsUtils_ParseDataGet(tokens, "\"accuracy\":", &tmp3) == TRUE)
            {
                **latitude  = tmp1;
                **longitude = tmp2;
                **accuracy  = tmp3;
                ret = EXIT_SUCCESS;
            }

    g_strfreev(tokens);

    return ret;
}

/*!
 * \brief mlsAgpsUtils_Print: Print out some information.
 */
void mlsAgpsUtils_Print(gint isError, gchar *format, ...)
{
    if (isError == 0)
        if(getenv("STYL_DEBUG")==NULL)
            return;

    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}

#ifdef __cplusplus
}
#endif
/*@}*/
