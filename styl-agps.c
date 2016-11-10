//
//  libstyl_agps.c
//  libstyl_agps
//
//  Created by Hoàng Trung Huy on 11/7/16.
//  Copyright © 2016 Hoàng Trung Huy. All rights reserved.
//

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#include "styl-agps.h"

#include <curl/curl.h>
#include <json-c/json.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <string.h>

#define JSON_BUFFER		100000
#define DEFAULT_JSON_FILE	"/data/workspace/agps/styl-agps.json"


static int CallBackWrite(void* buf, size_t len, size_t size, void* userdata);
static void ExportLocation(char *httpData, double *longitude, double *latitude, double *accuracy);

int StylAgpsGetLocation(double *longitude, double *latitude, double *accuracy)
{
	const char *url = "https://www.googleapis.com/geolocation/v1/geolocate?key=AIzaSyBx6LZQwV-73Z_LtJLXvcnpUMJpCIaCR6g";
	const char *jsonFile = getenv("STYL_AGPS_FILE");
	char jsonString[JSON_BUFFER];
	char httpData[JSON_BUFFER];
	char *stylDebug = getenv("STYL_DEBUG");

	/* Response information. */
	int httpCode = 0;

	CURL* curl = curl_easy_init();

	/* Set remote URL. */
	curl_easy_setopt(curl, CURLOPT_URL, url);

	struct curl_slist *headers = NULL;
	headers = curl_slist_append(headers, "content-type: application/json");
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

	if (NULL == jsonFile)
	{
		jsonFile = (char *)DEFAULT_JSON_FILE;
	}
	memset(jsonString, '\0', JSON_BUFFER);
	ReadFullFile(jsonFile, jsonString);
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonString);

	/* Don't bother trying IPv6, which would increase DNS resolution time. */
	curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);

	/* Don't wait forever, time out after 10 seconds. */
	curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);

	/* Follow HTTP redirects if necessary. */
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

	/* Hook up data handling function. */
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CallBackWrite);

	/* Hook up data container (will be passed as the last parameter to the
	 * callback handling function).  Can be any pointer type, since it will
	 * internally be passed as a void pointer.
	 */
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, httpData);

	/* Run our HTTP GET command, capture the HTTP response code, and clean up. */
	curl_easy_perform(curl);
	curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
	curl_easy_cleanup(curl);

	if (httpCode == 200)
	{
		printf("Got successful response from %s\n", url);
		if (NULL != stylDebug)
		{
			printf("STYL_DEBUG: %s: httpData: \n%s\n",__func__, httpData);
		}
		ExportLocation(httpData, longitude, latitude, accuracy);
	}
	else
	{
		printf("Couldn't GET from %s  - exiting\n", url);
		return 1;
	}
	
	return 0;
}

static int ReadFullFile(const char* fileName, char *buffer)
{
	int ret = EXIT_SUCCESS;
	int fd = 0;
	struct stat fdStat;
	void *fmap = NULL;

	fd = open(fileName, O_RDONLY);
	if (fd <= 0)
	{
		perror(fileName);
		ret = EXIT_FAILURE;
		goto EXIT;
	}
	ret = fstat(fd, &fdStat);
	if (ret)
	{
		perror("STAT");
		ret = EXIT_FAILURE;
		goto EXIT;
	}

	/* Read json file into memory */
	fmap = mmap(NULL, fdStat.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	if (NULL == fmap)
	{
		perror("MMAP");
		ret = EXIT_FAILURE;
		goto EXIT;
	}

	memcpy(buffer, fmap, fdStat.st_size);
	
	close(fd);
	
EXIT:
	return ret;
}

static int CallBackWrite(void* buffer, size_t len, size_t size, void* userData) {
	size_t sLen;

	if (len * size > 0)
	{
		sLen = strnlen((char *)userData, JSON_BUFFER);

		strncpy(&((char*)userData)[sLen], (char*)buffer, (len * size));
	}

	return (int)(len * size);
}

static void ExportLocation(char *httpData, double *longitude, double *latitude, double *accuracy)
{
	char *stylDebug = getenv("STYL_DEBUG");
	size_t httpDataLen = 0;
	struct json_object *base_t = json_object_new_object();
	struct json_tokener *tok = json_tokener_new();
	int jerr = 0;

	if (NULL != stylDebug)
	{
		printf("STYL_DEBUG: %s: httpData: \n%s\n",__func__, httpData);
	}

	do
	{
		httpDataLen = strnlen(httpData, (size_t) JSON_BUFFER);
		base_t = json_tokener_parse_ex(tok, httpData, (int) httpDataLen);
		jerr = json_tokener_get_error(tok);
	}
	while (json_tokener_continue == jerr);

	if (json_tokener_success != jerr)
	{
		printf("ERROR: %s: parse failed\n", __func__);
		return;
	}

	struct json_object *location_t = json_object_new_object();
	struct json_object *accuracy_t = json_object_new_object();
	struct json_object *longitude_t = json_object_new_object();
	struct json_object *latitude_t = json_object_new_object();

	json_object_object_get_ex(base_t, "location", &location_t);
	json_object_object_get_ex(base_t, "accuracy", &accuracy_t);
	json_object_object_get_ex(location_t, "lng", &longitude_t);
	json_object_object_get_ex(location_t, "lat", &latitude_t);

	*longitude = json_object_get_double(longitude_t);
	*latitude = json_object_get_double(latitude_t);
	*accuracy = json_object_get_double(accuracy_t);

	if (NULL != stylDebug)
	{
		printf("STYL_DEBUG: %s: Lng %f - Lat %f - Acc %f\n", __func__, *longitude, *latitude, *accuracy);
	}
}

static int ParseConfig(char *buffer, const int bufferLen, node_t *paramList )
{
	int paramCount = 0;
	int pos = 0;

	if (NULL == buffer)
	{
		printf("ERROR: parse buffer is null\n");
		goto EXIT;
	}

	paramCount = 0;
	pos = 0;
	for (int i = 0; i < bufferLen; i++)
	{
		switch (buffer[i])
		{
			case '=':
				memset(paramList[paramCount].key, '\0', DATA_LEN);
				memcpy(paramList[paramCount].key, &buffer[pos], (i-pos));
				pos = i + 1;
				break;

			case '\n':
				memset(paramList[paramCount].value, '\0', DATA_LEN);
				memcpy(paramList[paramCount].value, &buffer[pos], (i-pos));
				pos = i + 1;
				paramCount++;
				break;

			default:
				break;
		}
		
	}
	
EXIT:
	return paramCount;
}

#ifdef __cplusplus
}
#endif /* __cplusplus */
