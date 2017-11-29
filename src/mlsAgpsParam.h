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
 * @file    mlsAgpsParam.h
 * @brief   C code - Implement parameter processing of A-GPS feature.
 *
 * Long description.
 * @date    10/10/2017
 * @author  Alvin Nguyen - alvin.nguyen@styl.solutions
 */

#ifndef MLSAGPSPARAM_H_INCLUDED
#define MLSAGPSPARAM_H_INCLUDED
#ifdef __cplusplus
extern "C"
{
#endif

/********** Include section ***************************************************/
/********** Constant and compile switch definition section ********************/
/********** Type definition section *******************************************/
/********** Macro definition section*******************************************/
#define PARAM_NUMBER            4

#define MLS_AGPS_PARAM_TIMEOUT           "googleRequestTimeoutSec"
#define MLS_AGPS_PARAM_TIMEOUT_DEFAULT   10
#define MLS_AGPS_PARAM_URL               "geoLocationURL"
#define MLS_AGPS_PARAM_KEY               "keyAPI"
#define MLS_AGPS_FREQ_USEC               "agpsUpdateFrequencyUSec"

/********** Function declaration section **************************************/
GHashTable *    mlsAgpsParam_New(const gchar* filename);

void            mlsAgpsParam_Free(GHashTable * param_table);

void            mlsAgpsParam_Print(GHashTable * param_table);

gchar *         mlsAgpsParam_Key2Value(GHashTable * param_table, gchar * keyword);

#ifdef __cplusplus
}
#endif
#endif // MLSAGPSPARAM_H_INCLUDED
/*@}*/
