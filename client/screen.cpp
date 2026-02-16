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

void init_screen(Adafruit_ILI9341 &tft){
    tft.begin();
    tft.setRotation(2);
    tft.fillScreen(ILI9341_BLACK);
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(TEXT_SIZE);
    tft.setCursor(0, 0);
}

void show_menu(Adafruit_ILI9341 &tft, StaticJsonDocument<1024> &task, int op){
    tft.fillScreen(ILI9341_BLACK);
    tft.print(task["id"].as<const char*>());
    tft.print(": ");
    tft.println(task["name"].as<const char*>());

    switch (op){
        case 0:
        tft.println(task["desc"].as<const char*>());
        tft.println();
        break;

        case 1:
        tft.print("Added: ");
        tft.println(task["date"].as<const char*>());
        break;

        case 2:
        tft.print("Expires: ");
        tft.println(task["expiry"].as<const char*>());
        break;

        default:
        Serial.print("Option not in menu");
        break;
    }
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
    if (selected == -1){
        tft.println(id + ": " + name);
    }
    else{
        const int line_height = 8 * TEXT_SIZE;
        const int y = selected * line_height;
        tft.fillRect(0, y, tft.width(), line_height, ILI9341_WHITE);
        tft.setTextColor(ILI9341_BLACK);
        tft.println(id + ": " + name);
        tft.setTextColor(ILI9341_WHITE);
    }
}
