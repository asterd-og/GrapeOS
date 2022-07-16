#pragma once

#include <sys/drivers/video/base.h>

class VirtualCanvas : public Base {
    private:
        uint32_t size;
    public:
        int x;
        int y;
        void init(int x, int y, uint32_t width, uint32_t height, uint32_t bpp, uint32_t pitch);
        void Clear(uint32_t color);
        void Update();
};