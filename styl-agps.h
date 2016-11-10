//
//  libstyl_agps.h
//  libstyl_agps
//
//  Created by Hoàng Trung Huy on 11/7/16.
//  Copyright © 2016 Hoàng Trung Huy. All rights reserved.
//

#ifndef libstyl_agps_h
#define libstyl_agps_h

#define BUFFER_LEN		5120		// ((255 + 1) x 2 ) x 10
#define DATA_LEN		255			// Supported path name

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

typedef struct _dict_node {
	char key[DATA_LEN];
	char value[DATA_LEN];
} node_t;

int ParseConfig(char *buffer, const int bufferLen, node_t *paramList);
int ReadFullFile(const char* jsonFile, char *jsonString);
int StylAgpsGetLocation(double *longitude, double *latitude, double *accuracy);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* libstyl_agps_h */
