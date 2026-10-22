#include <stdbool.h>
#include <stdint.h>
bool bit_change(uint32_t value, unsigned bit, unsigned op, uint32_t *out);
bool bit_test(uint32_t value, unsigned bit, bool *out);
bool extract_field(uint32_t value, unsigned offset, unsigned width,
                   uint32_t *out);
bool insert_field(uint32_t value, unsigned offset, unsigned width,
                  uint32_t field, uint32_t *out);
unsigned count_bits(uint32_t value);

bool bit_change(uint32_t value, unsigned bit, unsigned op,
                uint32_t *out) { /* TODO */
  return 0;
}
bool bit_test(uint32_t value, unsigned bit, bool *out) { /* TODO */ return 0; }
bool extract_field(uint32_t value, unsigned offset, unsigned width,
                   uint32_t *out) { /* TODO */
  return 0;
}
bool insert_field(uint32_t value, unsigned offset, unsigned width,
                  uint32_t field, uint32_t *out) { /* TODO */
  return 0;
}
unsigned count_bits(uint32_t value) { /* TODO */ return 0; }
