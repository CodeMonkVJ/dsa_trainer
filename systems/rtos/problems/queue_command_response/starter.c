#include "lab.h"
typedef struct {
  uint32_t id, value;
} Message;
typedef struct {
  QueueHandle_t requests, replies;
} Channel;
bool channel_init(Channel *c, unsigned capacity);
bool channel_send(Channel *c, const Message *message, bool reply,
                  TickType_t wait);
bool channel_receive(Channel *c, Message *message, bool reply, TickType_t wait);
void channel_destroy(Channel *c);

bool channel_init(Channel *c, unsigned capacity) {
  (void)c;
  (void)capacity; /* TODO */
  return false;
}
bool channel_send(Channel *c, const Message *message, bool reply,
                  TickType_t wait) {
  (void)c;
  (void)message;
  (void)reply;
  (void)wait; /* TODO */
  return false;
}
bool channel_receive(Channel *c, Message *message, bool reply,
                     TickType_t wait) {
  (void)c;
  (void)message;
  (void)reply;
  (void)wait; /* TODO */
  return false;
}
void channel_destroy(Channel *c) { (void)c; /* TODO */ }
