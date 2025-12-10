#include "config.h"
#include <Arduino.h>

//user variable definitions
const char* SSID = "Willy room"; //Wifi name
const char* password = "gbiui7Hc"; //Wifi password
const int TEXT_SIZE = 3; //Default: 3
const int HOLD_MS = 3000; //Default: 3000

//server variable definitions
const char* IP = "https://ruukha.pythonanywhere.com"; //server IP

//pin definitions
const uint8_t TFT_CS = 5;
const uint8_t TFT_RST = 4;
const uint8_t TFT_DC = 17;
const uint8_t TFT_SDI = 23;
const uint8_t TFT_SCK = 18;
const uint8_t TFT_LED = 2;
const uint8_t BTN_PIN = 32;
const uint8_t ENC_SW = 25;
const uint8_t ENC_DT = 26;
const uint8_t ENC_CLK = 27;

//code utilities definitions
const int DEBOUNCE_MS = 50; //default: 50
const int DELAY_MS = 60000; //default: 60000
const int INACTIVITY_MS = 10000; //default: 10000