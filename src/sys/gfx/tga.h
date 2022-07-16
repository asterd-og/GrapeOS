#pragma once

#include <stdint.h>

class Tga {
    public:
        int width, height;
        unsigned int* data;
        
        void          load(const char* name);
        unsigned int* parse(unsigned char *ptr, int size);
};