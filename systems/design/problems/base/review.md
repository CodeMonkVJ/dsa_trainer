# ISR-to-worker self-review

This checklist is for your own assessment; it does not execute or grade your design.

- [ ] I state the arrival model, maximum worker blackout, service rate, ISR budget, and scheduling assumptions.
- [ ] My capacity calculation includes burst arrivals during the blackout and all distinct frame owners.
- [ ] ISR operations have bounded execution time and never block or allocate.
- [ ] My queue operation matches the interrupt priority rules of the chosen RTOS.
- [ ] I explain publish/acquire ordering and the platform-specific DMA/cache handoff.
- [ ] Each frame has one owner, including enqueue failure and queue overflow.
- [ ] The worker cannot miss a wakeup between checking for data and sleeping.
- [ ] My overflow policy produces observable loss metrics and defined downstream behavior.
- [ ] Shutdown stops the source, quiesces DMA/ISR, wakes the worker, and reclaims all frames before freeing memory.
- [ ] I discuss a full queue, delayed worker, nested interrupt, and shutdown race.
- [ ] I distinguish analytical bounds from measurements still required on hardware.
