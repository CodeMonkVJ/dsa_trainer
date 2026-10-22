#include <stddef.h>
#include <stdint.h>
typedef enum { HEX_OK, HEX_INVALID, HEX_OVERFLOW } HexResult;
HexResult parse_hex(const char *text, size_t length, uint32_t *out);

HexResult parse_hex(const char *s, size_t n, uint32_t *out) {
  if (!s || !out || !n)
    return HEX_INVALID;
  size_t i = 0;
  uint32_t v = 0;
  if (n >= 2 && s[0] == '0' && (s[1] == 'x' || s[1] == 'X'))
    i = 2;
  if (i == n)
    return HEX_INVALID;
  for (; i < n; ++i) {
    unsigned char c = (unsigned char)s[i];
    unsigned d;
    if (c >= '0' && c <= '9')
      d = c - '0';
    else if (c >= 'a' && c <= 'f')
      d = c - 'a' + 10;
    else if (c >= 'A' && c <= 'F')
      d = c - 'A' + 10;
    else
      return HEX_INVALID;
    if (v > (UINT32_MAX - d) / 16)
      return HEX_OVERFLOW;
    v = v * 16 + d;
  }
  *out = v;
  return HEX_OK;
}
