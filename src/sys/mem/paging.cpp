// Paging - original file by levex
// https://github.com/levex/osdev

#include <sys/mem/paging.h>
#include <sys/debug/dbg.h>

namespace Paging {
	static uint32_t* page_directory = 0;
	static uint32_t page_dir_loc = 0;
	static uint32_t* last_page = 0;

	/* Paging now will be really simple
	 * we reserve 0-8MB for kernel stuff
	 * heap will be from approx 1mb to 4mb
	 * and paging stuff will be from 4mb
	 */


	void v2p(uint32_t virt, uint32_t phys)
	{
		uint16_t id = virt >> 22;
		for(int i = 0; i < 1024; i++)
		{
			last_page[i] = phys | 3;
			phys += 4096;
		}
		page_directory[id] = ((uint32_t)last_page) | 3;
		last_page = (uint32_t *)(((uint32_t)last_page) + 4096);
		Dbg::printf("Mapping 0x%x (%d) to 0x%x\n", virt, id, phys);
	}

	void enable()
	{
		asm volatile("mov %%eax, %%cr3": :"a"(page_dir_loc));	
		asm volatile("mov %cr0, %eax");
		asm volatile("orl $0x80000000, %eax");
		asm volatile("mov %eax, %cr0");
	}

	void init()
	{
		page_directory = (uint32_t*)0x400000;
		page_dir_loc = (uint32_t)page_directory;
		last_page = (uint32_t *)0x404000;
		for(int i = 0; i < 1024; i++)
		{
			page_directory[i] = 0 | 2;
		}
		v2p(0, 0);
		v2p(0x400000, 0x400000);
		enable();
		Dbg::printf("Paging was successfully enabled!\n");
	}
}