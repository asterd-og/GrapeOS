#pragma once

#include <stdint.h>
#include <stddef.h>
#include <sys/desktop/window.h>
#include <sys/lib/list.h>

namespace Wm {
    void init();
    int  addWindow(Window win);
    void removeWindow(int id);
    void update();
}