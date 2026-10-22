# Persistent Configuration Service

Design a local Linux service that owns a versioned configuration document up to 64 KiB. There is one writer service and many client readers. Updates may race, the process may crash, and the machine may lose power at any write, synchronization or rename. Disk space can run out.

Assume a local filesystem with documented atomic same-filesystem replacement and file/directory synchronization support; identify what you would verify on the deployed filesystem/storage stack. Do not assume the same guarantees for network filesystems.

## Required discussion

- Define read/update APIs, validation rules, schema version and revision numbers. How do clients prevent lost updates?
- Describe immutable reader snapshots and their ownership, plus synchronization between validation, persistence and publication.
- Give the exact update sequence: staging, complete writes, integrity metadata, file synchronization, atomic replacement, directory synchronization and acknowledgment.
- Distinguish visibility from durability. Define results when replacement succeeds but directory synchronization fails: the client must not be told that the old configuration is certainly still active.
- Explain how request identities and expected revisions make retry safe after an ambiguous response or lost acknowledgment.
- Write recovery rules for missing, truncated, corrupted and unsupported-version documents and abandoned temporary files.
- Describe schema migration, validation failure, downgrade compatibility, bootstrap/default policy and any backup strategy.
- Cover partial writes, interrupted calls, ENOSPC/EIO, ownership/permissions and safe temporary-file creation in the target directory.
- State what process-kill tests can establish and what requires power-loss or filesystem-specific fault testing.

## Deliverables

Write an API/result table, record format, concurrency protocol, commit state machine, crash-point recovery table and migration policy. Include a fault-injection matrix for every persistence operation.

## Interview challenges

Two clients update the same revision. The file rename succeeds but directory synchronization fails. The client times out after a successful commit and retries. A new binary starts with an unsupported future schema. Explain the visible state and what each caller can safely conclude.

## Practice format

Write your answer in the editor and save it. Use **Review checklist**, then **Save self-review** to record your assessment. This exercise has no automated correctness grade. Reference designs unlock in red. No hardware is required.
