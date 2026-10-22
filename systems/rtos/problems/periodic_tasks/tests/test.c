#include "harness.h"
#include DSA_IMPLEMENTATION

static void run_tests(void *unused) {
  (void)unused;
  TickType_t t = xTaskGetTickCount(), initial = t;
  (void)periodic_wait(&t, 20);
  CHECK("absolute release is not returned early",
        t == initial + 20 &&
            (TickType_t)(xTaskGetTickCount() - t) < portMAX_DELAY / 2);
  (void)periodic_wait(&t, 20);
  CHECK("next release preserves phase", t == initial + 40);
  t = xTaskGetTickCount() - 20;
  initial = t;
  CHECK("late release does not reset phase",
        !periodic_wait(&t, 5) && t == initial + 5);
  CHECK("invalid period preserves deadline",
        !periodic_wait(&t, 0) && t == initial + 5 && !periodic_wait(NULL, 1));
  CHECK("unsigned tick wrap", periodic_next(portMAX_DELAY - 2, 5) == 2);
  CHECK("ordinary next release", periodic_next(10, 7) == 17);
}
