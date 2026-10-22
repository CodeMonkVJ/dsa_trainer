#include "lab.h"
typedef struct {
  SemaphoreHandle_t mutex;
  int value, inverse;
} SharedState;
bool shared_init(SharedState *s);
bool shared_add(SharedState *s, int delta, TickType_t wait);
bool shared_read(SharedState *s, int *value, int *inverse, TickType_t wait);
void shared_destroy(SharedState *s);

bool shared_init(SharedState *s) {
  (void)s; /* TODO */
  return false;
}
bool shared_add(SharedState *s, int delta, TickType_t wait) {
  (void)s;
  (void)delta;
  (void)wait; /* TODO */
  return false;
}
bool shared_read(SharedState *s, int *value, int *inverse, TickType_t wait) {
  (void)s;
  (void)value;
  (void)inverse;
  (void)wait; /* TODO */
  return false;
}
void shared_destroy(SharedState *s) { (void)s; /* TODO */ }
