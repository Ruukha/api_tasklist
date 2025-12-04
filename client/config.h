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
extern const uint8_t TFT_CS;
extern const uint8_t TFT_RST;
extern const uint8_t TFT_DC;
extern const uint8_t TFT_SDI;
extern const uint8_t TFT_SCK;
extern const uint8_t TFT_LED;
extern const uint8_t BTN_PIN;
extern const uint8_t ENC_CLK;
extern const uint8_t ENC_SW;
extern const uint8_t ENC_DT;

//code utilities
extern const int DEBOUNCE_MS;
extern const int DELAY_MS; //measured in ms
extern time_t last_update;
extern time_t last_cached_update;