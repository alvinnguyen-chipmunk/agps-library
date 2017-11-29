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
 * @file    mlsAgpsUtils.h
 * @brief   C code - Implement some utils of A-GPS feature.
 *
 * Long description.
 * @date    10/10/2017
 * @author  Alvin Nguyen - alvin.nguyen@styl.solutions
 */

#ifndef MLSAGPSUTILS_H_INCLUDED
#define MLSAGPSUTILS_H_INCLUDED
#ifdef __cplusplus
extern "C"
{
#endif

/********** Include section ***************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <string.h>

/********** Constant and compile switch definition section ********************/
/********** Type definition section *******************************************/
/********** Macro definition section*******************************************/
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define STYL_INFO(format, ...)  \
    mlsAgpsUtils_Print(0, "%s[STYL INFO]: " format " %s\n", ANSI_COLOR_BLUE, ##__VA_ARGS__, ANSI_COLOR_RESET);

#define STYL_INFO_1(format, ...)  \
    mlsAgpsUtils_Print(0, "%s[STYL INFO]: " format " %s\n", ANSI_COLOR_GREEN, ##__VA_ARGS__, ANSI_COLOR_RESET);

#define STYL_ERROR(format, ...) \
    mlsAgpsUtils_Print(1, "%s[STYL ERROR]: " format " %s\n", ANSI_COLOR_RED, ##__VA_ARGS__, ANSI_COLOR_RESET);

#define STYL_WARNING(format, ...)  \
    mlsAgpsUtils_Print(0, "%s[STYL WARNING]: " format " %s\n", ANSI_COLOR_YELLOW, ##__VA_ARGS__, ANSI_COLOR_RESET);

#define STYL_DEBUG(format, ...)  \
    mlsAgpsUtils_Print(0, "%s[STYL DEBUG]: " format " %s\n", ANSI_COLOR_CYAN, ##__VA_ARGS__, ANSI_COLOR_RESET);

/********** Function declaration section **************************************/
/*!
 * \brief mlsAgpsUtils_ParseData: Parse data of message response of location
 */
gint mlsAgpsUtils_ParseData(gchar *data,
                             gdouble **longitude,
                             gdouble **latitude,
                             gdouble **accuracy);

/*!
 * \brief mlsAgpsUtils_Print: Print out some information.
 */
void mlsAgpsUtils_Print(gint isError, gchar *format, ...);

#ifdef __cplusplus
}
#endif
#endif // MLSAGPSUTILS_H_INCLUDED
/*@}*/
