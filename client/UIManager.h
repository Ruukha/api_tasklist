#pragma once
#include "icons.h"
#include "screen.h"

class UIManager{
    private:
        uint8_t frame{0};
        Icon* icon{nullptr};
        Screen& screen;
        uint16_t iconX;
        uint16_t iconY;

    public:
        UIManager(Screen& screen);
        void setIcon(Icon* icon);
        void removeIcon();
        void animate();
        void setIconCoords(int16_t newIconX, int16_t newIconY);
};