# Queue Command and Response

Exchange copied commands and responses with bounded queues and explicit timeouts.

## Required behavior

A Channel owns separate bounded request and response queues of Message {id,value}. channel_init rejects zero capacity/null and cleans partial allocation. channel_send(channel, message, reply, wait) routes by reply (false=request, true=response), copying the message. channel_receive uses the same routing and preserves output on failure. Return false on full/empty timeout or invalid pointers. channel_destroy only after all users stop. Use tracked lab_queue_create/delete factories; callers initialize successfully before other operations. No UART or physical LED required.

## API

```c
#include "lab.h" /* FreeRTOS task, queue, semaphore, timer and event APIs */
typedef struct {uint32_t id,value;} Message;
typedef struct {QueueHandle_t requests,replies;} Channel;
bool channel_init(Channel *c, unsigned capacity);
bool channel_send(Channel *c,const Message *message,bool reply,TickType_t wait);
bool channel_receive(Channel *c,Message *message,bool reply,TickType_t wait);
void channel_destroy(Channel *c);
```

## Practice environment

Write C using the supplied FreeRTOS APIs in the editor. Save your changes and press **Run tests**. This exercise runs on Linux x86 using the pinned FreeRTOS POSIX port, configured as a single-core preemptive scheduler at 1,000 logical ticks/s. No ESP32 hardware or ESP-IDF installation is needed.

Use blocking synchronization rather than guessed startup sleeps. Do not print/log from RTOS tasks; the harness records results and prints after the scheduler stops. Kernel assertions, deadlocks and invalid API use fail the run. The timeout is a watchdog, not a timing grade. Desktop scheduling and simulator results do not establish hardware real-time guarantees. Do not change API declarations or harness configuration.
