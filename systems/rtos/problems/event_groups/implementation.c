#include "lab.h"
EventGroupHandle_t events_create(void);
bool events_set(EventGroupHandle_t group, EventBits_t bits);
EventBits_t events_wait(EventGroupHandle_t group, EventBits_t mask, bool all,
                        bool clear, TickType_t wait);

EventGroupHandle_t events_create(void) { return xEventGroupCreate(); }
bool events_set(EventGroupHandle_t g, EventBits_t bits) {
  if (!g || !bits || (bits & ~(EventBits_t)255))
    return false;
  xEventGroupSetBits(g, bits);
  return true;
}
EventBits_t events_wait(EventGroupHandle_t g, EventBits_t mask, bool all,
                        bool clear, TickType_t wait) {
  if (!g || !mask || (mask & ~(EventBits_t)255))
    return 0;
  return xEventGroupWaitBits(g, mask, clear ? pdTRUE : pdFALSE,
                             all ? pdTRUE : pdFALSE, wait);
}
