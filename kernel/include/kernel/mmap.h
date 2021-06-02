#pragma once

typedef struct multiboot_mem_map {
    unsigned int size;
    unsigned long long base_addr;
    unsigned long long length;
    unsigned int type;
} multiboot_mem_map_t;

typedef multiboot_mem_map_t mmap_entry_t;