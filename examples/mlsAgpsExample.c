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
 * @file    mlsAgpsExample.c
 * @brief   C code - Implement example application for A-GPS feature.
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
#include <glib-object.h>
#include <unistd.h>
#include <signal.h>

#include <mlsAgps.h>

/********** Local Constant and compile switch definition section **************/
/********** Local Type definition section *************************************/
/********** Local Macro definition section ************************************/
#define TIME_SLEEP 3

/********** Local (static) variable definition ********************************/
static gint LOOP_COUNT = 10000;
static gint run = 1;

/********** Local (static) function declaration section ***********************/
static void HandleSignal(gint sig);

/********** Local function definition section *********************************/
static void HandleSignal(gint sig)
{
    if (sig == SIGINT)
    {
        printf("\nStop stylagps_demo. Thank you for using STYL demos!\n");
        run = 0;
    }
}

/********** Global function definition section ********************************/
gint main(int argc, const char * argv[])
{
    gdouble longitude = 0;
    gdouble latitude = 0;
    gdouble accuracy = 0;
    gint ret = EXIT_FAILURE;

    signal(SIGINT, HandleSignal);

    GObject * nm_client = StylAgpsInit();

    printf(" \x1b[35m ** Version: %s ** \x1b[0m \n", StylAgpsGetVersion());

    g_return_val_if_fail(nm_client, EXIT_FAILURE);

    printf("\n \x1b[32m ************************************ \x1b[0m \n");

    while(LOOP_COUNT)
    {
        if(run==0)
            break;

        printf(" \x1b[33m Running [#%d]... \x1b[0m \n", LOOP_COUNT);

        ret = StylAgpsGetLocation(nm_client, &latitude, &longitude, &accuracy);

        if (EXIT_SUCCESS == ret)
        {
            printf(" \x1b[34m => AGPS: \n        Latitude: %.8f Longitude: %.8f Accuracy: %.8f \x1b[0m \t\n",
                       latitude, longitude, accuracy);
        }
        else
        {
            printf(" \x1b[31m Cannot query locaion. Retry with debug option to get more information. \x1b[0m");
        }
        sleep(TIME_SLEEP);
        LOOP_COUNT--;

        printf("\n \x1b[32m ************************************ \x1b[0m \n");
    }

    StylAgpsFinalize(nm_client);

    return EXIT_SUCCESS;
}

#ifdef __cplusplus
}
#endif
/*@}*/
