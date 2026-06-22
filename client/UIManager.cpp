#include <Arduino.h>
#include "UIManager.h"

// void show_menu(Adafruit_ILI9341 &tft, StaticJsonDocument<1024> &task, int op){
//     Serial.print("Showing menu...\n");

//     tft.setCursor(0, 0);
//     tft.fillScreen(ILI9341_BLACK);
//     tft.print(task["id"].as<const char*>());
//     tft.print(": ");
//     tft.println(task["name"].as<const char*>());
//     tft.println();

//     switch (op){
//         case 0:
//         tft.println(task["description"].as<const char*>());
//         break;

//         case 1:
//         tft.print("Added:\n");
//         tft.print(task["date"].as<const char*>());
//         break;

//         case 2:
//         tft.print("Expires:\n");
//         tft.print(task["expiry"].as<const char*>());
//         break;

//         default:
//         Serial.print("Option not in menu");
//         break;
//     }
// }

UIManager::UIManager(Screen& screen)
    : screen(screen)
{}

void UIManager::setIcon(Icon* newIcon){
    icon = newIcon;
}

void UIManager::removeIcon(){
    icon = nullptr;
}

void UIManager::animate(){
    screen.drawIcon(*icon, frame, iconX, iconY);
}

void UIManager::setIconCoords(int16_t newIconX, int16_t newIconY)
{
    int16_t maxX = screen.getWidth();
    int16_t maxY = screen.getHeight();

    if (!icon){
        iconX = newIconX;
        iconY = newIconY;
        return;
    }

    iconX = constrain(newIconX, 0, maxX - icon->width * icon->scale);
    iconY = constrain(newIconY, 0, maxY - icon->height * icon->scale);
}
