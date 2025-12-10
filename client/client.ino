#include <WiFi.h>
#include <Arduino.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Adafruit_ILI9341.h>

#include "logic.h"
#include "screen.h"
#include "config.h"
#include "button.h"

time_t last_update;
time_t last_cached_update;

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);
int n_disp_tasks;

Button btn = {BTN_PIN, DEBOUNCE_MS, HOLD_MS};
Button enc_btn = {ENC_SW, DEBOUNCE_MS, HOLD_MS};
void setup() {
  Serial.begin(115200);
  pinMode(TFT_CS, OUTPUT);
  pinMode(TFT_RST, OUTPUT);
  pinMode(TFT_DC, OUTPUT);
  pinMode(TFT_SDI, OUTPUT);
  pinMode(TFT_SCK, OUTPUT);
  pinMode(TFT_LED, OUTPUT);
  pinMode(BTN_PIN, INPUT_PULLUP);
  pinMode(ENC_SW, INPUT_PULLUP);
  pinMode(ENC_DT, INPUT_PULLUP);
  pinMode(ENC_CLK, INPUT_PULLUP);
  Serial.println("Starting initialisation...");

  tft.setCursor(0, 0);
  init_screen(tft);
  n_disp_tasks = (tft.height() + 8*TEXT_SIZE-1)/TEXT_SIZE*8;
  digitalWrite(TFT_LED, HIGH);

  init(btn);
  init(enc_btn);

  do{
    Serial.print("Trying to connect...\n");
    WiFi.begin(SSID, password);
    Serial.printf("Wifi status: %d\n", WiFi.status());
    delay(5000);
  }while (WiFi.status() != WL_CONNECTED);
  Serial.print("Successfully connected!\n");

  get_last_update();
  update_logic(tft);

  Serial.print("Successfully initialised!\n");
}

void loop() {
  static bool on = true;
  static unsigned long now = 0;
  now = millis();
  
  //button switch
  ButtonState btn_state = update(btn);
  if (btn_state == BUTTON_HOLD){
    ESP.restart();
  }
  else if (btn_state == BUTTON_PRESS){
    on = !on;
    digitalWrite(TFT_LED, on);
  }
  
  static unsigned long ms = millis();
  if (on){
    static int selected = -1;

    //encoder rotation
    static int last_clk = LOW;
    static int state_clk = digitalRead(ENC_CLK);
    static unsigned long enc_ms = 0;

    last_clk = state_clk;
    state_clk = digitalRead(ENC_CLK);
    if (last_clk != state_clk){
      enc_ms = now;
      if (digitalRead(ENC_DT) != state_clk){
        //clockwise
        selected++;
      }
      else {
        //counter clockwise
        selected--;
      }
      selected = constrain(selected, -1, n_disp_tasks-1);
      Serial.println(selected);
      update_logic(tft, selected);
    }
    if (now - enc_ms > INACTIVITY_MS && selected != -1){
      selected = -1;
      Serial.println(selected);
      update_logic(tft, selected);
    }

    //update
    if ((now - ms) > DELAY_MS){
      ms = now;
      get_last_update();
      if (last_update > last_cached_update){
        Serial.printf("Last update/cache time: %lld, %lld\n", (long long)last_update, (long long)last_cached_update);
        Serial.print("New update available\n");
        update_logic(tft, selected);
      }
    }
  }
}
