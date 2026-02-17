#include "config.h"
#include <Arduino.h>

//user variables
const char* SSID = ""; //Wifi name
const char* password = ""; //Wifi password
const int TEXT_SIZE = 3; //Default: 3
const int HOLD_MS = 3000; //Default: 3000

//server variables
const char* IP = "https://ruukha.pythonanywhere.com"; //server IP

//other variables
const int DEBOUNCE_MS = 50; //default: 50
const int DELAY_MS = 60000; //default: 60000
const int FRAME_MS = 400; //default: 400