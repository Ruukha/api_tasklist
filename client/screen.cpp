#include "screen.h"
#include "config.h"

void test() {
    Serial.begin(115200);
    Serial.println("Adafruit test");
    Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);
    delay(500);
    pinMode(BTN, INPUT_PULLUP);
    pinMode(TFT_LED, OUTPUT);
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

void draw_task(String id, String name, Adafruit_ILI9341 tft)
{
    tft.begin();
    tft.setRotation(2);
    tft.fillScreen(ILI9341_BLACK);
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(TEXT_SIZE);
    tft.setCursor(0, 0);
    tft.println(id + ": " + name);
}
