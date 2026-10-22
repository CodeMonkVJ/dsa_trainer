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
  uint32_t v = 123;
  bool b = false;
  CHECK(bit_change(0, 31, 1, &v) && v == UINT32_C(0x80000000));
  CHECK(bit_change(UINT32_MAX, 31, 0, &v) && v == UINT32_C(0x7fffffff));
  CHECK(bit_change(3, 0, 2, &v) && v == 2);
  CHECK(bit_test(UINT32_MAX, 31, &b) && b);
  CHECK(!bit_change(0, 32, 1, &v) && v == 2);
  CHECK(!bit_change(0, 1, 3, &v) && !bit_change(0, 0, 0, NULL));
  CHECK(!bit_test(0, 32, &b) && !bit_test(0, 0, NULL));
  CHECK(extract_field(UINT32_MAX, 0, 32, &v) && v == UINT32_MAX);
  CHECK(insert_field(0, 0, 32, UINT32_MAX, &v) && v == UINT32_MAX);
  CHECK(insert_field(0xff, 4, 4, 2, &v) && v == 0x2f);
  CHECK(!insert_field(0, 0, 2, 4, &v) && v == 0x2f);
  CHECK(!extract_field(0, 1, 32, &v) && !extract_field(0, 0, 0, &v));
  CHECK(!extract_field(0, UINT_MAX, 1, &v) && !extract_field(0, 0, 33, &v));
  CHECK(count_bits(0) == 0 && count_bits(UINT32_MAX) == 32 &&
        count_bits(0x55555555) == 16);
  CHECK(bit_test(0, 0, &b) && !b);
  CHECK(extract_field(UINT32_C(0x1234abcd), 8, 8, &v) && v == 0xab);
  CHECK(extract_field(UINT32_C(0x80000000), 31, 1, &v) && v == 1);
  CHECK(insert_field(UINT32_MAX, 31, 1, 0, &v) && v == UINT32_C(0x7fffffff));
  CHECK(!extract_field(0, 0, 1, NULL) && !insert_field(0, 0, 1, 0, NULL));
  v = 123;
  CHECK(!insert_field(0, 31, 2, 0, &v) && v == 123);
  CHECK(!insert_field(0, 0, 0, 0, &v) && v == 123);
  bool all_bits = true;
  for (unsigned bit = 0; bit < 32; ++bit) {
    uint32_t one = UINT32_C(1) << bit;
    all_bits = all_bits && bit_change(0, bit, 1, &v) && v == one &&
               bit_change(one, bit, 0, &v) && v == 0 &&
               bit_change(one, bit, 2, &v) && v == 0 && count_bits(one) == 1;
  }
  CHECK(all_bits);
  printf("DSA_RESULT {\"passed\":%d,\"total\":%d}\n", passed, total);
  return passed == total ? 0 : 1;
}
