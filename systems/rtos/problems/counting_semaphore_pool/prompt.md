# Counting Semaphore Resource Pool

Bound access to a finite number of resources with a counting semaphore.

## Required behavior

PermitPool owns a counting semaphore initialized with capacity available permits. pool_init rejects zero/null; pool_acquire waits up to wait ticks and consumes one permit, pool_release returns one permit and fails if already full. Caller must return only permits it owns. Do not maintain a separate unsynchronized count. Destroy after all users stop.

## API

```c
#include "lab.h" /* FreeRTOS task, queue, semaphore, timer and event APIs */
typedef struct {SemaphoreHandle_t permits;} PermitPool;
bool pool_init(PermitPool *pool,unsigned capacity);
bool pool_acquire(PermitPool *pool,TickType_t wait);
bool pool_release(PermitPool *pool);
void pool_destroy(PermitPool *pool);
```

## Practice environment

Write C using the supplied FreeRTOS APIs in the editor. Save your changes and press **Run tests**. This exercise runs on Linux x86 using the pinned FreeRTOS POSIX port, configured as a single-core preemptive scheduler at 1,000 logical ticks/s. No ESP32 hardware or ESP-IDF installation is needed.

Use blocking synchronization rather than guessed startup sleeps. Do not print/log from RTOS tasks; the harness records results and prints after the scheduler stops. Kernel assertions, deadlocks and invalid API use fail the run. The timeout is a watchdog, not a timing grade. Desktop scheduling and simulator results do not establish hardware real-time guarantees. Do not change API declarations or harness configuration.
