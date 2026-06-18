#include <BH1750_WE.h>

class LightSensor{
    private:
        BH1750_WE sensor;

    public:
        LightSensor();
        bool begin();
        float read();
};