#include <kernel/mmap.h>
#include <kernel/multiboot.h>
#include <stdbool.h>

#pragma once

// Buffer size of expected entry amount
#define ENTRY_BUFFER_SIZE  99

// Amount of memory in KiB
extern unsigned long long mem_amount;

// Amount of free memory
extern unsigned long long free_memory;

// Initializes memory, finds out how much RAM is available and sorts it for paging
int memory_initialize(multiboot_info_t* mbt);

// Returns the bitmap of the memory, telling you what is allocated and what is free
//uint32_t* get_memory_bitmap(void);

// Allocates a random page in physical memory and returns a pointer
void* allocate_page(void);
// Sets a specified page to free
void deallocate_page(void* page_addr);
// Sets a defined page to used or free
void set_page(void* page_addr, bool free);