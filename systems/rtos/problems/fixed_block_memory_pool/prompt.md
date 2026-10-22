# Fixed-Block Memory Pool

Allocate bounded reusable blocks with ownership validation and no per-allocation heap use.

## Required behavior

MemoryPool has four 32-byte blocks and a mutex; capacity is 1..4. mem_pool_get returns a free block or NULL on exhaustion/mutex timeout. mem_pool_put accepts only the exact start of a currently allocated block owned by that pool; reject null, foreign, interior and double-return pointers. Identify pointers without subtracting or ordering unrelated objects. Protect metadata with the mutex. Successful get transfers exclusive block ownership to caller until put. Destroy only after all owners return blocks and users stop.

## API

```c
#include "lab.h" /* FreeRTOS task, queue, semaphore, timer and event APIs */
typedef struct{unsigned char blocks[4][32];bool used[4];unsigned capacity;SemaphoreHandle_t mutex;} MemoryPool;
bool mem_pool_init(MemoryPool *p,unsigned capacity);
void *mem_pool_get(MemoryPool *p,TickType_t wait);
bool mem_pool_put(MemoryPool *p,void *block);
void mem_pool_destroy(MemoryPool *p);
```

## Practice environment

Write C using the supplied FreeRTOS APIs in the editor. Save your changes and press **Run tests**. This exercise runs on Linux x86 using the pinned FreeRTOS POSIX port, configured as a single-core preemptive scheduler at 1,000 logical ticks/s. No ESP32 hardware or ESP-IDF installation is needed.

Use blocking synchronization rather than guessed startup sleeps. Do not print/log from RTOS tasks; the harness records results and prints after the scheduler stops. Kernel assertions, deadlocks and invalid API use fail the run. The timeout is a watchdog, not a timing grade. Desktop scheduling and simulator results do not establish hardware real-time guarantees. Do not change API declarations or harness configuration.
