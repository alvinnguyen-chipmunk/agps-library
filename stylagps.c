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

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#include "stylagps.h"
#include "stylAgpsUtils.h"

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
#include <assert.h>

#ifndef STYL_SW_VERSION
#define STYL_SW_VERSION     "1.2"
#endif

static int CallBackWrite(void* buf, size_t len, size_t size, void* userdata);
static void ExportLocation(char *httpData, double *longitude, double *latitude, double *accuracy);
static int ParseConfig(char *buffer, const int bufferLen, node_t *paramDict);
static int GetValueFromKey(node_t *paramDict, const char* key, char *value);
static int ReadFile(const char* fileName, char *buffer);

int StylAgpsGetLocation(double *longitude, double *latitude, double *accuracy)
{
	char url[URL_LEN];
	char jsonString[JSON_BUFFER_LEN];
	char httpData[JSON_BUFFER_LEN];
	char keyAPI[PARAM_LEN];
	char *stylDebug = getenv("STYL_DEBUG");
	char confBuffer[BUFFER_LEN];
	char tmp[PARAM_LEN];	// to be used to read non-char key
	node_t paramDict[MAX_PARAM_NODE];
	int ret = EXIT_SUCCESS;
	unsigned int timeoutSec = DEFAULT_TIME_SEC;
	CURL* curl;

	/* Initialize all arrays */
	memset(url, '\0', sizeof(url));
	memset(httpData, '\0', sizeof(httpData));
	memset(keyAPI, '\0', sizeof(keyAPI));
	memset(confBuffer, '\0', sizeof(confBuffer));

	/* Read stylagps.conf */
	ret = ReadFile(CONFIG_FILE, confBuffer);
	if (ret)
	{
		printf("ERROR: %s: line %d\n", __func__, __LINE__);
		goto EXIT;
	}

	ret = ParseConfig(confBuffer, sizeof(confBuffer), paramDict);
	if (ret <= 0)
	{
		printf("ERROR: No param found. Please check /etc/stylagps/stylagps.conf");
		goto EXIT;
	}

	/* Read Geo Location URL from CONFIG_FILE */
	ret = GetValueFromKey(paramDict, "geoLocationURL", url);
	if (ret)
	{
		printf("ERROR: %s: line %d: geoLocationURL is not found in %s\n", __func__, __LINE__, CONFIG_FILE);
		goto EXIT;
	}
	if (stylDebug)
	{
		printf("DEBUG: url: %s\n", url);
	}

	/* Read Key API from CONFIG_FILE */
	ret = GetValueFromKey(paramDict, "keyAPI", keyAPI);
	if (ret)
	{
		printf("ERROR: %s: line %d: keyAPI is not found in %s\n", __func__, __LINE__, CONFIG_FILE);
		goto EXIT;
	}
        memcpy(&url[strlen(url)], "key=", 4);
        memcpy(&url[strlen(url)], keyAPI, strlen(keyAPI));

	if (stylDebug)
	{
		printf("DEBUG: url: %s\n", url);
	}

	/* Read timeoutSec (SEC) from CONFIG_FILE */
	ret = GetValueFromKey(paramDict, "timeoutSec", tmp);
	if (ret)
	{
		if (stylDebug)
		{
			printf("No <timeoutSec> in %s. Using default 10 sec\n", CONFIG_FILE);
		}
		timeoutSec = DEFAULT_TIME_SEC;
	}
	else
	{
		timeoutSec = (unsigned int)atoi(tmp);
	}

	/* Response information. */
	int httpCode = 0;

	curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();

	/* Set remote URL. */
	curl_easy_setopt(curl, CURLOPT_URL, url);

	struct curl_slist *headers = NULL;
	headers = curl_slist_append(headers, "content-type: application/json");
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

	/* Read WiFi neighbors from stylagps.json */
	memset(jsonString, '\0', sizeof(jsonString));
        ret = CreateJsonStringListAP(jsonString, sizeof(jsonString));
        if (ret)
        {
                goto EXIT;
        }

	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonString);

	/* Don't bother trying IPv6, which would increase DNS resolution time. */
	curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);

	/* Don't wait forever, time out after timeoutSec seconds. */
	curl_easy_setopt(curl, CURLOPT_TIMEOUT, timeoutSec);

	/* Follow HTTP redirects if necessary. */
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

	/* Hook up data handling function. */
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CallBackWrite);

	/* force a new connection to be used */
	curl_easy_setopt(curl, CURLOPT_FRESH_CONNECT, 1);

	/* make connection get closed at once after use  */
	curl_easy_setopt(curl, CURLOPT_FORBID_REUSE, 1);

	/* Hook up data container (will be passed as the last parameter to the
	 * callback handling function).  Can be any pointer type, since it will
	 * internally be passed as a void pointer.
	 */
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, httpData);

	/* Run our HTTP GET command, capture the HTTP response code, and clean up. */
	curl_easy_perform(curl);
	curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);

	/* Free up mem */
	curl_slist_free_all(headers);
	curl_easy_cleanup(curl);
	curl_global_cleanup();

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
		ret = EXIT_FAILURE;
	}

EXIT:
	return ret;
}

static int ReadFile(const char* fileName, char *buffer)
{
	int ret = EXIT_SUCCESS;
	int fd = 0;
	struct stat fdStat;
	void *fmap = NULL;

	assert( (fileName != NULL) && (buffer != NULL) );

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
		perror("fstat");
		ret = EXIT_FAILURE;
		goto EXIT;
	}

	fmap = mmap(NULL, fdStat.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	if (NULL == fmap)
	{
		perror("mmap");
		ret = EXIT_FAILURE;
		goto EXIT;
	}

	memcpy(buffer, fmap, fdStat.st_size);
	ret = munmap(fmap, fdStat.st_size);
	if (ret)
	{
		perror("munmap");
		ret = EXIT_FAILURE;
		goto EXIT;
	}
EXIT:
	close(fd);
	return ret;
}

static int CallBackWrite(void* buffer, size_t len, size_t size, void* userData) {
	size_t sLen;

	assert( (buffer != NULL) && (userData != NULL)  );

	if (len * size > 0)
	{
		sLen = strnlen((char *)userData, (size_t) JSON_BUFFER_LEN);

		strncpy(&((char*)userData)[sLen], (char*)buffer, (len * size));
	}

	return (int)(len * size);
}

static void ExportLocation(char *httpData, double *longitude, double *latitude, double *accuracy)
{
	char *stylDebug = getenv("STYL_DEBUG");
	size_t httpDataLen = 0;
	struct json_object *base_t;
	struct json_tokener *tok = json_tokener_new();
	int jerr = 0;

	assert( (httpData != NULL) && (longitude != NULL) && (latitude != NULL) && (accuracy != NULL) );

	if (NULL != stylDebug)
	{
		printf("STYL_DEBUG: %s: httpData: \n%s\n",__func__, httpData);
	}

	do
	{
		httpDataLen = strnlen(httpData, (size_t) JSON_BUFFER_LEN);
		base_t = json_tokener_parse_ex(tok, httpData, (int) httpDataLen);
		jerr = json_tokener_get_error(tok);
	}
	while (json_tokener_continue == jerr);

	if (json_tokener_success != jerr)
	{
		printf("ERROR: %s: parse failed\n", __func__);
		goto EXIT;
	}
	else
	{
		json_tokener_free(tok);
	}

	struct json_object *location_t;
	struct json_object *accuracy_t;
	struct json_object *longitude_t;
	struct json_object *latitude_t;

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

EXIT:
	json_object_put(base_t);
	return;
}

static int ParseConfig(char *buffer, const int bufferLen, node_t *paramDict )
{
	int paramCount = 0;
	int pos = 0;

	assert( (buffer != NULL) && (paramDict != NULL) );

	if (NULL == buffer)
	{
		printf("ERROR: config content is null. Please check %s\n", CONFIG_FILE);
		goto EXIT;
	}

	paramCount = 0;
	pos = 0;
	for (int i = 0; i < bufferLen; i++)
	{
		switch (buffer[i])
		{
			case '=':
				memset(paramDict[paramCount].key, '\0', PARAM_LEN);
				memcpy(paramDict[paramCount].key, &buffer[pos], (i-pos));
				pos = i + 1;
				break;

			case '\n':
				memset(paramDict[paramCount].value, '\0', PARAM_LEN);
				memcpy(paramDict[paramCount].value, &buffer[pos], (i-pos));
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

static int GetValueFromKey(node_t *paramDict, const char* key, char *value)
{
	int ret = EXIT_FAILURE;
	assert( (paramDict != NULL) && (key != NULL) );

	for (int i = 0; i < MAX_PARAM_NODE; i++)
	{
		if ( 0 == strncmp(paramDict[i].key, key, PARAM_LEN) )
		{
			strncpy(value, paramDict[i].value, PARAM_LEN);
			ret = EXIT_SUCCESS;
			goto EXIT;
		}
	}

EXIT:
	return ret;
}

char *GetVersion(void)
{
	return STYL_SW_VERSION;
}

#ifdef __cplusplus
}
#endif /* __cplusplus */
