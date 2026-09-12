#ifndef __GPS_TRANSFORM_H
#define __GPS_TRANSFORM_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Construct or destroy the GPS_Transform object.
 * @param wgLat Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param wgLon Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param mgLat Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param mgLon Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void GPS_Transform(double wgLat, double wgLon, double* mgLat, double* mgLon);

#ifdef __cplusplus
}
#endif

#endif
