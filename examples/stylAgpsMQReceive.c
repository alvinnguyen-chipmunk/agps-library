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
#include "common.h"

static int run = 1;

void HandleSignal(int sig);

int main(int argc, const char * argv[])
{

    double longitude = 0;
    double latitude = 0;
    double accuracy = 0;
    int ret = 0;
    int fd = 0;
    mqd_t mq;
    struct mq_attr attr;
    char buffer[MAX_SIZE];
    ssize_t bytes_read;
    mode_t omask;

    omask = umask(0);

    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = MAX_SIZE;
    attr.mq_curmsgs = 0;

    mq = mq_open(AGPS_QUEUE_NAME, O_CREAT | O_RDONLY | O_NOCTTY | O_SYNC, 0777, &attr);
    CHECK((mqd_t)-1 != mq);
    memset(buffer, '\0', MAX_SIZE);

    signal(SIGINT, HandleSignal);

    while(run)
    {
        bytes_read = mq_receive(mq, buffer, MAX_SIZE, NULL);
        if (bytes_read > 0)
        {
            sscanf(buffer, "%lf %lf %lf", &longitude, &latitude, &accuracy);
            printf("RECEIVED from '%s' Lng: %f - Lat: %f - Acc: %f\n", AGPS_QUEUE_NAME, longitude, latitude, accuracy);
            memset(buffer, '\0', MAX_SIZE);
        }
        usleep(AGPS_FREQ_SEC);
    }

    CHECK((mqd_t)-1 != mq_close(mq));
    CHECK((mqd_t)-1 != mq_unlink(AGPS_QUEUE_NAME));
    umask(omask);

    return ret;
}

void HandleSignal(int sig)
{
    if (sig == SIGINT)
    {
        printf("Stop stylagps_demo. Thank you for using STYL demos!\n");
        run = 0;
    }
}
