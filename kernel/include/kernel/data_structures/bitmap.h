#include <stdint.h>
#include <limits.h>

typedef uint32_t word_t;
enum { BITS_PER_WORD = sizeof(word_t) * CHAR_BIT};
#define WORD_OFFSET(b) ((b) / BITS_PER_WORD)
#define BIT_OFFSET(b)  ((b) % BITS_PER_WORD)

int get_bit(word_t *map, int n);
void set_bit(word_t *map, int n);
void clear_bit(word_t *map, int n);