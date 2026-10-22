#include "lab.h"
TickType_t periodic_next(TickType_t previous, TickType_t period);
bool periodic_wait(TickType_t *previous, TickType_t period);

TickType_t periodic_next(TickType_t previous, TickType_t period) {
  (void)previous;
  (void)period; /* TODO */
  return 0;
}
bool periodic_wait(TickType_t *previous, TickType_t period) {
  (void)previous;
  (void)period; /* TODO */
  return false;
}
