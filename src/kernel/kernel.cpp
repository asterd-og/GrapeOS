#include <kernel/kernel.h>
#include <kernel/multiboot.h>

#include <sys/mem/heap.h>
#include <sys/mem/paging.h>

#include <sys/drivers/video/canvas.h>

#include <sys/tables/gdt/gdt.h>
#include <sys/tables/gdt/tss.h>
#include <sys/tables/idt/idt.h>
#include <sys/tables/idt/isr.h>
#include <sys/tables/idt/irq.h>

#include <sys/hw/pic.h>

#include <sys/debug/dbg.h>

#include <sys/drivers/ps2/mouse.h>
#include <sys/drivers/ps2/kb.h>

#include <sys/desktop/wm.h>
#include <sys/desktop/window.h>
#include <sys/desktop/desktop.h>
#include <sys/desktop/lockScreen.h>

#include <sys/drivers/initrd/ramdisk.h>

#include <sys/lib/gfx/aaf.h>

#include <sys/software/shell.h>

#include <sys/hw/task.h>

#include <sys/usermode/syscall.h>

#include <sys/drivers/video/vga.h>

#include <sys/hw/pit.h>

extern uint32_t kernel_end;

void KMain(void* MBPtr);

extern "C" void KInit(void* MBPtr) {
    KMain(MBPtr);
}

Canvas Vbe;
Vga Console;

void InitTables() {
    asm volatile("cli");

    Gdt::init();
    Dbg::printf("GDT - Initialised.\n");

    Tss::init(5, 0x10, 0);
    Dbg::printf("TSS - Initialised.\n");

    // Set TSS stack so that when process return from usermode to kernel mode, the kernel have a ready-to-use stack
    uint32_t esp;
    asm volatile("mov %%esp, %0" : "=r"(esp));
    Tss::set_stack(0x10, esp);

    Dbg::printf("TSS - Stack set up.\n");

    //INTS
    Idt::init();
    Dbg::printf("Idt - Initialised.\n");

    Isr::init();
    Dbg::printf("Isr - Initialised.\n");

    Irq::init();
    Dbg::printf("Irq - Initialised.\n");

    Pic::init();
    Dbg::printf("Pic - Initialised.\n");

    asm volatile("sti");
}

void idleTask() {
    for(;;);
}

void KMain(void* MBPtr) {
    Dbg::enable();

    InitTables();

    Paging::init();

    Pit::init(5000);

    Multiboot::read(MBPtr);
    multiboot_t* mboot=Multiboot::get();

    Heap::init(&kernel_end);

    Tar::SetRamdisk((uint8_t*)Multiboot::get_module(0));

    Vbe.Init((int)mboot->framebuffer_width,
             (int)mboot->framebuffer_height,
             (uint32_t)mboot->framebuffer_pitch,
             (uint32_t)mboot->framebuffer_bpp,
             (uint32_t*)mboot->framebuffer_addr);

    Kb::install();
    Mouse::install((uint32_t)mboot->framebuffer_width, (uint32_t)mboot->framebuffer_height);

    LockScreen::init();
    LockScreen::update();

    memcpy(Mouse::currentCursorData, Mouse::cur_normal, 13*11);

    Desktop::init();

    for(;;) KUpdate();
}

void KUpdate() {
    Desktop::update();
    Mouse::draw();
    Vbe.Update();
}