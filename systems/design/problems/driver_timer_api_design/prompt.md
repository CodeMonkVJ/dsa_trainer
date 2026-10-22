# Driver / Timer API Design

Design a C API for an asynchronous hardware timer driver shared by multiple clients. Hardware provides four compare channels; an interrupt records expirations, while a worker dispatches user callbacks. Clients may create timers, arm/rearm them, cancel them, and close the driver from task context.

This is an API and lifecycle design exercise, not a repeat of the Timer Service coding exercise. You must specify observable guarantees under concurrent calls and partial failure.

## Required discussion

- Define driver and timer states, valid transitions, handle lifetimes, and which operations are legal in task, worker-callback, or interrupt context.
- Propose C signatures and error results for initialization, timer creation, arming, cancellation, and shutdown. Separate relative/absolute time, clock source, overflow, past deadlines, and timer/channel exhaustion.
- State whether callbacks run under a driver lock, whether callbacks may rearm/cancel, and who owns callback context while pending or executing.
- Define cancellation linearization and return results when expiry has queued a callback or callback execution has started. Distinguish cancel-request from cancel-and-wait.
- Define what a successful synchronous cancel guarantees about future callback access. Address callbacks attempting to cancel themselves, and shutdown from callback context.
- Describe initialization failure after each resource acquisition: memory, clock, hardware channels, interrupt registration, queue and worker. Unwind partial state safely.
- Explain concurrent close/arm/cancel behavior, stale handles and ID reuse, in-flight callbacks, and late interrupts.
- Explain how hardware-counter wrap, clock changes, and delivery jitter affect the contract.

## Deliverables

Write the public API, state machine, operation/result table, callback ownership contract, two expiry/cancellation interleavings, initialization/unwind pseudocode and shutdown order.

## Interview challenges

An expiry is already in the dispatch queue when cancel arrives. A callback tries cancel-and-wait on itself. Worker creation fails after IRQ registration. A stale handle is used after a channel is recycled. Explain each result precisely.

## Practice format

Write your design in the editor and save it. Use **Review checklist** to assess your answer, then **Save self-review** to record your own assessment. These exercises have no executable tests or automatic correctness grading. References unlock in red, as for coding exercises.
