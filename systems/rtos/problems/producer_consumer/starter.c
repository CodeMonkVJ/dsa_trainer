#include "lab.h"
typedef struct {
  unsigned data[4], capacity, head, tail, count;
  bool closed;
  SemaphoreHandle_t mutex, slots, items;
} Stream;
bool stream_init(Stream *s, unsigned capacity);
bool stream_push(Stream *s, unsigned value);
bool stream_pop(Stream *s, unsigned *out);
void stream_close(Stream *s);
void stream_destroy(Stream *s);

bool stream_init(Stream *s, unsigned capacity) {
  (void)s;
  (void)capacity; /* TODO */
  return false;
}
bool stream_push(Stream *s, unsigned value) {
  (void)s;
  (void)value; /* TODO */
  return false;
}
bool stream_pop(Stream *s, unsigned *out) {
  (void)s;
  (void)out; /* TODO */
  return false;
}
void stream_close(Stream *s) { (void)s; /* TODO */ }
void stream_destroy(Stream *s) { (void)s; /* TODO */ }
