# Bit Utilities

Implement fixed-width bit operations with checked positions and fields.

## Contract

Implement bit_change(value, bit, op, out): op 0 clears, 1 sets, 2 toggles. bit_test reads a bit. extract_field/insert_field use a least-significant-bit offset and a width in 1..32; offset + width must not exceed 32. Reject fields that do not fit and invalid pointers/operations without changing output. count_bits returns the population count. All values are uint32_t; avoid shifts by 32. No allocation.

## API

```c
#include <stdint.h>
#include <stdbool.h>
bool bit_change(uint32_t value, unsigned bit, unsigned op, uint32_t *out);
bool bit_test(uint32_t value, unsigned bit, bool *out);
bool extract_field(uint32_t value, unsigned offset, unsigned width, uint32_t *out);
bool insert_field(uint32_t value, unsigned offset, unsigned width, uint32_t field, uint32_t *out);
unsigned count_bits(uint32_t value);
```

Implement the API in `starter.c`. The reference lives in `implementation.c`; the harness includes the selected source through `DSA_IMPLEMENTATION`.

Run from this directory:

```sh
gcc -std=c17 -Wall -Wextra -Wpedantic tests/test.c -o /tmp/systems-base
/tmp/systems-base
```
