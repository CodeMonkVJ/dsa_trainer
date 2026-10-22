#include <stdbool.h>
#include <stddef.h>
typedef struct {
  unsigned char *data;
  size_t capacity, head, tail, count;
} Ring;
bool ring_init(Ring *r, unsigned char *storage, size_t capacity);
bool ring_push(Ring *r, unsigned char value);
bool ring_pop(Ring *r, unsigned char *out);

bool ring_init(Ring *r, unsigned char *storage, size_t capacity) { /* TODO */
  return 0;
}
bool ring_push(Ring *r, unsigned char value) { /* TODO */ return 0; }
bool ring_pop(Ring *r, unsigned char *out) { /* TODO */ return 0; }
