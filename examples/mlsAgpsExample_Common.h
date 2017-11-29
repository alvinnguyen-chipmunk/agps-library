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
 * @file    mlsAgpsExample_Common.h
 * @brief   C header for some macro will use on example application of A-GPS feature.
 *
 * Long description.
 * @date    10/10/2017
 * @author  Alvin Nguyen - alvin.nguyen@styl.solutions
 */

#ifndef MLSAGPSEXAMPLE_COMMON_H_INCLUDED
#define MLSAGPSEXAMPLE_COMMON_H_INCLUDED
#ifdef __cplusplus
extern "C"
{
#endif

/********** Include section ***************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

/********** Constant and compile switch definition section ********************/
/********** Type definition section *******************************************/
/********** Macro definition section*******************************************/
#define ANSI_COLOR_RED     "\x1b[1;31m"
#define ANSI_COLOR_GREEN   "\x1b[1;32m"
#define ANSI_COLOR_YELLOW  "\x1b[1;33m"
#define ANSI_COLOR_BLUE    "\x1b[1;34m"
#define ANSI_COLOR_MAGENTA "\x1b[1;35m"
#define ANSI_COLOR_CYAN    "\x1b[1;36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define STYL_SHOW(format, ...)  \
    mlsAgpsExampleCommon_Print(1, "%s[STYL AGPS INFO]: " format " %s\n", ANSI_COLOR_BLUE, ##__VA_ARGS__, ANSI_COLOR_RESET);

#define STYL_SHOW_1(format, ...)  \
    mlsAgpsExampleCommon_Print(1, "%s[STYL AGPS INFO]: " format " %s\n", ANSI_COLOR_GREEN, ##__VA_ARGS__, ANSI_COLOR_RESET);

#define STYL_SHOW_2(format, ...)  \
    mlsAgpsExampleCommon_Print(1, "%s[STYL AGPS  INFO]: " format " %s\n", ANSI_COLOR_YELLOW, ##__VA_ARGS__, ANSI_COLOR_RESET);

#define STYL_INFO(format, ...)  \
    mlsAgpsExampleCommon_Print(0, "%s[STYL AGPS INFO]: " format " %s\n", ANSI_COLOR_BLUE, ##__VA_ARGS__, ANSI_COLOR_RESET);

#define STYL_INFO_1(format, ...)  \
    mlsAgpsExampleCommon_Print(0, "%s[STYL AGPS INFO]: " format " %s\n", ANSI_COLOR_GREEN, ##__VA_ARGS__, ANSI_COLOR_RESET);

#define STYL_ERROR(format, ...) \
    mlsAgpsExampleCommon_Print(1, "%s[STYL AGPS ERROR]: " format " %s\n", ANSI_COLOR_RED, ##__VA_ARGS__, ANSI_COLOR_RESET);

#define STYL_WARNING(format, ...)  \
    mlsAgpsExampleCommon_Print(0, "%s[STYL AGPS WARNING]: " format " %s\n", ANSI_COLOR_YELLOW, ##__VA_ARGS__, ANSI_COLOR_RESET);

#define STYL_DEBUG(format, ...)  \
    mlsAgpsExampleCommon_Print(0, "%s[STYL AGPS DEBUG]: " format " %s\n", ANSI_COLOR_CYAN, ##__VA_ARGS__, ANSI_COLOR_RESET);

#define QUEUE_NAME  "/test_queue"
#define MAX_SIZE    1024
#define MSG_STOP    "exit"

#define AGPS_QUEUE_NAME  "/stylagps_queue"

#define AGPS_DATA_FILE  "/tmp/stylagps.data"

#define AGPS_FREQ_SEC   3000000

#define CHECK(x) \
    do { \
        if (!(x)) { \
            fprintf(stderr, "\x1b[31m %s:%d:", __func__, __LINE__); \
            perror(#x); \
            fprintf(stderr, "\x1b[0m"); \
            exit(-1); \
        } \
    } while (0) \

#define errExit(msg)    do { fprintf(stderr, "\x1b[31m"); \
                             perror(msg); exit(EXIT_FAILURE); \
                             fprintf(stderr, "\x1b[0m"); \
                           } while (0)

/********** Function declaration section **************************************/
/*!
 * \brief mlsAgpsExampleCommon_Print: Print out some information.
 */
void mlsAgpsExampleCommon_Print(int isError, char *format, ...);


#ifdef __cplusplus
}
#endif
#endif // MLSAGPSEXAMPLE_COMMON_H_INCLUDED
/*@}*/
