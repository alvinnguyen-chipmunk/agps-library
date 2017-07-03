#ifndef STYL_AGPS_UTILS_H_INCLUDED
#define STYL_AGPS_UTILS_H_INCLUDED

#define __DEBUG__(format, ...) fprintf (stderr, format, ## __VA_ARGS__)
#define DEBUG(format, args...) __DEBUG__("%s||%s():[%d] " format "\n",__FILE__,__FUNCTION__, __LINE__, ##args)
#define DEBUG_1(format, ...) DEBUG("\n"      format, ##__VA_ARGS__)
#define DEBUG_0() DEBUG("\n")
#define STYL_DEBUG(format, ...) DEBUG("\n      "format, ##__VA_ARGS__)



#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <string.h>

gint styl_agps_utils_data_parse(gchar *data,
                                gdouble **longitude, gdouble **latitude, gdouble **accuracy);

#endif // STYL_AGPS_UTILS_H_INCLUDED
