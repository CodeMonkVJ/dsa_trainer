#include "lab.h"
typedef struct {
  SemaphoreHandle_t permits;
} PermitPool;
bool pool_init(PermitPool *pool, unsigned capacity);
bool pool_acquire(PermitPool *pool, TickType_t wait);
bool pool_release(PermitPool *pool);
void pool_destroy(PermitPool *pool);

bool pool_init(PermitPool *p, unsigned cap) {
  if (!p || !cap)
    return false;
  p->permits = xSemaphoreCreateCounting(cap, cap);
  return p->permits != NULL;
}
bool pool_acquire(PermitPool *p, TickType_t wait) {
  return p && xSemaphoreTake(p->permits, wait) == pdTRUE;
}
bool pool_release(PermitPool *p) {
  return p && xSemaphoreGive(p->permits) == pdTRUE;
}
void pool_destroy(PermitPool *p) {
  if (p)
    vSemaphoreDelete(p->permits);
}
