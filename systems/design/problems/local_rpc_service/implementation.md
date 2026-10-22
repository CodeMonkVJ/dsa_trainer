# One possible reference design

## Protocol and budgets

Use a fixed-size header with protocol version, message type, uint32 big-endian payload length and uint64 connection-local request ID. Limit payloads to 4 KiB before allocating. Separate an update's stable idempotency key and expected revision from its response-routing ID. Reject duplicate outstanding routing IDs. Define whether unknown message types receive an error or close the connection; do not guess payload layouts.

A single nonblocking event loop owns socket reads, writes and each connection's framing/output state. Incrementally assemble frames, preserve unread bytes and handle multiple frames per read. Maintain offsets across short writes. EOF inside a frame is malformed/truncated input; clean EOF still does not revoke already committed work.

At acceptance, reserve a job descriptor, bounded request bytes and a bounded reply allowance. The 32-job queue limit does not include the four running jobs unless explicitly defined; count both. Apply per-connection outstanding limits, the 64 KiB per-connection output limit and the 2 MiB global output limit jointly. For these small configuration operations, define a maximum response size up front and reserve it; do not let completed workers allocate arbitrary replies. Stop reading or reject new work when admission credits run out, while preserving capacity for existing completions. Use a fair per-client admission policy.

## Ownership and execution

Worker jobs own immutable request data and a reference to a connection-generation token, not just an fd. The loop consumes completions and serializes responses. Disconnect retires the generation and drops undeliverable results; it does not free a still-referenced job/context. Each resource reservation is released exactly once when the request reaches its terminal state.

Use ACCEPTED → QUEUED → RUNNING → COMMITTED → REPLIED, plus REJECTED, EXPIRED and CANCELED states. Cancellation that atomically removes a queued job guarantees no execution. A running handler can observe a cooperative cancel flag before its commit boundary, but cancellation after commit returns TOO_LATE/COMMITTED and cannot pretend to undo the update. Synchronize every state transition.

Convert a received timeout budget into a server-side monotonic deadline and include queue time. A client-side timeout describes the client's wait, not necessarily the operation's outcome.

## Retries and lifecycle

Reads can generally be retried. An update uses expected revision plus a durable idempotency key/payload digest. A lost response after commit must be resolved by retry/status lookup, not blindly replayed as a new mutation. Bound deduplication retention and explain behavior after that window. Do not claim end-to-end exactly-once execution from a volatile request-ID map.

Check authorized peer identity on accept according to deployment policy; use a trusted socket directory. On startup failure, release only acquired descriptors, workers and path ownership. Signal handlers only notify the event loop through an appropriate safe mechanism.

Shutdown stops admissions, removes/cancels queued jobs according to policy, drains or cooperatively cancels running handlers, delivers bounded replies until a deadline, closes clients, joins workers and finally releases shared state. Persisted commits survive client disappearance.

Test with socket pairs and deterministic worker barriers: one-byte headers, concatenated frames, oversized lengths, short writes, no-progress readers, disconnect-after-commit, cancel/commit races and fd reuse. These are host-only scenarios and do not need network privileges or hardware.
