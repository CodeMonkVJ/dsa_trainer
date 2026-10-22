#define _POSIX_C_SOURCE 200809L
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef DSA_IMPLEMENTATION
#define DSA_IMPLEMENTATION "../implementation.c"
#endif
#include DSA_IMPLEMENTATION
static unsigned passed, total;
static void check(const char *name, bool ok) {
  ++total;
  if (ok)
    ++passed;
  printf("DSA_CASE "
         "{\"input\":\"%s\",\"expected\":true,\"actual\":%s,\"passed\":%s}\n",
         name, ok ? "true" : "false", ok ? "true" : "false");
  if (!ok)
    fprintf(stderr, "FAIL: %s\n", name);
}
#define CHECK(name, expr) check(name, !!(expr))
static int finish(void) {
  printf("DSA_RESULT {\"passed\":%u,\"total\":%u}\n", passed, total);
  return total && passed == total ? 0 : 1;
}
#define REQUIRE(expr)                                                          \
  do {                                                                         \
    if (!(expr)) {                                                             \
      CHECK("test setup or prerequisite failed", false);                       \
      exit(finish());                                                          \
    }                                                                          \
  } while (0)

#include <errno.h>
#include <fcntl.h>
#include <poll.h>
#include <unistd.h>
typedef struct {
  ssize_t result;
  int error;
} TransferStep;
typedef struct {
  int result, error;
} WaitStep;
typedef struct {
  TransferStep transfers[12];
  size_t transfer_count, at;
  WaitStep waits[12];
  size_t wait_count, wait_at;
  unsigned char data[32];
  size_t offset;
  int calls, clock_calls;
  int64_t time, last_deadline;
  bool wrote, advance_clock;
} Script;
static ssize_t script_transfer(Script *s, void *read_buffer,
                               const void *write_buffer, size_t n) {
  ++s->calls;
  if (s->at >= s->transfer_count) {
    errno = EIO;
    return -1;
  }
  TransferStep step = s->transfers[s->at++];
  errno = step.error;
  if (step.result > 0 && (size_t)step.result <= n &&
      s->offset + (size_t)step.result <= sizeof s->data) {
    if (write_buffer)
      memcpy(s->data + s->offset, write_buffer, (size_t)step.result);
    else
      memcpy(read_buffer, s->data + s->offset, (size_t)step.result);
    s->offset += (size_t)step.result;
  }
  return step.result;
}
static ssize_t script_read(void *ctx, void *b, size_t n) {
  return script_transfer(ctx, b, NULL, n);
}
static ssize_t script_write(void *ctx, const void *b, size_t n) {
  return script_transfer(ctx, NULL, b, n);
}
static int script_wait(void *ctx, bool writing, int64_t deadline) {
  Script *s = ctx;
  s->wrote = writing;
  s->last_deadline = deadline;
  if (s->wait_at >= s->wait_count) {
    errno = EIO;
    return -1;
  }
  WaitStep step = s->waits[s->wait_at++];
  errno = step.error;
  return step.result;
}
static int64_t script_now(void *ctx) {
  Script *s = ctx;
  ++s->clock_calls;
  int64_t t = s->time;
  if (s->advance_clock)
    ++s->time;
  return t;
}
static IoOps script_ops(Script *s) {
  return (IoOps){s, script_read, script_write, script_wait, script_now};
}
typedef struct {
  int fd;
  int64_t now;
} PipeContext;
static ssize_t pipe_read(void *ctx, void *b, size_t n) {
  return read(((PipeContext *)ctx)->fd, b, n);
}
static ssize_t pipe_write(void *ctx, const void *b, size_t n) {
  return write(((PipeContext *)ctx)->fd, b, n);
}
static int pipe_wait(void *ctx, bool writing, int64_t deadline) {
  PipeContext *p = ctx;
  struct pollfd fd = {p->fd, writing ? POLLOUT : POLLIN, 0};
  int64_t left = deadline - p->now;
  return poll(&fd, 1, left > 0 ? (int)left : 0);
}
static int64_t pipe_now(void *ctx) { return ((PipeContext *)ctx)->now; }
int main(void) {
  unsigned char buffer[16] = {0};
  IoResult result;
  Script s = {.transfers = {{2, 0}, {-1, EINTR}, {1, 0}, {2, 0}},
              .transfer_count = 4};
  memcpy(s.data, "abcde", 5);
  IoOps ops = script_ops(&s);
  result = io_read_exact(&ops, buffer, 5, 100);
  CHECK("short reads and interruption preserve progress",
        result.status == IO_OK && result.transferred == 5 &&
            result.error == 0 && memcmp(buffer, "abcde", 5) == 0);
  s = (Script){.transfers = {{1, 0}, {0, 0}}, .transfer_count = 2};
  s.data[0] = 'x';
  ops = script_ops(&s);
  result = io_read_exact(&ops, buffer, 4, 100);
  CHECK("partial EOF is explicit", result.status == IO_EOF &&
                                       result.transferred == 1 &&
                                       result.error == 0 && buffer[0] == 'x');
  s = (Script){.transfers = {{2, 0}, {-1, EAGAIN}, {-1, EWOULDBLOCK}, {2, 0}},
               .transfer_count = 4,
               .waits = {{-1, EINTR}, {1, 0}, {1, 0}},
               .wait_count = 3};
  ops = script_ops(&s);
  result = io_write_all(&ops, "abcd", 4, 100);
  CHECK("write retries wait interruptions and repeated would-block",
        result.status == IO_OK && result.transferred == 4 &&
            memcmp(s.data, "abcd", 4) == 0 && s.wait_at == 3 && s.wrote &&
            s.last_deadline == 100);
  s = (Script){.transfers = {{2, 0}, {-1, EAGAIN}},
               .transfer_count = 2,
               .waits = {{0, 0}},
               .wait_count = 1};
  ops = script_ops(&s);
  result = io_write_all(&ops, "abcd", 4, 100);
  CHECK("timeout retains partial output",
        result.status == IO_TIMEOUT && result.transferred == 2 &&
            result.error == 0 && memcmp(s.data, "ab", 2) == 0);
  s = (Script){.transfers = {{1, 0}, {-1, EPIPE}}, .transfer_count = 2};
  ops = script_ops(&s);
  result = io_write_all(&ops, "abc", 3, 100);
  CHECK("fatal errno and partial bytes retained", result.status == IO_ERROR &&
                                                      result.transferred == 1 &&
                                                      result.error == EPIPE);
  s = (Script){.transfers = {{0, 0}}, .transfer_count = 1};
  ops = script_ops(&s);
  result = io_write_all(&ops, "a", 1, 100);
  CHECK("zero write cannot spin",
        result.status == IO_ERROR && result.error == EIO && s.calls == 1);
  s = (Script){.transfers = {{5, 0}}, .transfer_count = 1};
  ops = script_ops(&s);
  result = io_read_exact(&ops, buffer, 1, 100);
  CHECK("impossible transfer count rejected", result.status == IO_ERROR &&
                                                  result.transferred == 0 &&
                                                  result.error == EIO);
  s = (Script){
      .transfers = {{-1, EINTR}, {-1, EINTR}, {-1, EINTR}, {-1, EINTR}},
      .transfer_count = 4,
      .advance_clock = true};
  ops = script_ops(&s);
  result = io_read_exact(&ops, buffer, 1, 3);
  CHECK("interruptions cannot extend absolute deadline",
        result.status == IO_TIMEOUT && s.calls == 3 && result.transferred == 0);
  s = (Script){.transfers = {{-1, EAGAIN}},
               .transfer_count = 1,
               .waits = {{-1, EBADF}},
               .wait_count = 1};
  ops = script_ops(&s);
  result = io_read_exact(&ops, buffer, 1, 100);
  CHECK("wait error preserved",
        result.status == IO_ERROR && result.error == EBADF);
  s = (Script){.transfers = {{-1, EAGAIN}},
               .transfer_count = 1,
               .waits = {{2, 0}},
               .wait_count = 1};
  ops = script_ops(&s);
  result = io_read_exact(&ops, buffer, 1, 100);
  CHECK("invalid readiness result rejected",
        result.status == IO_ERROR && result.error == EIO);
  s = (Script){.transfers = {{-1, 0}}, .transfer_count = 1};
  ops = script_ops(&s);
  result = io_read_exact(&ops, buffer, 1, 100);
  CHECK("missing error code normalized",
        result.status == IO_ERROR && result.error == EIO);
  s = (Script){.time = -1};
  ops = script_ops(&s);
  result = io_read_exact(&ops, buffer, 1, 100);
  CHECK("clock failure stops before I/O",
        result.status == IO_ERROR && result.error == EIO && s.calls == 0);
  s = (Script){0};
  ops = script_ops(&s);
  result = io_read_exact(&ops, NULL, 0, 0);
  CHECK("zero length needs no calls", result.status == IO_OK &&
                                          result.transferred == 0 &&
                                          s.clock_calls == 0 && s.calls == 0);
  CHECK("invalid arguments do not invoke callbacks",
        io_read_exact(NULL, buffer, 1, 100).status == IO_INVALID &&
            io_read_exact(&ops, NULL, 1, 100).status == IO_INVALID &&
            io_write_all(&ops, "a", (size_t)PTRDIFF_MAX + 1, 100).status ==
                IO_INVALID &&
            io_read_exact(&ops, buffer, 1, -1).status == IO_INVALID &&
            s.clock_calls == 0);
  ops.read_some = NULL;
  CHECK("required read callback validated",
        io_read_exact(&ops, buffer, 1, 100).status == IO_INVALID);
  ops = script_ops(&s);
  ops.write_some = NULL;
  CHECK("unused callback may be absent",
        io_read_exact(&ops, NULL, 0, 0).status == IO_OK);
  s.time = 100;
  result = io_read_exact(&ops, buffer, 1, 100);
  CHECK("deadline boundary is timeout",
        result.status == IO_TIMEOUT && s.calls == 0);
  s = (Script){.transfers = {{-1, EAGAIN}, {3, 0}},
               .transfer_count = 2,
               .waits = {{1, 0}},
               .wait_count = 1};
  memcpy(s.data, "xyz", 3);
  ops = script_ops(&s);
  result = io_read_exact(&ops, buffer, 3, 100);
  CHECK("read readiness uses the read direction",
        result.status == IO_OK && result.transferred == 3 && !s.wrote &&
            s.wait_at == 1 && memcmp(buffer, "xyz", 3) == 0);
  s = (Script){.transfers = {{1, 0}, {-1, EACCES}}, .transfer_count = 2};
  s.data[0] = 'q';
  ops = script_ops(&s);
  result = io_read_exact(&ops, buffer, 2, 100);
  CHECK("partial read error retains errno and bytes",
        result.status == IO_ERROR && result.error == EACCES &&
            result.transferred == 1 && buffer[0] == 'q');
  s = (Script){.transfers = {{-2, EINTR}}, .transfer_count = 1};
  ops = script_ops(&s);
  result = io_read_exact(&ops, buffer, 1, 100);
  CHECK("invalid negative transfer is not retried",
        result.status == IO_ERROR && result.error == EIO && s.calls == 1);
  s = (Script){.transfers = {{-1, EAGAIN}},
               .transfer_count = 1,
               .waits = {{-1, EINTR}, {1, 0}},
               .wait_count = 2,
               .advance_clock = true};
  ops = script_ops(&s);
  result = io_read_exact(&ops, buffer, 1, 3);
  CHECK("wait interruption retains original deadline",
        result.status == IO_TIMEOUT && s.calls == 1 && s.wait_at == 2 &&
            s.last_deadline == 3);
  ops = script_ops(&s);
  ops.wait_ready = NULL;
  CHECK("missing readiness callback rejected",
        io_read_exact(&ops, buffer, 1, 100).status == IO_INVALID);
  ops = script_ops(&s);
  ops.now_ms = NULL;
  CHECK("missing clock callback rejected",
        io_write_all(&ops, "a", 1, 100).status == IO_INVALID);
  ops = script_ops(&s);
  ops.write_some = NULL;
  CHECK("missing write callback rejected",
        io_write_all(&ops, "a", 1, 100).status == IO_INVALID);
  int fds[2];
  REQUIRE(pipe(fds) == 0);
  REQUIRE(fcntl(fds[0], F_SETFL, O_NONBLOCK) == 0 &&
          fcntl(fds[1], F_SETFL, O_NONBLOCK) == 0);
  PipeContext pc = {fds[1], 0};
  IoOps real = {&pc, pipe_read, pipe_write, pipe_wait, pipe_now};
  result = io_write_all(&real, "pipe", 4, 100);
  CHECK("actual nonblocking pipe write",
        result.status == IO_OK && result.transferred == 4);
  REQUIRE(close(fds[1]) == 0);
  pc.fd = fds[0];
  result = io_read_exact(&real, buffer, 5, 100);
  CHECK("actual pipe partial read then EOF",
        result.status == IO_EOF && result.transferred == 4 &&
            memcmp(buffer, "pipe", 4) == 0);
  REQUIRE(close(fds[0]) == 0);
  return finish();
}
