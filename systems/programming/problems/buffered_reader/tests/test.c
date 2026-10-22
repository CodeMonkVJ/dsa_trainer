#include <limits.h>
#include <stdio.h>
#include <string.h>
#ifndef DSA_IMPLEMENTATION
#define DSA_IMPLEMENTATION "../implementation.c"
#endif
#include DSA_IMPLEMENTATION
static int passed, total;
#define CHECK(expr)                                                            \
  do {                                                                         \
    bool ok_ = !!(expr);                                                       \
    ++total;                                                                   \
    passed += ok_;                                                             \
    printf("DSA_CASE "                                                         \
           "{\"input\":%d,\"expected\":true,\"actual\":%s,\"passed\":%s}\n",   \
           __LINE__, ok_ ? "true" : "false", ok_ ? "true" : "false");          \
    if (!ok_)                                                                  \
      fprintf(stderr, "FAIL line %d: %s\n", __LINE__, #expr);                  \
  } while (0)
typedef struct {
  const char *s;
  size_t pos, n;
  int calls, fail_at;
} Source;
static int source(void *ctx, unsigned char b[4]) {
  Source *s = ctx;
  ++s->calls;
  if (s->fail_at && s->calls >= s->fail_at)
    return -1;
  size_t n = s->n - s->pos;
  if (n > 4)
    n = 4;
  memcpy(b, s->s + s->pos, n);
  s->pos += n;
  return (int)n;
}
static int short_source(void *ctx, unsigned char b[4]) {
  Source *s = ctx;
  ++s->calls;
  if (s->pos == s->n)
    return 0;
  b[0] = (unsigned char)s->s[s->pos++];
  return 1;
}
int main(void) {
  Source s = {"abcdefghij", 0, 10, 0, 0};
  Reader r;
  unsigned char b[20] = {0};
  CHECK(reader_init(&r, source, &s) && reader_read(&r, b, 1) == 1 &&
        b[0] == 'a' && s.calls == 1);
  CHECK(reader_read(&r, b, 2) == 2 && memcmp(b, "bc", 2) == 0 && s.calls == 1);
  CHECK(reader_read(&r, b, 20) == 7 && memcmp(b, "defghij", 7) == 0);
  int calls = s.calls;
  CHECK(reader_read(&r, b, 1) == 0 && s.calls == calls);
  CHECK(reader_read(&r, NULL, 0) == 0 && !reader_init(&r, NULL, &s));
  s = (Source){"abcde", 0, 5, 0, 2};
  reader_init(&r, source, &s);
  CHECK(reader_read(&r, b, 8) == 4 && memcmp(b, "abcd", 4) == 0);
  CHECK(reader_read(&r, b, 1) == -1 && reader_read(&r, NULL, 0) == 0);
  CHECK(reader_read(&r, NULL, 1) == -1 && reader_read(NULL, b, 1) == -1);
  s = (Source){"abcde", 0, 5, 0, 0};
  reader_init(&r, short_source, &s);
  CHECK(reader_read(&r, b, 10) == 5 && memcmp(b, "abcde", 5) == 0 &&
        s.calls == 6);
  s = (Source){"abcde", 0, 5, 0, 0};
  reader_init(&r, source, &s);
  CHECK(reader_read(&r, NULL, 0) == 0 && s.calls == 0);
  CHECK(reader_read(&r, b, (size_t)PTRDIFF_MAX + 1) == -1 && s.calls == 0);
  CHECK(reader_read(&r, b, 1) == 1 && b[0] == 'a');
  CHECK(reader_read(&r, NULL, 1) == -1 && s.calls == 1);
  CHECK(reader_read(&r, b, 3) == 3 && memcmp(b, "bcd", 3) == 0 && s.calls == 1);
  s = (Source){"", 0, 0, 0, 0};
  reader_init(&r, source, &s);
  b[0] = 77;
  CHECK(reader_read(&r, b, 1) == 0 && b[0] == 77 && s.calls == 1);
  CHECK(reader_read(&r, b, 1) == 0 && s.calls == 1);
  s = (Source){"abcd", 0, 4, 0, 1};
  reader_init(&r, source, &s);
  CHECK(reader_read(&r, b, 1) == -1 && s.calls == 1);
  CHECK(reader_read(&r, b, 1) == -1 && s.calls == 1 && b[0] == 77);
  printf("DSA_RESULT {\"passed\":%d,\"total\":%d}\n", passed, total);
  return passed == total ? 0 : 1;
}
