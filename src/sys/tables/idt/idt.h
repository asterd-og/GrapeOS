#pragma once

#include <stdint.h>
#include <stddef.h>
#include <sys/tables/idt/isr.h>

namespace Idt {
    void set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags);
    void init();
}