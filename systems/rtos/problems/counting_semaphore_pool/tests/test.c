#include "harness.h"
#include DSA_IMPLEMENTATION

static void run_tests(void *unused) {
  (void)unused;
  PermitPool p;
  CHECK("invalid pool capacity", !pool_init(&p, 0) && !pool_init(NULL, 1));
  require(pool_init(&p, 2));
  CHECK("all permits initially available",
        pool_acquire(&p, 0) && pool_acquire(&p, 0));
  CHECK("exhausted pool times out", !pool_acquire(&p, 2));
  CHECK("return allows reuse", pool_release(&p) && pool_acquire(&p, 0));
  CHECK("all permits returned", pool_release(&p) && pool_release(&p));
  CHECK("over-release rejected", !pool_release(&p));
  CHECK("invalid pool rejected", !pool_acquire(NULL, 0) && !pool_release(NULL));
  pool_destroy(&p);
}
