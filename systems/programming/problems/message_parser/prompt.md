# Message Parser

Decode a framed byte stream across partial inputs with bounded lengths.

## Contract

Wire format: 2-byte unsigned big-endian payload length, 1-byte type, then payload (0..64 bytes). Known types are 1 and 2; skip unknown types after consuming their complete payload. parser_feed accepts arbitrary chunks, including multiple messages, and emits known messages through a synchronous callback. Callback payload is borrowed and valid only during the call; copy it to retain it. Length > 64 poisons the parser until parser_init. Return false for malformed length, invalid pointers, or recursive feed; invalid arguments do not poison it. A malformed frame stops processing the rest of that chunk; earlier valid frames may already have been emitted. parser_finish is true only at a clean frame boundary and false for truncated or poisoned streams. Empty payloads are valid. Single-threaded; do not reset/destroy the parser from its callback.

## API

```c
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
typedef void (*MessageCallback)(void *, uint8_t, const unsigned char *, size_t);
typedef struct { unsigned char header[3], payload[64]; size_t header_used, used, length; bool failed, feeding; MessageCallback callback; void *context; } MessageParser;
bool parser_init(MessageParser *p, MessageCallback callback, void *context);
bool parser_feed(MessageParser *p, const unsigned char *data, size_t n);
bool parser_finish(const MessageParser *p);
```

Implement the API in `starter.c`. The reference lives in `implementation.c`; the harness includes the selected source through `DSA_IMPLEMENTATION`.

Run from this directory:

```sh
gcc -std=c17 -Wall -Wextra -Wpedantic tests/test.c -o /tmp/systems-message_parser
/tmp/systems-message_parser
```
