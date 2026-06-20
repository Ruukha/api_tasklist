#pragma once
#include "config.h"

struct Icon {
    const uint8_t* data;
    const uint8_t frames;
    const uint8_t width;
    const uint8_t height;
    const uint8_t scale;
    const int frame_ms = Config::DEFAULT_FRAME_MS;
};

namespace Icons{
    extern const Icon loading;
    extern const Icon error;
}