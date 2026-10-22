#include "lab.h"
typedef struct {
  TickType_t last[4], timeout;
  unsigned tasks;
  SemaphoreHandle_t mutex;
} Watchdog;
bool watchdog_init(Watchdog *w, unsigned tasks, TickType_t timeout,
                   TickType_t now);
bool watchdog_beat(Watchdog *w, unsigned task, TickType_t now);
bool watchdog_healthy(Watchdog *w, TickType_t now);
void watchdog_destroy(Watchdog *w);

bool watchdog_init(Watchdog *w, unsigned tasks, TickType_t timeout,
                   TickType_t now) {
  if (!w || !tasks || tasks > 4 || !timeout || timeout >= portMAX_DELAY / 2)
    return false;
  *w = (Watchdog){
      .tasks = tasks, .timeout = timeout, .mutex = xSemaphoreCreateMutex()};
  if (!w->mutex)
    return false;
  for (unsigned i = 0; i < tasks; ++i)
    w->last[i] = now;
  return true;
}
bool watchdog_beat(Watchdog *w, unsigned task, TickType_t now) {
  if (!w || task >= w->tasks)
    return false;
  xSemaphoreTake(w->mutex, portMAX_DELAY);
  w->last[task] = now;
  xSemaphoreGive(w->mutex);
  return true;
}
bool watchdog_healthy(Watchdog *w, TickType_t now) {
  if (!w)
    return false;
  xSemaphoreTake(w->mutex, portMAX_DELAY);
  bool ok = true;
  for (unsigned i = 0; i < w->tasks; ++i)
    if ((TickType_t)(now - w->last[i]) > w->timeout)
      ok = false;
  xSemaphoreGive(w->mutex);
  return ok;
}
void watchdog_destroy(Watchdog *w) {
  if (w)
    vSemaphoreDelete(w->mutex);
}
