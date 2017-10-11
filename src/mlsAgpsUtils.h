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

#ifdef __RELEASE__
#define __DEBUG__(format, ...)
#else
#define __DEBUG__(format, ...) fprintf(stderr, "%s", ANSI_COLOR_RESET); fprintf (stderr, format, ## __VA_ARGS__)
#endif // __RELEASE__
#define DEBUG_BEGIN(format, args...) __DEBUG__("[STYLAGPS-DEBUG]: %s||%s():[%d] " format ": ",__FILE__,__FUNCTION__, __LINE__, ##args)
#define DEBUG_END(format, args...) __DEBUG__(format "\n", ##args)
#define DEBUG(format, args...) __DEBUG__("[STYLAGPS-DEBUG]: %s||%s():[%d] " format "\n",__FILE__,__FUNCTION__, __LINE__, ##args)
#define DEBUG_1(format, ...) DEBUG("\n"      format, ##__VA_ARGS__)
#define DEBUG_0() DEBUG("\n")
#define STYL_DEBUG(format, ...) DEBUG(format, ##__VA_ARGS__)

#define STYL_DEBUG_BEGIN(format, ...) DEBUG_BEGIN(format, ##__VA_ARGS__)
#define STYL_DEBUG_END(format, ...) DEBUG_END(format, ##__VA_ARGS__)


#define __ERROR__(format, ...) fprintf (stderr, format, ## __VA_ARGS__) ; fprintf(stderr, "%s", ANSI_COLOR_RESET)
#define ERROR(format, args...) __ERROR__("%s [STYLAGPS-ERROR]: %s():[%d] " format "%s \n",ANSI_COLOR_RED, __FUNCTION__, __LINE__, ##args, ANSI_COLOR_RED)
#define STYL_ERROR(format, ...) ERROR(format, ##__VA_ARGS__)
#define STYL_ERROR_INLINE(format, ...) __ERROR__("%s" format "%s", ANSI_COLOR_RED, ##__VA_ARGS__, ANSI_COLOR_RED)

#ifndef __CONSOLE__
#define __WARNING__(format, ...)
#else
#define __WARNING__(format, ...) fprintf (stderr, format, ## __VA_ARGS__); fprintf(stderr, "%s", ANSI_COLOR_RESET)
#endif // __CONSOLE__
#define WARNING(format, args...) __WARNING__("%s [STYLAGPS-WARNING]: %s():[%d] " format "%s \n",ANSI_COLOR_YELLOW, __FUNCTION__, __LINE__, ##args, ANSI_COLOR_YELLOW)
#define STYL_WARNING(format, ...) WARNING(format, ##__VA_ARGS__)
#define STYL_WARNING_INLINE(format, ...) __WARNING__("%s" format "%s", ANSI_COLOR_YELLOW, ##__VA_ARGS__, ANSI_COLOR_YELLOW)

#ifndef __CONSOLE__
#define __INFO__(format, ...)
#else
#define __INFO__(format, ...) fprintf (stdout, format, ## __VA_ARGS__); fprintf(stdout, "%s", ANSI_COLOR_RESET)
#endif // __CONSOLE__
#define INFO(format, args...) __INFO__("%s [STYLAGPS-INFO]: %s():[%d] " format "%s \n",ANSI_COLOR_GREEN, __FUNCTION__, __LINE__, ##args, ANSI_COLOR_GREEN)
#define STYL_INFO(format, ...) INFO(format, ##__VA_ARGS__)
#define STYL_INFO_INLINE(format, ...) __INFO__("%s" format "%s", ANSI_COLOR_GREEN, ##__VA_ARGS__, ANSI_COLOR_GREEN)
#define STYL_INFO_OTHER(format, ...) __INFO__("%s" format "%s", ANSI_COLOR_BLUE, ##__VA_ARGS__, ANSI_COLOR_BLUE)

/********** Function declaration section **************************************/
gint styl_agps_utils_data_parse(gchar *data,
                                gdouble **longitude, gdouble **latitude, gdouble **accuracy);

#ifdef __cplusplus
}
#endif
#endif // MLSAGPSUTILS_H_INCLUDED
/*@}*/
