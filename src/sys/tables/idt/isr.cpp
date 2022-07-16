#include <sys/tables/idt/isr.h>
#include <sys/tables/idt/idt.h>
#include <sys/debug/dbg.h>
#include <stddef.h>
/*
 * Exception Handlers
 */

char *exception_messages[] = {
	"division by zero",
	"debug",
	"non-maskable interrupt",
	"breakpoint",
	"detected overflow",
	"out-of-bounds",
	"invalid opcode",
	"no coprocessor",
	"double fault",
	"coprocessor segment overrun",
	"bad TSS",
	"segment not present",
	"stack fault",
	"general protection fault",
	"page fault",
	"unknown interrupt",
	"coprocessor fault",
	"alignment check",
	"machine check",
	"reserved",
	"reserved",
	"reserved",
	"reserved",
	"reserved",
	"reserved",
	"reserved",
	"reserved",
	"reserved",
	"reserved",
	"reserved",
	"reserved",
	"reserved"
};

static void * isrs_routines[32] = { NULL };

namespace Isr {
	extern "C" void _isr0();
	extern "C" void _isr1();
	extern "C" void _isr2();
	extern "C" void _isr3();
	extern "C" void _isr4();
	extern "C" void _isr5();
	extern "C" void _isr6();
	extern "C" void _isr7();
	extern "C" void _isr8();
	extern "C" void _isr9();
	extern "C" void _isr10();
	extern "C" void _isr11();
	extern "C" void _isr12();
	extern "C" void _isr13();
	extern "C" void _isr14();
	extern "C" void _isr15();
	extern "C" void _isr16();
	extern "C" void _isr17();
	extern "C" void _isr18();
	extern "C" void _isr19();
	extern "C" void _isr20();
	extern "C" void _isr21();
	extern "C" void _isr22();
	extern "C" void _isr23();
	extern "C" void _isr24();
	extern "C" void _isr25();
	extern "C" void _isr26();
	extern "C" void _isr27();
	extern "C" void _isr28();
	extern "C" void _isr29();
	extern "C" void _isr30();
	extern "C" void _isr31();

	void installHandler(int isrs, void *handler) {
		isrs_routines[isrs] = handler;
	}

	void uninstallHandler(int isrs) {
		isrs_routines[isrs] = 0;
	}

	void init() {
		/* Exception Handlers */
		Idt::set_gate(0, (unsigned)_isr0, 0x08, 0x8E);
		Idt::set_gate(1, (unsigned)_isr1, 0x08, 0x8E);
		Idt::set_gate(2, (unsigned)_isr2, 0x08, 0x8E);
		Idt::set_gate(3, (unsigned)_isr3, 0x08, 0x8E);
		Idt::set_gate(4, (unsigned)_isr4, 0x08, 0x8E);
		Idt::set_gate(5, (unsigned)_isr5, 0x08, 0x8E);
		Idt::set_gate(6, (unsigned)_isr6, 0x08, 0x8E);
		Idt::set_gate(7, (unsigned)_isr7, 0x08, 0x8E);
		Idt::set_gate(8, (unsigned)_isr8, 0x08, 0x8E);
		Idt::set_gate(9, (unsigned)_isr9, 0x08, 0x8E);
		Idt::set_gate(10, (unsigned)_isr10, 0x08, 0x8E);
		Idt::set_gate(11, (unsigned)_isr11, 0x08, 0x8E);
		Idt::set_gate(12, (unsigned)_isr12, 0x08, 0x8E);
		Idt::set_gate(13, (unsigned)_isr13, 0x08, 0x8E);
		Idt::set_gate(14, (unsigned)_isr14, 0x08, 0x8E);
		Idt::set_gate(15, (unsigned)_isr15, 0x08, 0x8E);
		Idt::set_gate(16, (unsigned)_isr16, 0x08, 0x8E);
		Idt::set_gate(17, (unsigned)_isr17, 0x08, 0x8E);
		Idt::set_gate(18, (unsigned)_isr18, 0x08, 0x8E);
		Idt::set_gate(19, (unsigned)_isr19, 0x08, 0x8E);
		Idt::set_gate(20, (unsigned)_isr20, 0x08, 0x8E);
		Idt::set_gate(21, (unsigned)_isr21, 0x08, 0x8E);
		Idt::set_gate(22, (unsigned)_isr22, 0x08, 0x8E);
		Idt::set_gate(23, (unsigned)_isr23, 0x08, 0x8E);
		Idt::set_gate(24, (unsigned)_isr24, 0x08, 0x8E);
		Idt::set_gate(25, (unsigned)_isr25, 0x08, 0x8E);
		Idt::set_gate(26, (unsigned)_isr26, 0x08, 0x8E);
		Idt::set_gate(27, (unsigned)_isr27, 0x08, 0x8E);
		Idt::set_gate(28, (unsigned)_isr28, 0x08, 0x8E);
		Idt::set_gate(29, (unsigned)_isr29, 0x08, 0x8E);
		Idt::set_gate(30, (unsigned)_isr30, 0x08, 0x8E);
		Idt::set_gate(31, (unsigned)_isr31, 0x08, 0x8E);
	}
}

extern "C" void fault_handler(registers_t* r) {
	if (r->int_no < 32) {
		void (*handler)(registers_t *r);
		handler = isrs_routines[r->int_no];
		if (handler) {
			handler(r);
		} else {
			Dbg::printf("exception: %s.\n", exception_messages[r->int_no]);
			for (;;) ;
			//panic("exception: %s.\n", exception_messages[r->int_no]);
		}
	}
}