#ifndef __DATA_PROC_DEF_H
#define __DATA_PROC_DEF_H

#include <stdint.h>

namespace DataProc
{

    /* Recorder */
    typedef enum
    {
        RECORDER_CMD_START,
        RECORDER_CMD_PAUSE,
        RECORDER_CMD_CONTINUE,
        RECORDER_CMD_STOP,
/**
 * @brief Own and retain the Recorder_Cmd_t state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    } Recorder_Cmd_t;

    typedef struct
    {
/**
 * @brief Own and retain the cmd state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        Recorder_Cmd_t cmd;
/**
 * @brief Own and retain the time state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        uint16_t time;
/**
 * @brief Own and retain the Recorder_Info_t state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    } Recorder_Info_t;

    /* Storage */
    typedef enum
    {
        STORAGE_CMD_LOAD,
        STORAGE_CMD_SAVE,
        STORAGE_CMD_ADD,
        STORAGE_CMD_REMOVE
/**
 * @brief Own and retain the Storage_Cmd_t state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    } Storage_Cmd_t;

    typedef enum
    {
        STORAGE_TYPE_UNKNOW,
        STORAGE_TYPE_INT,
        STORAGE_TYPE_FLOAT,
        STORAGE_TYPE_DOUBLE,
        STORAGE_TYPE_STRING
/**
 * @brief Own and retain the Storage_Type_t state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    } Storage_Type_t;

    typedef struct
    {
/**
 * @brief Own and retain the cmd state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        Storage_Cmd_t cmd;
        const char *key;
        void *value;
/**
 * @brief Own and retain the size state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        uint16_t size;
/**
 * @brief Own and retain the type state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        Storage_Type_t type;
/**
 * @brief Own and retain the Storage_Info_t state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    } Storage_Info_t;

#define STORAGE_VALUE_REG(act, data, dataType)       \
    do                                               \
    {                                                \
        DataProc::Storage_Info_t info;               \
        DATA_PROC_INIT_STRUCT(info);                 \
        info.cmd = DataProc::STORAGE_CMD_ADD;        \
        info.key = #data;                            \
        info.value = &data;                          \
        info.size = sizeof(data);                    \
        info.type = dataType;                        \
        act->Notify("Storage", &info, sizeof(info)); \
    } while (0)

    typedef struct
    {
/**
 * @brief Own and retain the isDetect state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        bool isDetect;
/**
 * @brief Own and retain the totalSizeMB state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        float totalSizeMB;
/**
 * @brief Own and retain the freeSizeMB state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        float freeSizeMB;
        const char *type;
/**
 * @brief Own and retain the Storage_Basic_Info_t state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    } Storage_Basic_Info_t;

    /* StatusBar */
    typedef enum
    {
        STATUS_BAR_STYLE_TRANSP,
        STATUS_BAR_STYLE_BLACK,
/**
 * @brief Own and retain the StatusBar_Style_t state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    } StatusBar_Style_t;

    typedef enum
    {
        STATUS_BAR_CMD_APPEAR,
        STATUS_BAR_CMD_SET_STYLE,
        STATUS_BAR_CMD_SET_LABEL_REC
/**
 * @brief Own and retain the StatusBar_Cmd_t state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    } StatusBar_Cmd_t;

    typedef enum
    {
        SMART_ASSISTANT_CMD_BEGIN,
        SMART_ASSISTANT_CMD_GAIN_TOKEN
/**
 * @brief Own and retain the SaAPI_Cmd_t state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    } SaAPI_Cmd_t;

    typedef struct
    {
/**
 * @brief Own and retain the cmd state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        StatusBar_Cmd_t cmd;
        union
        {
/**
 * @brief Own and retain the appear state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
            bool appear;
/**
 * @brief Own and retain the style state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
            StatusBar_Style_t style;
            struct
            {
/**
 * @brief Own and retain the show state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
                bool show;
                const char *str;
/**
 * @brief Own and retain the labelRec state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
            } labelRec;
/**
 * @brief Own and retain the param state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        } param;
/**
 * @brief Own and retain the StatusBar_Info_t state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    } StatusBar_Info_t;

    /* MusicPlayer */
    typedef struct
    {
        const char *music;
/**
 * @brief Own and retain the MusicPlayer_Info_t state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    } MusicPlayer_Info_t;

    /* SysConfig */
    typedef enum
    {
        SYSCONFIG_CMD_LOAD,
        SYSCONFIG_CMD_SAVE,
/**
 * @brief Own and retain the SysConfig_Cmd_t state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    } SysConfig_Cmd_t;

    typedef struct
    {
/**
 * @brief Own and retain the cmd state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        SysConfig_Cmd_t cmd;
/**
 * @brief Own and retain the longitude state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        float longitude;
/**
 * @brief Own and retain the latitude state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        float latitude;
/**
 * @brief Own and retain the timeZone state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        int16_t timeZone;
/**
 * @brief Own and retain the soundEnable state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        bool soundEnable;
/**
 * @brief Own and retain the language state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        char language[8];
/**
 * @brief Own and retain the arrowTheme state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        char arrowTheme[16];
/**
 * @brief Own and retain the mapDirPath state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        char mapDirPath[16];
/**
 * @brief Own and retain the mapExtName state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        char mapExtName[8];
/**
 * @brief Own and retain the mapWGS84 state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        bool mapWGS84;
/**
 * @brief Own and retain the SysConfig_Info_t state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    } SysConfig_Info_t;

    /* TrackFilter */
    typedef enum
    {
        TRACK_FILTER_CMD_START = RECORDER_CMD_START,
        TRACK_FILTER_CMD_PAUSE = RECORDER_CMD_PAUSE,
        TRACK_FILTER_CMD_CONTINUE = RECORDER_CMD_CONTINUE,
        TRACK_FILTER_CMD_STOP = RECORDER_CMD_STOP,
/**
 * @brief Own and retain the TrackFilter_Cmd_t state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    } TrackFilter_Cmd_t;

    typedef struct
    {
/**
 * @brief Own and retain the cmd state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        TrackFilter_Cmd_t cmd;
        void *pointCont;
/**
 * @brief Own and retain the level state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        uint8_t level;
/**
 * @brief Own and retain the isActive state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        bool isActive;
/**
 * @brief Own and retain the TrackFilter_Info_t state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    } TrackFilter_Info_t;

}

#endif
