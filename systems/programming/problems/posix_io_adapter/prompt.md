# POSIX I/O Adapter

Handle short transfers, EINTR, EAGAIN, EOF, and absolute deadlines without losing partial progress.

## Contract

Implement io_read_exact and io_write_all using injected POSIX-style operations. IoOps contains read_some, write_some, wait_ready and now_ms callbacks plus shared context. Only the selected transfer callback is required, along with wait_ready and now_ms. Callbacks use errno like read/write/poll. Transfer callbacks must be nonblocking; readiness can race and report EAGAIN again. The harness also connects these operations to actual nonblocking pipes.

Return IoResult {status, transferred, error}. IO_OK means all requested bytes transferred. Read zero means IO_EOF, even after partial progress. Write zero means IO_ERROR/EIO to prevent an infinite loop. Negative transfer returns other than -1 are IO_ERROR/EIO. Positive returns must not exceed the remaining request; reject impossible counts as IO_ERROR/EIO. Errors retain the bytes already transferred. Set error only for IO_ERROR (the saved errno, or EIO for invalid callback results); all other statuses use error=0.

Retry EINTR, and on EAGAIN/EWOULDBLOCK wait for readiness. wait_ready(context, writing, absolute_deadline_ms) returns 1 for readiness, 0 for timeout, or -1 with errno. Retry interrupted waits, always using the SAME absolute monotonic deadline, then retry the transfer. A readiness result other than -1/0/1 is IO_ERROR/EIO. A negative clock result is IO_ERROR/EIO. A failed syscall with errno=0 is also EIO.

For every pending transfer or wait, check now_ms first: now >= deadline is IO_TIMEOUT. No deadline extension on progress or interruption. Deadline must be nonnegative. Reject a null operations pointer, required callback, nonzero-length null buffer, or request greater than PTRDIFF_MAX as IO_INVALID before invoking callbacks. Zero length with otherwise valid arguments returns IO_OK without callbacks; its buffer may be null. Caller guarantees the buffer object contains the stated length and callbacks obey their memory-access contracts. The adapter cannot interrupt an accidentally blocking callback.

The functions are synchronous and retain no borrowed buffer or context after returning. This exercise adds OS error/retry semantics to the existing Buffered Reader; it does not internally buffer leftovers.

## API

```c
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <sys/types.h>
typedef enum { IO_OK, IO_EOF, IO_TIMEOUT, IO_ERROR, IO_INVALID } IoStatus;
typedef struct { IoStatus status; size_t transferred; int error; } IoResult;
typedef struct {
 void *context;
 ssize_t (*read_some)(void *, void *, size_t);
 ssize_t (*write_some)(void *, const void *, size_t);
 int (*wait_ready)(void *, bool, int64_t);
 int64_t (*now_ms)(void *);
} IoOps;
IoResult io_read_exact(const IoOps *ops, void *buffer, size_t length, int64_t deadline_ms);
IoResult io_write_all(const IoOps *ops, const void *buffer, size_t length, int64_t deadline_ms);
```

Save your implementation in the editor and use **Run tests**. All tests run on the Linux x86 host. No hardware is required.
