#pragma once
#include "screen.h"
#include "initResult.h"

class InitHandler{
    private:
        Screen& screen;

    public:
        InitHandler(Screen& screen);
        bool handle(const InitResult& res);
};