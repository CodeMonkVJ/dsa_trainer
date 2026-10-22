#include "lab.h"
bool philosopher_round(SemaphoreHandle_t forks[5], unsigned index,
                       TickType_t wait);

bool philosopher_round(SemaphoreHandle_t forks[5], unsigned index,
                       TickType_t wait) {
  (void)forks;
  (void)index;
  (void)wait; /* TODO */
  return false;
}
