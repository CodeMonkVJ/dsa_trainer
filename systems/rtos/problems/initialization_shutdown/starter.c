#include "lab.h"
typedef struct {
  QueueHandle_t queue;
  SemaphoreHandle_t mutex, done;
  TaskHandle_t worker;
  bool running;
  unsigned processed;
  int sum;
} Session;
bool session_init(Session *s);
bool session_send(Session *s, int value, TickType_t wait);
void session_close(Session *s);

bool session_init(Session *s) {
  (void)s; /* TODO */
  return false;
}
bool session_send(Session *s, int value, TickType_t wait) {
  (void)s;
  (void)value;
  (void)wait; /* TODO */
  return false;
}
void session_close(Session *s) { (void)s; /* TODO */ }
