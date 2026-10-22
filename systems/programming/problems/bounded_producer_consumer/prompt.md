# Bounded Producer–Consumer Queue

Implement a blocking FIFO of non-null `void *` payloads using C17 and POSIX pthreads.

## Mandatory requirements

- Distinguish full from empty and use every capacity slot.
- Push waits while full and open; pop waits while empty and open. Use **while** predicates to handle spurious wakeups and competing waiters.
- Protect every read and write of queue state, including the stop/closed flag, with the same mutex.
- Closing wakes **all** waiting producers and consumers.
- Define who owns every payload on success, failure, shutdown, and destruction.

## API and lifecycle

Use the declarations in `starter.c`. Do not copy a queue after initialization.

- `bq_init(q, capacity)`: allocate pointer storage, initialize mutex/condition variables, and return true. Reject zero capacity, invalid pointers, allocation-size overflow, allocation failures, and synchronization initialization failures. Clean up partial initialization. Only use/destroy a successfully initialized queue.
- `bq_push(q, payload)`: block until space exists or the queue closes. Return true only when the payload was enqueued; reject null payload/queue immediately. A push after close returns false even if space remains.
- `bq_pop(q, out)`: block until an item exists or the queue closes. Return the oldest pointer through `out` on success. **Drain items already queued after close**; return false when closed and empty. Invalid arguments return false. Preserve `*out` on failure.
- `bq_close(q)`: idempotent, safe concurrently with push/pop and other close calls; set closed under the mutex and broadcast both conditions. A null queue is a no-op.
- `bq_destroy(q, dispose)`: caller first closes the queue, joins every producer/consumer and ensures no other API calls can occur. Call `dispose` exactly once per remaining item, release pointer storage, and destroy synchronization objects. A non-null disposer is required if items remain. A null queue is a no-op. Destroy exactly once; reinitialization is allowed afterward.

### Ownership

Before push, the producer owns its payload. A successful push transfers ownership to the queue; a failed push leaves ownership with the producer. A successful pop transfers ownership to the consumer. Close does not free queued items. Destroy disposes remaining items after all threads have stopped. A payload must not be submitted twice while it is already owned by the queue, and callers must not access it after transferring ownership.

The queue manages pointers, not the objects they reference. Callers supply the correct destructor (`free` for individual heap allocations). Consumers dispose popped items themselves. The reference never calls a disposer while holding the queue mutex.

### Shutdown

1. Call `bq_close` to prevent further pushes and wake all waiters.
2. Consumers may drain pending work; blocked producers return false and reclaim their rejected payloads.
3. Join all threads, then destroy the queue.

For normal completion, join producers before closing so their work can finish. For early shutdown, close first so blocked producers can exit. Do not use `pthread_cancel`, asynchronous signal handlers, or concurrent destruction in this exercise; these require additional cleanup rules. pthread operations on valid initialized objects are assumed to succeed during normal use.

Reference complexity: O(capacity) pointer storage, O(1) queue bookkeeping per push/pop excluding blocking, and O(remaining items) destruction.
