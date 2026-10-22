#include "harness.h"
#include DSA_IMPLEMENTATION

static void run_tests(void *unused) {
  (void)unused;
  TaskHandle_t self = xTaskGetCurrentTaskHandle();
  uint32_t bits = 99;
  CHECK("empty notification times out", take_count(true, 2) == 0);
  CHECK("counting notifications accepted",
        notify_count(self) && notify_count(self) && notify_count(self));
  CHECK("decrement semantics",
        take_count(false, 0) == 3 && take_count(false, 0) == 2 &&
            take_count(false, 0) == 1 && take_count(false, 0) == 0);
  require(notify_count(self) && notify_count(self));
  CHECK("clear semantics",
        take_count(true, 0) == 2 && take_count(true, 0) == 0);
  CHECK("bit notifications coalesce",
        notify_bits(self, 1) && notify_bits(self, 4) &&
            wait_bits(0, UINT32_MAX, &bits, 0) && bits == 5);
  bits = 99;
  CHECK("timeout preserves output", !wait_bits(0, 0, &bits, 2) && bits == 99);
  CHECK("invalid targets rejected", !notify_count(NULL) &&
                                        !notify_bits(NULL, 1) &&
                                        !wait_bits(0, 0, NULL, 0));
}
