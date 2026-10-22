# Hexadecimal Parser

Parse bounded hexadecimal text with explicit error results.

## Contract

parse_hex(text, length, out) parses a uint32_t from exactly length bytes. Accept optional 0x/0X and upper/lowercase hex; reject empty input, bare prefix, signs, whitespace, embedded NULs and trailing junk. Never read past length. HEX_INVALID covers invalid pointers and characters; HEX_OVERFLOW covers numeric overflow. Process left-to-right and return the first error encountered; output changes only on success. Leading zeros are allowed.

## API

```c
#include <stdint.h>
#include <stddef.h>
typedef enum { HEX_OK, HEX_INVALID, HEX_OVERFLOW } HexResult;
HexResult parse_hex(const char *text, size_t length, uint32_t *out);
```

Implement the API in `starter.c`. The reference lives in `implementation.c`; the harness includes the selected source through `DSA_IMPLEMENTATION`.

Run from this directory:

```sh
gcc -std=c17 -Wall -Wextra -Wpedantic tests/test.c -o /tmp/systems-hexadecimal_parser
/tmp/systems-hexadecimal_parser
```
