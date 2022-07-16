#pragma once

#include <stdint.h>
#include <stddef.h>
#include <sys/tables/idt/isr.h>

namespace Irq {
    void install_handler(int irq, void *handler);
    void uninstall_handler(int irq);
    void remap();
    void init();
}