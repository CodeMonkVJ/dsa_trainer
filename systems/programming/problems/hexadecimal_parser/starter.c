#include <stddef.h>
#include <stdint.h>
typedef enum { HEX_OK, HEX_INVALID, HEX_OVERFLOW } HexResult;
HexResult parse_hex(const char *text, size_t length, uint32_t *out);

HexResult parse_hex(const char *text, size_t length, uint32_t *out) { /* TODO */
  return HEX_INVALID;
}
