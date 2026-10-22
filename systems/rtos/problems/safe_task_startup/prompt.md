# Safe Task Startup

Pass task parameters safely with a copy handshake and clean creation failure handling.

## Required behavior

startup_copy(value, out) starts a worker that copies a caller-local value, acknowledges that copy, then returns the copied value through out. The launching task deliberately changes its original variable after acknowledgment. Wait for worker completion before returning; preserve out on invalid input or resource/task creation failure. Use lab_binary_create, lab_task_create, lab_queue_delete, and lab_task_delete for tracked resources and deterministic failure injection. Worker signals done after its last access to shared context then suspends; launcher deletes it. No arbitrary sleep to protect parameter lifetime.

## API

```c
#include "lab.h" /* FreeRTOS task, queue, semaphore, timer and event APIs */
bool startup_copy(int value, int *out);
```

## Practice environment

Write C using the supplied FreeRTOS APIs in the editor. Save your changes and press **Run tests**. This exercise runs on Linux x86 using the pinned FreeRTOS POSIX port, configured as a single-core preemptive scheduler at 1,000 logical ticks/s. No ESP32 hardware or ESP-IDF installation is needed.

Use blocking synchronization rather than guessed startup sleeps. Do not print/log from RTOS tasks; the harness records results and prints after the scheduler stops. Kernel assertions, deadlocks and invalid API use fail the run. The timeout is a watchdog, not a timing grade. Desktop scheduling and simulator results do not establish hardware real-time guarantees. Do not change API declarations or harness configuration.
