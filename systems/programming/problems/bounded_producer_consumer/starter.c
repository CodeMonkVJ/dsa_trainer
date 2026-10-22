#include <pthread.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef struct {
  void **slots;
  size_t capacity, head, tail, count;
  bool closed;
  pthread_mutex_t mutex;
  pthread_cond_t not_empty, not_full;
} BoundedQueue;

bool bq_init(BoundedQueue *q, size_t capacity);
bool bq_push(BoundedQueue *q, void *payload);
bool bq_pop(BoundedQueue *q, void **out);
void bq_close(BoundedQueue *q);
void bq_destroy(BoundedQueue *q, void (*dispose)(void *));

/* TODO: implement synchronization, ownership, and shutdown per prompt.md. */
bool bq_init(BoundedQueue *q, size_t capacity) {
  (void)q;
  (void)capacity;
  return false;
}
bool bq_push(BoundedQueue *q, void *payload) {
  (void)q;
  (void)payload;
  return false;
}
bool bq_pop(BoundedQueue *q, void **out) {
  (void)q;
  (void)out;
  return false;
}
void bq_close(BoundedQueue *q) { (void)q; }
void bq_destroy(BoundedQueue *q, void (*dispose)(void *)) {
  (void)q;
  (void)dispose;
}
