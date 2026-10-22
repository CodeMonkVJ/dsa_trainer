#include "harness.h"
#include DSA_IMPLEMENTATION

typedef struct {
  Stream *s;
  SemaphoreHandle_t done;
  bool producer, ok;
  unsigned base, mask, count;
} StreamJob;
static void stream_job(void *arg) {
  StreamJob *j = arg;
  j->ok = true;
  if (j->producer) {
    for (unsigned i = 0; i < 8; ++i)
      if (!stream_push(j->s, j->base + i))
        j->ok = false;
  } else {
    unsigned value;
    while (stream_pop(j->s, &value)) {
      if (value >= 16 || (j->mask & (1u << value)))
        j->ok = false;
      else
        j->mask |= 1u << value;
      ++j->count;
    }
  }
  xSemaphoreGive(j->done);
  vTaskSuspend(NULL);
  for (;;) {
  }
}
typedef struct {
  Stream *s;
  SemaphoreHandle_t done;
  bool push, result;
  unsigned out;
} BlockedStream;
static void blocked_stream(void *arg) {
  BlockedStream *j = arg;
  j->result = j->push ? stream_push(j->s, 77) : stream_pop(j->s, &j->out);
  xSemaphoreGive(j->done);
  vTaskSuspend(NULL);
  for (;;) {
  }
}

static void run_tests(void *unused) {
  (void)unused;
  Stream s;
  unsigned out = 99;
  CHECK("invalid capacity", !stream_init(&s, 0) && !stream_init(&s, 5));
  require(stream_init(&s, 2));
  CHECK("FIFO before close", stream_push(&s, 1) && stream_push(&s, 2) &&
                                 stream_pop(&s, &out) && out == 1);
  stream_close(&s);
  stream_close(&s);
  CHECK("close rejects push and drains",
        !stream_push(&s, 3) && stream_pop(&s, &out) && out == 2);
  out = 99;
  CHECK("closed empty preserves output", !stream_pop(&s, &out) && out == 99);
  stream_destroy(&s);
  for (int push = 0; push < 2; ++push) {
    require(stream_init(&s, 1));
    if (push)
      require(stream_push(&s, 1));
    SemaphoreHandle_t done = xSemaphoreCreateBinary();
    require(done != NULL);
    BlockedStream j = {&s, done, push != 0, true, 99};
    TaskHandle_t task;
    spawn(blocked_stream, &j, 4, &task);
    CHECK("operation blocks on full or empty", eTaskGetState(task) == eBlocked);
    stream_close(&s);
    require(xSemaphoreTake(done, 100) == pdTRUE);
    CHECK("close releases blocked task", !j.result && (push || j.out == 99));
    vTaskDelete(task);
    vSemaphoreDelete(done);
    stream_destroy(&s);
  }
  require(stream_init(&s, 3));
  SemaphoreHandle_t done = xSemaphoreCreateCounting(4, 0);
  require(done != NULL);
  StreamJob j[4];
  TaskHandle_t tasks[4];
  for (int i = 0; i < 4; ++i) {
    j[i] = (StreamJob){
        .s = &s, .done = done, .producer = i < 2, .base = (unsigned)i * 8};
    spawn(stream_job, &j[i], 2, &tasks[i]);
  }
  for (int i = 0; i < 2; ++i)
    require(xSemaphoreTake(done, 1000) == pdTRUE);
  stream_close(&s);
  for (int i = 0; i < 2; ++i)
    require(xSemaphoreTake(done, 1000) == pdTRUE);
  CHECK("all items delivered exactly once",
        j[0].ok && j[1].ok && j[2].ok && j[3].ok &&
            j[2].count + j[3].count == 16 && (j[2].mask | j[3].mask) == 65535 &&
            !(j[2].mask & j[3].mask));
  for (int i = 0; i < 4; ++i)
    vTaskDelete(tasks[i]);
  vSemaphoreDelete(done);
  stream_destroy(&s);
}
