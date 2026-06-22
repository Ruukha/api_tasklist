#include <BH1750_WE.h>

#include "initResult.h"

class LightSensor{
    private:
        BH1750_WE sensor;

    public:
        LightSensor();
        InitResult begin();
        float read();
};