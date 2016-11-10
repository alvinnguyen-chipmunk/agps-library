//
//  libstyl_agps.h
//  libstyl_agps
//
//  Created by Hoàng Trung Huy on 11/7/16.
//  Copyright © 2016 Hoàng Trung Huy. All rights reserved.
//

#ifndef libstyl_agps_h
#define libstyl_agps_h
#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

int StylAgpsGetLocation(double *longitude, double *latitude, double *accuracy);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* libstyl_agps_h */
