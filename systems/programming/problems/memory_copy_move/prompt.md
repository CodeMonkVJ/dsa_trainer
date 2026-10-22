# Memory Copy and Move

Copy byte ranges with explicit overlap and bounds contracts.

## Contract

byte_copy(dst, dst_capacity, src, n) copies n bytes; source and destination must not overlap. byte_move permits overlap in either direction. Both return false for n > capacity or null pointers with n > 0 and leave destination unchanged on these errors. n == 0 succeeds even for null pointers. Caller supplies valid objects containing the stated number of readable/writable bytes; capacity cannot validate an arbitrary pointer. Overlap in byte_copy is a caller precondition, as with memcpy. Use byte operations, no libc copy functions. The portable reference move uses temporary storage (O(n) space) and returns false unchanged on allocation failure.

## API

```c
#include <stddef.h>
#include <stdbool.h>
bool byte_copy(void *dst, size_t capacity, const void *src, size_t n);
bool byte_move(void *dst, size_t capacity, const void *src, size_t n);
```

Implement the API in `starter.c`. The reference lives in `implementation.c`; the harness includes the selected source through `DSA_IMPLEMENTATION`.

Run from this directory:

```sh
gcc -std=c17 -Wall -Wextra -Wpedantic tests/test.c -o /tmp/systems-memory_copy_move
/tmp/systems-memory_copy_move
```
