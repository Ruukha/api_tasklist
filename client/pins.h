#pragma once
#include <Arduino.h>

namespace Pins{
    inline constexpr uint8_t TFT_CS = 5;
    inline constexpr uint8_t TFT_RST = 4;
    inline constexpr uint8_t TFT_DC = 17;
    inline constexpr uint8_t TFT_SDI = 23;
    inline constexpr uint8_t TFT_SCK = 18;
    inline constexpr uint8_t TFT_LED = 2;
    inline constexpr uint8_t BTN = 32;
    inline constexpr uint8_t ENC_SW = 25;
    inline constexpr uint8_t ENC_DT = 26;
    inline constexpr uint8_t ENC_CLK = 27;
    inline constexpr uint8_t I2C_SCL = 22;
    inline constexpr uint8_t I2C_SDA = 21;
}