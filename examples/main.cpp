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
#include "stylagps.h"

int main(int argc, const char * argv[]) {

	double longitude = 0;
	double latitude = 0;
	double accuracy = 0;
	int ret = 0;

	ret = StylAgpsGetLocation(&longitude, &latitude, &accuracy);

	if (EXIT_SUCCESS == ret)
	{
		printf("Lng: %f\nLat: %f\nAcc: %f\n", longitude, latitude, accuracy);
	}

    return ret;
}
