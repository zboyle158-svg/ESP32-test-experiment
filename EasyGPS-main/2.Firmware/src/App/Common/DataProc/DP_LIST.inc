
/**
 * @file DP_LIST.inc
 * @brief Single source of truth for DataProc account declarations.
 *
 * @details This is an X-macro include, not a standalone translation unit.
 * DataProc.cpp defines `DP_DEF` differently for each include pass: first to
 * allocate accounts, then to invoke each node initialiser. Keep processing
 * logic in the corresponding DP_*.cpp file.
 */
/* Data processing node list */
DP_DEF(Storage, 0);
DP_DEF(Clock, 0);
DP_DEF(GPS, sizeof(HAL::GPS_Info_t));
DP_DEF(Power, 0);
DP_DEF(SportStatus, sizeof(HAL::SportStatus_Info_t));
DP_DEF(Recorder, 0);
DP_DEF(IMU, sizeof(HAL::IMU_Info_t));
DP_DEF(MAG, sizeof(HAL::MAG_Info_t));
DP_DEF(StatusBar, 0);
DP_DEF(MusicPlayer, 0);
DP_DEF(WiFi, sizeof(HAL::WiFi_Info_t));
DP_DEF(BLE, sizeof(HAL::BLE_Info_t));
DP_DEF(Backlight, sizeof(uint16_t));
DP_DEF(TzConv, 0);
DP_DEF(SysConfig, 0);
DP_DEF(TrackFilter, 0);
DP_DEF(SmartAssistant, sizeof(HAL::Saa_Info_t));
