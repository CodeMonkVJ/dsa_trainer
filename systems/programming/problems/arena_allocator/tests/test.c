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
  _Alignas(max_align_t) unsigned char storage[128], other_storage[32];
  memset(storage, 0xa5, sizeof storage);
  Arena a, b;
  CHECK("invalid initialization",
        !arena_init(NULL, storage, 128) && !arena_init(&a, NULL, 128));
  if (_Alignof(max_align_t) > 1)
    CHECK("misaligned base rejected", !arena_init(&a, storage + 1, 100));
  REQUIRE(arena_init(&a, storage, sizeof storage) &&
          arena_init(&b, other_storage, sizeof other_storage));
  unsigned char *first = arena_alloc(&a, 3, 1);
  CHECK("initial allocation and untouched bytes",
        first == storage && a.used == 3 && first[0] == 0xa5);
  unsigned char *aligned = arena_alloc(&a, 8, _Alignof(max_align_t));
  CHECK("requested alignment and non-overlap",
        aligned != NULL && (uintptr_t)aligned % _Alignof(max_align_t) == 0 &&
            aligned >= first + 3);
  size_t before = a.used;
  unsigned char snapshot[128];
  memcpy(snapshot, storage, sizeof storage);
  CHECK("invalid allocation preserves state",
        !arena_alloc(&a, 0, 1) && !arena_alloc(&a, 1, 0) &&
            !arena_alloc(&a, 1, 3) &&
            !arena_alloc(&a, 1, _Alignof(max_align_t) * 2) && a.used == before);
  CHECK("overflow request preserves state and bytes",
        !arena_alloc(&a, SIZE_MAX, 1) && a.used == before &&
            memcmp(snapshot, storage, sizeof storage) == 0);
  ArenaMark mark = arena_mark(&a), foreign = arena_mark(&b);
  REQUIRE(arena_alloc(&a, 5, 1) != NULL);
  before = a.used;
  CHECK("foreign mark rejected",
        !arena_rewind(&a, foreign) && a.used == before);
  CHECK("rewind reclaims used space",
        arena_rewind(&a, mark) && a.used == mark.offset);
  CHECK("rewind invalidates all prior marks", !arena_rewind(&a, mark));
  mark = arena_mark(&a);
  CHECK("reset empties arena", arena_reset(&a) && a.used == 0);
  CHECK("reset rejects stale mark", !arena_rewind(&a, mark));
  CHECK("whole capacity fits exactly",
        arena_alloc(&a, 128, 1) == storage && a.used == 128);
  CHECK("exhaustion does not advance", !arena_alloc(&a, 1, 1) && a.used == 128);
  REQUIRE(arena_reset(&a));
  mark = arena_mark(&a);
  mark.offset = 1;
  CHECK("future offset rejected", !arena_rewind(&a, mark) && a.used == 0);
  a.epoch = UINT64_MAX;
  mark = arena_mark(&a);
  CHECK("epoch exhaustion never wraps",
        !arena_reset(&a) && !arena_rewind(&a, mark) && a.epoch == UINT64_MAX);
  REQUIRE(arena_init(&b, other_storage, 0));
  CHECK("zero capacity is empty", !arena_alloc(&b, 1, 1) && b.used == 0);
  CHECK("null operations rejected",
        !arena_alloc(NULL, 1, 1) && !arena_reset(NULL) &&
            !arena_rewind(NULL, mark) && arena_mark(NULL).owner == NULL);
  REQUIRE(arena_init(&b, other_storage, 3));
  REQUIRE(arena_alloc(&b, 3, 1) != NULL);
  CHECK("padding cannot bypass capacity",
        !arena_alloc(&b, 1, _Alignof(max_align_t)) && b.used == 3);
  return finish();
}
