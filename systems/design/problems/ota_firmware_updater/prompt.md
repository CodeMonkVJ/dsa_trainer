# OTA Firmware Updater

Design an OTA update system for a fleet of intermittently connected embedded devices. Each has 2 MiB flash, a 64 KiB protected bootloader, and firmware images up to 768 KiB. Devices may lose power at any flash write or reset unexpectedly during their first boot. The network and update server transport path are untrusted; authorized release-signing keys are managed separately.

## Required discussion

- Define trust boundaries, manifest/image authenticity, immutable trust anchors, signing-key rotation/revocation, freshness and anti-downgrade policy. Explain why transport encryption or an unsigned checksum alone is insufficient.
- Propose a flash map that fits the budget, including slots, metadata, configuration, erase/write alignment and image overhead.
- Define download, verification, pending boot, trial boot, confirmation and rollback states. Specify durable transitions and recovery after torn writes or interrupted installation.
- Explain how the bootloader independently chooses and verifies an image. How do you avoid bricking both slots? How are interrupted swap/copy operations resumed if your architecture needs them?
- Define trial boot health criteria, watchdog/reset behavior, attempt limits and confirmation authority. Distinguish firmware rollback from malicious version downgrade.
- Define when an irreversible security counter advances so an unconfirmed trial does not invalidate its recovery image.
- Address hardware revision, bootloader version, multi-image dependencies, persistent-data schema migration and rollback compatibility.
- Propose staged rollout cohorts, pause/rollback decisions, telemetry, offline devices, retries, resource limits and a recovery path.
- State the threat model and what happens if a release key or the running application is compromised.

## Deliverables

Write a flash map, device/update state machine, trust and verification flow, power-loss recovery table, compatibility policy, trial-health contract and fleet rollout plan. End with a fault-injection matrix covering interruption at every durable transition.

## Interview challenges

Power fails during metadata confirmation. The new image boots but corrupts persistent settings. A device stays offline for six months. The fleet health service reports a rising crash rate. Explain recovery and rollout decisions without relying on uninterrupted connectivity.

## Practice format

Write your design in the editor and save it. Use **Review checklist** to assess your answer, then **Save self-review** to record your own assessment. These exercises have no executable tests or automatic correctness grading. References unlock in red, as for coding exercises.
