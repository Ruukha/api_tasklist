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
  Serial.println("Starting initialisation...");
  tft.setCursor(0, 0);
  pinMode(TFT_CS, OUTPUT);
  pinMode(TFT_RST, OUTPUT);
  pinMode(TFT_DC, OUTPUT);
  pinMode(TFT_SDI, OUTPUT);
  pinMode(TFT_SCK, OUTPUT);
  pinMode(TFT_LED, OUTPUT);
  pinMode(BTN, INPUT_PULLUP);
  digitalWrite(BTN, HIGH);

  init_screen(tft);
  digitalWrite(TFT_LED, HIGH);

  do{
    Serial.print("Trying to connect...\n");
    WiFi.begin(SSID, password);
    Serial.printf("Wifi status: %d\n", WiFi.status());
    delay(5000);
  }while (WiFi.status() != WL_CONNECTED);
  Serial.print("Successfully connected!\n");

  get_last_update();
  update(tft);

  Serial.print("Successfully initialised!\n");
}

void loop() {
  static bool on = true;
  static unsigned long last_debounce = millis();
  static int btn_state = HIGH;
  static int last_btn_state = HIGH;
  static unsigned long ms = millis();

  //button switch
  btn_state = digitalRead(BTN);
  if ((millis() - last_debounce) > DEBOUNCE_MS){
    if (btn_state == HIGH && last_btn_state == LOW){
      on = !on;
      digitalWrite(TFT_LED, on);
    }
  }
  if (btn_state != last_btn_state){
    last_debounce = millis();
  }
  last_btn_state = btn_state;

  if (on){
    //update
    if ((millis() - ms) > DELAY_MS){
      ms = millis();
      get_last_update();
      if (last_update > last_cached_update){
        Serial.printf("Last update/cache time: %lld, %lld\n", (long long)last_update, (long long)last_cached_update);
        Serial.print("New update available\n");
        update(tft);
      }
    }
  }
}
