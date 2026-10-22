#include "lab.h"
typedef struct {
  unsigned data[4], capacity, head, tail, count;
  bool closed;
  SemaphoreHandle_t mutex, slots, items;
} Stream;
bool stream_init(Stream *s, unsigned capacity);
bool stream_push(Stream *s, unsigned value);
bool stream_pop(Stream *s, unsigned *out);
void stream_close(Stream *s);
void stream_destroy(Stream *s);

bool stream_init(Stream *s, unsigned cap) {
  if (!s || !cap || cap > 4)
    return false;
  *s = (Stream){.capacity = cap};
  s->mutex = xSemaphoreCreateMutex();
  s->slots = xSemaphoreCreateCounting(cap, cap);
  s->items = xSemaphoreCreateCounting(cap, 0);
  if (!s->mutex || !s->slots || !s->items) {
    stream_destroy(s);
    return false;
  }
  return true;
}
bool stream_push(Stream *s, unsigned value) {
  if (!s)
    return false;
  for (;;) {
    if (xSemaphoreTake(s->slots, 1) == pdTRUE) {
      xSemaphoreTake(s->mutex, portMAX_DELAY);
      if (s->closed) {
        xSemaphoreGive(s->mutex);
        xSemaphoreGive(s->slots);
        return false;
      }
      s->data[s->head] = value;
      s->head = (s->head + 1) % s->capacity;
      ++s->count;
      xSemaphoreGive(s->mutex);
      xSemaphoreGive(s->items);
      return true;
    }
    xSemaphoreTake(s->mutex, portMAX_DELAY);
    bool closed = s->closed;
    xSemaphoreGive(s->mutex);
    if (closed)
      return false;
  }
}
bool stream_pop(Stream *s, unsigned *out) {
  if (!s || !out)
    return false;
  for (;;) {
    if (xSemaphoreTake(s->items, 1) == pdTRUE) {
      xSemaphoreTake(s->mutex, portMAX_DELAY);
      *out = s->data[s->tail];
      s->tail = (s->tail + 1) % s->capacity;
      --s->count;
      xSemaphoreGive(s->mutex);
      xSemaphoreGive(s->slots);
      return true;
    }
    xSemaphoreTake(s->mutex, portMAX_DELAY);
    bool ended = s->closed && !s->count;
    xSemaphoreGive(s->mutex);
    if (ended)
      return false;
  }
}
void stream_close(Stream *s) {
  if (!s)
    return;
  xSemaphoreTake(s->mutex, portMAX_DELAY);
  s->closed = true;
  xSemaphoreGive(s->mutex);
}
void stream_destroy(Stream *s) {
  if (!s)
    return;
  if (s->mutex)
    vSemaphoreDelete(s->mutex);
  if (s->slots)
    vSemaphoreDelete(s->slots);
  if (s->items)
    vSemaphoreDelete(s->items);
}
