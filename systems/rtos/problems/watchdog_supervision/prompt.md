# Watchdog Supervision

Track each task's progress independently using wrap-safe logical tick arithmetic.

## Required behavior

Watchdog monitors 1..4 tasks. watchdog_init(w, tasks, timeout, now) records now for every task and rejects zero timeout or timeout >= portMAX_DELAY/2. watchdog_beat updates only a valid task id under the mutex. watchdog_healthy(now) succeeds only when every task's unsigned elapsed ticks <= timeout. Repeated beats from one task must not mask another stalled task. Supplied times advance modulo TickType_t; elapsed intervals must remain below half the range. This is a software supervision policy, not a real hardware watchdog/reset. Use injectable logical time for deterministic tests; no actual sleeps needed.

## API

```c
#include "lab.h" /* FreeRTOS task, queue, semaphore, timer and event APIs */
typedef struct{TickType_t last[4],timeout;unsigned tasks;SemaphoreHandle_t mutex;} Watchdog;
bool watchdog_init(Watchdog *w,unsigned tasks,TickType_t timeout,TickType_t now);
bool watchdog_beat(Watchdog *w,unsigned task,TickType_t now);
bool watchdog_healthy(Watchdog *w,TickType_t now);
void watchdog_destroy(Watchdog *w);
```

## Practice environment

Write C using the supplied FreeRTOS APIs in the editor. Save your changes and press **Run tests**. This exercise runs on Linux x86 using the pinned FreeRTOS POSIX port, configured as a single-core preemptive scheduler at 1,000 logical ticks/s. No ESP32 hardware or ESP-IDF installation is needed.

Use blocking synchronization rather than guessed startup sleeps. Do not print/log from RTOS tasks; the harness records results and prints after the scheduler stops. Kernel assertions, deadlocks and invalid API use fail the run. The timeout is a watchdog, not a timing grade. Desktop scheduling and simulator results do not establish hardware real-time guarantees. Do not change API declarations or harness configuration.
