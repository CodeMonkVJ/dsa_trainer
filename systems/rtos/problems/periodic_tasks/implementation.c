#include "lab.h"
TickType_t periodic_next(TickType_t previous, TickType_t period);
bool periodic_wait(TickType_t *previous, TickType_t period);

TickType_t periodic_next(TickType_t previous, TickType_t period) {
  return previous + period;
}
bool periodic_wait(TickType_t *previous, TickType_t period) {
  if (!previous || !period)
    return false;
  return xTaskDelayUntil(previous, period) == pdTRUE;
}
