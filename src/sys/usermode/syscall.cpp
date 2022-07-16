#include <sys/usermode/syscall.h>
#include <sys/debug/dbg.h>

extern "C" void jump_usermode();

void * syscall_table[NUM_SYSCALLS] = {
    Dbg::printf
};

void Syscall_dispatcher(registers_t * regs) {
    if(regs->eax >= NUM_SYSCALLS) return;
    void * system_api = syscall_table[regs->eax];
    int ret;
    // memcpy(&saved_context, regs, sizeof(register_t));
    asm volatile (" \
        push %1; \
        push %2; \
        push %3; \
        push %4; \
        push %5; \
        call *%6; \
        pop %%ebx; \
        pop %%ebx; \
        pop %%ebx; \
        pop %%ebx; \
        pop %%ebx; \
        " : "=a" (ret) : "r" (regs->edi), "r" (regs->esi), "r" (regs->edx), "r" (regs->ecx), "r" (regs->ebx), "r" (system_api));

    // I don't believe this would set eax to return value ?
    regs->eax = ret;
}

void Syscall_init() {
    jump_usermode();
    //register_interrupt_handler(0x80, syscall_dispatcher);
}

extern "C" void test_user_function() {
    Dbg::printf("Hello from debug and user mode!\n");
    Dbg::printf("Going to return!\n");
    // printf("Usmode %s\n", "printf");
    // vbe_DrawFString(5, 5, BLACK, kernel_font, "Usermode Initialised (THIS IS A MESSAGE FROM USERMODE)\n");
    return;
}