#include <WiFi.h>
#include <Arduino.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Adafruit_ILI9341.h>

#include "logic.h"
#include "screen.h"
#include "config.h"

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);
void setup() {
  Serial.begin(115200);
  tft.setCursor(0, 0);

  WiFi.begin(SSID, password);
  while (WiFi.status() != WL_CONNECTED){
    Serial.print("Trying to connect...\n");
    delay(500);
  }

  update(tft);
}

void loop() {
  static time_t ms = millis();
  if ((millis() - ms) > DELAY){
    ms = millis();
    get_last_update();
    if (last_update > last_cached_update){
      update(tft);
    }
  }
}
