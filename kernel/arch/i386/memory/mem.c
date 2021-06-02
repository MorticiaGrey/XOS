#include <kernel/memory/mem.h>
#include <stdint.h>
#include <kernel/data_structures/bitmap.h>
#include <stdio.h>

// Pointer to bitmap of free memory
//uint32_t *free_mem_bitmap;
uint32_t free_mem_bitmap[10000];
// Variable recording how long the bitmap is in amount of available pages
unsigned long free_mem_bitmap_length;

unsigned long long free_memory;

/** Initializes memory, finds the available RAM and sorts it for paging
*
* @param mbt This is the multiboot information structure, containing among other things the pointer to the memory map
*
* @return Will return 1 if successful, otherwise will return an error code
*/
int memory_initialize(multiboot_info_t* mbt) {
	mmap_entry_t* entry = mbt->mmap_addr;
	while (entry < mbt->mmap_addr + mbt->mmap_length) {
		entry = (mmap_entry_t*) ((unsigned int) entry + entry->size + sizeof(entry->size));
        if (entry->type == 1) {
			mem_amount += entry->length;
            free_mem_bitmap_length += entry->length / 4;
		}
	}
    printf("Total free pages: %d\n", free_mem_bitmap_length);
    free_memory = mem_amount;
    return 1;
}

/** Returns a pointed to the bitmap which holds the data about what memory is allocated and what memory is free
*
* @return Pointer to bitmap determining what memory is free or not
*
uint32_t* get_memory_bitmap(void) {
    return free_mem_bitmap;
}*/

/** Finds the first available page and returns a pointer to it while setting it to allocated
*
* @return Pointer to the allocated page
*/
void* allocate_page(void) {
    // Possible optimization: keep record of the last allocated entry and start searching from there
    // i might have to be longer datatype, i.e. uint32_t

    // Iterates through available entries in the bitmap
    unsigned int i = 0;
    while (i < free_mem_bitmap_length) {
        i++;
        if (get_bit(free_mem_bitmap, i) == 0) {
            set_bit(free_mem_bitmap, i);
            // printf("bit: %d\n", get_bit(free_mem_bitmap, i));
            // printf("iteration: %d\n", i);
            free_memory -= 4096;
            return (void*) (i * 4096);
        }
    }
    return (void*) 0x0;
}

/** Deallocates a defined page
*
* @param page_addr Page to be deallocated
*/
void deallocate_page(void* page_addr) {
    clear_bit(free_mem_bitmap, (int) page_addr / 4096);
}

/** Sets a defined page to either allocated or free
*
* @param page_addr Address of the page to be set allocated or deallocated
* @param free Whether the defined page is to be allocated or free
*/
void set_page(void* page_addr, bool set) {
    if (set) {
        set_bit(free_mem_bitmap, (int) page_addr / 4096);
    } else {
        clear_bit(free_mem_bitmap, (int) page_addr / 4096);
    }
}
