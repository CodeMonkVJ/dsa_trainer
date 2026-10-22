#ifndef RTOS_HARNESS_H
#define RTOS_HARNESS_H
#include "lab.h"
#include <stdio.h>
#include <stdlib.h>
#ifndef DSA_IMPLEMENTATION
#error Supply DSA_IMPLEMENTATION through compile.sh
#endif

static struct {
  const char *name;
  bool passed;
} lab_cases[256];
static unsigned lab_total, lab_passed;
static void lab_check(const char *name, bool result) {
  taskENTER_CRITICAL();
  if (lab_total >= 256) {
    taskEXIT_CRITICAL();
    _Exit(2);
  }
  lab_cases[lab_total].name = name;
  lab_cases[lab_total++].passed = result;
  if (result)
    ++lab_passed;
  taskEXIT_CRITICAL();
}
#define CHECK(name, expr) lab_check(name, !!(expr))
static void require(bool result) { configASSERT(result); }
static void spawn(TaskFunction_t fn, void *arg, UBaseType_t priority,
                  TaskHandle_t *handle) {
  require(xTaskCreate(fn, "lab", configMINIMAL_STACK_SIZE, arg, priority,
                      handle) == pdPASS);
}
static void run_tests(void *);
static void supervisor(void *arg) {
  run_tests(arg);
  vTaskEndScheduler();
  for (;;) {
  }
}
static void json_string(const char *s) {
  putchar('"');
  for (; *s; ++s) {
    if (*s == '"' || *s == '\\')
      putchar('\\');
    if ((unsigned char)*s >= 32)
      putchar(*s);
  }
  putchar('"');
}
int main(void) {
  spawn(supervisor, NULL, 3, NULL);
  vTaskStartScheduler();
  /* The POSIX port uses signals. No stdio from preemptible RTOS tasks:
     record results there, print only after the scheduler has stopped. */
  for (unsigned i = 0; i < lab_total; ++i) {
    fputs("DSA_CASE {\"input\":", stdout);
    json_string(lab_cases[i].name);
    printf(",\"expected\":true,\"actual\":%s,\"passed\":%s}\n",
           lab_cases[i].passed ? "true" : "false",
           lab_cases[i].passed ? "true" : "false");
  }
  printf("DSA_RESULT {\"passed\":%u,\"total\":%u}\n", lab_passed, lab_total);
  return lab_total && lab_passed == lab_total ? 0 : 1;
}
#endif
