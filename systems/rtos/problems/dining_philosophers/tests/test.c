#include "harness.h"
#include DSA_IMPLEMENTATION

typedef struct {
  SemaphoreHandle_t *forks, done;
  unsigned index;
  bool ok;
} Philosopher;
static void philosopher(void *arg) {
  Philosopher *p = arg;
  p->ok = true;
  for (unsigned i = 0; i < 20; ++i) {
    p->ok = philosopher_round(p->forks, p->index, 100) && p->ok;
    vTaskDelay(1);
  }
  xSemaphoreGive(p->done);
  vTaskSuspend(NULL);
  for (;;) {
  }
}

static void run_tests(void *unused) {
  (void)unused;
  SemaphoreHandle_t forks[5];
  for (int i = 0; i < 5; ++i) {
    forks[i] = xSemaphoreCreateMutex();
    require(forks[i] != NULL);
  }
  CHECK("invalid philosopher rejected",
        !philosopher_round(NULL, 0, 0) && !philosopher_round(forks, 5, 0));
  require(xSemaphoreTake(forks[1], 0) == pdTRUE);
  CHECK("second acquisition times out", !philosopher_round(forks, 0, 1));
  CHECK("partial lock released", xSemaphoreTake(forks[0], 0) == pdTRUE);
  xSemaphoreGive(forks[0]);
  xSemaphoreGive(forks[1]);
  SemaphoreHandle_t done = xSemaphoreCreateCounting(5, 0);
  require(done != NULL);
  Philosopher p[5];
  TaskHandle_t tasks[5];
  for (int i = 0; i < 5; ++i) {
    p[i] = (Philosopher){forks, done, (unsigned)i, false};
    spawn(philosopher, &p[i], 2, &tasks[i]);
  }
  bool ok = true;
  for (int i = 0; i < 5; ++i)
    require(xSemaphoreTake(done, 1000) == pdTRUE);
  for (int i = 0; i < 5; ++i) {
    ok = p[i].ok && ok;
    vTaskDelete(tasks[i]);
  }
  CHECK("all five finish repeated rounds", ok);
  for (int i = 0; i < 5; ++i) {
    CHECK("fork returned after contention",
          xSemaphoreTake(forks[i], 0) == pdTRUE);
    xSemaphoreGive(forks[i]);
    vSemaphoreDelete(forks[i]);
  }
  vSemaphoreDelete(done);
}
