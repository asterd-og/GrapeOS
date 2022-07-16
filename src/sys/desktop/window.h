#pragma once

#include <stdint.h>
#include <stddef.h>
#include <sys/drivers/video/virtualCanvas.h>
#include <sys/desktop/elements/base.h>
#include <sys/desktop/elements/button.h>

class Window {
    private:
        bool moving;
        void(*onUpdate)(Window*);
        Button closeButton;
    public:
        char* name;
        int x, y, xo, yo, width, height;
        VirtualCanvas canvas;
        int id;
        void create(int x, int y, int width, int height, char* name, void(*onUpdate)(Window*), int id);
        void update();
};
