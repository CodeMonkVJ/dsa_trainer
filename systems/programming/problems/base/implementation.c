#include <stdbool.h>
#include <stdint.h>
bool bit_change(uint32_t value, unsigned bit, unsigned op, uint32_t *out);
bool bit_test(uint32_t value, unsigned bit, bool *out);
bool extract_field(uint32_t value, unsigned offset, unsigned width,
                   uint32_t *out);
bool insert_field(uint32_t value, unsigned offset, unsigned width,
                  uint32_t field, uint32_t *out);
unsigned count_bits(uint32_t value);

static bool valid_field(unsigned o, unsigned w) {
  return w > 0 && w <= 32 && o <= 32 - w;
}
static uint32_t mask(unsigned w) { return UINT32_MAX >> (32 - w); }
bool bit_change(uint32_t v, unsigned b, unsigned op, uint32_t *out) {
  if (!out || b >= 32 || op > 2)
    return false;
  uint32_t m = UINT32_C(1) << b;
  *out = op == 0 ? v & ~m : op == 1 ? v | m : v ^ m;
  return true;
}
bool bit_test(uint32_t v, unsigned b, bool *out) {
  if (!out || b >= 32)
    return false;
  *out = (v & (UINT32_C(1) << b)) != 0;
  return true;
}
bool extract_field(uint32_t v, unsigned o, unsigned w, uint32_t *out) {
  if (!out || !valid_field(o, w))
    return false;
  *out = (v >> o) & mask(w);
  return true;
}
bool insert_field(uint32_t v, unsigned o, unsigned w, uint32_t f,
                  uint32_t *out) {
  if (!out || !valid_field(o, w) || (f & ~mask(w)))
    return false;
  *out = (v & ~(mask(w) << o)) | (f << o);
  return true;
}
unsigned count_bits(uint32_t v) {
  unsigned n = 0;
  while (v) {
    v &= v - 1;
    ++n;
  }
  return n;
}
