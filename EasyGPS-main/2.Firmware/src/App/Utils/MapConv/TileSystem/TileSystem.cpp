#include "TileSystem.h"

#include <algorithm>
#include <math.h>
#include <string.h>

using namespace Microsoft_MapPoint;

/**
 * @brief Own and retain the EarthRadius state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
static const double EarthRadius = 6378137;
/**
 * @brief Own and retain the MinLatitude state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
static const double MinLatitude = -85.05112878;
/**
 * @brief Own and retain the MaxLatitude state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
static const double MaxLatitude = 85.05112878;
/**
 * @brief Own and retain the MinLongitude state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
static const double MinLongitude = -180;
/**
 * @brief Own and retain the MaxLongitude state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
static const double MaxLongitude = 180;
/**
 * @brief Own and retain the MATH_PI state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
static const double MATH_PI = 3.1415926535897932384626433832795;

/// <summary>  
/// Clips a number to the specified minimum and maximum values.  
/// </summary>  
/// <param name="n">The number to clip.</param>  
/// <param name="minValue">Minimum allowable value.</param>  
/// <param name="maxValue">Maximum allowable value.</param>  
/// <returns>The clipped value.</returns>  
static double Clip(double n, double minValue, double maxValue)
{
    return std::min(std::max(n, minValue), maxValue);
}


/**
 * @brief Convert map or coordinate data between the supported representations.
 * @param levelOfDetail Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
uint32_t TileSystem::MapSize(int levelOfDetail)
{
    return (uint32_t)256 << levelOfDetail;
}

/**
 * @brief Execute the GroundResolution operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param latitude Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param levelOfDetail Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
double TileSystem::GroundResolution(double latitude, int levelOfDetail)
{
/**
 * @brief Execute the Clip operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param latitude Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param MinLatitude Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param MaxLatitude Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    latitude = Clip(latitude, MinLatitude, MaxLatitude);
    return cos(latitude * MATH_PI / 180) * 2 * MATH_PI * EarthRadius / MapSize(levelOfDetail);
}
 
/**
 * @brief Convert map or coordinate data between the supported representations.
 * @param latitude Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param levelOfDetail Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param screenDpi Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
double TileSystem::MapScale(double latitude, int levelOfDetail, int screenDpi)
{
    return GroundResolution(latitude, levelOfDetail) * screenDpi / 0.0254;
}

/**
 * @brief Execute the LatLongToPixelXY operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param latitude Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param longitude Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param levelOfDetail Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param pixelX Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param pixelY Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void TileSystem::LatLongToPixelXY(double latitude, double longitude, int levelOfDetail, int* pixelX, int* pixelY)
{
/**
 * @brief Execute the Clip operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param latitude Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param MinLatitude Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param MaxLatitude Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    latitude = Clip(latitude, MinLatitude, MaxLatitude);
/**
 * @brief Execute the Clip operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param longitude Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param MinLongitude Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param MaxLongitude Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    longitude = Clip(longitude, MinLongitude, MaxLongitude);

    double x = (longitude + 180) / 360;
/**
 * @brief Execute the sin operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    double sinLatitude = sin(latitude * MATH_PI / 180);
/**
 * @brief Execute the log operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param MATH_PI Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    double y = 0.5 - log((1 + sinLatitude) / (1 - sinLatitude)) / (4 * MATH_PI);

/**
 * @brief Convert map or coordinate data between the supported representations.
 * @param levelOfDetail Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    uint32_t mapSize = MapSize(levelOfDetail);
    *pixelX = (int)Clip(x * mapSize + 0.5, 0, mapSize - 1);
    *pixelY = (int)Clip(y * mapSize + 0.5, 0, mapSize - 1);
}

/**
 * @brief Execute the PixelXYToLatLong operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param pixelX Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param pixelY Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param levelOfDetail Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param latitude Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param longitude Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void TileSystem::PixelXYToLatLong(int pixelX, int pixelY, int levelOfDetail, double* latitude, double* longitude)
{
/**
 * @brief Convert map or coordinate data between the supported representations.
 * @param levelOfDetail Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    double mapSize = MapSize(levelOfDetail);
    double x = (Clip(pixelX, 0, mapSize - 1) / mapSize) - 0.5;
    double y = 0.5 - (Clip(pixelY, 0, mapSize - 1) / mapSize);

    *latitude = 90 - 360 * atan(exp(-y * 2 * MATH_PI)) / MATH_PI;
    *longitude = 360 * x;
}

/**
 * @brief Execute the PixelXYToTileXY operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param pixelX Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param pixelY Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param tileX Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param tileY Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void TileSystem::PixelXYToTileXY(int pixelX, int pixelY, int* tileX, int* tileY)
{
    *tileX = pixelX / 256;
    *tileY = pixelY / 256;
}
 
/**
 * @brief Execute the TileXYToPixelXY operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param tileX Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param tileY Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param pixelX Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param pixelY Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void TileSystem::TileXYToPixelXY(int tileX, int tileY, int* pixelX, int* pixelY)
{
    *pixelX = tileX * 256;
    *pixelY = tileY * 256;
}

/**
 * @brief Execute the TileXYToQuadKey operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param tileX Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param tileY Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param levelOfDetail Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param quadKeyBuffer Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param len Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void TileSystem::TileXYToQuadKey(int tileX, int tileY, int levelOfDetail, char* quadKeyBuffer, uint32_t len)
{
/**
 * @brief Own and retain the quadKeyIndex state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    uint32_t quadKeyIndex = 0;
    for (int i = levelOfDetail; i > 0; i--)
    {
/**
 * @brief Own and retain the digit state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        char digit = '0';
        int mask = 1 << (i - 1);
        if ((tileX & mask) != 0)
        {
            digit++;
        }
        if ((tileY & mask) != 0)
        {
            digit++;
            digit++;
        }
        quadKeyBuffer[quadKeyIndex] = digit;
        quadKeyIndex++;

        if (quadKeyIndex >= len - 1)
        {
            break;
        }
    }

    quadKeyBuffer[quadKeyIndex] = '\0';
}

/**
 * @brief Execute the QuadKeyToTileXY operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param quadKey Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param tileX Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param tileY Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param levelOfDetail Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void TileSystem::QuadKeyToTileXY(const char* quadKey, int* tileX, int* tileY, int* levelOfDetail)
{
    *tileX = *tileY = 0;
    int len = (int)strlen(quadKey);
    *levelOfDetail = len;
    for (int i = len; i > 0; i--)
    {
        int mask = 1 << (i - 1);
        switch (quadKey[len - i])
        {
        case '0':
            break;

        case '1':
            *tileX |= mask;
            break;

        case '2':
            *tileY |= mask;
            break;

        case '3':
            *tileX |= mask;
            *tileY |= mask;
            break;

        default:
            //throw new ArgumentException("Invalid QuadKey digit sequence.");
            break;
        }
    }
}
