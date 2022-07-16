#pragma once

#include <stdint.h>
#include <stddef.h>

struct Registerss {
    uint32_t __ignored, fs, es, ds;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t int_no, err_no;
    uint32_t eip, cs, efl, useresp, ss;
};

typedef struct Registerss registers_t;

namespace Isr {
    void init();
    void installHandler(int isrs, void *handler);
    void uninstallHandler(int isrs);
}