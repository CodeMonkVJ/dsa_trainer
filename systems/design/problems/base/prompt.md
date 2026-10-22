# ISR-to-Worker Pipeline

Design an ADC acquisition pipeline on a single-core MCU with an RTOS. An interrupt signals a completed 256-byte DMA frame. Sustained arrival rate is 4,000 frames/s, with an additional burst allowance of 40 frames. The worker can be unavailable for 3 ms and needs at most 20 µs to process a frame once scheduled. The pipeline has a 32 KiB RAM budget. The interrupt must return within 5 µs.

Treat these as design assumptions to validate, not hardware guarantees. Explain any assumptions needed to turn arrival and service rates into a bound.

## Required discussion

- Draw the hardware/DMA → ISR → bounded buffer → worker path and lifecycle states.
- Budget ISR execution, scheduler delay, burst backlog, service time, and end-to-end latency. Size the queue and backing pool explicitly, including queued, DMA-owned and worker-owned frames.
- Define ownership at every transition. Can DMA reuse a frame before worker completion? What happens if enqueue fails?
- Choose synchronization appropriate to the RTOS and interrupt priorities. Discuss memory ordering, DMA/cache coherency, wakeup races, and why a task-level mutex or blocking queue is unsuitable in an ISR.
- Choose a full-buffer policy and explain consequences for lost samples, counters, sequence numbers, and downstream processing.
- Specify startup order and shutdown while an ISR is active or the worker is blocked. Account for queued buffers and in-flight DMA before freeing resources.
- Explain what changes for nested interrupts, multiple producers, SMP, or DMA on a noncoherent platform.

## Deliverables

Write an architecture sketch, state/ownership transitions, capacity calculation, producer/consumer pseudocode, shutdown sequence, and a failure-injection plan. End with the assumptions you would measure on target hardware.

## Interview challenges

The queue fills during a burst. The worker is preempted after reading a descriptor but before releasing it. Shutdown starts just as DMA completes. A higher-priority interrupt cannot use the RTOS queue API. Explain each outcome without unbounded blocking or leaking a frame.

## Practice format

Write your design in the editor and save it. Use **Review checklist** to assess your answer, then **Save self-review** to record your own assessment. These exercises have no executable tests or automatic correctness grading. References unlock in red, as for coding exercises.
