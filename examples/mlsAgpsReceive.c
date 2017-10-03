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
#include "mlsAgpsExample_Common.h"

static int run = 1;

void HandleSignal(int sig);

int main(int argc, const char * argv[])
{

    double longitude = 0;
    double latitude = 0;
    double accuracy = 0;
    int ret = 0;
    int fd = 0;
    char space = 0;

    signal(SIGINT, HandleSignal);

    while(run)
    {
        fd = open(AGPS_DATA_FILE, O_RDONLY);
        if(fd > 0)
        {
            int retValue = read(fd, &longitude, sizeof(longitude));
            retValue = read(fd, &space, 1);
            retValue = read(fd, &latitude, sizeof(latitude));
            retValue = read(fd, &space, 1);
            retValue = read(fd, &accuracy, sizeof(accuracy));

            close(fd);
            remove(AGPS_DATA_FILE);

            printf("RECEIVE [Lng: %f\tLat: %f\tAcc: %f]\n", longitude, latitude, accuracy);
        }
        usleep(AGPS_FREQ_SEC);
    }

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
