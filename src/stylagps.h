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

#ifndef libstyl_agps_h
#define libstyl_agps_h

#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <glib-object.h>

#define DATA_NAME "stylagps.conf"

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

gint            StylAgpsGetLocation(GObject * nm_device, gdouble *latitude, gdouble *longitude, gdouble *accuracy);

GObject *       StylAgpsInit();

void            StylAgpsFinalize(GObject * nm_device);

gchar *         StylAgpsGetVersion(void);

unsigned long   StylAgpsGetFrequencyUSec();

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* libstyl_agps_h */
