#include <kernel/data_structures/bitmap.h>

int get_bit(word_t *map, int n) {
    word_t bit = map[WORD_OFFSET(n)] & (1 << BIT_OFFSET(n));
    return bit != 0;
}

void set_bit(word_t *map, int n) {
    map[WORD_OFFSET(n)] |= (1 << BIT_OFFSET(n));
}

void clear_bit(word_t *map, int n) {
    map[WORD_OFFSET(n)] &= ~(1 << BIT_OFFSET(n));
}