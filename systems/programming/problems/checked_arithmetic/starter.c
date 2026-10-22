#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
bool size_add(size_t a, size_t b, size_t *out);
bool size_mul(size_t a, size_t b, size_t *out);
bool size_align_up(size_t value, size_t alignment, size_t *out);

bool size_add(size_t a, size_t b, size_t *out) {
  (void)a;
  (void)b;
  (void)out; /* TODO */
  return false;
}
bool size_mul(size_t a, size_t b, size_t *out) {
  (void)a;
  (void)b;
  (void)out; /* TODO */
  return false;
}
bool size_align_up(size_t value, size_t alignment, size_t *out) {
  (void)value;
  (void)alignment;
  (void)out; /* TODO */
  return false;
}
