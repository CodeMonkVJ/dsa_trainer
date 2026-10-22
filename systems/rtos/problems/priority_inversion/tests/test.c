#include "harness.h"
#include DSA_IMPLEMENTATION

typedef struct {
  SemaphoreHandle_t lock, low_ready, low_go, high_go, medium_go, done;
  unsigned trace[3], count;
  bool low_ok, high_ok;
} Inversion;
static void inv_record(Inversion *s, unsigned value) {
  taskENTER_CRITICAL();
  if (s->count < 3)
    s->trace[s->count++] = value;
  taskEXIT_CRITICAL();
}
static void inv_low(void *arg) {
  Inversion *s = arg;
  s->low_ok = resource_lock_take(s->lock, 100);
  xSemaphoreGive(s->low_ready);
  xSemaphoreTake(s->low_go, portMAX_DELAY);
  inv_record(s, 1);
  if (s->low_ok)
    s->low_ok = resource_lock_release(s->lock);
  xSemaphoreGive(s->done);
  vTaskSuspend(NULL);
  for (;;) {
  }
}
static void inv_high(void *arg) {
  Inversion *s = arg;
  xSemaphoreTake(s->high_go, portMAX_DELAY);
  s->high_ok = resource_lock_take(s->lock, 100);
  inv_record(s, 2);
  if (s->high_ok)
    s->high_ok = resource_lock_release(s->lock);
  xSemaphoreGive(s->done);
  vTaskSuspend(NULL);
  for (;;) {
  }
}
static void inv_medium(void *arg) {
  Inversion *s = arg;
  xSemaphoreTake(s->medium_go, portMAX_DELAY);
  inv_record(s, 3);
  xSemaphoreGive(s->done);
  vTaskSuspend(NULL);
  for (;;) {
  }
}
static void inversion_case(bool inherit) {
  Inversion s = {0};
  s.lock = resource_lock_create(inherit);
  s.low_ready = xSemaphoreCreateBinary();
  s.low_go = xSemaphoreCreateBinary();
  s.high_go = xSemaphoreCreateBinary();
  s.medium_go = xSemaphoreCreateBinary();
  s.done = xSemaphoreCreateCounting(3, 0);
  require(s.lock && s.low_ready && s.low_go && s.high_go && s.medium_go &&
          s.done);
  vTaskPrioritySet(NULL, 6);
  TaskHandle_t low, high, medium;
  spawn(inv_low, &s, 2, &low);
  require(xSemaphoreTake(s.low_ready, 100) == pdTRUE);
  spawn(inv_high, &s, 4, &high);
  spawn(inv_medium, &s, 3, &medium);
  xSemaphoreGive(s.high_go);
  for (unsigned i = 0; i < 20 && eTaskGetState(high) != eBlocked; ++i)
    vTaskDelay(1);
  /* Ensure high has passed its start gate and is now blocked on the resource.
   */
  require(uxSemaphoreGetCount(s.high_go) == 0 &&
          eTaskGetState(high) == eBlocked);
  CHECK("low owner priority matches primitive",
        uxTaskPriorityGet(low) == (inherit ? 4 : 2));
  xSemaphoreGive(s.low_go);
  xSemaphoreGive(s.medium_go);
  for (int i = 0; i < 3; ++i)
    require(xSemaphoreTake(s.done, 100) == pdTRUE);
  CHECK("owners acquire and release successfully",
        s.low_ok && s.high_ok && s.count == 3);
  CHECK("inheritance changes runnable order",
        inherit ? (s.trace[0] == 1 && s.trace[1] == 2 && s.trace[2] == 3)
                : (s.trace[0] == 3 && s.trace[1] == 1 && s.trace[2] == 2));
  vTaskDelete(low);
  vTaskDelete(high);
  vTaskDelete(medium);
  vTaskPrioritySet(NULL, 3);
  vSemaphoreDelete(s.lock);
  vSemaphoreDelete(s.low_ready);
  vSemaphoreDelete(s.low_go);
  vSemaphoreDelete(s.high_go);
  vSemaphoreDelete(s.medium_go);
  vSemaphoreDelete(s.done);
}

static void run_tests(void *unused) {
  (void)unused;
  CHECK("invalid handle rejected",
        !resource_lock_take(NULL, 0) && !resource_lock_release(NULL));
  inversion_case(false);
  inversion_case(true);
}
