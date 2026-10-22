# Task Scheduling and Blocking

Coordinate higher- and lower-priority tasks using blocking rather than busy waiting.

## Required behavior

Implement scheduling_trace(out, capacity). Reject null output or capacity < 3. Create a low-priority worker (2) and a higher-priority worker (4). The low worker records 1, releases the high worker, and records 3 after it resumes. The high worker records 2. Return true only after both finish and release all synchronization resources. The caller runs at priority 3. No busy loops, delays used to guess ordering, or task priority changes. Expected trace is 1,2,3: the high worker must block until released and preempt the low worker. Assume task creation succeeds after semaphore creation; reject semaphore allocation failure cleanly.

## API

```c
#include "lab.h" /* FreeRTOS task, queue, semaphore, timer and event APIs */
bool scheduling_trace(unsigned *out, size_t capacity);
```

## Practice environment

Write C using the supplied FreeRTOS APIs in the editor. Save your changes and press **Run tests**. This exercise runs on Linux x86 using the pinned FreeRTOS POSIX port, configured as a single-core preemptive scheduler at 1,000 logical ticks/s. No ESP32 hardware or ESP-IDF installation is needed.

Use blocking synchronization rather than guessed startup sleeps. Do not print/log from RTOS tasks; the harness records results and prints after the scheduler stops. Kernel assertions, deadlocks and invalid API use fail the run. The timeout is a watchdog, not a timing grade. Desktop scheduling and simulator results do not establish hardware real-time guarantees. Do not change API declarations or harness configuration.
