#define _POSIX_C_SOURCE 200809L
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef DSA_IMPLEMENTATION
#define DSA_IMPLEMENTATION "../implementation.c"
#endif
#include DSA_IMPLEMENTATION
static unsigned passed, total;
static void check(const char *name, bool ok) {
  ++total;
  if (ok)
    ++passed;
  printf("DSA_CASE "
         "{\"input\":\"%s\",\"expected\":true,\"actual\":%s,\"passed\":%s}\n",
         name, ok ? "true" : "false", ok ? "true" : "false");
  if (!ok)
    fprintf(stderr, "FAIL: %s\n", name);
}
#define CHECK(name, expr) check(name, !!(expr))
static int finish(void) {
  printf("DSA_RESULT {\"passed\":%u,\"total\":%u}\n", passed, total);
  return total && passed == total ? 0 : 1;
}
#define REQUIRE(expr)                                                          \
  do {                                                                         \
    if (!(expr)) {                                                             \
      CHECK("test setup or prerequisite failed", false);                       \
      exit(finish());                                                          \
    }                                                                          \
  } while (0)

int main(void) {
  size_t out = 77;
  CHECK("addition boundary",
        size_add(SIZE_MAX - 1, 1, &out) && out == SIZE_MAX);
  CHECK("addition rejects overflow without mutation",
        !size_add(SIZE_MAX, 1, &out) && out == SIZE_MAX);
  CHECK("addition accepts zeros", size_add(0, 0, &out) && out == 0);
  out = 77;
  CHECK("multiplication rejects overflow",
        !size_mul(SIZE_MAX, 2, &out) && out == 77);
  CHECK("zero product", size_mul(SIZE_MAX, 0, &out) && out == 0 &&
                            size_mul(0, SIZE_MAX, &out) && out == 0);
  CHECK("maximum product", size_mul(SIZE_MAX, 1, &out) && out == SIZE_MAX);
  CHECK("quotient multiplication boundary",
        size_mul(SIZE_MAX / 3, 3, &out) && out == (SIZE_MAX / 3) * 3);
  out = 77;
  CHECK("first multiplication overflow above quotient",
        !size_mul(SIZE_MAX / 3 + 1, 3, &out) && out == 77);
  CHECK("alignment rounds up", size_align_up(17, 16, &out) && out == 32);
  CHECK("already aligned unchanged", size_align_up(32, 16, &out) && out == 32);
  CHECK("alignment one preserves maximum",
        size_align_up(SIZE_MAX, 1, &out) && out == SIZE_MAX);
  out = 77;
  CHECK("alignment overflow preserves output",
        !size_align_up(SIZE_MAX, 2, &out) && out == 77);
  CHECK("invalid alignments rejected",
        !size_align_up(1, 0, &out) && !size_align_up(1, 3, &out) && out == 77);
  size_t top = SIZE_MAX / 2 + 1;
  CHECK("highest representable alignment",
        size_align_up(1, top, &out) && out == top);
  out = 77;
  CHECK("rounding above highest alignment overflows",
        !size_align_up(top + 1, top, &out) && out == 77);
  CHECK("null outputs rejected", !size_add(1, 1, NULL) &&
                                     !size_mul(1, 1, NULL) &&
                                     !size_align_up(1, 1, NULL));
  bool small = true;
  for (size_t a = 0; a < 64; ++a)
    for (size_t b = 0; b < 64; ++b) {
      size_t sum = 0, product = 0;
      small = small && size_add(a, b, &sum) && sum == a + b &&
              size_mul(a, b, &product) && product == a * b;
    }
  CHECK("small arithmetic exhaustive grid", small);
  bool aligned = true;
  for (size_t a = 1; a <= 64; a *= 2)
    for (size_t v = 0; v < 200; ++v) {
      size_t expected = ((v + a - 1) / a) * a;
      aligned = aligned && size_align_up(v, a, &out) && out == expected;
    }
  CHECK("small alignment exhaustive grid", aligned);
  out = 12;
  CHECK("output can alias caller input", size_add(out, 5, &out) && out == 17 &&
                                             size_mul(out, 2, &out) &&
                                             out == 34);
  return finish();
}
