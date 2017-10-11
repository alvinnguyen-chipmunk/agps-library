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
/********** Constant and compile switch definition section ********************/
/********** Type definition section *******************************************/
/********** Macro definition section*******************************************/
#define QUEUE_NAME  "/test_queue"
#define MAX_SIZE    1024
#define MSG_STOP    "exit"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

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

#ifdef __cplusplus
}
#endif
#endif // MLSAGPSEXAMPLE_COMMON_H_INCLUDED
/*@}*/
