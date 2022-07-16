#pragma once

#include <stdint.h>
#include <sys/lib/gfx/aaf.h>
#include <sys/lib/gfx/fonts.h>
#include <sys/lib/gfx/colors.h>
#include <sys/gfx/tga.h>
#include <sys/gfx/bmp.h>
#include <sys/lib/printf.h>
#include <sys/drivers/video/base.h>

class Canvas : public Base {
    private:
        uint32_t* FBAddr;
        uint32_t size;
    public:
        void Init(int width, int height, uint32_t pitch, uint32_t bpp, uint32_t* FBAddr=0);
        
        void Clear(uint32_t color);
        void Update();
};

extern Canvas Vbe;