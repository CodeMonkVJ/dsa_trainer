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
  Ring r;
  unsigned char s[3], v = 99;
  CHECK(!ring_init(&r, s, 0) && !ring_init(NULL, s, 3) &&
        !ring_init(&r, NULL, 3));
  CHECK(ring_init(&r, s, 3) && !ring_pop(&r, &v) && v == 99);
  CHECK(ring_push(&r, 1) && ring_push(&r, 2) && ring_push(&r, 3) &&
        !ring_push(&r, 4) && r.count == 3);
  CHECK(ring_pop(&r, &v) && v == 1 && ring_push(&r, 4));
  CHECK(ring_pop(&r, &v) && v == 2 && ring_pop(&r, &v) && v == 3 &&
        ring_pop(&r, &v) && v == 4);
  CHECK(!ring_pop(&r, &v) && v == 4 && !ring_pop(&r, NULL));
  CHECK(ring_init(&r, s, 1));
  bool wrapped = true;
  for (unsigned i = 0; i < 1000; ++i)
    wrapped = wrapped && ring_push(&r, (unsigned char)i) && !ring_push(&r, 0) &&
              ring_pop(&r, &v) && v == (unsigned char)i;
  CHECK(wrapped);
  CHECK(!ring_push(NULL, 1) && !ring_pop(NULL, &v));
  CHECK(ring_init(&r, s, 3) && ring_push(&r, 255));
  size_t saved_head = r.head, saved_tail = r.tail, saved_count = r.count;
  CHECK(!ring_pop(&r, NULL) && r.head == saved_head && r.tail == saved_tail &&
        r.count == saved_count);
  CHECK(ring_pop(&r, &v) && v == 255);
  bool fifo = true;
  for (unsigned cycle = 0; cycle < 100; ++cycle) {
    for (unsigned j = 0; j < 3; ++j)
      fifo = ring_push(&r, (unsigned char)(cycle + j)) && fifo;
    saved_head = r.head;
    saved_tail = r.tail;
    fifo = !ring_push(&r, 99) && r.head == saved_head && r.tail == saved_tail &&
           r.count == 3 && fifo;
    for (unsigned j = 0; j < 3; ++j) {
      bool popped = ring_pop(&r, &v);
      fifo = popped && v == (unsigned char)(cycle + j) && fifo;
    }
  }
  CHECK(fifo);
  printf("DSA_RESULT {\"passed\":%d,\"total\":%d}\n", passed, total);
  return passed == total ? 0 : 1;
}
