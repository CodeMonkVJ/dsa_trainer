#include "lab.h"
typedef struct {
  SemaphoreHandle_t permits;
} PermitPool;
bool pool_init(PermitPool *pool, unsigned capacity);
bool pool_acquire(PermitPool *pool, TickType_t wait);
bool pool_release(PermitPool *pool);
void pool_destroy(PermitPool *pool);

bool pool_init(PermitPool *pool, unsigned capacity) {
  (void)pool;
  (void)capacity; /* TODO */
  return false;
}
bool pool_acquire(PermitPool *pool, TickType_t wait) {
  (void)pool;
  (void)wait; /* TODO */
  return false;
}
bool pool_release(PermitPool *pool) {
  (void)pool; /* TODO */
  return false;
}
void pool_destroy(PermitPool *pool) { (void)pool; /* TODO */ }
