#include "harness.h"
#include DSA_IMPLEMENTATION

static void run_tests(void *unused) {
  (void)unused;
  int out = 99;
  CHECK("null output rejected", !startup_copy(1, NULL));
  CHECK("worker owns a copy", startup_copy(42, &out) && out == 42);
  CHECK("negative parameter survives handoff",
        startup_copy(-7, &out) && out == -7);
  for (int failure = 0; failure < 3; ++failure) {
    lab_fail_after = failure;
    out = 99;
    CHECK("startup failure unwinds and preserves output",
          !startup_copy(42, &out) && out == 99 && lab_live_objects == 0);
  }
  lab_fail_after = -1;
  CHECK("startup recovers after failures",
        startup_copy(5, &out) && out == 5 && lab_live_objects == 0);
}
