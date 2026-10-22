#include "harness.h"
#include DSA_IMPLEMENTATION

static void run_tests(void *unused) {
  (void)unused;
  Session s;
  CHECK("null session rejected",
        !session_init(NULL) && !session_send(NULL, 1, 0));
  session_close(NULL);
  for (int failure = 0; failure < 4; ++failure) {
    lab_fail_after = failure;
    CHECK("each initialization failure unwinds",
          !session_init(&s) && !s.running && lab_live_objects == 0);
    session_close(&s);
  }
  lab_fail_after = -1;
  require(session_init(&s));
  CHECK("negative request rejected", !session_send(&s, -1, 0));
  for (int i = 1; i <= 4; ++i)
    require(session_send(&s, i, 100));
  session_close(&s);
  CHECK("shutdown drains prior work",
        !s.running && s.processed == 4 && s.sum == 10 && lab_live_objects == 0);
  session_close(&s);
  CHECK("idempotent close and rejected new work",
        !session_send(&s, 5, 0) && lab_live_objects == 0);
  require(session_init(&s));
  vTaskDelay(1);
  CHECK("idle worker really blocked", eTaskGetState(s.worker) == eBlocked);
  session_close(&s);
  CHECK("blocked worker exits cleanly",
        !s.running && s.processed == 0 && lab_live_objects == 0);
}
