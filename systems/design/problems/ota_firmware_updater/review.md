# OTA updater self-review

Manual design assessment; no automatic grading.

- [ ] My flash map fits 2 MiB with real metadata/alignment overhead and a recovery image.
- [ ] Signed metadata binds image identity, hash, size, hardware and compatibility requirements.
- [ ] Trust roots are protected and the bootloader independently verifies executable images.
- [ ] I specify key rotation, revocation and recovery trust policy.
- [ ] Each durable state can recover from torn writes or power loss.
- [ ] The unconfirmed image cannot destroy the only known-good recovery path.
- [ ] Trial boot has bounded attempts, meaningful local health checks and watchdog behavior.
- [ ] Anti-downgrade counters do not invalidate recovery before trial confirmation.
- [ ] Persistent data remains usable after firmware rollback.
- [ ] Rollout health has cohorts, thresholds, denominators and a pause mechanism.
- [ ] Offline devices and interrupted downloads follow a bounded retry/storage policy.
- [ ] I distinguish an authorized rollback from an attacker replaying an old release.
