# Deadlock-Free Dining Philosophers

Acquire shared resources in a global order and release partial acquisitions on timeout.

## Required behavior

philosopher_round(forks, index, wait) acquires the two adjacent mutexes for index 0..4 in ascending fork-index order, then releases both. If either acquisition times out, release anything acquired and return false. Reject invalid index/null forks or null individual handles before touching locks. All fork handles are distinct nonrecursive mutexes. This establishes deadlock freedom, not a starvation-freedom proof. No delays while holding locks or busy waits.

## API

```c
#include "lab.h" /* FreeRTOS task, queue, semaphore, timer and event APIs */
bool philosopher_round(SemaphoreHandle_t forks[5],unsigned index,TickType_t wait);
```

## Practice environment

Write C using the supplied FreeRTOS APIs in the editor. Save your changes and press **Run tests**. This exercise runs on Linux x86 using the pinned FreeRTOS POSIX port, configured as a single-core preemptive scheduler at 1,000 logical ticks/s. No ESP32 hardware or ESP-IDF installation is needed.

Use blocking synchronization rather than guessed startup sleeps. Do not print/log from RTOS tasks; the harness records results and prints after the scheduler stops. Kernel assertions, deadlocks and invalid API use fail the run. The timeout is a watchdog, not a timing grade. Desktop scheduling and simulator results do not establish hardware real-time guarantees. Do not change API declarations or harness configuration.
