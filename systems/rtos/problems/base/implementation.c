#include "lab.h"
bool scheduling_trace(unsigned *out, size_t capacity);

typedef struct {
  unsigned *out;
  SemaphoreHandle_t gate, high_done, low_done;
  unsigned count;
} Schedule;
static void schedule_record(Schedule *s, unsigned value) {
  taskENTER_CRITICAL();
  s->out[s->count++] = value;
  taskEXIT_CRITICAL();
}
static void scheduled_high(void *arg) {
  Schedule *s = arg;
  xSemaphoreTake(s->gate, portMAX_DELAY);
  schedule_record(s, 2);
  xSemaphoreGive(s->high_done);
  vTaskDelete(NULL);
}
static void scheduled_low(void *arg) {
  Schedule *s = arg;
  schedule_record(s, 1);
  xSemaphoreGive(s->gate);
  schedule_record(s, 3);
  xSemaphoreGive(s->low_done);
  vTaskDelete(NULL);
}
bool scheduling_trace(unsigned *out, size_t capacity) {
  if (!out || capacity < 3)
    return false;
  Schedule s = {.out = out};
  s.gate = xSemaphoreCreateBinary();
  s.high_done = xSemaphoreCreateBinary();
  s.low_done = xSemaphoreCreateBinary();
  if (!s.gate || !s.high_done || !s.low_done) {
    if (s.gate)
      vSemaphoreDelete(s.gate);
    if (s.high_done)
      vSemaphoreDelete(s.high_done);
    if (s.low_done)
      vSemaphoreDelete(s.low_done);
    return false;
  }
  TaskHandle_t high, low;
  configASSERT(xTaskCreate(scheduled_high, "high", configMINIMAL_STACK_SIZE, &s,
                           4, &high) == pdPASS);
  configASSERT(xTaskCreate(scheduled_low, "low", configMINIMAL_STACK_SIZE, &s,
                           2, &low) == pdPASS);
  xSemaphoreTake(s.high_done, portMAX_DELAY);
  xSemaphoreTake(s.low_done, portMAX_DELAY);
  vSemaphoreDelete(s.gate);
  vSemaphoreDelete(s.high_done);
  vSemaphoreDelete(s.low_done);
  return true;
}
