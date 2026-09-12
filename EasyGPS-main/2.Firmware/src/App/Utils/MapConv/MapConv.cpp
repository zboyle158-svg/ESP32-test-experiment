/*
 * MIT License
 * Copyright (c) 2021 _VIFEXTech
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include "MapConv.h"
#include <stdio.h>
#include "GPS_Transform/GPS_Transform.h"

using namespace::Microsoft_MapPoint;

#ifndef constrain
#  define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))
#endif

char MapConv::dirPath[] = "/MAP";
char MapConv::extName[] = "bin";
int16_t MapConv::levelMin = 0;
int16_t MapConv::levelMax = 19;
bool MapConv::coordTransformEnable = false;

/**
 * @brief Construct or destroy the MapConv object.
 * @return Operation result or status; inspect it before using dependent state.
 */
MapConv::MapConv()
{
    priv.level = 16;
    priv.tileSize = 256;
}

/**
 * @brief Change the Level configuration of the object.
 * @param level Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void MapConv::SetLevel(int level)
{
    priv.level = constrain(level, levelMin, levelMax);
}

/**
 * @brief Read MapTile from the current object state.
 * @param longitude Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param latitude Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param mapTile Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void MapConv::GetMapTile(double longitude, double latitude, MapTile_t* mapTile)
{
/**
 * @brief Own and retain the y state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    int32_t x, y;
/**
 * @brief Convert map or coordinate data between the supported representations.
 * @param longitude Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param latitude Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param x Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param y Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    ConvertMapCoordinate(longitude, latitude, &x, &y);
/**
 * @brief Convert map or coordinate data between the supported representations.
 * @param x Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param y Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param mapTile Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    ConvertPosToTile(x, y, mapTile);
}

void MapConv::ConvertMapCoordinate(
    double longitude, double latitude,
    int32_t* mapX, int32_t* mapY
)
{
/**
 * @brief Own and retain the pixelY state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    int pixelX, pixelY;

    if (coordTransformEnable)
    {
/**
 * @brief Execute the GPS_Transform operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param latitude Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param longitude Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param latitude Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param longitude Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
        GPS_Transform(latitude, longitude, &latitude, &longitude);
    }

    TileSystem::LatLongToPixelXY(
        latitude,
        longitude,
        priv.level,
        &pixelX,
        &pixelY
    );

    *mapX = pixelX;
    *mapY = pixelY;
};

void MapConv::ConvertMapLevelPos(
    int32_t* destX, int32_t* destY,
    int32_t srcX, int32_t srcY, int srcLevel
)
{
/**
 * @brief Read Level from the current object state.
 * @return Operation result or status; inspect it before using dependent state.
 */
    int diffLevel = srcLevel - GetLevel();
    if (diffLevel >= 0)
    {
        *destX = srcX >> diffLevel;
        *destY = srcY >> diffLevel;
    }
    else
    {
        *destX = srcX << -diffLevel;
        *destY = srcY << -diffLevel;
    }
}

/**
 * @brief Convert map or coordinate data between the supported representations.
 * @param x Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param y Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param path Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param len Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
int MapConv::ConvertMapPath(int32_t x, int32_t y, char* path, uint32_t len)
{
/**
 * @brief Own and retain the tileX state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    int32_t tileX = x / priv.tileSize;
/**
 * @brief Own and retain the tileY state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    int32_t tileY = y / priv.tileSize;
    int ret = snprintf(
                  path, len,
                  "%s/%d/%d/%d.%s",
                  dirPath,
                  priv.level,
                  tileX,
                  tileY,
                  extName
              );

/**
 * @brief Own and retain the ret state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    return ret;
}

/**
 * @brief Convert map or coordinate data between the supported representations.
 * @param x Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param y Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param mapTile Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void MapConv::ConvertPosToTile(int32_t x, int32_t y, MapTile_t* mapTile)
{
    mapTile->tileX = x / priv.tileSize;
    mapTile->tileY = y / priv.tileSize;
    mapTile->subX = x % priv.tileSize;
    mapTile->subY = y % priv.tileSize;
}
