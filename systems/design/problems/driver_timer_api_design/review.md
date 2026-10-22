# Driver/timer API self-review

Manual assessment only; no automatic correctness grade.

- [ ] My API specifies time units, clock, deadline boundaries, overflow and capacity errors.
- [ ] Driver and timer state transitions make every public operation well-defined.
- [ ] Callback context remains valid until a documented quiescence guarantee.
- [ ] I distinguish pending expiry, queued dispatch and running callback.
- [ ] I define cancellation's linearization point and separate request-only from synchronous cancel.
- [ ] Successful synchronous cancel prevents future access to the retired callback/context.
- [ ] Self-cancel and callback-triggered shutdown cannot deadlock.
- [ ] I explain the callback lock policy and reentrancy.
- [ ] Every partial initialization failure unwinds only resources actually acquired.
- [ ] Shutdown prevents new operations, quiesces hardware/IRQ, and drains or suppresses dispatch before freeing state.
- [ ] Stale handles cannot operate on a newly reused timer.
- [ ] I walk through at least two concrete cancellation/expiry schedules.
