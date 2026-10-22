# Recoverable Record Log

Encode bounded checksummed records and recover only the intact prefix of a damaged or truncated log.

## Contract

Implement a bounded byte-buffer record log. Each record is 12 header bytes followed by 0..256 payload bytes. The header contains ASCII ILOG at bytes 0..3, a little-endian uint32 length at 4..7, and little-endian CRC-32 at 8..11. CRC-32/ISO-HDLC uses reflected polynomial 0xEDB88320, initial state 0xFFFFFFFF and final XOR 0xFFFFFFFF. The record checksum covers the four ENCODED length bytes followed by payload, not the magic or checksum itself.

log_crc32 returns the standard CRC of a valid byte range; a null pointer is permitted only for zero length. log_append validates all arguments/space before writing, appends one record, and updates *used only on success. Reject null buffer/used, used > capacity, payload > 256, or null payload with nonzero length; leave the ENTIRE buffer and used unchanged on failure. Caller provides valid, non-overlapping objects; payload and used must not overlap the output buffer.

log_recover scans without modifying input and returns {status, valid_bytes, records}. LOG_CLEAN means an exact record boundary, including an empty buffer. A null pointer is valid only for zero length. LOG_TRUNCATED means fewer than 12 bytes remain for the next header OR a valid full header declares an incomplete payload. LOG_CORRUPT means bad magic, oversized length, or checksum mismatch. LOG_INVALID means nonzero input length with a null pointer. Stop at the FIRST bad/incomplete record, report only the preceding valid prefix, and never search ahead for another magic sequence. A complete header's magic/length errors take precedence over payload truncation. Zero-length records count.

This is record encoding and recovery over a byte snapshot, not a claim that memory writes are atomic or durable. A real file/flash owner must separately handle partial writes, synchronization, truncating the invalid suffix and power-loss behavior. CRC detects accidental corruption, not malicious tampering. No allocation or unaligned integer casts.

## API

```c
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
typedef enum { LOG_CLEAN, LOG_TRUNCATED, LOG_CORRUPT, LOG_INVALID } LogStatus;
typedef struct { LogStatus status; size_t valid_bytes, records; } LogRecovery;
uint32_t log_crc32(const void *data, size_t length);
bool log_append(unsigned char *buffer, size_t capacity, size_t *used, const void *payload, size_t length);
LogRecovery log_recover(const unsigned char *buffer, size_t length);
```

Save your implementation in the editor and use **Run tests**. All tests run on the Linux x86 host. No hardware is required.
