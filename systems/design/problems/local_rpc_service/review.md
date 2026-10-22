# Local RPC self-review

Manual assessment only; no executable tests or automatic grading.

- [ ] My protocol bounds lengths before allocation and handles arbitrary stream chunking.
- [ ] Connection-local routing IDs and durable retry identities have separate roles.
- [ ] Admission control accounts for queued jobs, in-flight requests and reserved replies.
- [ ] Per-client and global limits interact without permitting unbounded memory growth.
- [ ] Workers never concurrently write directly to the same socket.
- [ ] Request and connection lifetimes survive disconnect and delayed completion.
- [ ] Descriptor reuse cannot route an old response to a new client.
- [ ] Queued and running cancellation have explicit, different guarantees.
- [ ] A timeout or disconnect is not incorrectly treated as proof of rollback.
- [ ] Retry/deduplication semantics have a retention and failure model.
- [ ] Shutdown handles new admissions, queued work, running work and slow clients.
- [ ] I cover malformed frames, backpressure, authorization and partial initialization.
