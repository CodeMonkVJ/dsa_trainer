#include "lab.h"
bool notify_count(TaskHandle_t task);
uint32_t take_count(bool clear, TickType_t wait);
bool notify_bits(TaskHandle_t task, uint32_t bits);
bool wait_bits(uint32_t entry_mask, uint32_t exit_mask, uint32_t *out,
               TickType_t wait);

bool notify_count(TaskHandle_t task) {
  if (!task)
    return false;
  return xTaskNotifyGive(task) == pdPASS;
}
uint32_t take_count(bool clear, TickType_t wait) {
  return ulTaskNotifyTake(clear ? pdTRUE : pdFALSE, wait);
}
bool notify_bits(TaskHandle_t task, uint32_t bits) {
  return task && xTaskNotify(task, bits, eSetBits) == pdPASS;
}
bool wait_bits(uint32_t entry, uint32_t exit, uint32_t *out, TickType_t wait) {
  if (!out)
    return false;
  uint32_t v;
  if (xTaskNotifyWait(entry, exit, &v, wait) != pdTRUE)
    return false;
  *out = v;
  return true;
}
