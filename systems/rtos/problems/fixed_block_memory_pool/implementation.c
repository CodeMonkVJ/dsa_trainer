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

bool mem_pool_init(MemoryPool *p, unsigned cap) {
  if (!p || !cap || cap > 4)
    return false;
  *p = (MemoryPool){.capacity = cap, .mutex = xSemaphoreCreateMutex()};
  return p->mutex != NULL;
}
void *mem_pool_get(MemoryPool *p, TickType_t wait) {
  if (!p || xSemaphoreTake(p->mutex, wait) != pdTRUE)
    return NULL;
  void *result = NULL;
  for (unsigned i = 0; i < p->capacity; ++i)
    if (!p->used[i]) {
      p->used[i] = true;
      result = p->blocks[i];
      break;
    }
  xSemaphoreGive(p->mutex);
  return result;
}
bool mem_pool_put(MemoryPool *p, void *block) {
  if (!p || !block)
    return false;
  xSemaphoreTake(p->mutex, portMAX_DELAY);
  bool ok = false;
  for (unsigned i = 0; i < p->capacity; ++i)
    if (block == (void *)p->blocks[i] && p->used[i]) {
      p->used[i] = false;
      ok = true;
      break;
    }
  xSemaphoreGive(p->mutex);
  return ok;
}
void mem_pool_destroy(MemoryPool *p) {
  if (p)
    vSemaphoreDelete(p->mutex);
}
