#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <curl/curl.h>
#include <string.h>

#include "styl_agps_query.h"
#include "styl_agps_param.h"
#include "styl_agps_utils.h"

////////////////////////////////////////////////////////////////////////////////////////////////

static size_t styl_agps_query_back_write(void *contents, size_t size, size_t nmemb, void *userp);

////////////////////////////////////////////////////////////////////////////////////////////////

gchar * styl_agps_query_exec(gchar * json_string, GHashTable * param_table)
{
    struct curl_slist *     curl_headers        = NULL;
    CURL*                   curl                = NULL;
    guint                   curl_timeout        = STYL_AGPS_PARAM_TIMEOUT_DEFAULT;
    gchar *                 buffer              = NULL;
    gchar *                 buffer_1            = NULL;
    gchar *                 curl_url            = NULL;
    gint                    curl_reponse_code   = 1;

    gboolean                can_execute         = FALSE;
    gchar *                 pcurl_reponse_data  = NULL;
    gchar                   curl_reponse_data[1024];
    gint                    res;

    if(json_string == NULL || param_table == NULL)
        return NULL;

    /* Global libcurl initialisation */
    curl_global_init(CURL_GLOBAL_ALL);

    /* Start a libcurl easy session */
    curl = curl_easy_init();

    /* Set options for a curl easy handle */
    /* CURLOPT_IPRESOLVE        specify which IP protocol version to use            */
    /* CURLOPT_FOLLOWLOCATION   follow HTTP 3xx redirects                           */
    /* CURLOPT_FRESH_CONNECT    force a new connection to be used                   */
    /* CURLOPT_FORBID_REUSE     make connection get closed at once after use        */
    /*                                                                              */
    /* CURLOPT_WRITEDATA        custom pointer passed to the write callback         */
    /* CURLOPT_WRITEFUNCTION    set callback for writing received data              */
    /* CURLOPT_HTTPHEADER       set custom HTTP headers                             */
    /* CURLOPT_POSTFIELDS       specify data to POST to server                      */
    /* CURLOPT_TIMEOUT          set maximum time the request is allowed to take     */
    /* CURLOPT_URL              provide the URL to use in the request               */

    /* Don't bother trying IPv6, which would increase DNS resolution time. */
    curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);

    /* Follow HTTP redirects if necessary. */
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

    /* force a new connection to be used */
    curl_easy_setopt(curl, CURLOPT_FRESH_CONNECT, 1);

    /* make connection get closed at once after use  */
    curl_easy_setopt(curl, CURLOPT_FORBID_REUSE, 1);

    /* Hook up data container (will be passed as the last parameter to the
     * callback handling function).  Can be any pointer type, since it will
     * internally be passed as a void pointer.
     */
    //curl_reponse_data = g_malloc(sizeof(gchar)*1024);
    //DEBUG_1("curl_reponse_data: %p", curl_reponse_data);
    memset(curl_reponse_data, 0, 1024);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)curl_reponse_data);

    /* Hook up data handling function. */
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, styl_agps_query_back_write);

    curl_headers = curl_slist_append(curl_headers, "content-type: application/json");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, curl_headers);

    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_string);

    /* Don't wait forever, time out after curl_timeout seconds. */
    buffer = styl_agps_param_key_to_value(param_table, STYL_AGPS_PARAM_TIMEOUT);
    if(buffer)
    {
        curl_timeout = (gint)g_ascii_strtoull (buffer, NULL, 10);
    }
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, curl_timeout);

    buffer = styl_agps_param_key_to_value(param_table, STYL_AGPS_PARAM_URL);
    buffer_1 = styl_agps_param_key_to_value(param_table, STYL_AGPS_PARAM_KEY);
    if(buffer!=NULL && buffer_1!=NULL)
    {
        can_execute = TRUE;
        curl_url = g_strdup_printf("%skey=%s", buffer, buffer_1);
        /* Set remote URL. */
        curl_easy_setopt(curl, CURLOPT_URL, curl_url);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    /* Run our HTTP GET command, capture the HTTP response code, and clean up. */
    res = curl_easy_perform(curl);
    DEBUG_1("\n************** curl_reponse_data: %s", curl_reponse_data);
    if(res != CURLE_OK)
    {
        fprintf(stderr, "curl_easy_perform() failed: %s\n",
                curl_easy_strerror(res));
    }
    else
    {
        pcurl_reponse_data = g_strdup(curl_reponse_data);
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &curl_reponse_code);
        if(curl_reponse_code != 200)
        {
            g_free(pcurl_reponse_data);
            pcurl_reponse_data=NULL;
            STYL_ERROR("Can't get from %s", curl_url);
        }
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////
    /* Free up memory */
    curl_easy_cleanup(curl);
    curl_slist_free_all(curl_headers);
    g_free(curl_url);
    curl_global_cleanup();

    return pcurl_reponse_data;
}

static size_t styl_agps_query_back_write(void *contents, size_t size, size_t nmemb, void * userp)
{
    gsize realsize = size * nmemb;
    if(realsize > 0)
    {
        if(realsize < 1024)
            g_strlcpy((gchar *)userp, (gchar *)contents, realsize);
        else
            return 0;
    }
    return realsize;
}
