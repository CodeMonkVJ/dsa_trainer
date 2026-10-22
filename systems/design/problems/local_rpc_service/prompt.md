# Local RPC Service

Design a Linux local RPC service over a Unix-domain SOCK_STREAM socket. It supports reading configuration and applying revision-checked updates. Clients can disconnect or retry after losing a response. Some handlers run on workers and may finish after the client leaves.

Use these initial limits: 64 connections, 4 KiB payload per request, 16 outstanding requests per connection, four workers, a global work queue of 32 jobs, 64 KiB output buffering per connection and 2 MiB output buffering globally. Explain how combined limits and admission control bound total memory rather than simply assuming every limit can be independently saturated.

## Required discussion

- Define the framed protocol: version, message type, length, request identity, result/error and forward-compatibility rules.
- Handle partial/coalesced reads, partial writes, EOF mid-frame, malformed/oversized lengths and unknown message types.
- Describe the event loop, worker handoff, response routing and immutable/ref-counted request ownership.
- Define acceptance, queueing, execution, commit and response-delivery states. Where are operation and cancellation linearization points?
- Specify queue saturation, slow-reader backpressure, fairness and rejection behavior. Account for memory already reserved for work and future replies.
- Distinguish a transport request ID from a stable retry/idempotency key. Explain which operations are safe to retry and how long deduplication lasts.
- Define monotonic deadlines, queued-request expiration, cooperative cancellation and what a client can infer after a timeout/disconnect.
- Protect against stale completions when a file descriptor or connection ID is reused.
- Describe local-client authorization, socket lifecycle, startup failures, signal handling, graceful draining and forced shutdown policy.
- Explain verification using socket pairs, fragmented traffic, blocked readers and injected worker completion schedules.

## Deliverables

Write a protocol layout, connection/request state machines, budget calculation, operation/result table, cancellation/retry contract and shutdown sequence. Include at least three race interleavings.

## Interview challenges

A worker commits an update but the connection dies before the reply. A cancel arrives after commit. A slow reader exhausts output space while workers are producing responses. A new connection reuses a closed connection's file descriptor. Explain each outcome.

## Practice format

Write your answer in the editor and save it. Use **Review checklist**, then **Save self-review** to record your assessment. This exercise has no automated correctness grade. Reference designs unlock in red. No hardware is required.
