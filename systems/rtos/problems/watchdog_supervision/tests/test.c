#include "harness.h"
#include DSA_IMPLEMENTATION

static void run_tests(void *unused) {
  (void)unused;
  Watchdog w;
  CHECK("invalid watchdog config", !watchdog_init(&w, 0, 5, 0) &&
                                       !watchdog_init(&w, 5, 5, 0) &&
                                       !watchdog_init(&w, 2, 0, 0) &&
                                       !watchdog_init(&w, 2, portMAX_DELAY, 0));
  require(watchdog_init(&w, 2, 5, 100));
  CHECK("healthy at timeout boundary", watchdog_healthy(&w, 105));
  require(watchdog_beat(&w, 0, 106));
  CHECK("one healthy task cannot mask stale peer", !watchdog_healthy(&w, 106));
  require(watchdog_beat(&w, 1, 106));
  CHECK("all tasks recovered", watchdog_healthy(&w, 106));
  CHECK("invalid task cannot alter state",
        !watchdog_beat(&w, 2, 112) && !watchdog_healthy(&w, 112));
  watchdog_destroy(&w);
  require(watchdog_init(&w, 2, 6, portMAX_DELAY - 3));
  CHECK("wraparound within deadline", watchdog_healthy(&w, 2));
  CHECK("wraparound expired", !watchdog_healthy(&w, 3));
  watchdog_destroy(&w);
}
