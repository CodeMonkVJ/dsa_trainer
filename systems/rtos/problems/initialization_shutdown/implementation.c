#include "lab.h"
typedef struct {
  QueueHandle_t queue;
  SemaphoreHandle_t mutex, done;
  TaskHandle_t worker;
  bool running;
  unsigned processed;
  int sum;
} Session;
bool session_init(Session *s);
bool session_send(Session *s, int value, TickType_t wait);
void session_close(Session *s);

static void session_worker(void *arg) {
  Session *s = arg;
  for (;;) {
    int v;
    xQueueReceive(s->queue, &v, portMAX_DELAY);
    if (v < 0)
      break;
    xSemaphoreTake(s->mutex, portMAX_DELAY);
    ++s->processed;
    s->sum += v;
    xSemaphoreGive(s->mutex);
  }
  xSemaphoreGive(s->done);
  vTaskSuspend(NULL);
  for (;;) {
  }
}
bool session_init(Session *s) {
  if (!s)
    return false;
  *s = (Session){0};
  s->queue = lab_queue_create(2, sizeof(int));
  if (s->queue)
    s->mutex = lab_mutex_create();
  if (s->mutex)
    s->done = lab_binary_create();
  if (s->done && lab_task_create(session_worker, s, 2, &s->worker)) {
    s->running = true;
    return true;
  }
  lab_queue_delete(s->queue);
  lab_queue_delete(s->mutex);
  lab_queue_delete(s->done);
  *s = (Session){0};
  return false;
}
bool session_send(Session *s, int value, TickType_t wait) {
  return s && s->running && value >= 0 &&
         xQueueSend(s->queue, &value, wait) == pdTRUE;
}
void session_close(Session *s) {
  if (!s || !s->running)
    return;
  int stop = -1;
  xQueueSend(s->queue, &stop, portMAX_DELAY);
  xSemaphoreTake(s->done, portMAX_DELAY);
  lab_task_delete(s->worker);
  lab_queue_delete(s->queue);
  lab_queue_delete(s->mutex);
  lab_queue_delete(s->done);
  s->queue = NULL;
  s->mutex = NULL;
  s->done = NULL;
  s->worker = NULL;
  s->running = false;
}
