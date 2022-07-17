#pragma once

#include <stdint.h>
#include <stddef.h>
#include <sys/desktop/elements/base.h>

class DropDown : public Element {
    private:
        bool show;
        uint32_t colorC;
        bool locked = false;
    public:
        char* opts[12];
        int optsSize;
        int optsIdx;
        char* current;
        void create(int x, int y, int width, int height, uint32_t color, uint32_t colorHovered, uint32_t fg, font_t font, char* text, Base canvas);
        void add(char* data);
        void update();
};