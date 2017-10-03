#include "mlsAgpsJson.h"
#include "mlsAgpsUtils.h"
#include "mlsAgpsNM.h"

////////////////////////////////////////////////////////////////////////////

static void styl_agps_json_append(gpointer data, gpointer userdata);

////////////////////////////////////////////////////////////////////////////

gchar *styl_agps_json_new(GObject * nm_client)
{
    gchar * json_string = NULL;
    gchar * buffer      = NULL;

    GSList * access_point_list = styl_agps_nm_get_ap_list(nm_client);

    if(access_point_list)
    {
        json_string = g_strdup("{\n \"wifiAccessPoints\":\n [");
        g_slist_foreach(access_point_list, styl_agps_json_append, (gpointer)&json_string);
        buffer = g_strdup_printf("%s\n%s", json_string, " ]\n}");
        g_free(json_string);
        json_string = buffer;
    }
    styl_agps_nm_free_ap_list(access_point_list);

    return json_string;
}

static void styl_agps_json_append(gpointer data, gpointer userdata)
{
    gchar **json_string = (gchar **)userdata;
    gchar * str = (gchar *) data;
    gchar * buffer = NULL;
    buffer = g_strdup_printf("%s\n%s", *json_string, str);
    g_free(*json_string);
    *json_string=NULL;
    *json_string = buffer;
}
