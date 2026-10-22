#include "lab.h"
typedef struct {
  TickType_t last[4], timeout;
  unsigned tasks;
  SemaphoreHandle_t mutex;
} Watchdog;
bool watchdog_init(Watchdog *w, unsigned tasks, TickType_t timeout,
                   TickType_t now);
bool watchdog_beat(Watchdog *w, unsigned task, TickType_t now);
bool watchdog_healthy(Watchdog *w, TickType_t now);
void watchdog_destroy(Watchdog *w);

bool watchdog_init(Watchdog *w, unsigned tasks, TickType_t timeout,
                   TickType_t now) {
  (void)w;
  (void)tasks;
  (void)timeout;
  (void)now; /* TODO */
  return false;
}
bool watchdog_beat(Watchdog *w, unsigned task, TickType_t now) {
  (void)w;
  (void)task;
  (void)now; /* TODO */
  return false;
}
bool watchdog_healthy(Watchdog *w, TickType_t now) {
  (void)w;
  (void)now; /* TODO */
  return false;
}
void watchdog_destroy(Watchdog *w) { (void)w; /* TODO */ }
