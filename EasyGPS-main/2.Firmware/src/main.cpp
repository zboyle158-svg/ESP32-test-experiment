/**
 * @file main.cpp
 * @brief EasyGPS firmware entry point.
 *
 * @details The Arduino runtime calls ::setup once after reset.  This file
 * deliberately only assembles the three architectural layers:
 * - ChappieCore: board support package and physical peripherals;
 * - HAL: periodic acquisition task for hardware state;
 * - App: LVGL pages, business data and user interaction.
 *
 * Keeping business logic out of this file makes the boot sequence explicit
 * and prevents a page from depending on an uninitialised peripheral.
 */
#include <Arduino.h>
#include "lvgl.h"
#include "ChappieCore/ChappieCore.h"
#include "App/App.h"
#include "App/Common/HAL/HAL.h"

/** @brief Process-wide board support package instance used by HAL and App. */
ChappieCore Chappie;

/**
 * @brief Initialise the firmware in dependency order.
 *
 * @details `Chappie.begin()` must precede all subsequent calls because it
 * creates the display, I2C bus, sensors and LVGL ports.  `HAL_Init()` then
 * starts the FreeRTOS sampling task. `App_Init()` finally creates pages that
 * consume the sampled data.  LVGL is enabled last, so no frame is rendered
 * against a partially-created UI tree.
 */
void setup()
{
  /* Init Chappie Core */
  Chappie.begin();

  /* Connect HAL */
  HAL::HAL_Init();

  /* UI Create */
  App_Init();

  /* Memory Check */
  _LOG("[PSRAM] free PSRAM: %d\r\n", ESP.getFreePsram());
  // Serial.printf("Deafult free size: %d\n", heap_caps_get_free_size(MALLOC_CAP_DEFAULT));
  // Serial.printf("PSRAM free size: %d\n", heap_caps_get_free_size(MALLOC_CAP_SPIRAM));

#if !CHAPPIE_CORE_USE_LVGL_WITHOUT_RTOS
  Chappie.lvgl.enable();
#endif
}

/**
 * @brief Arduino compatibility loop.
 *
 * @details The default configuration runs LVGL and HAL in FreeRTOS tasks;
 * this function therefore only yields CPU time.  When
 * `CHAPPIE_CORE_USE_LVGL_WITHOUT_RTOS` is enabled, it becomes responsible for
 * calling `lv_timer_handler()` frequently enough for LVGL timers and redraws.
 */
void loop()
{
#if CHAPPIE_CORE_USE_LVGL_WITHOUT_RTOS
  lv_timer_handler();
  delay(1);
#endif
  // HAL::HAL_Update();
  delay(10);
}
