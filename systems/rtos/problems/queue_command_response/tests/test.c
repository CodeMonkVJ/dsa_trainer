#include "harness.h"
#include DSA_IMPLEMENTATION

static void run_tests(void *unused) {
  (void)unused;
  Channel c;
  Message m = {1, 42}, out = {99, 99};
  CHECK("invalid capacity", !channel_init(&c, 0) && !channel_init(NULL, 1));
  require(channel_init(&c, 2));
  CHECK("empty queue timeout preserves output",
        !channel_receive(&c, &out, false, 2) && out.id == 99 &&
            out.value == 99);
  CHECK("request is copied", channel_send(&c, &m, false, 0));
  m.value = 999;
  m.id = 2;
  CHECK("second request fits", channel_send(&c, &m, false, 0));
  CHECK("full queue rejects with timeout", !channel_send(&c, &m, false, 2));
  CHECK("FIFO first payload",
        channel_receive(&c, &out, false, 0) && out.id == 1 && out.value == 42);
  CHECK("FIFO second payload",
        channel_receive(&c, &out, false, 0) && out.id == 2 && out.value == 999);
  CHECK("response route independent",
        channel_send(&c, &out, true, 0) && !channel_receive(&c, &m, false, 0) &&
            channel_receive(&c, &m, true, 0) && m.id == 2);
  CHECK("invalid arguments", !channel_send(&c, NULL, false, 0) &&
                                 !channel_receive(&c, NULL, false, 0));
  channel_destroy(&c);
  CHECK("channel resource cleanup", lab_live_objects == 0);
  lab_fail_after = 1;
  CHECK("partial allocation cleanup",
        !channel_init(&c, 2) && lab_live_objects == 0);
  lab_fail_after = -1;
}
