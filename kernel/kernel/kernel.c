#include <stdio.h>
#include <stdint.h>

#include <kernel/tty.h>
#include <kernel/multiboot.h>
#include <kernel/mmap.h>
#include <kernel/memory/mem.h>
#include <kernel/memory/paging.h>

/*
To do:
 - Find permenant solution for stack
*/

unsigned long long mem_amount;

unsigned int iterator;

void kernel_main(multiboot_info_t* mbt, unsigned int magic) {
	int* mem_marker __attribute__((align(4096))) = 1; // Used to mark the start of kernel memory
	terminal_initialize((void*) mbt->framebuffer_addr, mbt->framebuffer_width, mbt->framebuffer_height);
	if (memory_initialize(mbt) != 1) {
		printf("Memory could not be initialized\n");
		while (1 == 1);
	}
	printf("Kernel Successfully Loaded\n");

	// Reserve kernel memory so it won't overwritten

	/*unsigned int i = 0;
	while (i < 7) {
		printf("%p\n", allocate_page());
		i++;
	}*/

	// Reserve a few pages for kernel
	int kernel_pages_to_reserve = 4;
	int i = 0;
	while (i < kernel_pages_to_reserve) {
		set_page((void*) (*mem_marker + (i * 4096)), true);
		i++;
	}

	// Reserve low memory

	// Reserve stack memory

	// Reserve graphical memory
	uint32_t framebuffer_pitch = (mbt->framebuffer_width * mbt->framebuffer_height) * mbt->framebuffer_bpp;
	uint32_t framebuffer_page_amount = (framebuffer_pitch / 4096) + 1;
	for (uint32_t i = 0; i <= framebuffer_page_amount; i++) {
		set_page((void*) mbt->framebuffer_addr + (i * 4096), true);
	}

	// Reserve IO memory

	// Memory virtualization, i.e. page map
	init_paging(kernel_pages_to_reserve);

	printf("Success!\n");
}