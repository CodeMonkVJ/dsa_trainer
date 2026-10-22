# RTOS Producer–Consumer Buffer

Build a semaphore-counted bounded buffer with cooperative close and drain semantics.

## Required behavior

Stream holds up to 4 copied unsigned values; capacity is 1..4. Use mutex for head/tail/count/closed and counting semaphores for slots/items. stream_push blocks while full until a slot or close; it returns false after close, including if capacity remains. stream_pop drains after close and returns false only when closed and empty; preserve out on failure. Wait in at most one-tick semaphore slices to observe close: no fake semaphore permits, unsynchronized stop flags, or busy polling. Resource release after all API users stop. Successful initialization is a precondition for operations; null arguments rejected. stream_close is idempotent and synchronized. All initialized semaphore operations are assumed to succeed; initialization must unwind partial allocations.

## API

```c
#include "lab.h" /* FreeRTOS task, queue, semaphore, timer and event APIs */
typedef struct {unsigned data[4],capacity,head,tail,count;bool closed;SemaphoreHandle_t mutex,slots,items;} Stream;
bool stream_init(Stream *s,unsigned capacity);
bool stream_push(Stream *s,unsigned value);
bool stream_pop(Stream *s,unsigned *out);
void stream_close(Stream *s);
void stream_destroy(Stream *s);
```

## Practice environment

Write C using the supplied FreeRTOS APIs in the editor. Save your changes and press **Run tests**. This exercise runs on Linux x86 using the pinned FreeRTOS POSIX port, configured as a single-core preemptive scheduler at 1,000 logical ticks/s. No ESP32 hardware or ESP-IDF installation is needed.

Use blocking synchronization rather than guessed startup sleeps. Do not print/log from RTOS tasks; the harness records results and prints after the scheduler stops. Kernel assertions, deadlocks and invalid API use fail the run. The timeout is a watchdog, not a timing grade. Desktop scheduling and simulator results do not establish hardware real-time guarantees. Do not change API declarations or harness configuration.
