#pragma once

#include <sys/desktop/elements/base.h>

class Image : public Element {
    public:
        void create(int x, int y, Bmp img, Base canvas);
        void update();
};