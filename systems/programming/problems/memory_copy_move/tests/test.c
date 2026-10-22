#include <limits.h>
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
  unsigned char src[] = {0, 255, 2, 0}, d[6] = {9, 9, 9, 9, 9, 9};
  CHECK(byte_copy(d + 1, 4, src, 4) && memcmp(d + 1, src, 4) == 0 &&
        d[0] == 9 && d[5] == 9);
  CHECK(!byte_copy(d, 2, src, 4) && d[0] == 9);
  CHECK(byte_copy(NULL, 0, NULL, 0) && byte_move(NULL, 0, NULL, 0));
  CHECK(!byte_move(NULL, 4, src, 4) && !byte_copy(d, 4, NULL, 4));
  char a[] = "abcdef";
  CHECK(byte_move(a + 2, 4, a, 4) && memcmp(a, "ababcd", 6) == 0);
  CHECK(byte_move(a, 4, a + 2, 4) && memcmp(a, "abcdcd", 6) == 0);
  CHECK(byte_move(a, 6, a, 6) && !byte_move(a, 2, src, 3) && a[0] == 'a');
  bool matches_libc = true;
  for (size_t from = 0; from < 12; ++from) {
    for (size_t to = 0; to < 12; ++to) {
      for (size_t length = 0; length <= 12; ++length) {
        if (from + length > 12 || to + length > 12)
          continue;
        unsigned char actual[12], expected[12];
        for (size_t i = 0; i < 12; ++i)
          actual[i] = expected[i] = (unsigned char)(i * 23);
        memmove(expected + to, expected + from, length);
        bool moved = byte_move(actual + to, 12 - to, actual + from, length);
        matches_libc =
            matches_libc && moved && memcmp(actual, expected, 12) == 0;
        if (from + length <= to || to + length <= from) {
          for (size_t i = 0; i < 12; ++i)
            actual[i] = expected[i] = (unsigned char)(i * 23);
          memcpy(expected + to, expected + from, length);
          bool copied = byte_copy(actual + to, 12 - to, actual + from, length);
          matches_libc =
              matches_libc && copied && memcmp(actual, expected, 12) == 0;
        }
      }
    }
  }
  CHECK(matches_libc);
  unsigned char before[6];
  memcpy(before, d, sizeof d);
  CHECK(!byte_move(d, 2, src, 4) && memcmp(d, before, sizeof d) == 0);
  CHECK(!byte_copy(d, 2, src, 4) && memcmp(d, before, sizeof d) == 0);
  printf("DSA_RESULT {\"passed\":%d,\"total\":%d}\n", passed, total);
  return passed == total ? 0 : 1;
}
