#include "harness.h"
#include DSA_IMPLEMENTATION

static void run_tests(void *unused) {
  (void)unused;
  unsigned out[4] = {0, 0, 0, 99};
  CHECK("rejects invalid output",
        !scheduling_trace(NULL, 3) && !scheduling_trace(out, 2));
  CHECK("blocked high task lets lower task run", scheduling_trace(out, 4));
  CHECK("priority handoff order",
        out[0] == 1 && out[1] == 2 && out[2] == 3 && out[3] == 99);
  memset(out, 0, sizeof out);
  CHECK("repeatable without startup sleeps",
        scheduling_trace(out, 3) && out[0] == 1 && out[1] == 2 && out[2] == 3);
}
