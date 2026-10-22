# Timer Service

Register, expire and cancel timers with explicit callback lifetime rules.

## Contract

Use a fixed pool of 16 one-shot timers. timer_register takes an absolute monotonic uint64_t deadline and returns a nonzero unique ID, or 0 on capacity/argument/ID exhaustion. timer_cancel returns true only for a pending ID. timer_expire(now) dispatches due timers ordered by deadline, then ID, returning the callback count. Remove each timer before invoking it; callbacks may register/cancel timers, including other due timers. Timers registered during dispatch wait until the next expire call (snapshot the ID limit). Recursive expire returns 0. Callback context is borrowed and must live until callback completion or successful cancellation. A callback cannot cancel itself once execution begins. All calls must occur on the same event-loop thread: cross-thread cancellation requires external serialization; a failed cancel is not proof a concurrent callback has completed. Never destroy the service inside a callback. Cancellation does not free context automatically.

## API

```c
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
typedef void (*TimerCallback)(void *);
typedef struct { uint64_t id, deadline; TimerCallback callback; void *context; } TimerEntry;
typedef struct { TimerEntry entries[16]; uint64_t next_id; bool dispatching; } TimerService;
void timer_init(TimerService *s);
uint64_t timer_register(TimerService *s, uint64_t deadline, TimerCallback callback, void *context);
bool timer_cancel(TimerService *s, uint64_t id);
size_t timer_expire(TimerService *s, uint64_t now);
```

Implement the API in `starter.c`. The reference lives in `implementation.c`; the harness includes the selected source through `DSA_IMPLEMENTATION`.

Run from this directory:

```sh
gcc -std=c17 -Wall -Wextra -Wpedantic tests/test.c -o /tmp/systems-timer_service
/tmp/systems-timer_service
```
