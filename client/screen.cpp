#include <ArduinoJson.h>

#include "screen.h"
#include "config.h"
#include "icons.h"

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
    Serial.print("Showing menu...\n");

    tft.setCursor(0, 0);
    tft.fillScreen(ILI9341_BLACK);
    tft.print(task["id"].as<const char*>());
    tft.print(": ");
    tft.println(task["name"].as<const char*>());
    tft.println();

    switch (op){
        case 0:
        tft.println(task["description"].as<const char*>());
        break;

        case 1:
        tft.print("Added:\n");
        tft.print(task["date"].as<const char*>());
        break;

        case 2:
        tft.print("Expires:\n");
        tft.print(task["expiry"].as<const char*>());
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
    tft.println(id + ": " + name);
}

void draw_icon(Adafruit_ILI9341 &tft, const volatile Icon& icon, int frame){
    int x = tft.width() - 9;
    int y = tft.height() - 9;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            uint16_t color = icon.data[frame][i][j] ? ILI9341_WHITE : ILI9341_BLACK;
            tft.fillRect(x + j * 3, y + i * 3, 3, 3, color);
        }
    }
}