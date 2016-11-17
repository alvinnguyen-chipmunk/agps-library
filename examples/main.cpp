//
//  main.c
//  libstyl_agps
//
//  Created by Hoàng Trung Huy on 11/7/16.
//  Copyright © 2016 Hoàng Trung Huy. All rights reserved.
//

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
