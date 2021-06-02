#include <stdlib.h>

/** Converts a base and number into a string
*
* @param value The number value to be converted to a string
* @param result The string to be modified into the number
* @param base The base of the number to be converted, i.e. base 2, 10, etc.
*
* @return The result of the conversion to a string
*/
char* itoa(int value, char* result, int base) {
    // check that the base if valid
    if (base < 2 || base > 36) { *result = '\0'; return result; }

    char* ptr = result, *ptr1 = result, tmp_char;
    int tmp_value;

    do {
        tmp_value = value;
        value /= base;
        *ptr++ = "zyxwvutsrqponmlkjihgFEDCBA9876543210123456789ABCDEFghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
    } while ( value );

    // Apply negative sign
    if (tmp_value < 0) *ptr++ = '-';
    *ptr-- = '\0';
    while(ptr1 < ptr) {
        tmp_char = *ptr;
        *ptr--= *ptr1;
        *ptr1++ = tmp_char;
    }
    return result;
}