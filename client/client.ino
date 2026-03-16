#include <WiFi.h>
#include <Arduino.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Adafruit_ILI9341.h>
#include <ESP32Encoder.h>
#include <Wire.h>
#include <BH1750_WE.h>

#include "logic.h"
#include "screen.h"
#include "config.h"
#include "pins.h"
#include "button.h"
#include "requests.h"
#include "icons.h"
#include "credentials.h"

#define BH1750_ADDR 0x23

time_t last_update;
time_t last_cached_update;

volatile int enc_rotation = 0;  // positive=CW, negative=CCW
volatile unsigned long enc_last_interrupt = 0;
const unsigned long ENC_DEBOUNCE_US = 5000;

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);
int tasks_cap = tft.height() / (TEXT_SIZE * 8);
StaticJsonDocument<4096> tasks;

volatile const Icon* current_icon = &loading_icon;
TaskHandle_t animationTaskHandle = NULL;
volatile bool is_active = true;

volatile static bool on = true;
static bool valid = true;

Button btn = {BTN_PIN, DEBOUNCE_MS, HOLD_MS};
Button enc_btn = {ENC_SW, DEBOUNCE_MS, HOLD_MS};
ESP32Encoder enc;

BH1750_WE bh1750(BH1750_ADDR);

void handleEncoder(bool &menu, int &counter, int &op, StaticJsonDocument<1024> &task, char saved_id[8]) {
    static int64_t lastCount = 0;

    int64_t now = enc.getCount();
    int64_t delta = now - lastCount;
    if (delta == 0) return;

    lastCount = now;

    int rotation = (delta > 0) ? +1 : -1;

    int steps = (int)delta;

    if (rotation > 0) {
        if (!menu) counter++; else op++;
    } else {
        if (!menu) counter--; else op--;
    }

    op = constrain(op, 0, 2);
    counter = constrain(counter, 0, (int)tasks.size());

    Serial.printf("enc_count:%lld delta:%lld counter:%i op:%i\n",
                    (long long)now, (long long)delta, counter, op);

    if (!menu) {
        scroll(tft, tasks, counter);
    } else {
        const char* id = getId(tasks, counter);
        if (strcmp(id, saved_id)) {
        current_icon = &loading_icon;
        if (!get_task_by_id(task, id)) current_icon = &error_icon;
        strncpy(saved_id, id, 8);
        }
        show_menu(tft, task, op);
    }
}

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
    pinMode(ENC_DT, INPUT_PULLUP);
    pinMode(ENC_CLK, INPUT_PULLUP);
    Serial.println("Starting initialisation...");

    Wire.begin(BH_SDA, BH_SCL);
    Wire.setClock(100000);
    bool bh1750_init = bh1750.init();
    Serial.print("BH1750 init: ");
    Serial.println(bh1750_init ? "OK" : "ERROR");
    
    ledcAttach(TFT_LED, TFT_FREQ, TFT_RES);
    tft.setCursor(0, 0);
    init_screen(tft);
    float lux = bh1750.getLux();
    setBrightness(bh1750.getLux(), TFT_LED);
    Serial.println(lux);
    xTaskCreate(animationTask, "Animate", 2048, NULL, 1, &animationTaskHandle);

    init(btn);
    init(enc_btn);
    enc.attachHalfQuad(ENC_DT, ENC_CLK);
    enc.setFilter(1023);
    enc.clearCount();

    int wifiTries = 0;
    do{
        Serial.print("Trying to start WiFi...\n");
        WiFi.begin(SSID, password);
        Serial.printf("Wifi status: %d\n", WiFi.status());
        wifiTries++;
        if (wifiTries > 3) {
            current_icon = &error_icon;
            tft.printf("Wifi error: %d\n", WiFi.status());
            valid = false;
        }
        delay(5000);
    }while (WiFi.status() != WL_CONNECTED && wifiTries <= 3);
    Serial.print("WiFi connected!\n");

    get_last_update(last_update);
    if (!update(tft, tasks)) current_icon = &error_icon; else is_active = false;
    last_cached_update = last_update;

    Serial.print("Successfully initialised!\n");
}

void loop() {  
    // button switch
    static float lux;
    static ButtonState btn_state;
    btn_state = update(btn);
    if (btn_state == BUTTON_HOLD){
        Serial.printf("Restarting...\n");
        ESP.restart();
    }
    else if (btn_state == BUTTON_PRESS){
        Serial.printf("Toggling screen\n");
        on = !on;
        if(on){
        //Rising edge
            float lux = bh1750.getLux();
            setBrightness(bh1750.getLux(), TFT_LED);
            Serial.println(lux);
        }
        else ledcWrite(TFT_LED, 0);
    }

    if (on && valid){
        // rotary encoder logic
        static int counter = 0;
        static bool menu = false;
        static int op = 0;
        static char saved_id[8] = "";
        static StaticJsonDocument<1024> task;

        handleEncoder(menu, counter, op, task, saved_id);

        // rotary encoder button logic
        static ButtonState enc_state;
        enc_state = update(enc_btn);
        if (enc_state == BUTTON_HOLD){
            // select task for removal
            enc_state = BUTTON_NONE;
            const char* task_id = getId(tasks, counter);
            StaticJsonDocument<1024> task;
            current_icon = &loading_icon;
            if (get_task_by_id(task, task_id)){
                if (remove_task_id(task_id)){
                    Serial.printf("Successfully deleted task %s\n", task_id);
                    if (!update(tft, tasks, counter)) current_icon = &error_icon; else is_active = false;
                    last_cached_update = last_update;
                }
                else current_icon = &error_icon;
            }
            else current_icon = &error_icon;
        }
        else if (enc_state == BUTTON_PRESS){
            // show description / go back
            Serial.print("Toggling menu\n");
            menu = !menu;
            op = 0;
            if (!update(tft, tasks, counter, menu, op)) current_icon = &error_icon; else is_active = false;
        }

        // data update
        static unsigned long ms = millis();

        if ((millis() - ms) > DELAY_MS){
            ms = millis();
            current_icon = &loading_icon;
            get_last_update(last_update);
            if (last_update > last_cached_update){
                Serial.printf("Last update/cache time: %lld, %lld\n", (long long)last_update, (long long)last_cached_update);
                Serial.print("New update available\n");

                if (!update(tft, tasks, counter, menu, op)) current_icon = &error_icon; else is_active = false;
                last_cached_update = last_update;
            }
        }
    }
}

void animationTask(void *pvParameters) {
    int current_frame = 0;
    bool last_active = is_active;
    int icon_size = (sizeof(current_icon->data[0]) / sizeof(current_icon->data[0][0])) * current_icon->scale;
    while (true) {
        if (current_icon && is_active && on) {
            current_frame = (current_frame + 1) % current_icon->frames;
            draw_icon(tft, *current_icon, current_frame);
        }
        if (!is_active && last_active && on) tft.fillRect(tft.width() - icon_size, tft.height() - icon_size, icon_size, icon_size, ILI9341_BLACK);
        last_active = is_active;
        vTaskDelay(FRAME_MS / portTICK_PERIOD_MS);
    }
}