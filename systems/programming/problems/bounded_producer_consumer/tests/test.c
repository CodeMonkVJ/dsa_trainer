#define _POSIX_C_SOURCE 200809L
#include <pthread.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* Observe actual condition-wait entry, rather than guessing with sleeps.
   This wrapper leaves the real pthread wait and mutex semantics intact. */
static pthread_mutex_t probe_mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t probe_changed = PTHREAD_COND_INITIALIZER;
static unsigned wait_calls, unique_waiters;
static bool observing;
static _Thread_local bool reported;
static int observed_wait(pthread_cond_t *condition, pthread_mutex_t *mutex) {
  pthread_mutex_lock(&probe_mutex);
  if (observing) {
    ++wait_calls;
    if (!reported) {
      ++unique_waiters;
      reported = true;
    }
    pthread_cond_broadcast(&probe_changed);
  }
  pthread_mutex_unlock(&probe_mutex);
  return pthread_cond_wait(condition, mutex);
}
#define pthread_cond_wait observed_wait
#ifndef DSA_IMPLEMENTATION
#define DSA_IMPLEMENTATION "../implementation.c"
#endif
#include DSA_IMPLEMENTATION
#undef pthread_cond_wait

static int passed, total;
#define CHECK(expr)                                                            \
  do {                                                                         \
    bool ok = !!(expr);                                                        \
    ++total;                                                                   \
    passed += ok;                                                              \
    printf("DSA_CASE "                                                         \
           "{\"input\":%d,\"expected\":true,\"actual\":%s,\"passed\":%s}\n",   \
           __LINE__, ok ? "true" : "false", ok ? "true" : "false");            \
    if (!ok)                                                                   \
      fprintf(stderr, "FAIL line %d: %s\n", __LINE__, #expr);                  \
  } while (0)
static void require(bool ok) {
  if (!ok) {
    fputs("Test setup failed\n", stderr);
    exit(2);
  }
}
static void start_observing(void) {
  pthread_mutex_lock(&probe_mutex);
  observing = true;
  wait_calls = unique_waiters = 0;
  pthread_mutex_unlock(&probe_mutex);
}
static void await_waiters(unsigned unique, unsigned calls) {
  pthread_mutex_lock(&probe_mutex);
  while (unique_waiters < unique || wait_calls < calls)
    pthread_cond_wait(&probe_changed, &probe_mutex);
  pthread_mutex_unlock(&probe_mutex);
}
static void stop_observing(void) {
  pthread_mutex_lock(&probe_mutex);
  observing = false;
  pthread_mutex_unlock(&probe_mutex);
}
static pthread_t start(void *(*fn)(void *), void *arg) {
  pthread_t t;
  require(pthread_create(&t, NULL, fn, arg) == 0);
  return t;
}
static void join(pthread_t t) { require(pthread_join(t, NULL) == 0); }
static int *payload(int value) {
  int *p = malloc(sizeof *p);
  require(p != NULL);
  *p = value;
  return p;
}
static int disposed;
static void dispose(void *p) {
  ++disposed;
  free(p);
}
typedef struct {
  BoundedQueue *q;
  void *in, *out;
  bool result;
} Operation;
static void *push_one(void *arg) {
  Operation *op = arg;
  op->result = bq_push(op->q, op->in);
  return NULL;
}
static void *pop_one(void *arg) {
  Operation *op = arg;
  op->result = bq_pop(op->q, &op->out);
  return NULL;
}
static void test_fifo_and_ownership(void) {
  BoundedQueue q;
  void *out = NULL;
  CHECK(!bq_init(NULL, 1) && !bq_init(&q, 0) && !bq_init(&q, SIZE_MAX));
  require(bq_init(&q, 2));
  int *a = payload(1), *b = payload(2), *c = payload(3);
  CHECK(!bq_push(NULL, a) && !bq_push(&q, NULL) && !bq_pop(&q, NULL));
  CHECK(bq_push(&q, a) && bq_push(&q, b));
  CHECK(bq_pop(&q, &out) && out == a);
  free(a);
  CHECK(bq_push(&q, c));
  bq_close(&q);
  bq_close(&q);
  int *rejected = payload(4);
  CHECK(!bq_push(&q, rejected) && *rejected == 4);
  free(rejected);
  CHECK(bq_pop(&q, &out) && out == b);
  free(b);
  CHECK(bq_pop(&q, &out) && out == c);
  free(c);
  out = &q;
  CHECK(!bq_pop(&q, &out) && out == &q && !bq_pop(NULL, &out));
  bq_destroy(&q, dispose);
  require(bq_init(&q, 2));
  require(bq_push(&q, payload(5)) && bq_push(&q, payload(6)));
  bq_close(&q);
  disposed = 0;
  bq_destroy(&q, dispose);
  CHECK(disposed == 2);
}
static void test_wait_predicates(bool producer) {
  BoundedQueue q;
  require(bq_init(&q, 1));
  int *a = payload(10), *b = payload(20);
  if (producer)
    require(bq_push(&q, a));
  Operation op = {.q = &q, .in = b};
  start_observing();
  pthread_t t = start(producer ? push_one : pop_one, &op);
  await_waiters(1, 1);
  /* Deliberately wake the waiter without satisfying its predicate. */
  pthread_mutex_lock(&q.mutex);
  pthread_cond_broadcast(producer ? &q.not_full : &q.not_empty);
  pthread_mutex_unlock(&q.mutex);
  await_waiters(1, 2); /* Must re-check and wait again. */
  void *out = NULL;
  if (producer) {
    CHECK(bq_pop(&q, &out) && out == a);
    free(a);
  } else {
    require(bq_push(&q, a));
  }
  join(t);
  stop_observing();
  CHECK(op.result && (producer || op.out == a));
  if (producer) {
    CHECK(bq_pop(&q, &out) && out == b);
    free(b);
  } else {
    free(a);
    free(b);
  }
  bq_close(&q);
  bq_destroy(&q, dispose);
}
static void test_shutdown(bool producers) {
  BoundedQueue q;
  require(bq_init(&q, 1));
  int *queued = NULL;
  if (producers) {
    queued = payload(42);
    require(bq_push(&q, queued));
  }
  Operation ops[3];
  pthread_t threads[3];
  start_observing();
  for (size_t i = 0; i < 3; ++i) {
    ops[i] = (Operation){
        .q = &q, .in = producers ? payload((int)i) : NULL, .out = &q};
    threads[i] = start(producers ? push_one : pop_one, &ops[i]);
  }
  await_waiters(3, 3);
  bq_close(&q);
  for (size_t i = 0; i < 3; ++i) {
    join(threads[i]);
    CHECK(!ops[i].result && (producers || ops[i].out == &q));
    if (producers)
      free(ops[i].in); /* Failed push retained caller ownership. */
  }
  stop_observing();
  if (producers) {
    void *out = NULL;
    CHECK(bq_pop(&q, &out) && out == queued);
    free(out);
  }
  bq_destroy(&q, dispose);
}
enum {
  PRODUCERS = 4,
  CONSUMERS = 4,
  PER_PRODUCER = 200,
  ITEMS = PRODUCERS * PER_PRODUCER
};
typedef struct {
  BoundedQueue q;
  pthread_mutex_t mutex;
  unsigned seen[ITEMS], count;
  bool valid;
} Stress;
typedef struct {
  Stress *s;
  unsigned index;
  bool ok;
} Producer;
static void *produce(void *arg) {
  Producer *p = arg;
  p->ok = true;
  for (unsigned i = 0; i < PER_PRODUCER; ++i) {
    int *value = payload((int)(p->index * PER_PRODUCER + i));
    if (!bq_push(&p->s->q, value)) {
      free(value);
      p->ok = false;
      break;
    }
  }
  return NULL;
}
static void *consume(void *arg) {
  Stress *s = arg;
  void *out = NULL;
  while (bq_pop(&s->q, &out)) {
    int value = *(int *)out;
    pthread_mutex_lock(&s->mutex);
    if (value < 0 || value >= ITEMS)
      s->valid = false;
    else
      ++s->seen[value];
    ++s->count;
    pthread_mutex_unlock(&s->mutex);
    free(out);
  }
  return NULL;
}
static void test_stress(size_t capacity) {
  Stress s = {.valid = true};
  require(bq_init(&s.q, capacity));
  require(pthread_mutex_init(&s.mutex, NULL) == 0);
  Producer producers[PRODUCERS];
  pthread_t producers_t[PRODUCERS], consumers_t[CONSUMERS];
  for (unsigned i = 0; i < CONSUMERS; ++i)
    consumers_t[i] = start(consume, &s);
  for (unsigned i = 0; i < PRODUCERS; ++i) {
    producers[i] = (Producer){.s = &s, .index = i};
    producers_t[i] = start(produce, &producers[i]);
  }
  for (unsigned i = 0; i < PRODUCERS; ++i) {
    join(producers_t[i]);
    CHECK(producers[i].ok);
  }
  bq_close(&s.q);
  for (unsigned i = 0; i < CONSUMERS; ++i)
    join(consumers_t[i]);
  bool exactly_once = s.valid && s.count == ITEMS;
  for (unsigned i = 0; i < ITEMS; ++i)
    exactly_once = exactly_once && s.seen[i] == 1;
  CHECK(exactly_once);
  bq_destroy(&s.q, dispose);
  pthread_mutex_destroy(&s.mutex);
}
int main(void) {
  alarm(4); /* A broken predicate or missed shutdown wake must not hang. */
  test_fifo_and_ownership();
  test_wait_predicates(true);
  test_wait_predicates(false);
  test_shutdown(true);
  test_shutdown(false);
  test_stress(1);
  test_stress(7);
  alarm(0);
  printf("DSA_RESULT {\"passed\":%d,\"total\":%d}\n", passed, total);
  return passed == total ? 0 : 1;
}
