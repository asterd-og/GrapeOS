#include <sys/tables/idt/irq.h>
#include <sys/tables/idt/idt.h>
#include <sys/hw/io.h>

void *irq_routines[16] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0
};

namespace Irq {
	extern "C" void _irq0();
	extern "C" void _irq1();
	extern "C" void _irq2();
	extern "C" void _irq3();
	extern "C" void _irq4();
	extern "C" void _irq5();
	extern "C" void _irq6();
	extern "C" void _irq7();
	extern "C" void _irq8();
	extern "C" void _irq9();
	extern "C" void _irq10();
	extern "C" void _irq11();
	extern "C" void _irq12();
	extern "C" void _irq13();
	extern "C" void _irq14();
	extern "C" void _irq15();

	void install_handler(int irq, void *handler) {
		irq_routines[irq] = handler;
	}

	void uninstall_handler(int irq) {
		irq_routines[irq] = 0;
	}

	void remap() {
		io::outb(0x20, 0x11);
		io::outb(0xA0, 0x11);
		io::outb(0x21, 0x20);
		io::outb(0xA1, 0x28);
		io::outb(0x21, 0x04);
		io::outb(0xA1, 0x02);
		io::outb(0x21, 0x01);
		io::outb(0xA1, 0x01);
		io::outb(0x21, 0x0);
		io::outb(0xA1, 0x0);
	}

	void init() {
		remap();
		Idt::set_gate(32, (unsigned)_irq0, 0x08, 0x8E);
		Idt::set_gate(33, (unsigned)_irq1, 0x08, 0x8E);
		Idt::set_gate(34, (unsigned)_irq2, 0x08, 0x8E);
		Idt::set_gate(35, (unsigned)_irq3, 0x08, 0x8E);
		Idt::set_gate(36, (unsigned)_irq4, 0x08, 0x8E);
		Idt::set_gate(37, (unsigned)_irq5, 0x08, 0x8E);
		Idt::set_gate(38, (unsigned)_irq6, 0x08, 0x8E);
		Idt::set_gate(39, (unsigned)_irq7, 0x08, 0x8E);
		Idt::set_gate(40, (unsigned)_irq8, 0x08, 0x8E);
		Idt::set_gate(41, (unsigned)_irq9, 0x08, 0x8E);
		Idt::set_gate(42, (unsigned)_irq10, 0x08, 0x8E);
		Idt::set_gate(43, (unsigned)_irq11, 0x08, 0x8E);
		Idt::set_gate(44, (unsigned)_irq12, 0x08, 0x8E);
		Idt::set_gate(45, (unsigned)_irq13, 0x08, 0x8E);
		Idt::set_gate(46, (unsigned)_irq14, 0x08, 0x8E);
		Idt::set_gate(47, (unsigned)_irq15, 0x08, 0x8E);
	}
}

extern "C" void irq_handler(registers_t* r) {
	void (*handler)(registers_t* r);
	handler = irq_routines[r->int_no - 32];
	if (handler) {
		handler(r);
	}
	if (r->int_no >= 40) {
		io::outb(0xA0, 0x20);
	}
	io::outb(0x20, 0x20);
}