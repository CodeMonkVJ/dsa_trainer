#include "harness.h"
#include DSA_IMPLEMENTATION

typedef struct {
  SharedState *s;
  SemaphoreHandle_t done;
  bool ok;
} AddJob;
static void add_worker(void *arg) {
  AddJob *j = arg;
  j->ok = true;
  for (int i = 0; i < 100; ++i) {
    int v = 0, n = 0;
    j->ok = shared_add(j->s, 1, 20) && j->ok;
    j->ok = shared_read(j->s, &v, &n, 20) && j->ok && v == -n;
    taskYIELD();
  }
  xSemaphoreGive(j->done);
  vTaskSuspend(NULL);
  for (;;) {
  }
}

static void run_tests(void *unused) {
  (void)unused;
  SharedState s;
  require(shared_init(&s));
  int v = 99, n = 99;
  CHECK("initial snapshot", shared_read(&s, &v, &n, 0) && v == 0 && n == 0);
  require(xSemaphoreTake(s.mutex, 0) == pdTRUE);
  CHECK("updates respect owned mutex", !shared_add(&s, 1, 0));
  v = n = 99;
  CHECK("snapshot timeout preserves outputs",
        !shared_read(&s, &v, &n, 0) && v == 99 && n == 99);
  xSemaphoreGive(s.mutex);
  SemaphoreHandle_t done = xSemaphoreCreateCounting(4, 0);
  require(done != NULL);
  AddJob jobs[4];
  TaskHandle_t handles[4];
  for (int i = 0; i < 4; ++i) {
    jobs[i] = (AddJob){&s, done, false};
    spawn(add_worker, &jobs[i], 2, &handles[i]);
  }
  for (int i = 0; i < 4; ++i)
    require(xSemaphoreTake(done, 1000) == pdTRUE);
  bool ok = true;
  for (int i = 0; i < 4; ++i) {
    ok = jobs[i].ok && ok;
    vTaskDelete(handles[i]);
  }
  CHECK("concurrent invariant snapshots", ok);
  CHECK("all updates retained",
        shared_read(&s, &v, &n, 0) && v == 400 && n == -400);
  CHECK("invalid output rejected", !shared_read(&s, NULL, &n, 0));
  vSemaphoreDelete(done);
  shared_destroy(&s);
}
