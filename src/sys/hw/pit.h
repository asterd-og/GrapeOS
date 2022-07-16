#pragma once

#include <stdint.h>
#include <stddef.h>

#define PIT_DEF_FREQ 100

#define MS2PIT(ms) (100 / (ms))
#define PIT2MS(freq) (100 / (freq))

namespace Pit {
    void sleep(uint32_t sec);
    void msleep(uint32_t msec);

    uint32_t get_tick();

    void setfreq(uint32_t freq);
    uint32_t getfreq();
    void resetfreq();

    void init(uint32_t freq);
}