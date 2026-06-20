#include "icons.h"

namespace{
    const uint8_t pawIconData[] = {
        //frame 0
        0, 0, 1, 0, 0,
        1, 0, 0, 0, 1,
        0, 0, 1, 0, 0,
        0, 1, 1, 1, 0,
        0, 0, 0, 0, 0,
        
        //frame 1
        0, 0, 0, 0, 0,
        0, 0, 1, 0, 0,
        1, 0, 0, 0, 1,
        0, 0, 1, 0, 0,
        0, 1, 1, 1, 0
    };
    
    const uint8_t errorIconData[] = {
        //frame 0
        1, 0, 0, 0, 1,
        0, 1, 0, 1, 0,
        0, 0, 1, 0, 0,
        0, 1, 0, 1, 0,
        1, 0, 0, 0, 1,
        
        //frame 1
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0
    };
}

namespace Icons{
    const Icon loading{
        pawIconData, 2, 5, 5, 5
    };

    const Icon error{
    errorIconData, 2, 5, 5, 5
    };
}