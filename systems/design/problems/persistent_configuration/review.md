# Persistent configuration self-review

Manual assessment only; this checklist does not grade correctness.

- [ ] My update API has expected-revision and stable request-identity semantics.
- [ ] I serialize writers without holding a global reader lock across slow storage I/O.
- [ ] Reader snapshots have an explicit lifetime and cannot observe half an update.
- [ ] Staging and replacement remain on the same filesystem.
- [ ] I handle partial/interrupted writes and check synchronization/close results.
- [ ] I distinguish atomic visibility from durable acknowledgment.
- [ ] A failure after rename can return an explicit ambiguous outcome.
- [ ] Retrying an ambiguous update cannot apply it twice or overwrite a newer revision.
- [ ] Every crash point has a documented recovery state.
- [ ] Unsupported schema or corruption is not silently treated as an empty configuration.
- [ ] Migration and backup retention have a recovery/compatibility policy.
- [ ] I separate deterministic fault injection from real power-loss guarantees.
