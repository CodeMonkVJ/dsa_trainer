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

bool reader_init(Reader *r, BlockRead source, void *context) {
  if (!r || !source)
    return false;
  *r = (Reader){.source = source, .context = context};
  return true;
}
ptrdiff_t reader_read(Reader *r, unsigned char *dst, size_t n) {
  if (!r || (!dst && n) || n > PTRDIFF_MAX)
    return -1;
  size_t done = 0;
  while (done < n) {
    if (r->pos == r->end) {
      if (r->failed)
        return done ? (ptrdiff_t)done : -1;
      if (r->eof)
        break;
      int got = r->source(r->context, r->block);
      if (got < 0 || got > 4) {
        r->failed = true;
        return done ? (ptrdiff_t)done : -1;
      }
      r->pos = 0;
      r->end = (size_t)got;
      if (!got) {
        r->eof = true;
        break;
      }
    }
    dst[done++] = r->block[r->pos++];
  }
  return (ptrdiff_t)done;
}
