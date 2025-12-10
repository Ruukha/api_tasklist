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

void update_screen()
{

}

void init_screen(Screen &screen){
    screen.tft = Adafruit_ILI9341(screen.pin_cs, screen.pin_dt, screen.pin_rst);

    screen.tft.begin();
    screen.tft.setRotation(2);
    screen.tft.fillScreen(ILI9341_BLACK);
    screen.tft.setTextColor(ILI9341_WHITE);
    screen.tft.setTextSize(TEXT_SIZE);
    screen.tft.setCursor(0, 0);
}

void draw_task(String &id, String &name, Adafruit_ILI9341 &tft, const int selected){
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
