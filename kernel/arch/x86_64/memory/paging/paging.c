#include <kernel/memory/paging.h>

#include <kernel/memory/mem.h>

#include <stdint.h>

extern void set_page_dir(unsigned int*);
extern void enable_paging(void);

void init_paging(int kernel_pages) {
    set_page((void*)((kernel_pages + 1) * 4096), true);
	uint32_t page_directory[1024];
	*page_directory = (uint32_t*) ((kernel_pages + 1) * 4096);

    int i;
	for (i = 0; i < 1024; i++) {
		// Default state set to:
		//    Supervisor: Only kernel can access this
		//    Write Enabled: It can be both read from and written to
		//    Not Present: The page table is not present
		page_directory[i] = 0x00000002;
	}

	uint32_t first_page_table[1024];
	set_page((void*)((kernel_pages + 2) * 4096), true);
	*first_page_table = (uint32_t*) ((kernel_pages + 2) * 4096);

	for (i = 0; i < 1024; i++) {
		first_page_table[i] = (i * 0x1000) | 3; // supervisor, read/write, present
	}

	page_directory[0] = ((unsigned int) first_page_table) | 3;

	set_page_dir(page_directory);
	enable_paging();
}

void init_PAEpaging(int kernel_pages) {
    set_page((void*)((kernel_pages + 1) * 4096), true);
    uint64_t page_dir_ptr_tab[4];
    *page_dir_ptr_tab = (uint64_t*) ((kernel_pages + 1) * 4096);

    set_page((void*)((kernel_pages + 2) * 4096), true);
    uint64_t page_dir[512];
    *page_dir_ptr_tab = (uint64_t*) ((kernel_pages + 1) * 4096);

    page_dir_ptr_tab[0] = (uint64_t)&page_dir | 1;
    page_dir[0] = 0b10000011;

    asm volatile ("movl %%cr4, %%eax; bts $5, %%eax; movl %%eax, %%cr4" ::: "eax"); // set bit5 in CR4 to enable PAE		 
    asm volatile ("movl %0, %%cr3" :: "r" (&page_dir_ptr_tab));

    asm volatile ("movl %%cr0, %%eax; orl $0x80000000, %%eax; movl %%eax, %%cr0;" ::: "eax");
}

// Originally for 64 bit long mode, but this OS is in 32 bit protected mode if I remember correctly so watch out for errors there
void init_PDPpaging(void) {
	// PML4 Table -> 512 PDP Tables -> 512 PD -> 512 Page Table -> 512 Page Entries
}