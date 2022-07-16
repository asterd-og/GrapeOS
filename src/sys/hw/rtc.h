#pragma once

#include <stdint.h>
#include <stddef.h>

#define CURRENT_YEAR        2022                            // Change this each year!

namespace Rtc {
    extern int century_register;
    extern unsigned char second;
    extern unsigned char minute;
    extern unsigned char hour;
    extern unsigned char day;
    extern unsigned char month;
    extern unsigned int year;

    enum {
        cmos_address = 0x70,
        cmos_data    = 0x71
    };

    int get_update_in_progress_flag();
    unsigned char get_RTC_register(int reg);

    void read(); //basically update it
}