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
  int calls;
  size_t n;
  unsigned char bytes[64];
  uint8_t type;
} Capture;
static void capture(void *ctx, uint8_t type, const unsigned char *data,
                    size_t n) {
  Capture *c = ctx;
  ++c->calls;
  c->n = n;
  c->type = type;
  memcpy(c->bytes, data, n);
}
int main(void) {
  MessageParser p;
  Capture c = {0};
  CHECK(parser_init(&p, capture, &c) && parser_finish(&p));
  unsigned char stream[] = {0, 3, 1, 'a', 0, 'c', 0, 1, 99, 42, 0, 0, 2};
  for (size_t split = 0; split <= sizeof stream; ++split) {
    parser_init(&p, capture, &c);
    c.calls = 0;
    CHECK(parser_feed(&p, stream, split) &&
          parser_feed(&p, stream + split, sizeof stream - split) &&
          parser_finish(&p) && c.calls == 2);
  }
  parser_init(&p, capture, &c);
  c.calls = 0;
  for (size_t i = 0; i < sizeof stream; ++i)
    CHECK(parser_feed(&p, stream + i, 1));
  CHECK(c.calls == 2 && c.type == 2 && c.n == 0 && parser_finish(&p));
  parser_init(&p, capture, &c);
  c.calls = 0;
  CHECK(parser_feed(&p, stream, sizeof stream) && c.calls == 2);
  unsigned char large[] = {1, 0, 1};
  CHECK(!parser_feed(&p, large, 3) && !parser_finish(&p) &&
        !parser_feed(&p, NULL, 0));
  parser_init(&p, capture, &c);
  CHECK(parser_feed(&p, stream, 4) && !parser_finish(&p));
  CHECK(!parser_feed(&p, NULL, 1) && parser_feed(&p, stream + 4, 2) &&
        parser_finish(&p));
  unsigned char maxframe[67] = {0, 64, 1};
  CHECK(parser_feed(&p, maxframe, sizeof maxframe) && c.n == 64);
  CHECK(!parser_init(&p, NULL, NULL) && !parser_feed(NULL, stream, 1));
  parser_init(&p, capture, &c);
  c.calls = 0;
  const unsigned char binary[] = {0, 3, 1, 'a', 0, 255};
  CHECK(parser_feed(&p, binary, sizeof binary) && c.calls == 1 && c.type == 1 &&
        c.n == 3 && memcmp(c.bytes, binary + 3, 3) == 0);
  for (size_t prefix = 1; prefix < sizeof binary; ++prefix) {
    parser_init(&p, capture, &c);
    c.calls = 0;
    CHECK(parser_feed(&p, binary, prefix) && !parser_finish(&p) &&
          c.calls == 0);
  }
  parser_init(&p, capture, &c);
  c.calls = 0;
  const unsigned char too_long[] = {0, 65, 1};
  CHECK(!parser_feed(&p, too_long, sizeof too_long) && c.calls == 0 &&
        !parser_finish(&p));
  CHECK(!parser_feed(&p, binary, sizeof binary) && c.calls == 0);
  parser_init(&p, capture, &c);
  CHECK(parser_feed(&p, NULL, 0) && parser_finish(&p));
  CHECK(!parser_feed(&p, NULL, 1) && parser_finish(&p));
  CHECK(parser_feed(&p, binary, sizeof binary) && c.calls == 1);
  parser_init(&p, capture, &c);
  c.calls = 0;
  const unsigned char unknown[] = {0, 2, 99, 1, 2};
  CHECK(parser_feed(&p, unknown, sizeof unknown) && c.calls == 0 &&
        parser_finish(&p));
  printf("DSA_RESULT {\"passed\":%d,\"total\":%d}\n", passed, total);
  return passed == total ? 0 : 1;
}
