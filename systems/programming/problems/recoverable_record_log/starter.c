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

uint32_t log_crc32(const void *data, size_t length) {
  (void)data;
  (void)length; /* TODO */
  return 0;
}
bool log_append(unsigned char *buffer, size_t capacity, size_t *used,
                const void *payload, size_t length) {
  (void)buffer;
  (void)capacity;
  (void)used;
  (void)payload;
  (void)length; /* TODO */
  return false;
}
LogRecovery log_recover(const unsigned char *buffer, size_t length) {
  (void)buffer;
  (void)length; /* TODO */
  return (LogRecovery){LOG_INVALID, 0, 0};
}
