# Buffered Reader

Adapt block reads to arbitrary byte reads while retaining leftovers.

## Contract

reader_init installs a source callback that receives a 4-byte buffer and returns 0..4 bytes, or -1 on error. A short positive read is not EOF; only 0 is EOF. reader_read returns bytes copied, or -1 if an error occurs before any byte is copied. On an error after partial progress return that progress; the next nonzero read returns -1. EOF and source errors are sticky; zero-byte reads return 0 without invoking the source. Never drop leftovers. Invalid arguments return -1 without changing reader state. Requests greater than PTRDIFF_MAX are rejected. Reader and source context must remain alive throughout use. Single-threaded.

## API

```c
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
typedef int (*BlockRead)(void *context, unsigned char block[4]);
typedef struct { BlockRead source; void *context; unsigned char block[4]; size_t pos, end; bool eof, failed; } Reader;
bool reader_init(Reader *r, BlockRead source, void *context);
ptrdiff_t reader_read(Reader *r, unsigned char *dst, size_t n);
```

Implement the API in `starter.c`. The reference lives in `implementation.c`; the harness includes the selected source through `DSA_IMPLEMENTATION`.

Run from this directory:

```sh
gcc -std=c17 -Wall -Wextra -Wpedantic tests/test.c -o /tmp/systems-buffered_reader
/tmp/systems-buffered_reader
```
