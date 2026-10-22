#include "lab.h"
typedef struct {
  SemaphoreHandle_t mutex;
  int value, inverse;
} SharedState;
bool shared_init(SharedState *s);
bool shared_add(SharedState *s, int delta, TickType_t wait);
bool shared_read(SharedState *s, int *value, int *inverse, TickType_t wait);
void shared_destroy(SharedState *s);

bool shared_init(SharedState *s) {
  if (!s)
    return false;
  *s = (SharedState){.mutex = xSemaphoreCreateMutex()};
  return s->mutex != NULL;
}
bool shared_add(SharedState *s, int delta, TickType_t wait) {
  if (!s || xSemaphoreTake(s->mutex, wait) != pdTRUE)
    return false;
  s->value += delta;
  s->inverse = -s->value;
  xSemaphoreGive(s->mutex);
  return true;
}
bool shared_read(SharedState *s, int *value, int *inverse, TickType_t wait) {
  if (!s || !value || !inverse || xSemaphoreTake(s->mutex, wait) != pdTRUE)
    return false;
  *value = s->value;
  *inverse = s->inverse;
  xSemaphoreGive(s->mutex);
  return true;
}
void shared_destroy(SharedState *s) {
  if (s)
    vSemaphoreDelete(s->mutex);
}
