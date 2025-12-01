#pragma once
#include <Arduino.h>

//user variables
extern const char* SSID; //Wifi name
extern const char* password; //Wifi password
extern const int TEXT_SIZE;
extern const int HOLD_MS;

//server variables
extern const char* IP; //server IP

//pin definitions
extern const int TFT_CS;
extern const int TFT_RST;
extern const int TFT_DC;
extern const int TFT_SDI;
extern const int TFT_SCK;
extern const int TFT_LED;
extern const int BTN;

//code utilities
extern const int DEBOUNCE_MS;
extern const int DELAY; //measured in ms
extern time_t last_update;
extern time_t last_cached_update;