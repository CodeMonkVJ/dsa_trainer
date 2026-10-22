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
  if (!c || !capacity)
    return false;
  *c = (Channel){0};
  c->requests = lab_queue_create(capacity, sizeof(Message));
  c->replies = lab_queue_create(capacity, sizeof(Message));
  if (!c->requests || !c->replies) {
    channel_destroy(c);
    return false;
  }
  return true;
}
bool channel_send(Channel *c, const Message *m, bool reply, TickType_t wait) {
  return c && m &&
         xQueueSend(reply ? c->replies : c->requests, m, wait) == pdTRUE;
}
bool channel_receive(Channel *c, Message *m, bool reply, TickType_t wait) {
  return c && m &&
         xQueueReceive(reply ? c->replies : c->requests, m, wait) == pdTRUE;
}
void channel_destroy(Channel *c) {
  if (!c)
    return;
  lab_queue_delete(c->requests);
  lab_queue_delete(c->replies);
  *c = (Channel){0};
}
