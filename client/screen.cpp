#include <ArduinoJson.h>

#include "screen.h"
#include "config.h"

void test(Adafruit_ILI9341 &tft) {
    Serial.println("Adafruit test");
    delay(500);
    tft.begin();
    tft.setRotation(2);
    tft.fillScreen(ILI9341_BLACK);
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(3);
    tft.setCursor(0, 0);
    tft.fillScreen(ILI9341_BLACK);
    tft.setCursor(0, 0);
    tft.println("Hello!");
    Serial.println("Draw complete");
}

void screen_update()
{

}

void init_screen(Adafruit_ILI9341 &tft){
    tft.begin();
    tft.setRotation(2);
    tft.fillScreen(ILI9341_BLACK);
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(TEXT_SIZE);
    tft.setCursor(0, 0);
}

void draw_tasks(Adafruit_ILI9341 &tft, StaticJsonDocument<2048> &doc){
    tft.setCursor(0, 0);
    tft.fillScreen(ILI9341_BLACK);
    int i = 0;
    for (JsonPair kv : doc.as<JsonObject>()){
        String id = String(kv.key().c_str());
        String name = String(kv.value().as<const char*>());

        draw_task(id, name, tft);
        if (i >= tasks_cap) break;

        i++;
    }
}

void draw_task(String &id, String &name, Adafruit_ILI9341 &tft)
{
    Serial.println("Drawing task: " + id + ": " + name);
    tft.println(id + ": " + name);
}
