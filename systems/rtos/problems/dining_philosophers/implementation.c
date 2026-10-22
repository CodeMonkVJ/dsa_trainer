#include "lab.h"
bool philosopher_round(SemaphoreHandle_t forks[5], unsigned index,
                       TickType_t wait);

bool philosopher_round(SemaphoreHandle_t forks[5], unsigned index,
                       TickType_t wait) {
  if (!forks || index >= 5)
    return false;
  unsigned a = index, b = (index + 1) % 5;
  if (a > b) {
    unsigned t = a;
    a = b;
    b = t;
  }
  if (!forks[a] || !forks[b])
    return false;
  if (xSemaphoreTake(forks[a], wait) != pdTRUE)
    return false;
  if (xSemaphoreTake(forks[b], wait) != pdTRUE) {
    xSemaphoreGive(forks[a]);
    return false;
  }
  xSemaphoreGive(forks[b]);
  xSemaphoreGive(forks[a]);
  return true;
}
