#include "lab.h"
SemaphoreHandle_t resource_lock_create(bool inherit);
bool resource_lock_take(SemaphoreHandle_t lock, TickType_t wait);
bool resource_lock_release(SemaphoreHandle_t lock);

SemaphoreHandle_t resource_lock_create(bool inherit) {
  if (inherit)
    return xSemaphoreCreateMutex();
  SemaphoreHandle_t s = xSemaphoreCreateBinary();
  if (s)
    xSemaphoreGive(s);
  return s;
}
bool resource_lock_take(SemaphoreHandle_t s, TickType_t wait) {
  return s && xSemaphoreTake(s, wait) == pdTRUE;
}
bool resource_lock_release(SemaphoreHandle_t s) {
  return s && xSemaphoreGive(s) == pdTRUE;
}
