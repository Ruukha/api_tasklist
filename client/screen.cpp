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

void draw_task(String &id, String &name, Adafruit_ILI9341 &tft)
{
    tft.println(id + ": " + name);
}
