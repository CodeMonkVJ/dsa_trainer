# Priority Inversion and Inheritance

Demonstrate the scheduler difference between mutex ownership and binary semaphore signaling.

## Required behavior

resource_lock_create(inherit) creates an initially available mutex when inherit=true, or initially given binary semaphore otherwise. resource_lock_take/release wrap the correct semaphore APIs; reject null handles. No priority manipulation. Harness gates low/medium/high tasks so a high-priority waiter blocks behind a low-priority owner. With a mutex the owner's inherited priority must outrank the medium task. Without inheritance the medium task runs first. This tests FreeRTOS single-core logical scheduling, not desktop wall-clock deadlines or full priority-ceiling protocols.

## API

```c
#include "lab.h" /* FreeRTOS task, queue, semaphore, timer and event APIs */
SemaphoreHandle_t resource_lock_create(bool inherit);
bool resource_lock_take(SemaphoreHandle_t lock,TickType_t wait);
bool resource_lock_release(SemaphoreHandle_t lock);
```

## Practice environment

Write C using the supplied FreeRTOS APIs in the editor. Save your changes and press **Run tests**. This exercise runs on Linux x86 using the pinned FreeRTOS POSIX port, configured as a single-core preemptive scheduler at 1,000 logical ticks/s. No ESP32 hardware or ESP-IDF installation is needed.

Use blocking synchronization rather than guessed startup sleeps. Do not print/log from RTOS tasks; the harness records results and prints after the scheduler stops. Kernel assertions, deadlocks and invalid API use fail the run. The timeout is a watchdog, not a timing grade. Desktop scheduling and simulator results do not establish hardware real-time guarantees. Do not change API declarations or harness configuration.
