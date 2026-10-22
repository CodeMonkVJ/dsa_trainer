# Ring Buffer

Implement a bounded byte FIFO with wraparound and reject-on-full policy.

## Contract

ring_init takes caller-owned storage and positive capacity. ring_push/ring_pop return false when full/empty or arguments are invalid; failures preserve state and pop output. Store head, tail and count so every storage slot is usable. Overflow policy: reject the new byte. No allocation; caller owns storage for the buffer lifetime. Single-threaded; this is not a lock-free concurrent queue. Call operations only on successfully initialized buffers.

## API

```c
#include <stddef.h>
#include <stdbool.h>
typedef struct { unsigned char *data; size_t capacity, head, tail, count; } Ring;
bool ring_init(Ring *r, unsigned char *storage, size_t capacity);
bool ring_push(Ring *r, unsigned char value);
bool ring_pop(Ring *r, unsigned char *out);
```

Implement the API in `starter.c`. The reference lives in `implementation.c`; the harness includes the selected source through `DSA_IMPLEMENTATION`.

Run from this directory:

```sh
gcc -std=c17 -Wall -Wextra -Wpedantic tests/test.c -o /tmp/systems-ring_buffer
/tmp/systems-ring_buffer
```
