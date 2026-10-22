#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
typedef int (*BlockRead)(void *context, unsigned char block[4]);
typedef struct {
  BlockRead source;
  void *context;
  unsigned char block[4];
  size_t pos, end;
  bool eof, failed;
} Reader;
bool reader_init(Reader *r, BlockRead source, void *context);
ptrdiff_t reader_read(Reader *r, unsigned char *dst, size_t n);

bool reader_init(Reader *r, BlockRead source, void *context) { /* TODO */
  return 0;
}
ptrdiff_t reader_read(Reader *r, unsigned char *dst, size_t n) { /* TODO */
  return -1;
}
