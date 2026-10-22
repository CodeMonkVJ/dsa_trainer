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

#include <stdlib.h>

bool bq_init(BoundedQueue *q, size_t capacity) {
  if (!q || !capacity || capacity > SIZE_MAX / sizeof(void *))
    return false;
  void **slots = malloc(capacity * sizeof *slots);
  if (!slots)
    return false;
  if (pthread_mutex_init(&q->mutex, NULL)) {
    free(slots);
    return false;
  }
  if (pthread_cond_init(&q->not_empty, NULL)) {
    pthread_mutex_destroy(&q->mutex);
    free(slots);
    return false;
  }
  if (pthread_cond_init(&q->not_full, NULL)) {
    pthread_cond_destroy(&q->not_empty);
    pthread_mutex_destroy(&q->mutex);
    free(slots);
    return false;
  }
  q->slots = slots;
  q->capacity = capacity;
  q->head = q->tail = q->count = 0;
  q->closed = false;
  return true;
}

bool bq_push(BoundedQueue *q, void *payload) {
  if (!q || !payload)
    return false;
  pthread_mutex_lock(&q->mutex);
  /* The predicate and closed flag are always protected by this mutex. */
  while (q->count == q->capacity && !q->closed)
    pthread_cond_wait(&q->not_full, &q->mutex);
  if (q->closed) {
    pthread_mutex_unlock(&q->mutex);
    return false;
  }
  q->slots[q->tail] = payload;
  q->tail = q->tail == q->capacity - 1 ? 0 : q->tail + 1;
  ++q->count;
  pthread_cond_signal(&q->not_empty);
  pthread_mutex_unlock(&q->mutex);
  return true;
}

bool bq_pop(BoundedQueue *q, void **out) {
  if (!q || !out)
    return false;
  pthread_mutex_lock(&q->mutex);
  while (!q->count && !q->closed)
    pthread_cond_wait(&q->not_empty, &q->mutex);
  if (!q->count) {
    pthread_mutex_unlock(&q->mutex);
    return false;
  }
  *out = q->slots[q->head];
  q->head = q->head == q->capacity - 1 ? 0 : q->head + 1;
  --q->count;
  pthread_cond_signal(&q->not_full);
  pthread_mutex_unlock(&q->mutex);
  return true;
}

void bq_close(BoundedQueue *q) {
  if (!q)
    return;
  pthread_mutex_lock(&q->mutex);
  q->closed = true;
  /* Wake every waiter, including producers blocked on a full queue. */
  pthread_cond_broadcast(&q->not_empty);
  pthread_cond_broadcast(&q->not_full);
  pthread_mutex_unlock(&q->mutex);
}

void bq_destroy(BoundedQueue *q, void (*dispose)(void *)) {
  if (!q)
    return;
  /* Caller has closed and joined all users, so no locking is needed. */
  while (q->count) {
    void *payload = q->slots[q->head];
    q->head = q->head == q->capacity - 1 ? 0 : q->head + 1;
    --q->count;
    dispose(payload);
  }
  free(q->slots);
  q->slots = NULL;
  pthread_cond_destroy(&q->not_empty);
  pthread_cond_destroy(&q->not_full);
  pthread_mutex_destroy(&q->mutex);
}
