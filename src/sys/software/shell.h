#pragma once

#include <stdint.h>

namespace Shell {
    void init();
    void handleKey(int32_t keycode, char ch);
}

class Command {
    private:
        void* (executeFunc)(void);
    public:
        char* name;
        void execute();
};