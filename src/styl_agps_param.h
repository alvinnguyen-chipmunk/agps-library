#ifndef STYL_AGPS_PARAM_H_INCLUDED
#define STYL_AGPS_PARAM_H_INCLUDED

#define PARAM_NUMBER            4

#define STYL_AGPS_PARAM_TIMEOUT           "googleRequestTimeoutSec"
#define STYL_AGPS_PARAM_TIMEOUT_DEFAULT   10
#define STYL_AGPS_PARAM_URL               "geoLocationURL"
#define STYL_AGPS_PARAM_KEY               "keyAPI"

GHashTable *    styl_agps_param_new(const gchar* filename);

void            styl_agps_param_free(GHashTable * param_table);

void            styl_agps_param_print(GHashTable * param_table);

gchar *         styl_agps_param_key_to_value(GHashTable * param_table, gchar * keyword);

#endif // STYL_AGPS_PARAM_H_INCLUDED
