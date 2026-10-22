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

void timer_init(TimerService *s) { /* TODO */ }
uint64_t timer_register(TimerService *s, uint64_t deadline,
                        TimerCallback callback, void *context) { /* TODO */
  return 0;
}
bool timer_cancel(TimerService *s, uint64_t id) { /* TODO */ return 0; }
size_t timer_expire(TimerService *s, uint64_t now) { /* TODO */ return 0; }
