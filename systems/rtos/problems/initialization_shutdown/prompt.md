# Clean Initialization and Shutdown

Unwind partial task/object creation and stop an idle or busy worker without leaking resources.

## Required behavior

Session contains a request queue (capacity 2), mutex, completion semaphore and worker. session_init acquires them in that order and creates a priority-2 worker last, using lab_queue_create/lab_mutex_create/lab_binary_create/lab_task_create. Injected failure must leave live object count unchanged and running=false; cleanup all partial acquisitions. Worker blocks on queue, processes nonnegative integers into processed count and sum under mutex. session_send rejects negative values and closed/uninitialized sessions. A serialized controlling task calls session_close: send internal -1 sentinel, wait for worker's final completion acknowledgment, delete quiescent worker, free kernel objects, mark not running. Already queued work drains before sentinel. Close is idempotent. Worker must not access session after acknowledgment; suspend afterward. Public calls are serialized by one owner task; this exercise does not promise concurrent send/close. No volatile stop flag, arbitrary startup sleeps or forced deletion before acknowledgment. Retain processed/sum fields after close for inspection.

## API

```c
#include "lab.h" /* FreeRTOS task, queue, semaphore, timer and event APIs */
typedef struct{QueueHandle_t queue;SemaphoreHandle_t mutex,done;TaskHandle_t worker;bool running;unsigned processed;int sum;} Session;
bool session_init(Session *s);
bool session_send(Session *s,int value,TickType_t wait);
void session_close(Session *s);
```

## Practice environment

Write C using the supplied FreeRTOS APIs in the editor. Save your changes and press **Run tests**. This exercise runs on Linux x86 using the pinned FreeRTOS POSIX port, configured as a single-core preemptive scheduler at 1,000 logical ticks/s. No ESP32 hardware or ESP-IDF installation is needed.

Use blocking synchronization rather than guessed startup sleeps. Do not print/log from RTOS tasks; the harness records results and prints after the scheduler stops. Kernel assertions, deadlocks and invalid API use fail the run. The timeout is a watchdog, not a timing grade. Desktop scheduling and simulator results do not establish hardware real-time guarantees. Do not change API declarations or harness configuration.
