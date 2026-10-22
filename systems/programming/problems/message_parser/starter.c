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

bool parser_init(MessageParser *p, MessageCallback callback,
                 void *context) { /* TODO */
  return 0;
}
bool parser_feed(MessageParser *p, const unsigned char *data,
                 size_t n) { /* TODO */
  return 0;
}
bool parser_finish(const MessageParser *p) { /* TODO */ return 0; }
