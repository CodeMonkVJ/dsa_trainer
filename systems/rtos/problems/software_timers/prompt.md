# Software Timers and Deferred Work

Deliver timer events without blocking the shared timer daemon and shut timers down safely.

## Required behavior

PulseTimer is caller-owned and remains alive through pulse_destroy. pulse_create(timer,period,periodic,events,id) creates a stopped timer; reject null timer/events or period zero. On expiry copy id into the supplied uintptr_t event queue with zero wait; drop events when full. pulse_reset starts/restarts using xTimerReset. pulse_stop and pulse_destroy are synchronous from ordinary task context only, never from a timer callback: enqueue stop/delete and a daemon barrier with xTimerPendFunctionCall, then wait for that barrier. After they return no old callback may use context. Events already queued remain queued. The event queue outlives the timer. No vTaskDelay, logging, or blocking queue writes inside the callback. Invalid/null/uninitialized handles return false; failed create leaves handle null. Single controlling client, no concurrent reset/destroy.

## API

```c
#include "lab.h" /* FreeRTOS task, queue, semaphore, timer and event APIs */
typedef struct{TimerHandle_t handle;QueueHandle_t events;uintptr_t id;} PulseTimer;
bool pulse_create(PulseTimer *p,TickType_t period,bool periodic,QueueHandle_t events,uintptr_t id);
bool pulse_reset(PulseTimer *p);
bool pulse_stop(PulseTimer *p);
bool pulse_destroy(PulseTimer *p);
```

## Practice environment

Write C using the supplied FreeRTOS APIs in the editor. Save your changes and press **Run tests**. This exercise runs on Linux x86 using the pinned FreeRTOS POSIX port, configured as a single-core preemptive scheduler at 1,000 logical ticks/s. No ESP32 hardware or ESP-IDF installation is needed.

Use blocking synchronization rather than guessed startup sleeps. Do not print/log from RTOS tasks; the harness records results and prints after the scheduler stops. Kernel assertions, deadlocks and invalid API use fail the run. The timeout is a watchdog, not a timing grade. Desktop scheduling and simulator results do not establish hardware real-time guarantees. Do not change API declarations or harness configuration.
