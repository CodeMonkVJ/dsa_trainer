# Mutex-Protected Shared State

Keep a multi-field invariant valid across concurrent updates and snapshots.

## Required behavior

SharedState stores value and inverse=-value under one mutex. shared_init starts at zero. shared_add adds delta only after acquiring the mutex within wait ticks; shared_read returns both fields as one consistent snapshot and preserves outputs if it cannot acquire. All successful reads/writes must use the same mutex. Inputs keep arithmetic within signed int range and exclude INT_MIN. Destroy only after all workers stop.

## API

```c
#include "lab.h" /* FreeRTOS task, queue, semaphore, timer and event APIs */
typedef struct {SemaphoreHandle_t mutex;int value,inverse;} SharedState;
bool shared_init(SharedState *s);
bool shared_add(SharedState *s,int delta,TickType_t wait);
bool shared_read(SharedState *s,int *value,int *inverse,TickType_t wait);
void shared_destroy(SharedState *s);
```

## Practice environment

Write C using the supplied FreeRTOS APIs in the editor. Save your changes and press **Run tests**. This exercise runs on Linux x86 using the pinned FreeRTOS POSIX port, configured as a single-core preemptive scheduler at 1,000 logical ticks/s. No ESP32 hardware or ESP-IDF installation is needed.

Use blocking synchronization rather than guessed startup sleeps. Do not print/log from RTOS tasks; the harness records results and prints after the scheduler stops. Kernel assertions, deadlocks and invalid API use fail the run. The timeout is a watchdog, not a timing grade. Desktop scheduling and simulator results do not establish hardware real-time guarantees. Do not change API declarations or harness configuration.
