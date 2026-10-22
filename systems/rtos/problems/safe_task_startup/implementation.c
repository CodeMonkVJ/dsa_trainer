#include "lab.h"
bool startup_copy(int value, int *out);

typedef struct {
  int *input, *out;
  SemaphoreHandle_t copied, done;
} Startup;
static void startup_worker(void *arg) {
  Startup *s = arg;
  int local = *s->input;
  xSemaphoreGive(s->copied);
  *s->out = local;
  xSemaphoreGive(s->done);
  vTaskSuspend(NULL);
  for (;;) {
  }
}
bool startup_copy(int value, int *out) {
  if (!out)
    return false;
  Startup s = {.input = &value};
  int result = 0;
  s.out = &result;
  s.copied = lab_binary_create();
  s.done = lab_binary_create();
  TaskHandle_t task = NULL;
  if (!s.copied || !s.done || !lab_task_create(startup_worker, &s, 2, &task)) {
    lab_queue_delete(s.copied);
    lab_queue_delete(s.done);
    return false;
  }
  xSemaphoreTake(s.copied, portMAX_DELAY);
  value = -999;
  xSemaphoreTake(s.done, portMAX_DELAY);
  lab_task_delete(task);
  lab_queue_delete(s.copied);
  lab_queue_delete(s.done);
  *out = result;
  return true;
}
