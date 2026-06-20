#include "config.h"
#include <Arduino.h>

//user variables
const int TEXT_SIZE = 3; //Default: 3
const int HOLD_MS = 3000; //Default: 3000
const int TIMEOUT_MS = 60000; //Default: 60000
const int SLEEP_MS = 5 * 60000; //Default: 5 minutes (5 * 60000)

//server variables
const char* IP = "https://ruukha.pythonanywhere.com"; //server IP

//other variables (do NOT touch unless you know what you're doing)
const int DEBOUNCE_MS = 50; //default: 50
const int DELAY_MS = 60000; //default: 60000
const int DEFAULT_FRAME_MS = 400; //default: 400
const int TFT_FREQ = 5000; //default: 5000
const int TFT_RES = 8; //default: 8
const int WIFI_MS = 5000; //default: 5000