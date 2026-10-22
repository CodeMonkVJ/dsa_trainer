#include "harness.h"
#include DSA_IMPLEMENTATION

static void run_tests(void *unused) {
  (void)unused;
  QueueHandle_t events = xQueueCreate(4, sizeof(uintptr_t));
  require(events != NULL);
  PulseTimer p;
  uintptr_t id = 0;
  CHECK("invalid timer period",
        !pulse_create(&p, 0, false, events, 1) && p.handle == NULL);
  require(pulse_create(&p, 3, false, events, 42));
  CHECK("starts one-shot", pulse_reset(&p));
  CHECK("one-shot delivery",
        xQueueReceive(events, &id, 100) == pdTRUE && id == 42);
  CHECK("one-shot does not reload", xQueueReceive(events, &id, 6) == pdFALSE);
  CHECK("reset restarts one-shot",
        pulse_reset(&p) && xQueueReceive(events, &id, 100) == pdTRUE &&
            id == 42);
  CHECK("synchronous destroy", pulse_destroy(&p) && p.handle == NULL);
  require(pulse_create(&p, 3, true, events, 7));
  require(pulse_reset(&p));
  CHECK("periodic first event",
        xQueueReceive(events, &id, 100) == pdTRUE && id == 7);
  CHECK("periodic second event",
        xQueueReceive(events, &id, 100) == pdTRUE && id == 7);
  CHECK("synchronous stop", pulse_stop(&p));
  xQueueReset(events);
  CHECK("no callbacks after stop", xQueueReceive(events, &id, 8) == pdFALSE);
  CHECK("destroy stopped timer", pulse_destroy(&p) && !pulse_destroy(&p));
  /* A full output queue must not block the daemon or prevent a barrier. */
  vQueueDelete(events);
  events = xQueueCreate(1, sizeof(uintptr_t));
  require(events != NULL);
  require(pulse_create(&p, 1, true, events, 9));
  require(pulse_reset(&p));
  vTaskDelay(8);
  CHECK("full event queue cannot stall daemon",
        pulse_stop(&p) && pulse_destroy(&p));
  vQueueDelete(events);
}
