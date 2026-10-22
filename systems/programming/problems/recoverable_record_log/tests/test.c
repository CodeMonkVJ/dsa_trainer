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

int main(void) {
  CHECK("standard CRC check vector",
        log_crc32("123456789", 9) == UINT32_C(0xcbf43926));
  CHECK("empty CRC", log_crc32(NULL, 0) == 0);
  unsigned char buffer[700], snapshot[700];
  memset(buffer, 0xa5, sizeof buffer);
  size_t used = 0;
  CHECK("empty log clean", log_recover(NULL, 0).status == LOG_CLEAN &&
                               log_recover(buffer, 0).records == 0);
  CHECK("invalid pointer rejected", log_recover(NULL, 1).status == LOG_INVALID);
  REQUIRE(log_append(buffer, sizeof buffer, &used, "abc", 3));
  size_t first = used;
  const unsigned char golden[] = {'I',  'L',  'O',  'G',  3,   0,   0,  0,
                                  0x33, 0x5d, 0xe1, 0x66, 'a', 'b', 'c'};
  CHECK("record matches independent CRC/byte-order golden vector",
        memcmp(buffer, golden, sizeof golden) == 0);
  CHECK("independent golden record decodes",
        log_recover(golden, sizeof golden).status == LOG_CLEAN &&
            log_recover(golden, sizeof golden).records == 1);
  CHECK("header has explicit little-endian length",
        first == 15 && memcmp(buffer, "ILOG", 4) == 0 && buffer[4] == 3 &&
            buffer[5] == 0 && buffer[6] == 0 && buffer[7] == 0);
  unsigned char binary[256];
  for (unsigned i = 0; i < 256; ++i)
    binary[i] = (unsigned char)i;
  REQUIRE(log_append(buffer, sizeof buffer, &used, binary, sizeof binary));
  size_t second = used;
  REQUIRE(log_append(buffer, sizeof buffer, &used, NULL, 0));
  LogRecovery recovered = log_recover(buffer, used);
  CHECK("all records including empty payload recovered",
        recovered.status == LOG_CLEAN && recovered.valid_bytes == used &&
            recovered.records == 3);
  bool cuts = true;
  for (size_t n = 0; n <= used; ++n) {
    LogRecovery q = log_recover(buffer, n);
    size_t expected = n >= used     ? used
                      : n >= second ? second
                      : n >= first  ? first
                                    : 0;
    size_t count = n >= used ? 3 : n >= second ? 2 : n >= first ? 1 : 0;
    bool boundary = n == 0 || n == first || n == second || n == used;
    cuts = cuts && q.valid_bytes == expected && q.records == count &&
           q.status == (boundary ? LOG_CLEAN : LOG_TRUNCATED);
  }
  CHECK("every interrupted byte prefix has the right recovery boundary", cuts);
  memcpy(snapshot, buffer, sizeof buffer);
  size_t old = used;
  CHECK("insufficient append capacity preserves whole buffer",
        !log_append(buffer, used + 12, &used, "xx", 2) && used == old &&
            memcmp(buffer, snapshot, sizeof buffer) == 0);
  CHECK("oversized payload preserves whole buffer",
        !log_append(buffer, sizeof buffer, &used, binary, 257) && used == old &&
            memcmp(buffer, snapshot, sizeof buffer) == 0);
  CHECK("null nonempty payload rejected",
        !log_append(buffer, sizeof buffer, &used, NULL, 1) && used == old);
  CHECK("invalid append pointers rejected",
        !log_append(NULL, 10, &used, "a", 1) &&
            !log_append(buffer, 10, NULL, "a", 1));
  size_t invalid = sizeof buffer + 1;
  CHECK("invalid used value rejected",
        !log_append(buffer, sizeof buffer, &invalid, "a", 1) &&
            invalid == sizeof buffer + 1);
  unsigned char damaged[700];
  memcpy(damaged, buffer, sizeof buffer);
  damaged[first + 12] ^= 0x80;
  recovered = log_recover(damaged, used);
  CHECK("payload checksum mismatch stops at prior record",
        recovered.status == LOG_CORRUPT && recovered.valid_bytes == first &&
            recovered.records == 1);
  memcpy(damaged, buffer, sizeof buffer);
  damaged[first] = 'X';
  recovered = log_recover(damaged, used);
  CHECK("bad magic never resynchronizes to later records",
        recovered.status == LOG_CORRUPT && recovered.valid_bytes == first &&
            recovered.records == 1);
  memcpy(damaged, buffer, sizeof buffer);
  damaged[first + 4] = 1;
  damaged[first + 5] = 1;
  recovered = log_recover(damaged, first + 12);
  CHECK("oversized length is corrupt even with missing payload",
        recovered.status == LOG_CORRUPT && recovered.valid_bytes == first);
  memcpy(damaged, buffer, sizeof buffer);
  damaged[4] = 2;
  recovered = log_recover(damaged, used);
  CHECK("length bytes are checksum-protected",
        recovered.status == LOG_CORRUPT && recovered.valid_bytes == 0);
  unsigned char exact[12];
  size_t zero = 0;
  CHECK("zero payload fits exact header capacity",
        log_append(exact, sizeof exact, &zero, NULL, 0) && zero == 12 &&
            log_recover(exact, 12).records == 1);
  unsigned char unaligned[701];
  memcpy(unaligned + 1, buffer, used);
  CHECK("unaligned input safely decoded",
        log_recover(unaligned + 1, used).status == LOG_CLEAN);
  return finish();
}
