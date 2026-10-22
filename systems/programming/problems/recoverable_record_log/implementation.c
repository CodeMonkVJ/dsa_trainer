#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
typedef enum { LOG_CLEAN, LOG_TRUNCATED, LOG_CORRUPT, LOG_INVALID } LogStatus;
typedef struct {
  LogStatus status;
  size_t valid_bytes, records;
} LogRecovery;
uint32_t log_crc32(const void *data, size_t length);
bool log_append(unsigned char *buffer, size_t capacity, size_t *used,
                const void *payload, size_t length);
LogRecovery log_recover(const unsigned char *buffer, size_t length);

#include <string.h>
static uint32_t log_crc_update(uint32_t crc, const unsigned char *p, size_t n) {
  for (size_t i = 0; i < n; ++i) {
    crc ^= p[i];
    for (unsigned bit = 0; bit < 8; ++bit)
      crc = (crc >> 1) ^ ((crc & 1) ? UINT32_C(0xedb88320) : 0);
  }
  return crc;
}
uint32_t log_crc32(const void *data, size_t n) {
  return log_crc_update(UINT32_MAX, data, n) ^ UINT32_MAX;
}
static void log_put32(unsigned char *p, uint32_t v) {
  for (unsigned i = 0; i < 4; ++i)
    p[i] = (unsigned char)(v >> (8 * i));
}
static uint32_t log_get32(const unsigned char *p) {
  uint32_t v = 0;
  for (unsigned i = 0; i < 4; ++i)
    v |= (uint32_t)p[i] << (8 * i);
  return v;
}
bool log_append(unsigned char *b, size_t cap, size_t *used, const void *payload,
                size_t n) {
  if (!b || !used || *used > cap || n > 256 || (!payload && n) ||
      cap - *used < 12 || n > cap - *used - 12)
    return false;
  unsigned char encoded[4];
  log_put32(encoded, (uint32_t)n);
  uint32_t crc = log_crc_update(UINT32_MAX, encoded, 4);
  crc = log_crc_update(crc, payload, n) ^ UINT32_MAX;
  unsigned char *p = b + *used;
  memcpy(p, "ILOG", 4);
  memcpy(p + 4, encoded, 4);
  log_put32(p + 8, crc);
  if (n)
    memcpy(p + 12, payload, n);
  *used += 12 + n;
  return true;
}
LogRecovery log_recover(const unsigned char *b, size_t n) {
  if (!b && n)
    return (LogRecovery){LOG_INVALID, 0, 0};
  size_t offset = 0, records = 0;
  while (offset < n) {
    if (n - offset < 12)
      return (LogRecovery){LOG_TRUNCATED, offset, records};
    const unsigned char *p = b + offset;
    uint32_t length = log_get32(p + 4);
    if (memcmp(p, "ILOG", 4) || length > 256)
      return (LogRecovery){LOG_CORRUPT, offset, records};
    if (length > n - offset - 12)
      return (LogRecovery){LOG_TRUNCATED, offset, records};
    uint32_t crc = log_crc_update(UINT32_MAX, p + 4, 4);
    crc = log_crc_update(crc, p + 12, length) ^ UINT32_MAX;
    if (crc != log_get32(p + 8))
      return (LogRecovery){LOG_CORRUPT, offset, records};
    offset += 12 + length;
    ++records;
  }
  return (LogRecovery){LOG_CLEAN, offset, records};
}
