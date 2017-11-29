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
 * @file    mlsAgpsNM.h
 * @brief   C code - Implement NetworkManager processing of A-GPS feature.
 *
 * Long description.
 * @date    10/10/2017
 * @author  Alvin Nguyen - alvin.nguyen@styl.solutions
 */

#ifndef MLSAGPSNM_H_INCLUDED
#define MLSAGPSNM_H_INCLUDED
#ifdef __cplusplus
extern "C"
{
#endif

/********** Include section ***************************************************/
#include <dbus/dbus-glib.h>
#include <nm-client.h>
#include <nm-device.h>
#include <nm-device-wifi.h>

/********** Constant and compile switch definition section ********************/
/********** Type definition section *******************************************/
/********** Macro definition section*******************************************/
/********** Function declaration section **************************************/
NMClient *      mlsAgpsNM_GetNMClient();

GSList *        mlsAgpsNM_GetAPList(GObject * nm_client);

void            mlsAgpsNM_FreeAPList(GSList * access_point_list);

void            mlsAgpsNM_FreeAll(GObject *nm_client);


#ifdef __cplusplus
}
#endif
#endif // MLSAGPSNM_H_INCLUDED
/*@}*/
