/*******************************************************************************
 (C) Copyright 2009 Styl Solutions Co., Ltd. , All rights reserved *
 *
 This source code and any compilation or derivative thereof is the sole *
 property of Styl Solutions Co., Ltd. and is provided pursuant to a *
 Software License Agreement. This code is the proprietary information *
 of Styl Solutions Co., Ltd and is confidential in nature. Its use and *
 dissemination by any party other than Styl Solutions Co., Ltd is *
 strictly limited by the confidential information provisions of the *
 Agreement referenced above. *
 ******************************************************************************/
#if 0

#include <stdio.h>
#include <stdlib.h>
#include "styl_agps_tmp.h"

/* Global variables */
static gint LOOP_COUNT = 500;

int main(int argc, char *argv[])
{
    GObject * client = tmp_init();
    if(client!=NULL)
    {
        while(LOOP_COUNT)
        {
            printf("\n");
            g_message("Running [%d]...", LOOP_COUNT);

            tmp_execute(client);

            sleep(1);
            LOOP_COUNT--;
        }
        tmp_free(client);
    }
    return EXIT_SUCCESS;
}

// Change Log:
// 23 Apr 2013        Galen        Created

#else

#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <glib-object.h>
#include <unistd.h>
#include <signal.h>

#include "stylagps.h"

#if 0
#define USING_THREAD
#else
#ifdef USING_THREAD
#undef USING_THREAD
#endif // USING_THREAD
#endif // 1

static gint LOOP_COUNT = 10000;
static gint run = 1;

#define TIME_SLEEP 3

#ifdef USING_THREAD
G_LOCK_DEFINE(run);
#endif // USING_THREAD

static void HandleSignal(gint sig)
{
    if (sig == SIGINT)
    {
        printf("\nStop stylagps_demo. Thank you for using STYL demos!\n");
#ifdef USING_THREAD
        G_LOCK (run);
#endif // USING_THREAD
        run = 0;
#ifdef USING_THREAD
        G_UNLOCK (run);
#endif // USING_THREAD
    }
}

#ifndef USING_THREAD

gint main(int argc, const char * argv[])
{
    gdouble longitude = 0;
    gdouble latitude = 0;
    gdouble accuracy = 0;
    gint ret = EXIT_FAILURE;

    signal(SIGINT, HandleSignal);

    GObject * nm_client = StylAgpsInit();

    printf("Version: %s\n", StylAgpsGetVersion());

    g_return_val_if_fail(nm_client, EXIT_FAILURE);

    printf("\n\n======================================================================\n\n");

    while(LOOP_COUNT)
    {
        if(run==0)
            break;

        g_message("Running [%d]...", LOOP_COUNT);

        ret = StylAgpsGetLocation(nm_client, &latitude, &longitude, &accuracy);

        if (EXIT_SUCCESS == ret)
        {
            g_message(" => Response: \n    Latitude: %.8f Longitude: %.8f Accuracy: %.8f\t\n", latitude, longitude, accuracy);
        }
        else
        {
            g_warning("Cannot query locaion. Retry with debug option to get more information.");
        }
        sleep(TIME_SLEEP);
        LOOP_COUNT--;

        printf("\n\n======================================================================\n\n");
    }

    StylAgpsFinalize(nm_client);

    return EXIT_SUCCESS;
}

#else

static gpointer *QueryLocation(gpointer *thread_arg);
static void HandleSignal(int sig);

int main(int argc, const char * argv[])
{
    unsigned long long i = 0;
    GThread * threads;

    signal(SIGINT, HandleSignal);

    threads = g_thread_new("agps_child_thread", (gpointer)QueryLocation, NULL);

    if (threads==NULL)
    {
        printf("ERROR: return code from g_thread_new()");
        exit(-1);
    }

    printf("\nJoining child thread ...\n");
    if (g_thread_join(threads) == 0)
    {
        printf("\nMain thread exit without error!\n");
        exit(EXIT_SUCCESS);
    }
    perror("\nThread join");
    printf("\nMain thread exit with a error!\n");
    exit(EXIT_FAILURE);

}

static gpointer *QueryLocation(gpointer *thread_arg)
{
    gdouble longitude = 0;
    gdouble latitude = 0;
    gdouble accuracy = 0;
    gint ret;

    while(LOOP_COUNT)
    {
        G_LOCK (run);
        if(run==0)
        {
            G_UNLOCK (run);
            break;
        }
        G_UNLOCK (run);

        ret = FALSE;
        ret = StylAgpsGetLocation(&longitude, &latitude, &accuracy);

        if (EXIT_SUCCESS == ret)
        {
            g_message("    => Response: \n                Latitude: %.8f Longitude: %.8f Accuracy: %.8f\t\n", latitude, longitude, accuracy);
        }
        else
        {
            g_warning("Cannot query locaion. Retry with debug option to get more information.");
        }
        sleep(1);
        LOOP_COUNT--;
    }

    printf("\nChild thread exit!\n");
    g_thread_exit(NULL);
}
#endif // 1

#endif
