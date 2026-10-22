#include "lab.h"
typedef struct {
  unsigned char blocks[4][32];
  bool used[4];
  unsigned capacity;
  SemaphoreHandle_t mutex;
} MemoryPool;
bool mem_pool_init(MemoryPool *p, unsigned capacity);
void *mem_pool_get(MemoryPool *p, TickType_t wait);
bool mem_pool_put(MemoryPool *p, void *block);
void mem_pool_destroy(MemoryPool *p);

bool mem_pool_init(MemoryPool *p, unsigned capacity) {
  (void)p;
  (void)capacity; /* TODO */
  return false;
}
void *mem_pool_get(MemoryPool *p, TickType_t wait) {
  (void)p;
  (void)wait; /* TODO */
  return NULL;
}
bool mem_pool_put(MemoryPool *p, void *block) {
  (void)p;
  (void)block; /* TODO */
  return false;
}
void mem_pool_destroy(MemoryPool *p) { (void)p; /* TODO */ }
