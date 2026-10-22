# One possible reference design

## Public contract

Use opaque driver and timer handles containing a generation. The driver transitions CLOSED → INITIALIZING → OPEN → CLOSING → CLOSED; a timer transitions IDLE → ARMED → QUEUED → RUNNING → IDLE, with cancellation paths. CLOSED is not callable except through a separate allocation/initialization entry point.

Example signatures:

```c
DriverResult driver_open(const DriverConfig *, Driver **out);
DriverResult timer_create(Driver *, TimerHandle *out);
DriverResult timer_arm(TimerHandle, uint64_t monotonic_deadline_ns,
                       TimerCallback, void *context);
CancelResult timer_cancel(TimerHandle);
DriverResult timer_cancel_sync(TimerHandle);
DriverResult timer_release(TimerHandle);
DriverResult driver_close(Driver *);
```

Specify BAD_ARGUMENT, NO_MEMORY, NO_CHANNEL, STALE_HANDLE, CLOSED, BUSY, WOULD_DEADLOCK and hardware failures. For this version one client timer consumes a channel; at most four exist. Arming an already armed/running timer is BUSY; rearm only from IDLE or after synchronous cancellation. Deadlines are absolute monotonic nanoseconds; reject unrepresentable deadlines, and queue an already-past deadline for prompt dispatch. Delivery may be late, never intentionally early.

## Cancellation and lifetime

Maintain state and a dispatch generation under a lock. IRQ code records expiry using an interrupt-safe mechanism; it does not call users. Worker code claims an eligible generation and marks RUNNING under the lock, then invokes the callback outside it. On completion, the worker records IDLE and signals waiters.

A nonblocking cancel invalidates ARMED/QUEUED work and returns CANCELED, or reports RUNNING/NOT_PENDING. CANCELED means the retired callback will not begin. RUNNING provides no lifetime guarantee. Synchronous cancel invalidates pending work, waits for running work to finish, and succeeds only when that callback/context generation is no longer accessible. Serialize simultaneous arm/cancel; clients must not immediately rearm the same context while another caller frees it after cancel.

Reject synchronous cancel of oneself and synchronous close from callback context with WOULD_DEADLOCK. Document request-only self-cancel separately; it cannot undo the running call. A callback may operate on a different handle within the documented lock rules.

A worker that claims first may run; cancel_sync waits. A cancel that invalidates first causes the queued dispatch to be skipped. Generation checks prevent a late queued event from invoking a new timer occupying the same slot.

## Initialization and shutdown

Acquire memory, clock and hardware configuration, dispatch queue, IRQ registration and worker while the source remains masked. Enable interrupts only after OPEN is fully established. On failure, unwind in reverse acquisition order, synchronizing an IRQ if it could have executed.

On close, atomically transition to CLOSING, reject new API work, stop timers, mask and quiesce interrupts, invalidate pending events, wake and join dispatch, then release hardware and memory. Concurrent callers hold lifetime references until their operations exit. Stale handles fail generation validation.

Extend narrow hardware counters with a proven wrap protocol. Clock conversion must be checked; clock adjustments cannot silently alter monotonic deadlines. Document dispatch jitter and measure it separately from hardware resolution.
