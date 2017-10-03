#include "styl_agps_utils.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static gboolean styl_agps_utils_data_parse_get(gchar ** tokens, const gchar * keyword, gdouble *container);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

gint styl_agps_utils_data_parse(gchar *data,
                                gdouble **latitude, gdouble **longitude, gdouble **accuracy)
{
    gint ret = EXIT_FAILURE;
    gdouble tmp1 = 0, tmp2 = 0, tmp3 = 0;

    gchar ** tokens = NULL;
    tokens = g_strsplit_set (data,"\n",-1);

    if(styl_agps_utils_data_parse_get(tokens, "\"lat\":", &tmp1) == TRUE)
        if(styl_agps_utils_data_parse_get(tokens, "\"lng\":", &tmp2) == TRUE)
            if(styl_agps_utils_data_parse_get(tokens, "\"accuracy\":", &tmp3) == TRUE)
            {
                **latitude  = tmp1;
                **longitude = tmp2;
                **accuracy  = tmp3;
                ret = EXIT_SUCCESS;
            }

    g_strfreev(tokens);

    return ret;
}

static gboolean styl_agps_utils_data_parse_get(gchar ** tokens, const gchar * keyword, gdouble *container)
{
    gchar * buffer = NULL;
    for(gint i=0; i<g_strv_length(tokens); i++)
    {
        buffer = g_strrstr(tokens[i], keyword);
        if(buffer)
        {
            gchar tmp[128];
            gint end;
            if(sscanf(tokens[i], "%*[^0-9]%s", (char *)&tmp)==1)
            {
                end = strlen(tmp)-1;
                if(tmp[end]==',')
                    tmp[end]='\0';
                *container = g_ascii_strtod(tmp, NULL);
                return TRUE;
            }
        }
    }
    return FALSE;
}
