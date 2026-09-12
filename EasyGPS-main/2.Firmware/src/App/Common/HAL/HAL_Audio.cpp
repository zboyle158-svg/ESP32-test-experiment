#include "HAL.h"
#include "App/Utils/TonePlayer/TonePlayer.h"

/**
 * @brief Own and retain the player state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
static TonePlayer player;

#include "App/Common/Music/MusicCode.h"

/**
 * @brief Execute the Audio_Init operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 */
void HAL::Audio_Init()
{
    player.SetCallback([](uint32_t freq, uint16_t volume)
/**
 * @brief Execute the Buzz_Tone operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
                       { HAL::Buzz_Tone(freq); });
}

/**
 * @brief Refresh the HAL_Audio state without blocking the scheduler.
 * @details The function consumes the latest cached DataProc/HAL snapshot and updates presentation state; it does not own or free the source data.
 */
void HAL::Audio_Update()
{
    player.Update(millis());
}

/**
 * @brief Execute the Audio_PlayMusic operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param name Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
bool HAL::Audio_PlayMusic(const char *name)
{
/**
 * @brief Own and retain the retval state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    bool retval = false;
    for (int i = 0; i < sizeof(MusicList) / sizeof(MusicList[0]); i++)
    {
        if (strcmp(name, MusicList[i].name) == 0)
        {
            player.Play(MusicList[i].mc, MusicList[i].length);
            retval = true;
            break;
        }
    }
/**
 * @brief Own and retain the retval state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    return retval;
}
