#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
bool size_add(size_t a, size_t b, size_t *out);
bool size_mul(size_t a, size_t b, size_t *out);
bool size_align_up(size_t value, size_t alignment, size_t *out);

bool size_add(size_t a, size_t b, size_t *out) {
  if (!out || b > SIZE_MAX - a)
    return false;
  *out = a + b;
  return true;
}
bool size_mul(size_t a, size_t b, size_t *out) {
  if (!out || (a && b > SIZE_MAX / a))
    return false;
  *out = a * b;
  return true;
}
bool size_align_up(size_t value, size_t alignment, size_t *out) {
  if (!out || !alignment || (alignment & (alignment - 1)))
    return false;
  size_t padding = (alignment - (value & (alignment - 1))) & (alignment - 1);
  return size_add(value, padding, out);
}
