# Task Notifications

Handle counting and bit notifications without confusing wakeups with payload storage.

## Required behavior

notify_count(task) gives a counting notification; take_count(clear,wait) uses ulTaskNotifyTake, returning the value before decrement/reset. notify_bits ORs bits using eSetBits. wait_bits(entry_mask,exit_mask,out,wait) uses xTaskNotifyWait, preserves out on invalid input/timeout, and returns true only on receipt. All use notification index 0; finish one mode before switching. Null target/output is rejected. Notifications do not carry owned buffers; explain why a shared heap pointer needs a separately synchronized queue/mailbox.

## API

```c
#include "lab.h" /* FreeRTOS task, queue, semaphore, timer and event APIs */
bool notify_count(TaskHandle_t task);
uint32_t take_count(bool clear,TickType_t wait);
bool notify_bits(TaskHandle_t task,uint32_t bits);
bool wait_bits(uint32_t entry_mask,uint32_t exit_mask,uint32_t *out,TickType_t wait);
```

## Practice environment

Write C using the supplied FreeRTOS APIs in the editor. Save your changes and press **Run tests**. This exercise runs on Linux x86 using the pinned FreeRTOS POSIX port, configured as a single-core preemptive scheduler at 1,000 logical ticks/s. No ESP32 hardware or ESP-IDF installation is needed.

Use blocking synchronization rather than guessed startup sleeps. Do not print/log from RTOS tasks; the harness records results and prints after the scheduler stops. Kernel assertions, deadlocks and invalid API use fail the run. The timeout is a watchdog, not a timing grade. Desktop scheduling and simulator results do not establish hardware real-time guarantees. Do not change API declarations or harness configuration.
