#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
typedef void (*MessageCallback)(void *, uint8_t, const unsigned char *, size_t);
typedef struct {
  unsigned char header[3], payload[64];
  size_t header_used, used, length;
  bool failed, feeding;
  MessageCallback callback;
  void *context;
} MessageParser;
bool parser_init(MessageParser *p, MessageCallback callback, void *context);
bool parser_feed(MessageParser *p, const unsigned char *data, size_t n);
bool parser_finish(const MessageParser *p);

bool parser_init(MessageParser *p, MessageCallback cb, void *ctx) {
  if (!p || !cb)
    return false;
  *p = (MessageParser){.callback = cb, .context = ctx};
  return true;
}
bool parser_feed(MessageParser *p, const unsigned char *data, size_t n) {
  if (!p || (!data && n) || p->failed || p->feeding)
    return false;
  p->feeding = true;
  for (size_t i = 0; i < n; ++i) {
    if (p->header_used < 3) {
      p->header[p->header_used++] = data[i];
      if (p->header_used == 2) {
        p->length = ((size_t)p->header[0] << 8) | p->header[1];
        if (p->length > 64) {
          p->failed = true;
          p->feeding = false;
          return false;
        }
      }
      if (p->header_used < 3)
        continue;
    } else
      p->payload[p->used++] = data[i];
    if (p->used == p->length) {
      if (p->header[2] == 1 || p->header[2] == 2)
        p->callback(p->context, p->header[2], p->payload, p->length);
      p->header_used = 0;
      p->used = 0;
      p->length = 0;
    }
  }
  p->feeding = false;
  return true;
}
bool parser_finish(const MessageParser *p) {
  return p && !p->failed && !p->feeding && !p->header_used;
}
