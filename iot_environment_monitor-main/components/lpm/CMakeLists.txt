idf_component_register(SRCS "lpm.c"
                    PRIV_REQUIRES "esp_pm" "driver" "backlight" "nvs_helper"
                    INCLUDE_DIRS "include")
