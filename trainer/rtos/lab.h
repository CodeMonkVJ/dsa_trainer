#ifndef RTOS_LAB_H
#define RTOS_LAB_H
#include "FreeRTOS.h"
#include "event_groups.h"
#include "queue.h"
#include "semphr.h"
#include "task.h"
#include "timers.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

/* These factories make initialization failures reproducible. Students must
   use them in the initialization/shutdown exercise. Other labs use RTOS APIs.
 */
static int lab_fail_after = -1, lab_live_objects;
static inline bool lab_allow_create(void) {
  if (lab_fail_after == 0)
    return false;
  if (lab_fail_after > 0)
    --lab_fail_after;
  return true;
}
static inline QueueHandle_t lab_queue_create(UBaseType_t n, UBaseType_t size) {
  if (!lab_allow_create())
    return NULL;
  QueueHandle_t q = xQueueCreate(n, size);
  if (q)
    ++lab_live_objects;
  return q;
}
static inline SemaphoreHandle_t lab_mutex_create(void) {
  if (!lab_allow_create())
    return NULL;
  SemaphoreHandle_t m = xSemaphoreCreateMutex();
  if (m)
    ++lab_live_objects;
  return m;
}
static inline void lab_queue_delete(QueueHandle_t q) {
  if (q) {
    vQueueDelete(q);
    --lab_live_objects;
  }
}
static inline SemaphoreHandle_t lab_binary_create(void) {
  if (!lab_allow_create())
    return NULL;
  SemaphoreHandle_t s = xSemaphoreCreateBinary();
  if (s)
    ++lab_live_objects;
  return s;
}
static inline bool lab_task_create(TaskFunction_t fn, void *arg,
                                   UBaseType_t priority, TaskHandle_t *out) {
  if (!lab_allow_create())
    return false;
  if (xTaskCreate(fn, "owned-worker", configMINIMAL_STACK_SIZE, arg, priority,
                  out) != pdPASS)
    return false;
  ++lab_live_objects;
  return true;
}
static inline void lab_task_delete(TaskHandle_t task) {
  if (task) {
    vTaskDelete(task);
    --lab_live_objects;
  }
}
#endif
