#include "config.h"
#include <Arduino.h>

//user variable definitions
const char* SSID = ""; //Wifi name
const char* password = ""; //Wifi password
const int TEXT_SIZE = 3; //Default: 3
const int HOLD_MS = 3000; //Default: 3000

//server variable definitions
const char* IP = "http://127.0.0.1:5000"; //server IP

//pin definitions
const int TFT_CS = 5;
const int TFT_RST = 4;
const int TFT_DC = 17;
const int TFT_SDI = 23;
const int TFT_SCK = 18;
const int TFT_LED = 2;
const int BTN = 32;
const int DEBOUNCE_MS = 50;

//code utilities definitions
const int DELAY_MS = 60000; //default: 60000