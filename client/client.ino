#include <WiFi.h>
#include <Arduino.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Adafruit_ILI9341.h>

#include "logic.h"
#include "screen.h"
#include "config.h"
#include "button.h"
#include "requests.h"

time_t last_update;
time_t last_cached_update;

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);
int tasks_cap = tft.height() / (TEXT_SIZE * 8);
StaticJsonDocument<4096> tasks;

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
  digitalWrite(BTN_PIN, HIGH);
  pinMode(ENC_SW, INPUT_PULLUP);
  pinMode(ENC_DT, INPUT);
  pinMode(ENC_CLK, INPUT);
  Serial.println("Starting initialisation...");

  tft.setCursor(0, 0);
  init_screen(tft);
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

  get_last_update(last_update);
  update(tft, tasks);
  last_cached_update = last_update;

  Serial.print("Successfully initialised!\n");
}

void loop() {
  static bool on = true;
  
  // button switch
  static ButtonState btn_state;
  btn_state = update(btn);
  if (btn_state == BUTTON_HOLD){
    Serial.printf("Restarting...\n");
    ESP.restart();
  }
  else if (btn_state == BUTTON_PRESS){
    Serial.printf("Toggling screen\n");
    on = !on;
    digitalWrite(TFT_LED, on);
  }

  if (on){
    // rotary encoder logic
    static int counter = 0;
    static int e_lastCLK = LOW;
    static int e_clk;
    static int e_dt;
    static unsigned long last_e_ms = 0;
    static int e_debounce_ms = 3;
    static bool menu = false;
    static int op = 0;
    static char saved_id[8];
    static StaticJsonDocument<1024> task;

    e_clk = digitalRead(ENC_CLK);
    e_dt = digitalRead(ENC_DT);
    
    if (e_lastCLK != e_clk){ 
      e_lastCLK = e_clk;

      if (millis() - last_e_ms > e_debounce_ms){
        if (e_clk != e_dt){
          if (!menu) counter++; else op++;
        } 
        else {
          if (!menu) counter--; else op--;
        }
        op = constrain(op, 0, 2);
        counter = constrain(counter, 0, tasks.size());
        Serial.printf("enc_counter: %i, op: %i", counter, op);
        Serial.print("\n");
        if (!menu) scroll(tft, tasks, counter); 
        else {
          const char* id = getId(tasks, counter);
          if (strcmp(id, saved_id)){
            get_task_by_id(task, id);
            strncpy(saved_id, id, 8);
          }
          show_menu(tft, task, op);
        }
      }
    }

    // rotary encoder button logic
    static ButtonState enc_state;
    enc_state = update(enc_btn);
    if (enc_state == BUTTON_HOLD){
      // select task for removal
      enc_state = BUTTON_NONE;
      const char* task_id = getId(tasks, counter);
      StaticJsonDocument<1024> task;
      if (get_task_by_id(task, task_id)){
        if (remove_task_id(task_id)){
          Serial.printf("Successfully deleted task %s\n", task_id);
          update(tft, tasks, counter);
          last_cached_update = last_update;
        }
      }
    }
    else if (enc_state == BUTTON_PRESS){
      // show description / go back
      Serial.print("Toggling menu\n");
      menu = !menu;
      op = 0;
      update(tft, tasks, counter, menu, op);
    }

    // data update
    static unsigned long ms = millis();

    if ((millis() - ms) > DELAY_MS){
      ms = millis();
      get_last_update(last_update);
      if (last_update > last_cached_update){
        Serial.printf("Last update/cache time: %lld, %lld\n", (long long)last_update, (long long)last_cached_update);
        Serial.print("New update available\n");

        try{
          update(tft, tasks, counter, menu, op);
          last_cached_update = last_update;
        }
        catch (...) {
          Serial.printf("Error while updating!");
        }
      }
    }
  }
}