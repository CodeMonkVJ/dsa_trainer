#include "harness.h"
#include DSA_IMPLEMENTATION

typedef struct {
  EventGroupHandle_t group;
  SemaphoreHandle_t done;
  EventBits_t result;
} EventJob;
static void event_waiter(void *arg) {
  EventJob *j = arg;
  j->result = events_wait(j->group, 1, true, true, 100);
  xSemaphoreGive(j->done);
  vTaskSuspend(NULL);
  for (;;) {
  }
}
static void all_waiter(void *arg) {
  EventJob *j = arg;
  j->result = events_wait(j->group, 3, true, false, 1000);
  xSemaphoreGive(j->done);
  vTaskSuspend(NULL);
  for (;;) {
  }
}

static void run_tests(void *unused) {
  (void)unused;
  EventGroupHandle_t g = events_create();
  require(g != NULL);
  CHECK("invalid flags rejected", !events_set(g, 256) && !events_set(g, 0) &&
                                      !events_set(NULL, 1) &&
                                      events_wait(g, 0, false, false, 0) == 0);
  CHECK("wait-any snapshot before clear",
        events_set(g, 3) && events_wait(g, 1, false, true, 0) == 3 &&
            xEventGroupGetBits(g) == 2);
  CHECK("wait-all times out with current snapshot",
        events_wait(g, 3, true, false, 2) == 2);
  CHECK("wait-all succeeds", events_set(g, 1) &&
                                 events_wait(g, 3, true, true, 0) == 3 &&
                                 xEventGroupGetBits(g) == 0);
  SemaphoreHandle_t done = xSemaphoreCreateCounting(2, 0);
  require(done != NULL);
  EventJob j[2] = {{g, done, 0}, {g, done, 0}};
  TaskHandle_t t[2];
  spawn(event_waiter, &j[0], 4, &t[0]);
  spawn(event_waiter, &j[1], 4, &t[1]);
  CHECK("both event waiters blocked",
        eTaskGetState(t[0]) == eBlocked && eTaskGetState(t[1]) == eBlocked);
  require(events_set(g, 1));
  for (int i = 0; i < 2; ++i)
    require(xSemaphoreTake(done, 100) == pdTRUE);
  CHECK("one set wakes all matching clear-on-exit waiters",
        j[0].result == 1 && j[1].result == 1 && xEventGroupGetBits(g) == 0);
  for (int i = 0; i < 2; ++i)
    vTaskDelete(t[i]);
  EventJob all = {g, done, 0};
  TaskHandle_t all_task;
  spawn(all_waiter, &all, 4, &all_task);
  require(events_set(g, 1));
  CHECK("wait-all remains blocked after only one bit",
        eTaskGetState(all_task) == eBlocked);
  require(events_set(g, 2));
  require(xSemaphoreTake(done, 100) == pdTRUE);
  CHECK("wait-all wakes with the combined snapshot", all.result == 3);
  vTaskDelete(all_task);
  vSemaphoreDelete(done);
  vEventGroupDelete(g);
}
