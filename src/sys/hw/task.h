#pragma once

#include <stdint.h>
#include <stddef.h>
#include <sys/tables/idt/irq.h>

typedef enum {
    DEAD = 0,
    ALIVE
} state;

typedef struct {
    uint32_t eax, ebx, ecx, edx, esi, edi, esp, ebp, eip, eflags, cr3;
} Registers;

class Task {
    private:
        char* name;
        int id;
        uint32_t toTask;

        state currentState;

    public:
        Registers regs;

        uint32_t cr3;
        uint32_t eflags;
        
        Task* next;
        Task* prev;

        void create(char* name, uint32_t toTask, uint32_t stackSize = 4096);
};

namespace Tasking {
    void init();
    void addTask(Task* task);
    void yield();
}