#include <limits.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>

#define PRINT_NUMBER_BUFFER_SIZE  (64 + 5)

#define CAP_NUM_LOOKUP  "0123456789ABCDEF"
#define NUM_LOOKUP  "0123456789abcdef"

// Data structure to hold the flags for printf
typedef struct printf_flags {
	// If thing being printed is a number or a string
	bool is_number;
	// If number, is it base 2, 8, 10, etc.
	short base;
	// Print the sign, i.e. + or -
	bool print_sign;
	// Whether to capitalise letters which may appear while printing
	bool capitalise;
	// Prefix to print, if none leave null
	char* prefix;
	// The actual data, if number, to be printed
	int num_data;
	// Data to be printed if text
	char* string_data;
} printf_flags_t;

/* Helper function for printf */
unsigned int num_hex_digits(unsigned int n) {
    int ret = 0;
    while(n) {
        n >>= 4;
        ++ret;
    }
    return ret;
}

/** Print a defined number of characters
*
* @param data   String to be printed
* @param length Number of characters to be printed
*
* @return Successful
*/
static bool print(const char* data, size_t length) {
	const unsigned char* bytes = (const unsigned char*) data;
	for (size_t i = 0; i < length; i++)
		if (putchar(bytes[i]) == EOF)
			return false;
	return true;
}

/** Print a formatted string of characters
*
* @param format String to be formatted and printed
* @param ...    Arguments to format 'format' with
*
* @return Number of characters printed
*
*/
int printf(const char* restrict format, ...) {

	/*
	Todo:
	- Add support for capitalise flag
	*/

	va_list parameters;
	va_start(parameters, format);

	unsigned int written = 0;

	while (*format != '\0') {
		// Normal characters to be written
		if (format[0] != '%' || format[1] == '%') {
			if (format[0] == '%')
				format++;
			size_t amount = 1;
			while (format[amount] && format[amount] != '%')
				amount++;
			if (!print(format, amount))
				return -1;
			format += amount;
			written += amount;
			continue;
		}

		printf_flags_t flags;

		// Format characters
		switch (*++format) {
			case 'c': {
				flags.is_number = false;
				flags.string_data = (char*) va_arg(parameters, int);
			} break;
			case 's': {
				flags.is_number = false;
				flags.string_data = va_arg(parameters, const char*);
			} break;
			case 'd': {
				flags.is_number = true;
				flags.base = 10;
				flags.print_sign = false;
				flags.capitalise = false;
				flags.num_data = va_arg(parameters, int);
			} break;
			case 'p': {
				flags.is_number = true;
				flags.base = 16;
				flags.print_sign = false;
				flags.capitalise = true;
				flags.prefix = "0x";
				flags.num_data = va_arg(parameters, int);
			} break;
			case 'x': {
				flags.is_number = true;
				flags.base = 16;
				flags.print_sign = false;
				flags.capitalise = false;
				flags.num_data = va_arg(parameters, int);
			} break;
			case 'X': {
				flags.is_number = true;
				flags.base = 16;
				flags.print_sign = false;
				flags.capitalise = true;
				flags.num_data = va_arg(parameters, int);
			} break;
			case 'b': {
				flags.is_number = true;
				flags.base = 2;
				flags.print_sign = false;
				flags.capitalise = true;
				flags.num_data = va_arg(parameters, int);
			}
		}
		// Print based on flags set above
		if (!flags.is_number) {
			// Print string
			print(flags.string_data, strlen(flags.string_data));
			written += strlen(flags.string_data);
		} else {
			// Print prefix if it exists
			if (flags.prefix) {
				print(flags.prefix, strlen(flags.prefix));
				flags.prefix = "";
			}
			// Print number
			char str[PRINT_NUMBER_BUFFER_SIZE];
			itoa(flags.num_data, str, flags.base);
			print(str, strlen(str));
			written += strlen(str);
		}
		format++;
	}

	return written;
}
