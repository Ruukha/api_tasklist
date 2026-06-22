#pragma once
#include <Arduino.h>

namespace Config{
    //user variables
    inline constexpr int TEXT_SIZE = 3; //Default: 3
    inline constexpr int HOLD_MS = 3000; //Default: 3000
    inline constexpr int TIMEOUT_MS = 60000; //Default: 60000
    inline constexpr int SLEEP_MS = 5 * 60000; //Default: 5 minutes (5 * 60000)

    //server variables
    inline constexpr char* IP = "https://ruukha.pythonanywhere.com"; //server IP

    //other variables (do NOT touch unless you know what you're doing)
    inline constexpr int DEBOUNCE_MS = 50; //default: 50
    inline constexpr int DELAY_MS = 60000; //default: 60000
    inline constexpr int DEFAULT_FRAME_MS = 400; //default: 400
    inline constexpr int TFT_LED_FREQ = 5000; //default: 5000
    inline constexpr int TFT_LED_RES = 8; //default: 8
    inline constexpr int WIFI_RETRY_MS = 5000; //default: 5000
    inline constexpr int WIFI_TIMEOUT_MS = 10000; //default: 10000
}