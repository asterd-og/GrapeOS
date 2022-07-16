#pragma once

#include <sys/desktop/elements/base.h>

class Text : public Element {
    public:
        void create(int x, int y, uint32_t color, font_t font, char* text, Base canvas);
        void update();
};