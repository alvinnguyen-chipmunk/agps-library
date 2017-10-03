#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <string.h>

#include "styl_agps_param.h"
#include "styl_agps_utils.h"

//////////////////////////////////////////////////////////////////////////////////////////

static void styl_agps_param_print_core(gpointer key, gpointer value, gpointer userdata);
static void styl_agps_param_free_core(gpointer key, gpointer value, gpointer userdata);

//////////////////////////////////////////////////////////////////////////////////////////

GHashTable * styl_agps_param_new(const gchar* filename)
{
    FILE *fp = NULL;
    gchar buffer[255];

    g_return_val_if_fail(filename, NULL);

    STYL_DEBUG("Parameter file: %s", filename);

    GHashTable * param_table = NULL;
    param_table = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, NULL);

    fp = fopen(filename, "r");
    if(!fp)
        return NULL;

    for(gint i=0; i<PARAM_NUMBER; i++)
    {
        if(!feof(fp))
        {
            gchar ** token = NULL;
            memset(buffer, 0, 255);
            gint tmp = fscanf(fp, "%s", buffer);
            token = g_strsplit_set (buffer,"=",-1);
            if(g_strv_length(token)==2)
            {
                g_hash_table_insert(param_table, (gpointer )g_strdup(token[0]),(gpointer)g_strdup(token[1]));
            }
            g_strfreev(token);
        }
    }
    fclose(fp);
    fp=NULL;

    return param_table;
}

void styl_agps_param_free(GHashTable * param_table)
{
    if(param_table)
    {
        g_hash_table_foreach(param_table, styl_agps_param_free_core, NULL);
        g_hash_table_remove_all(param_table);
    }
}

void styl_agps_param_print(GHashTable * param_table)
{
    if(param_table)
        g_hash_table_foreach(param_table, styl_agps_param_print_core, NULL);
    else
        g_error("\nParameter is null.");
}

static void styl_agps_param_print_core(gpointer key, gpointer value, gpointer userdata)
{
    g_message("\n   Key: %s\n   Value: %s\n", (gchar *)key, (gchar *)value);
}

static void styl_agps_param_free_core(gpointer key, gpointer value, gpointer userdata)
{
    g_free((gchar *)key);
    g_free((gchar *)value);
    key=NULL;
    value=NULL;
}

gchar * styl_agps_param_key_to_value(GHashTable * param_table, gchar * keyword)
{
    gchar * value = NULL;
    if(g_hash_table_lookup_extended(param_table, (gconstpointer)keyword, NULL, (gpointer)&value))
    {
        return value;
    }
    return NULL;
}
