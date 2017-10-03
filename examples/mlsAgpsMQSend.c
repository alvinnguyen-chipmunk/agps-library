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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <mqueue.h>
#include <string.h>
#include <glib.h>
#include <glib-object.h>
#include <mlsAgps.h>
#include "mlsAgpsExample_Common.h"

#define DEFAULT_UPDATE_FREQUENCY_USEC        3000000

static int run = 1;

void HandleSignal(int sig);

int main(int argc, const char * argv[])
{

    double longitude = 0;
    double latitude = 0;
    double accuracy = 0;
    int ret = 0;
    int fd = 0;
    int msgLength = 0;
    mqd_t mq;

    char buffer[MAX_SIZE];

    struct mq_attr attr;

    mq = mq_open(AGPS_QUEUE_NAME, O_RDWR);

    CHECK((mqd_t)-1 != mq);

    memset(buffer, '\0', sizeof(buffer));

    printf("%s Version: %s %s\n", ANSI_COLOR_MAGENTA, StylAgpsGetVersion(), ANSI_COLOR_RESET);

    signal(SIGINT, HandleSignal);

    GObject * nm_client = StylAgpsInit();

    while(run)
    {
        if (mq_getattr(mq, &attr) == -1)
        {
            errExit("mq_getattr");
        }

        while(attr.mq_curmsgs)
        {
            ssize_t bytes_read;
            bytes_read = mq_receive(mq, buffer, MAX_SIZE, NULL);
            if (bytes_read > 0)
            {
                sscanf(buffer, "%lf %lf %lf", &longitude, &latitude, &accuracy);
                printf("%s REMOVE from '%s' Lng: %f - Lat: %f - Acc: %f %s\n",
                       ANSI_COLOR_RED, AGPS_QUEUE_NAME, longitude, latitude, accuracy, ANSI_COLOR_RESET);
                attr.mq_curmsgs--;
                memset(buffer, '\0', MAX_SIZE);
            }
        }

        ret = StylAgpsGetLocation(nm_client, &latitude, &longitude, &accuracy);

        if (EXIT_SUCCESS == ret)
        {
            sprintf(buffer, "%lf %lf %lf", longitude, latitude, accuracy);

            msgLength = strnlen(buffer, MAX_SIZE);

            mq_send(mq, buffer, msgLength, 0);

            printf("%s stylAgpsMQSend (Lng Lat Acc): %s %s\n", ANSI_COLOR_GREEN, buffer, ANSI_COLOR_RESET);

            memset(buffer, '\0', msgLength);
        }
        usleep(AGPS_FREQ_SEC);
    }

    /* cleanup */
    CHECK((mqd_t)-1 != mq_close(mq));

    StylAgpsFinalize(nm_client);

    return ret;
}

void HandleSignal(int sig)
{
    if (sig == SIGINT)
    {
        printf("%s Stop stylagps_demo. Thank you for using STYL demos! %s\n", ANSI_COLOR_YELLOW, ANSI_COLOR_RESET);
        run = 0;
    }
}
