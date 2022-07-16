#include <sys/hw/io.h>

namespace io
{
    uint8_t inb(uint16_t port)
    {
        uint8_t ret;
        asm volatile("inb %1, %0" : "=a"(ret) : "Nd"(port));
        return ret;
    }
    void outb(uint16_t port, uint8_t value) {
        asm volatile("outb %0, %1" : : "a"(value), "Nd"(port));
    }
    uint16_t inw(uint16_t port) {
        uint16_t ret;
        asm volatile("inw %1, %0" : "=a"(ret) : "Nd"(port));
        return ret;
    }
    void outw(uint16_t portid, uint16_t value)
    {
    	asm volatile("outw %%ax, %%dx": :"d" (portid), "a" (value));
    }
    uint32_t inl(uint16_t p)
    {
        uint32_t r;
        asm volatile("inl %%dx, %%eax":"=a"(r):"d"(p));
        return r;
    }
    void outl(uint16_t portid, uint32_t value)
    {
        asm volatile("outl %%eax, %%dx":: "d"(portid), "a"(value));
    }
    uint16_t ins(uint16_t _port) {
        uint16_t rv;
        asm volatile ("inw %1, %0" : "=a" (rv) : "dN" (_port));
        return rv;
    }
    void outs(uint16_t _port, uint16_t _data) {
        asm volatile ("outw %1, %0" : : "dN" (_port), "a" (_data));
    }
    void insw(uint16_t port, void* addr, size_t count)
    {
        asm volatile("cld; rep insw" : "+D"(addr), "+c"(count) : "d"(port));
    }
    void insb(uint16_t port, void* addr, size_t count)
    {
        asm volatile("cld; rep insb" : "+D"(addr), "+c"(count) : "d"(port));
    }
    void outsl(uint32_t port, const void* addr, size_t count)
    {
        asm volatile("cld; rep outsl" : "+S"(addr), "+c"(count) : "d"(port));
    }
    void outsw(uint16_t port, const void* addr, size_t count)
    {
        asm volatile("cld; rep outsw" : "+S"(addr), "+c"(count) : "d"(port));
    }
    void outsb(uint16_t port, const void* addr, size_t count)
    {
        asm volatile("cld; rep outsb" : "+S"(addr), "+c"(count) : "d"(port));
    }
    void wait()
    {
        asm volatile("outb %%al, $0x80" : : "a"(0));
    }
}