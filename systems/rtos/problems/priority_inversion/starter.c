#include "lab.h"
SemaphoreHandle_t resource_lock_create(bool inherit);
bool resource_lock_take(SemaphoreHandle_t lock, TickType_t wait);
bool resource_lock_release(SemaphoreHandle_t lock);

SemaphoreHandle_t resource_lock_create(bool inherit) {
  (void)inherit; /* TODO */
  return NULL;
}
bool resource_lock_take(SemaphoreHandle_t lock, TickType_t wait) {
  (void)lock;
  (void)wait; /* TODO */
  return false;
}
bool resource_lock_release(SemaphoreHandle_t lock) {
  (void)lock; /* TODO */
  return false;
}
