#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
typedef void (*TimerCallback)(void *);
typedef struct {
  uint64_t id, deadline;
  TimerCallback callback;
  void *context;
} TimerEntry;
typedef struct {
  TimerEntry entries[16];
  uint64_t next_id;
  bool dispatching;
} TimerService;
void timer_init(TimerService *s);
uint64_t timer_register(TimerService *s, uint64_t deadline,
                        TimerCallback callback, void *context);
bool timer_cancel(TimerService *s, uint64_t id);
size_t timer_expire(TimerService *s, uint64_t now);

void timer_init(TimerService *s) {
  if (s)
    *s = (TimerService){.next_id = 1};
}
uint64_t timer_register(TimerService *s, uint64_t deadline, TimerCallback cb,
                        void *ctx) {
  if (!s || !cb || !s->next_id)
    return 0;
  for (size_t i = 0; i < 16; ++i)
    if (!s->entries[i].id) {
      uint64_t id = s->next_id++;
      s->entries[i] = (TimerEntry){id, deadline, cb, ctx};
      return id;
    }
  return 0;
}
bool timer_cancel(TimerService *s, uint64_t id) {
  if (!s || !id)
    return false;
  for (size_t i = 0; i < 16; ++i)
    if (s->entries[i].id == id) {
      s->entries[i].id = 0;
      return true;
    }
  return false;
}
size_t timer_expire(TimerService *s, uint64_t now) {
  if (!s || s->dispatching)
    return 0;
  s->dispatching = true;
  size_t count = 0;
  uint64_t limit = s->next_id ? s->next_id - 1 : UINT64_MAX;
  for (;;) {
    size_t best = 16;
    for (size_t i = 0; i < 16; ++i) {
      TimerEntry *t = &s->entries[i];
      if (t->id && t->id <= limit && t->deadline <= now &&
          (best == 16 || t->deadline < s->entries[best].deadline ||
           (t->deadline == s->entries[best].deadline &&
            t->id < s->entries[best].id)))
        best = i;
    }
    if (best == 16)
      break;
    TimerEntry t = s->entries[best];
    s->entries[best].id = 0;
    ++count;
    t.callback(t.context);
  }
  s->dispatching = false;
  return count;
}
