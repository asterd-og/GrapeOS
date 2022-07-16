#include <sys/tables/idt/idt.h>
#include <sys/lib/string.h>

struct idt_entry {
	unsigned short base_low;
	unsigned short sel;
	unsigned char zero;
	unsigned char flags;
	unsigned short base_high;
} __attribute__((packed));

struct idt_ptr {
	unsigned short limit;
	unsigned int base;
} __attribute__((packed));

struct idt_ptr idtp;

namespace Idt {

	struct idt_entry idt_entries[256];
	extern "C" void idt_load();

	/*
	 * idt_set_gate
	 * Set an IDT gate
	 */
	void set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags) {
		idt_entries[num].base_low =		(base & 0xFFFF);
		idt_entries[num].base_high =	(base >> 16) & 0xFFFF;
		idt_entries[num].sel =			sel;
		idt_entries[num].zero =			0;
		idt_entries[num].flags =		flags;
	}

	/*
	 * idt_install
	 * Install the IDTs
	 */
	void init() {
		idtp.limit = (sizeof(struct idt_entry) * 256) - 1;
		idtp.base = &idt_entries;
		memset(&idt_entries, 0, sizeof(struct idt_entry) * 256);

		idt_load();
	}
}