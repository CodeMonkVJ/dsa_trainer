#include "lab.h"
bool notify_count(TaskHandle_t task);
uint32_t take_count(bool clear, TickType_t wait);
bool notify_bits(TaskHandle_t task, uint32_t bits);
bool wait_bits(uint32_t entry_mask, uint32_t exit_mask, uint32_t *out,
               TickType_t wait);

bool notify_count(TaskHandle_t task) {
  (void)task; /* TODO */
  return false;
}
uint32_t take_count(bool clear, TickType_t wait) {
  (void)clear;
  (void)wait; /* TODO */
  return 0;
}
bool notify_bits(TaskHandle_t task, uint32_t bits) {
  (void)task;
  (void)bits; /* TODO */
  return false;
}
bool wait_bits(uint32_t entry_mask, uint32_t exit_mask, uint32_t *out,
               TickType_t wait) {
  (void)entry_mask;
  (void)exit_mask;
  (void)out;
  (void)wait; /* TODO */
  return false;
}
