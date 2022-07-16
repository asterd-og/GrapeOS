ENTRY(_start)

SECTIONS
{
	. = 1M;

	.text BLOCK(4K) : ALIGN(4K)
	{
		. = ALIGN(8);
  		KEEP(*(.multiboot))
		*(.text)
	}
	.rodata BLOCK(4K) : ALIGN(4K)
	{
		*(.rodata)
	}
	.data BLOCK(4K) : ALIGN(4K){
		*(.data)
	}
	.bss BLOCK(4K) : ALIGN(4K){
		*(COMMON)
		*(.bss)
		*(.bootstrap_stack)
	}
    kernel_end = .;
}