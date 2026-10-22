# Checked Arithmetic and Alignment

Compute sizes and aligned offsets without integer overflow or partial output updates.

## Contract

Implement size_add, size_mul and size_align_up over size_t. Return false for a null output, arithmetic overflow, or invalid alignment; leave a non-null output unchanged on every failure. Alignment must be a nonzero power of two. Rounding an already aligned value leaves it unchanged; alignment 1 accepts every value, including SIZE_MAX. Zero arithmetic operands are valid. Never calculate an overflowing intermediate before checking it. Outputs may alias the caller's input variables because inputs are passed by value. No allocation, errno, compiler overflow intrinsics or wider integer types are needed.

## API

```c
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
bool size_add(size_t a, size_t b, size_t *out);
bool size_mul(size_t a, size_t b, size_t *out);
bool size_align_up(size_t value, size_t alignment, size_t *out);
```

Save your implementation in the editor and use **Run tests**. All tests run on the Linux x86 host. No hardware is required.
