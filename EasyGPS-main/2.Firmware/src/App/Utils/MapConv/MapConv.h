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
#ifndef __MAP_CONV_H
#define __MAP_CONV_H

#include <stdint.h>
#include <string.h>
#include "TileSystem/TileSystem.h"

#define MAP_CONV_DIR_PATH_MAX 16
#define MAP_CONV_EXT_NAME_MAX 8

class MapConv
{
public:
    typedef struct
    {
/**
 * @brief Own and retain the tileX state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        uint32_t tileX;
/**
 * @brief Own and retain the tileY state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        uint32_t tileY;
/**
 * @brief Own and retain the subX state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        uint32_t subX;
/**
 * @brief Own and retain the subY state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        uint32_t subY;
/**
 * @brief Own and retain the MapTile_t state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    } MapTile_t;

public:
/**
 * @brief Construct or destroy the MapConv object.
 * @return Operation result or status; inspect it before using dependent state.
 */
    MapConv();
    ~MapConv() {}

/**
 * @brief Change the Level configuration of the object.
 * @param level Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
    void SetLevel(int level);
/**
 * @brief Change the LevelUp configuration of the object.
 */
    void SetLevelUp()
    {
/**
 * @brief Change the Level configuration of the object.
 * @return Operation result or status; inspect it before using dependent state.
 */
        SetLevel(GetLevel() + 1);
    }
/**
 * @brief Change the LevelDown configuration of the object.
 */
    void SetLevelDown()
    {
/**
 * @brief Change the Level configuration of the object.
 * @return Operation result or status; inspect it before using dependent state.
 */
        SetLevel(GetLevel() - 1);
    }
/**
 * @brief Change the DirPath configuration of the object.
 * @param path Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
    static void SetDirPath(const char* path)
    {
        strncpy(dirPath, path, sizeof(dirPath));
        dirPath[sizeof(dirPath) - 1] = '\0';
    }
/**
 * @brief Change the ExtName configuration of the object.
 * @param name Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
    static void SetExtName(const char* name)
    {
        strncpy(extName, name, sizeof(extName));
        extName[sizeof(extName) - 1] = '\0';
    }

/**
 * @brief Change the CoordTransformEnable configuration of the object.
 * @param en Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
    static void SetCoordTransformEnable(bool en)
    {
        coordTransformEnable = en;
    }

/**
 * @brief Change the LevelRange configuration of the object.
 * @param min Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param max Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
    static void SetLevelRange(int16_t min, int16_t max)
    {
        levelMin = min;
        levelMax = max;
    }

/**
 * @brief Read Level from the current object state.
 * @return Operation result or status; inspect it before using dependent state.
 */
    int16_t GetLevel()
    {
        return priv.level;
    }
/**
 * @brief Read LevelMax from the current object state.
 * @return Operation result or status; inspect it before using dependent state.
 */
    static int16_t GetLevelMax()
    {
/**
 * @brief Own and retain the levelMax state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        return levelMax;
    }
/**
 * @brief Read LevelMin from the current object state.
 * @return Operation result or status; inspect it before using dependent state.
 */
    static int16_t GetLevelMin()
    {
/**
 * @brief Own and retain the levelMin state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        return levelMin;
    }

/**
 * @brief Read MapTile from the current object state.
 * @param longitude Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param latitude Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param mapTile Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
    void GetMapTile(double longitude, double latitude, MapTile_t* mapTile);
/**
 * @brief Convert map or coordinate data between the supported representations.
 * @param x Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param y Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param mapTile Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
    void ConvertPosToTile(int32_t x, int32_t y, MapTile_t* mapTile);
/**
 * @brief Convert map or coordinate data between the supported representations.
 * @param x Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param y Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param path Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param len Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    int ConvertMapPath(int32_t x, int32_t y, char* path, uint32_t len);
    void ConvertMapCoordinate(
        double longitude, double latitude,
        int32_t* mapX, int32_t* mapY
    );
    void ConvertMapLevelPos(
        int32_t* destX, int32_t* destY,
        int32_t srcX, int32_t srcY, int srcLevel
    );

protected:
    struct
    {
/**
 * @brief Own and retain the level state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        int16_t level;
/**
 * @brief Own and retain the tileSize state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        uint16_t tileSize;
/**
 * @brief Own and retain the priv state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    } priv;

/**
 * @brief Own and retain the dirPath state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    static char dirPath[MAP_CONV_DIR_PATH_MAX];
/**
 * @brief Own and retain the extName state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    static char extName[MAP_CONV_EXT_NAME_MAX];
/**
 * @brief Own and retain the levelMin state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    static int16_t levelMin;
/**
 * @brief Own and retain the levelMax state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    static int16_t levelMax;
/**
 * @brief Own and retain the coordTransformEnable state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    static bool coordTransformEnable;
};

#endif
