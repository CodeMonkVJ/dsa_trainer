#include "harness.h"
#include DSA_IMPLEMENTATION

static void run_tests(void *unused) {
  (void)unused;
  MemoryPool p;
  CHECK("invalid pool size", !mem_pool_init(&p, 0) && !mem_pool_init(&p, 5));
  require(mem_pool_init(&p, 2));
  unsigned char *a = mem_pool_get(&p, 0), *b = mem_pool_get(&p, 0);
  require(a && b);
  CHECK("distinct bounded blocks", a != b && mem_pool_get(&p, 0) == NULL);
  memset(a, 0xa5, 32);
  memset(b, 0x5a, 32);
  CHECK("blocks do not overlap", a[31] == 0xa5 && b[0] == 0x5a);
  int foreign = 0;
  CHECK("invalid returns rejected", !mem_pool_put(&p, NULL) &&
                                        !mem_pool_put(&p, &foreign) &&
                                        !mem_pool_put(&p, a + 1));
  CHECK("return validates ownership",
        mem_pool_put(&p, a) && !mem_pool_put(&p, a));
  void *again = mem_pool_get(&p, 0);
  CHECK("released block reused", again == a);
  require(xSemaphoreTake(p.mutex, 0) == pdTRUE);
  CHECK("mutex timeout", mem_pool_get(&p, 0) == NULL);
  xSemaphoreGive(p.mutex);
  CHECK("all blocks returned", mem_pool_put(&p, again) && mem_pool_put(&p, b));
  mem_pool_destroy(&p);
}
