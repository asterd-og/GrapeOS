#pragma once

#include <stdint.h>

namespace Paging {
    void v2p(uint32_t virt, uint32_t phys);
    void enable();
    void init();
}