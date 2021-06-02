#ifndef _KERNEL_TTY_H
#define _KERNEL_TTY_H

#include <stddef.h>

void terminal_initialize(void* buffer_addr, int frame_width, int frame_height);
void terminal_putchar(char c);
void terminal_write(const char* data, size_t size);
void terminal_writestring(const char* data);
void terminal_shift_text();

#endif
