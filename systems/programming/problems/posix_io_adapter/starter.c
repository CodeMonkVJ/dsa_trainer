#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <sys/types.h>
typedef enum { IO_OK, IO_EOF, IO_TIMEOUT, IO_ERROR, IO_INVALID } IoStatus;
typedef struct {
  IoStatus status;
  size_t transferred;
  int error;
} IoResult;
typedef struct {
  void *context;
  ssize_t (*read_some)(void *, void *, size_t);
  ssize_t (*write_some)(void *, const void *, size_t);
  int (*wait_ready)(void *, bool, int64_t);
  int64_t (*now_ms)(void *);
} IoOps;
IoResult io_read_exact(const IoOps *ops, void *buffer, size_t length,
                       int64_t deadline_ms);
IoResult io_write_all(const IoOps *ops, const void *buffer, size_t length,
                      int64_t deadline_ms);

IoResult io_read_exact(const IoOps *ops, void *buffer, size_t length,
                       int64_t deadline_ms) {
  (void)ops;
  (void)buffer;
  (void)length;
  (void)deadline_ms; /* TODO */
  return (IoResult){IO_INVALID, 0, 0};
}
IoResult io_write_all(const IoOps *ops, const void *buffer, size_t length,
                      int64_t deadline_ms) {
  (void)ops;
  (void)buffer;
  (void)length;
  (void)deadline_ms; /* TODO */
  return (IoResult){IO_INVALID, 0, 0};
}
