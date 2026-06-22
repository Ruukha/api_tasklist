#include <ArduinoJson.h>

#include "screen.h"
#include "config.h"
#include "icons.h"
#include "initResult.h"

Screen::Screen(const uint8_t pin_cs, const uint8_t pin_rst, const uint8_t pin_dc, const uint8_t pin_sdi, const uint8_t pin_sck, const uint8_t pin_led)
    : pin_cs(pin_cs),
    pin_rst(pin_rst),
    pin_dc(pin_dc),
    pin_sdi(pin_sdi),
    pin_sck(pin_sck),
    pin_led(pin_led),
    tft(pin_cs, pin_dc, pin_rst)
{}

InitResult Screen::begin(){
    pinMode(pin_cs, OUTPUT);
    pinMode(pin_rst, OUTPUT);
    pinMode(pin_dc, OUTPUT);
    pinMode(pin_sdi, OUTPUT);
    pinMode(pin_sck, OUTPUT);
    pinMode(pin_led, OUTPUT);
    ledcAttach(pin_led, Config::TFT_LED_FREQ, Config::TFT_LED_RES);
 
    tft.begin();
    tft.setRotation(2);
    tft.fillScreen(ILI9341_BLACK);
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(1);
    tft.setCursor(0, 0);

    return {InitStatus::OK, "Screen", "Cannot verify"};
}

int16_t Screen::getHeight() const {
    return tft.height();
}

int16_t Screen::getWidth() const {
    return tft.width();
}

void Screen::setBrightness(uint8_t brightness){
    //normalisation to do in taskApp:
    // float normalised = log10(lux + 1) / log10(1000);
    // int brightness = normalised * 255;
    // brightness = constrain(brightness, 20, 255);
    
    ledcWrite(pin_led, brightness);
}

void Screen::println(const String &text){
    //tft.println("- " + name); for tasks
    tft.println(text);
}

void Screen::clear(){
    tft.fillScreen(ILI9341_BLACK);
    tft.setCursor(0, 0);
}

void Screen::drawIcon(const Icon& icon, const uint8_t frame, const int x0, const int y0){
    const int frameSize = icon.width * icon.height;

    for (uint8_t y = 0; y < icon.height; y++){
        for (uint8_t x = 0; x < icon.width; x++){
            int index = frame * frameSize + y * icon.width + x;

            if (icon.data[index]) {
                tft.fillRect(
                    x0 + x * icon.scale,
                    y0 + y * icon.scale,
                    icon.scale, 
                    icon.scale,
                    ILI9341_WHITE
                );
            }
        }
    }
}

void Screen::setTextSize(uint8_t size){
    tft.setTextSize(size);
}