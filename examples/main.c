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
#include <pthread.h>
#include "stylagps.h"

static int run = 1;

void HandleSignal(int sig);
void *QueryLocation(void *threadID);

int main(int argc, const char * argv[]) {
        
        double longitude = 0;
        double latitude = 0;
        double accuracy = 0;
        unsigned long long i = 0;
        pthread_t threads;
        int ret = 0;
        int rc = 0;
        
        printf("Version: %s\n", GetVersion());
        
        signal(SIGINT, HandleSignal);
        
        
//        for (int i = 0; i < 4; i++)
//        {
                rc = pthread_create(&threads, NULL, QueryLocation, NULL);
                if (rc)
                {
                        printf("ERROR: return code from pthread_create() is %d\n", rc);
                        exit(-1);
                }
//        }
        
        while(run)
        {
                sleep(1);
        }
        
        pthread_exit(NULL);
        
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

void *QueryLocation(void *threadID)
{
        double longitude = 0;
        double latitude = 0;
        double accuracy = 0;
        int ret = 0;
        while(run)
        {
                ret = StylAgpsGetLocation(&longitude, &latitude, &accuracy);
                
                if (EXIT_SUCCESS == ret)
                {
                        printf("[SUB]Lng: %f\tLat: %f\tAcc: %f\t\n", longitude, latitude, accuracy);
                }
                sleep(3);
        }
        pthread_exit(NULL);
}
