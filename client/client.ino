#include <WiFi.h>
#include <Arduino.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Adafruit_ILI9341.h>

#include "logic.h"
#include "screen.h"
#include "config.h"

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);
time_t last_update;
time_t last_cached_update;
void setup() {
  Serial.begin(115200);
  tft.setCursor(0, 0);
  pinMode(TFT_CS, OUTPUT);
  pinMode(TFT_RST, OUTPUT);
  pinMode(TFT_DC, OUTPUT);
  pinMode(TFT_SDI, OUTPUT);
  pinMode(TFT_SCK, OUTPUT);
  pinMode(TFT_LED, OUTPUT);
  pinMode(BTN, INPUT_PULLUP);

  WiFi.begin(SSID, password);
  while (WiFi.status() != WL_CONNECTED){
    Serial.print("Trying to connect...\n");
    DELAY_MS(500);
  }

  get_last_update();
  update(tft);
}

void loop() {
  static bool on = false;
  static time_t last_debouce = millis();
  static int btn_state = HIGH;
  static int last_btn_state = HIGH;

  btn_state = digitalRead(BTN);
  //button switch
  if (btn_state != last_btn_state){
    last_debounce = millis();
  }
  if ((millis() - last_debounce) > DEBOUNCE_MS){
    if (btn_state == HIGH && last_btn_state == LOW){
      on = !on;
      digitalWrite(TFT_LED, on);
    }
    last_btn_state = btn_state;
  }

  if (on){
    if (btn_state != last_btn_state){
    last_debounce = millis();
    }
    if ((millis() - last_debounce) > DEBOUNCE_MS){
      if (btn_state == HIGH && last_btn_state == LOW){
        on = !on;
        digitalWrite(TFT_LED, on);
      }
      last_btn_state = btn_state;
    }

    static time_t ms = millis();
    //update
    if ((millis() - ms) > DELAY_MS){
      ms = millis();
      get_last_update();
      if (last_update > last_cached_update){
        update(tft);
      }
    }
  }
}
