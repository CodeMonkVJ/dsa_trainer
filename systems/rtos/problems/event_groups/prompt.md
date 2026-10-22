# Event Groups

Synchronize readiness flags with wait-any/all and clear-on-exit semantics.

## Required behavior

events_create returns an event group. events_set accepts a nonzero low-eight-bit mask; reject null or other bits. events_wait(group,mask,all,clear,wait) accepts the same masks and returns the RTOS snapshot (including unrelated set bits) at wake/timeout. It does not return only the requested bits. Invalid arguments return zero. On clear-on-exit, the returned value is the pre-clear snapshot. Destroy after all waiters stop.

## API

```c
#include "lab.h" /* FreeRTOS task, queue, semaphore, timer and event APIs */
EventGroupHandle_t events_create(void);
bool events_set(EventGroupHandle_t group,EventBits_t bits);
EventBits_t events_wait(EventGroupHandle_t group,EventBits_t mask,bool all,bool clear,TickType_t wait);
```

## Practice environment

Write C using the supplied FreeRTOS APIs in the editor. Save your changes and press **Run tests**. This exercise runs on Linux x86 using the pinned FreeRTOS POSIX port, configured as a single-core preemptive scheduler at 1,000 logical ticks/s. No ESP32 hardware or ESP-IDF installation is needed.

Use blocking synchronization rather than guessed startup sleeps. Do not print/log from RTOS tasks; the harness records results and prints after the scheduler stops. Kernel assertions, deadlocks and invalid API use fail the run. The timeout is a watchdog, not a timing grade. Desktop scheduling and simulator results do not establish hardware real-time guarantees. Do not change API declarations or harness configuration.
