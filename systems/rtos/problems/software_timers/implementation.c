#include "lab.h"
typedef struct {
  TimerHandle_t handle;
  QueueHandle_t events;
  uintptr_t id;
} PulseTimer;
bool pulse_create(PulseTimer *p, TickType_t period, bool periodic,
                  QueueHandle_t events, uintptr_t id);
bool pulse_reset(PulseTimer *p);
bool pulse_stop(PulseTimer *p);
bool pulse_destroy(PulseTimer *p);

static void pulse_callback(TimerHandle_t handle) {
  PulseTimer *p = pvTimerGetTimerID(handle);
  xQueueSend(p->events, &p->id, 0);
}
static void pulse_barrier(void *arg, uint32_t value) {
  (void)value;
  xSemaphoreGive((SemaphoreHandle_t)arg);
}
bool pulse_create(PulseTimer *p, TickType_t period, bool periodic,
                  QueueHandle_t events, uintptr_t id) {
  if (!p)
    return false;
  *p = (PulseTimer){.events = events, .id = id};
  if (!period || !events)
    return false;
  p->handle = xTimerCreate("pulse", period, periodic ? pdTRUE : pdFALSE, p,
                           pulse_callback);
  return p->handle != NULL;
}
bool pulse_reset(PulseTimer *p) {
  return p && p->handle && xTimerReset(p->handle, portMAX_DELAY) == pdPASS;
}
static bool pulse_control(PulseTimer *p, bool destroy) {
  if (!p || !p->handle)
    return false;
  SemaphoreHandle_t done = xSemaphoreCreateBinary();
  if (!done)
    return false;
  configASSERT(xTimerStop(p->handle, portMAX_DELAY) == pdPASS);
  if (destroy)
    configASSERT(xTimerDelete(p->handle, portMAX_DELAY) == pdPASS);
  configASSERT(xTimerPendFunctionCall(pulse_barrier, done, 0, portMAX_DELAY) ==
               pdPASS);
  configASSERT(xSemaphoreTake(done, portMAX_DELAY) == pdTRUE);
  vSemaphoreDelete(done);
  if (destroy)
    p->handle = NULL;
  return true;
}
bool pulse_stop(PulseTimer *p) { return pulse_control(p, false); }
bool pulse_destroy(PulseTimer *p) { return pulse_control(p, true); }
