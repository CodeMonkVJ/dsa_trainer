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

#include <errno.h>
static IoResult io_result(IoStatus status, size_t done, int error) {
  return (IoResult){status, done, error};
}
static IoResult io_transfer(const IoOps *o, void *buffer, size_t length,
                            int64_t deadline, bool writing) {
  if (!o || !o->now_ms || !o->wait_ready ||
      (writing ? !o->write_some : !o->read_some) || (!buffer && length) ||
      length > PTRDIFF_MAX || deadline < 0)
    return io_result(IO_INVALID, 0, 0);
  size_t done = 0;
  while (done < length) {
    int64_t now = o->now_ms(o->context);
    if (now < 0)
      return io_result(IO_ERROR, done, EIO);
    if (now >= deadline)
      return io_result(IO_TIMEOUT, done, 0);
    errno = 0;
    ssize_t n =
        writing
            ? o->write_some(o->context, (const unsigned char *)buffer + done,
                            length - done)
            : o->read_some(o->context, (unsigned char *)buffer + done,
                           length - done);
    if (n > 0) {
      if ((size_t)n > length - done)
        return io_result(IO_ERROR, done, EIO);
      done += (size_t)n;
      continue;
    }
    if (!n)
      return io_result(writing ? IO_ERROR : IO_EOF, done, writing ? EIO : 0);
    if (n < -1)
      return io_result(IO_ERROR, done, EIO);
    int error = errno;
    if (error == EINTR)
      continue;
    if (error != EAGAIN && error != EWOULDBLOCK)
      return io_result(IO_ERROR, done, error ? error : EIO);
    for (;;) {
      now = o->now_ms(o->context);
      if (now < 0)
        return io_result(IO_ERROR, done, EIO);
      if (now >= deadline)
        return io_result(IO_TIMEOUT, done, 0);
      errno = 0;
      int ready = o->wait_ready(o->context, writing, deadline);
      error = errno;
      if (ready == 1)
        break;
      if (ready == 0)
        return io_result(IO_TIMEOUT, done, 0);
      if (ready == -1 && error == EINTR)
        continue;
      return io_result(IO_ERROR, done, ready == -1 && error ? error : EIO);
    }
  }
  return io_result(IO_OK, done, 0);
}
IoResult io_read_exact(const IoOps *o, void *b, size_t n, int64_t deadline) {
  return io_transfer(o, b, n, deadline, false);
}
IoResult io_write_all(const IoOps *o, const void *b, size_t n,
                      int64_t deadline) {
  return io_transfer(o, (void *)b, n, deadline, true);
}
