#include <stdbool.h>
#include <stddef.h>
typedef struct {
  unsigned char *data;
  size_t capacity, head, tail, count;
} Ring;
bool ring_init(Ring *r, unsigned char *storage, size_t capacity);
bool ring_push(Ring *r, unsigned char value);
bool ring_pop(Ring *r, unsigned char *out);

bool ring_init(Ring *r, unsigned char *s, size_t cap) {
  if (!r || !s || !cap)
    return false;
  *r = (Ring){s, cap, 0, 0, 0};
  return true;
}
bool ring_push(Ring *r, unsigned char v) {
  if (!r || r->count == r->capacity)
    return false;
  r->data[r->tail] = v;
  r->tail = r->tail == r->capacity - 1 ? 0 : r->tail + 1;
  ++r->count;
  return true;
}
bool ring_pop(Ring *r, unsigned char *out) {
  if (!r || !out || !r->count)
    return false;
  *out = r->data[r->head];
  r->head = r->head == r->capacity - 1 ? 0 : r->head + 1;
  --r->count;
  return true;
}
