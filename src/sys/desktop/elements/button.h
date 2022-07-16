#pragma once

#include <sys/desktop/elements/base.h>

class Button : public Element {
    public:
        void create(int x, int y, int width, int height, uint32_t color, uint32_t colorHovered, uint32_t fg, font_t font, char* text, Base canvas);
        void update();
};