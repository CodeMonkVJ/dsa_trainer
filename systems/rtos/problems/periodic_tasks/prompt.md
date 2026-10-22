# Periodic Tasks Without Drift

Use absolute tick deadlines and handle missed releases and unsigned wraparound.

## Required behavior

periodic_next(previous, period) returns unsigned TickType_t addition, including wraparound. periodic_wait(previous, period) rejects null/zero without changing state; otherwise use xTaskDelayUntil to advance the absolute release by one period and return whether it actually blocked. A late release advances by one period rather than resetting the phase to now; callers decide catch-up/skip policy. Do not busy wait. Scheduling checks use logical ticks, not hard wall-clock deadlines. Wraparound arithmetic is tested separately without changing the live kernel clock.

## API

```c
#include "lab.h" /* FreeRTOS task, queue, semaphore, timer and event APIs */
TickType_t periodic_next(TickType_t previous, TickType_t period);
bool periodic_wait(TickType_t *previous, TickType_t period);
```

## Practice environment

Write C using the supplied FreeRTOS APIs in the editor. Save your changes and press **Run tests**. This exercise runs on Linux x86 using the pinned FreeRTOS POSIX port, configured as a single-core preemptive scheduler at 1,000 logical ticks/s. No ESP32 hardware or ESP-IDF installation is needed.

Use blocking synchronization rather than guessed startup sleeps. Do not print/log from RTOS tasks; the harness records results and prints after the scheduler stops. Kernel assertions, deadlocks and invalid API use fail the run. The timeout is a watchdog, not a timing grade. Desktop scheduling and simulator results do not establish hardware real-time guarantees. Do not change API declarations or harness configuration.
