#include "lab.h"
EventGroupHandle_t events_create(void);
bool events_set(EventGroupHandle_t group, EventBits_t bits);
EventBits_t events_wait(EventGroupHandle_t group, EventBits_t mask, bool all,
                        bool clear, TickType_t wait);

EventGroupHandle_t events_create(void) { /* TODO */ return NULL; }
bool events_set(EventGroupHandle_t group, EventBits_t bits) {
  (void)group;
  (void)bits; /* TODO */
  return false;
}
EventBits_t events_wait(EventGroupHandle_t group, EventBits_t mask, bool all,
                        bool clear, TickType_t wait) {
  (void)group;
  (void)mask;
  (void)all;
  (void)clear;
  (void)wait; /* TODO */
  return 0;
}
