#include <sys/hw/pic.h>
#include <sys/hw/io.h>

namespace Pic {
	void init()
	{
		/* set up cascading mode */
		io::outb(PIC_MASTER_CMD, 0x10 + 0x01);
		io::outb(PIC_SLAVE_CMD,  0x10 + 0x01);
		/* Setup master's vector offset */
		io::outb(PIC_MASTER_DATA, 0x20);
		/* Tell the slave its vector offset */
		io::outb(PIC_SLAVE_DATA, 0x28);
		/* Tell the master that he has a slave */
		io::outb(PIC_MASTER_DATA, 4);
		io::outb(PIC_SLAVE_DATA, 2);
		/* Enabled 8086 mode */
		io::outb(PIC_MASTER_DATA, 0x01);
		io::outb(PIC_SLAVE_DATA, 0x01);

		io::outb(PIC_MASTER_DATA, 0);
		io::outb(PIC_SLAVE_DATA, 0);

	}

	void eoi(uint8_t irq)
	{
		if(irq >= 8)
			io::outb(PIC_SLAVE_CMD, PIC_CMD_EOI);
		io::outb(PIC_MASTER_CMD, PIC_CMD_EOI);
	}
}