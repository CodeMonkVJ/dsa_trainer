# One possible reference design

## Architecture and bounds

Use a fixed frame pool, a bounded descriptor queue, and one worker. Configure one ISR producer for this version. Reserve a descriptor only after DMA completion; publish a pointer, length, sequence number, and capture timestamp.

Assume an arrival envelope of at most 40 + 4,000t frames over any interval of length t seconds, an initial empty backlog, a maximum 3 ms blackout, and guaranteed processing at 50,000 frames/s afterward. A conservative blackout backlog is 40 + 12 = 52 frames. Choose 64 queued descriptors. The 3 ms assumption must cover all competing work, not just one preemption; validate a service guarantee for repeated blackouts before accepting this bound. The service rate exceeds sustained arrivals.

The pool needs up to 64 queued frames, one worker-owned frame and two DMA buffers: 67 × 256 = 17,152 bytes, plus descriptors, alignment, synchronization and stack. Check the complete allocation fits 32 KiB. Bound worker delay using the service guarantee and items ahead; also account for capture time and scheduling. Do not call the 20 µs service time alone an end-to-end bound.

## Synchronization and ownership

DMA owns its programmed buffers. On completion, stop reusing the completed frame until ownership can transfer to the worker and eventually back to the pool. Install a free replacement before rearming DMA. The ISR acknowledges hardware, publishes a descriptor with an ISR-safe operation, requests a scheduler handoff when required, and returns. Measure this path against 5 µs.

A suitable RTOS queue combines publication and notification; verify the target interrupt's priority can legally call its ISR variant. Otherwise use a platform-specific interrupt-safe handoff. A custom single-producer queue needs acquire/release ordering and a notification protocol that cannot lose wakeups; volatile is not a substitute. DMA cache maintenance and barriers depend on the MCU and memory placement.

On overflow, drop the newly completed frame, return it safely to the pool, increment a loss counter and expose sequence gaps. Never spin waiting for the worker. If replacement storage is unavailable, stop or throttle acquisition according to the documented hardware policy.

## Lifecycle

Initialize the pool, queue and worker before enabling DMA and its interrupt. To stop: disable new captures, stop DMA, mask/acknowledge the interrupt, establish that no ISR can still publish, then notify the worker to drain or discard. Join the worker, reclaim its frame and all DMA buffers, and only then free the pool. Publish stop state through the chosen synchronization primitive.

Inject bursts, pool exhaustion, delayed service and shutdown at each ownership transition. For SMP or multiple producers, replace the single-producer assumptions and prove the new synchronization.

Background: [FreeRTOS ISR queue API](https://2www.freertos.org/Documentation/02-Kernel/04-API-references/06-Queues/06-xQueueSendToBackFromISR). Specific priorities, timing and DMA behavior require the chosen platform's documentation.
