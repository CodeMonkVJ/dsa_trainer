#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#ifndef DSA_IMPLEMENTATION
#define DSA_IMPLEMENTATION "../implementation.c"
#endif
#include DSA_IMPLEMENTATION
static int passed, total;
#define CHECK(expr)                                                            \
  do {                                                                         \
    bool ok_ = !!(expr);                                                       \
    ++total;                                                                   \
    passed += ok_;                                                             \
    printf("DSA_CASE "                                                         \
           "{\"input\":%d,\"expected\":true,\"actual\":%s,\"passed\":%s}\n",   \
           __LINE__, ok_ ? "true" : "false", ok_ ? "true" : "false");          \
    if (!ok_)                                                                  \
      fprintf(stderr, "FAIL line %d: %s\n", __LINE__, #expr);                  \
  } while (0)

int main(void) {
  uint32_t v = 7;
  const char bounded[] = {'a', 'B', 'z'};
  CHECK(parse_hex(bounded, 2, &v) == HEX_OK && v == 171);
  CHECK(parse_hex("0Xffffffff", 10, &v) == HEX_OK && v == UINT32_MAX);
  CHECK(parse_hex("100000000", 9, &v) == HEX_OVERFLOW && v == UINT32_MAX);
  CHECK(parse_hex("0000000000001", 13, &v) == HEX_OK && v == 1);
  const char *bad[] = {"", "0x", "-1", "+1", " 1", "1 ", "1g", "0xx1"};
  for (size_t i = 0; i < sizeof bad / sizeof *bad; ++i)
    CHECK(parse_hex(bad[i], strlen(bad[i]), &v) == HEX_INVALID && v == 1);
  CHECK(parse_hex("a\0b", 3, &v) == HEX_INVALID && v == 1);
  CHECK(parse_hex(NULL, 1, &v) == HEX_INVALID &&
        parse_hex("1", 1, NULL) == HEX_INVALID);
  const char exact[] = {'f', 'F'}; /* No NUL or readable suffix required. */
  CHECK(parse_hex(exact, sizeof exact, &v) == HEX_OK && v == 255);
  CHECK(parse_hex("0", 1, &v) == HEX_OK && v == 0);
  CHECK(parse_hex("0x7fAb", 6, &v) == HEX_OK && v == 32683);
  CHECK(parse_hex("fffffffff", 9, &v) == HEX_OVERFLOW && v == 32683);
  CHECK(parse_hex("g100000000", 10, &v) == HEX_INVALID && v == 32683);
  CHECK(parse_hex("100000000g", 10, &v) == HEX_OVERFLOW && v == 32683);
  const char non_ascii[] = {(char)0xff};
  CHECK(parse_hex(non_ascii, 1, &v) == HEX_INVALID && v == 32683);
  printf("DSA_RESULT {\"passed\":%d,\"total\":%d}\n", passed, total);
  return passed == total ? 0 : 1;
}
