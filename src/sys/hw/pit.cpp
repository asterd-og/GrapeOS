#include <sys/hw/pit.h>
#include <sys/tables/idt/irq.h>
#include <sys/hw/io.h>
#include <sys/hw/task.h>

namespace Pit {
    uint32_t tick=0;
    uint32_t frequency = PIT_DEF_FREQ;
    
    void sleep(uint32_t sec)
    {
        uint32_t start = tick;
        // tasking::switch_task();
        while (tick < start + sec * frequency);
    }

    void msleep(uint32_t msec)
    {
        uint32_t start = tick;
        while (tick < start + msec * (frequency / 100));
    }

    uint32_t get_tick()
    {
        return tick;
    }

    static void PIT_Handler(registers_t *regs)
    {
        tick++;
        Tasking::yield();
    }

    void setfreq(uint32_t freq)
    {
        if (freq < 19) freq = 19;
        frequency = freq;
        uint32_t divisor = 1193180 / frequency;
        io::outb(0x43, 0x36);
        uint8_t l = (uint8_t)divisor;
        uint8_t h = (uint8_t)(divisor >> 8);
        io::outb(0x40, l);
        io::outb(0x40, h);
    }

    uint32_t getfreq()
    {
        uint32_t freq = 0;
        io::outb(0x43, 0b0000000);
        freq = io::inb(0x40);
        freq |= io::inb(0x40) << 8;
        freq = 1193180 / freq;
        return freq;
    }

    void resetfreq()
    {
        setfreq(PIT_DEF_FREQ);
    }

    void init(uint32_t freq)
    {
        setfreq(freq);
        Irq::install_handler(0, PIT_Handler);
    }
}