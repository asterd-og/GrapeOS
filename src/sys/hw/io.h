#pragma once

#include <stdint.h>
#include <stddef.h>

namespace io
{
    void outb(uint16_t port, uint8_t value);
    uint8_t inb(uint16_t port);
    uint16_t inw(uint16_t port);
    void outl(uint16_t port, uint32_t value);
    void outw(uint16_t portid, uint16_t value);
    uint32_t inl(uint16_t port);
    uint16_t ins(uint16_t _port);
    void outs(uint16_t _port, uint16_t _data);
    void insl(uint32_t port, void* addr, size_t count);
    void insw(uint16_t port, void* addr, size_t count);
    void insb(uint16_t port, void* addr, size_t count);
    void outsl(uint32_t port, const void* addr, size_t count);
    void outsw(uint16_t port, const void* addr, size_t count);
    void outsb(uint16_t port, const void* addr, size_t count);
    void wait();
}