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
 * @date    29/11/2017
 * @author  Alvin Nguyen - alvin.nguyen@styl.solutions
 */

#ifdef __cplusplus
extern "C"
{
#endif

/********** Include section ***************************************************/
#include "mlsAgpsExample_Common.h"

/********** Local Constant and compile switch definition section **************/
/********** Local Type definition section *************************************/
/********** Local Macro definition section ************************************/
/********** Local (static) variable definition ********************************/
/********** Local (static) function declaration section ***********************/
/********** Local function definition section *********************************/
/********** Global function definition section ********************************/
/*!
 * \brief mlsAgpsExampleCommon_Print: Print out some information.
 */
void mlsAgpsExampleCommon_Print(int isError, char *format, ...)
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
