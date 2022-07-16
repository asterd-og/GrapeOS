#pragma once

#include <stdint.h>

class Aaf {
    public:
        int width;
        int height;
        int spacing;
        uint8_t* data;
        void load(char* path);
};

extern Aaf mainFont;