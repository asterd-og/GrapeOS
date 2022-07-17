#pragma once

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <sys/lib/gfx/fonts.h>
#include <sys/drivers/video/base.h>
#include <sys/gfx/bmp.h>

typedef enum {
    Btn = 0,
    Txt,
    Img,
    Drop
} ElementType;

class Element {
    public:
        int x, y, width, height;
        
        uint32_t color;
        uint32_t fg;
        uint32_t colorHovered;

        char* text;
        
        font_t font;

        bool clicked;
        bool hovering;

        Bmp image;
        
        ElementType type;

        Base canvas;

        virtual void update() {};
};