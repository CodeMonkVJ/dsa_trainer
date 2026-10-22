# One possible reference design

## API and ownership

Use read_snapshot() and update(expected_revision, request_id, document). Return APPLIED(revision), ALREADY_APPLIED(revision), CONFLICT(current_revision), INVALID, UNSUPPORTED_SCHEMA, STORAGE_ERROR or COMMIT_UNKNOWN. Request IDs belong to a client namespace and bind the exact operation/payload digest; reuse with a different payload is an error.

The service is the only writer. A commit mutex serializes updates and migrations. Publish immutable reference-counted snapshots under a short pointer-swap lock; readers release their reference after use. Do not hold the reader lock while waiting for storage. External readers opening the canonical path get either file generation, never a partially rewritten document.

The record contains format/schema version, revision, payload length, integrity digest and the last accepted request identity plus payload digest. Reject excessive lengths before allocating. A checksum detects damage; it does not authenticate malicious input. Client authorization and file ownership are separate checks.

## Commit protocol

Validate the proposed document and expected revision under the writer protocol. Create a unique exclusive temporary file in the same trusted directory, with the intended permissions. Write the complete encoded record using partial-write/EINTR handling. Synchronize the file and check close errors. Replace the canonical path atomically, then synchronize its containing directory before issuing a durable APPLIED acknowledgment.

Before replacement, failures leave the previously committed path active and the staging file can be removed safely. After replacement, other readers may already see the new generation. If directory synchronization fails, expose COMMIT_UNKNOWN/degraded storage state and reconcile the visible record rather than claiming the update was rolled back. Retain enough request identity to identify a retry; attempt to establish durability before returning durable success.

For a retry of the current committed request, match identity and digest and return ALREADY_APPLIED. Never reapply it over a newer revision. Supporting long-lived retry identities across many later updates requires a durable deduplication ledger and a stated retention bound; a single last-request field is not an unlimited exactly-once guarantee.

## Recovery and migration

With the stated filesystem assumptions, the canonical record after a crash is a complete old or new generation if one exists; validate it before publication. A staged file is not proof of commitment. If the canonical document is missing/corrupt, consult a separately specified validated backup or enter recovery mode. Only an explicit first-boot policy may install defaults. Do not silently discard settings.

Migrate a validated supported schema into a new record through the same commit protocol. Preserve a compatible recovery path and document whether older binaries can read the new schema. Reject unknown future schemas. A backup is useful only if its own update and retention protocol survive the crash states being claimed.

Trace failures before and after each write, file sync, close, replacement, directory sync and publication. Process-kill tests exercise application recovery; they do not remove the OS's caches and therefore do not alone prove power-loss durability.

References: [rename](https://man7.org/linux/man-pages/man2/rename.2.html), [fsync](https://man7.org/linux/man-pages/man2/fsync.2.html), and [read/short-I/O semantics](https://man7.org/linux/man-pages/man2/read.2.html).
