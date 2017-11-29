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
 * @file    mlsAgps.h
 * @brief   C header - Implement A-GPS feature.
 *
 * Long description.
 * @date    10/10/2017
 * @author  Alvin Nguyen - alvin.nguyen@styl.solutions
 */

#ifndef MLSAGPS_H_INCLUDED
#define MLSAGPS_H_INCLUDED
#ifdef __cplusplus
extern "C"
{
#endif

/********** Include section ***************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <glib-object.h>

/********** Constant and compile switch definition section ********************/
/********** Type definition section *******************************************/
/********** Macro definition section*******************************************/
#define DATA_NAME "stylagps.conf"

/********** Function declaration section **************************************/
gint            mlsAgps_GetLocation(GObject * nm_client, gdouble *latitude, gdouble *longitude, gdouble *accuracy);

GObject *       mlsAgps_Init();

void            mlsAgps_Finalize(GObject * nm_client);

const gchar *   mlsAgps_GetVersion(void);

#ifdef __cplusplus
}
#endif
#endif // MLSAGPS_H_INCLUDED
/*@}*/
