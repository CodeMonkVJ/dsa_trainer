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
static void increment(void *p) { ++*(int *)p; }
static int order[3], order_count;
static void record(void *p) { order[order_count++] = *(int *)p; }
typedef struct {
  TimerService *s;
  uint64_t cancel;
  int calls;
} Reentrant;
static void reenter(void *p) {
  Reentrant *r = p;
  ++r->calls;
  timer_cancel(r->s, r->cancel);
  timer_register(r->s, 0, increment, &r->calls);
  CHECK(timer_expire(r->s, 100) == 0);
}
int main(void) {
  TimerService s;
  timer_init(&s);
  int n = 0;
  int first = 1, second = 2, third = 3;
  timer_register(&s, 20, record, &third);
  timer_register(&s, 10, record, &first);
  timer_register(&s, 10, record, &second);
  CHECK(timer_expire(&s, 20) == 3 && order_count == 3 && order[0] == 1 &&
        order[1] == 2 && order[2] == 3);
  uint64_t a = timer_register(&s, 10, increment, &n),
           b = timer_register(&s, 20, increment, &n);
  CHECK(a && b && a != b && timer_expire(&s, 9) == 0);
  CHECK(timer_cancel(&s, b) && !timer_cancel(&s, b));
  CHECK(timer_expire(&s, 10) == 1 && n == 1 && !timer_cancel(&s, a));
  CHECK(timer_expire(&s, 100) == 0 && !timer_register(&s, 0, NULL, NULL));
  for (int i = 0; i < 16; ++i)
    CHECK(timer_register(&s, 0, increment, &n) != 0);
  CHECK(!timer_register(&s, 0, increment, &n) && timer_expire(&s, 0) == 16);
  timer_init(&s);
  Reentrant r = {&s, 0, 0};
  timer_register(&s, 0, reenter, &r);
  r.cancel = timer_register(&s, 0, increment, &n);
  CHECK(timer_expire(&s, 0) == 1 && r.calls == 1);
  CHECK(timer_expire(&s, 0) == 1 && r.calls == 2);
  s.next_id = UINT64_MAX;
  CHECK(timer_register(&s, 1, increment, &n) == UINT64_MAX &&
        !timer_register(&s, 1, increment, &n));
  CHECK(timer_expire(&s, UINT64_MAX) == 1 &&
        !timer_register(&s, 0, increment, &n));
  timer_init(&s);
  uint64_t old = timer_register(&s, 0, increment, &n);
  CHECK(timer_cancel(&s, old));
  uint64_t replacement = timer_register(&s, UINT64_MAX, increment, &n);
  CHECK(replacement != 0 && replacement != old && !timer_cancel(&s, old));
  CHECK(timer_expire(&s, UINT64_MAX - 1) == 0 &&
        timer_expire(&s, UINT64_MAX) == 1);
  CHECK(!timer_cancel(&s, 0) && !timer_cancel(NULL, 1) &&
        timer_expire(NULL, 0) == 0);
  printf("DSA_RESULT {\"passed\":%d,\"total\":%d}\n", passed, total);
  return passed == total ? 0 : 1;
}
