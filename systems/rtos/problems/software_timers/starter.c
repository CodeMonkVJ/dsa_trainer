#include "lab.h"
typedef struct {
  TimerHandle_t handle;
  QueueHandle_t events;
  uintptr_t id;
} PulseTimer;
bool pulse_create(PulseTimer *p, TickType_t period, bool periodic,
                  QueueHandle_t events, uintptr_t id);
bool pulse_reset(PulseTimer *p);
bool pulse_stop(PulseTimer *p);
bool pulse_destroy(PulseTimer *p);

bool pulse_create(PulseTimer *p, TickType_t period, bool periodic,
                  QueueHandle_t events, uintptr_t id) {
  (void)p;
  (void)period;
  (void)periodic;
  (void)events;
  (void)id; /* TODO */
  return false;
}
bool pulse_reset(PulseTimer *p) {
  (void)p; /* TODO */
  return false;
}
bool pulse_stop(PulseTimer *p) {
  (void)p; /* TODO */
  return false;
}
bool pulse_destroy(PulseTimer *p) {
  (void)p; /* TODO */
  return false;
}
