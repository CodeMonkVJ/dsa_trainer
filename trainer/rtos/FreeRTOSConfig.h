#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#define configUSE_PREEMPTION 1
#define configUSE_TIME_SLICING 1
#define configCPU_CLOCK_HZ 100000000UL
#define configTICK_RATE_HZ 1000
#define configMAX_PRIORITIES 8
#define configMINIMAL_STACK_SIZE 16384
#define configMAX_TASK_NAME_LEN 24
#define configUSE_16_BIT_TICKS 0
#define configIDLE_SHOULD_YIELD 1
#define configUSE_MUTEXES 1
#define configUSE_RECURSIVE_MUTEXES 1
#define configUSE_COUNTING_SEMAPHORES 1
#define configUSE_TASK_NOTIFICATIONS 1
#define configTASK_NOTIFICATION_ARRAY_ENTRIES 2
#define configUSE_TIMERS 1
#define configTIMER_TASK_PRIORITY 5
#define configTIMER_QUEUE_LENGTH 32
#define configTIMER_TASK_STACK_DEPTH 16384
#define configSUPPORT_DYNAMIC_ALLOCATION 1
#define configSUPPORT_STATIC_ALLOCATION 0
#define configUSE_IDLE_HOOK 0
#define configUSE_TICK_HOOK 0
#define configCHECK_FOR_STACK_OVERFLOW 0
#define configUSE_MALLOC_FAILED_HOOK 0
#define configUSE_TRACE_FACILITY 1
#define INCLUDE_vTaskPrioritySet 1
#define INCLUDE_uxTaskPriorityGet 1
#define INCLUDE_vTaskDelete 1
#define INCLUDE_vTaskSuspend 1
#define INCLUDE_vTaskDelayUntil 1
#define INCLUDE_vTaskDelay 1
#define INCLUDE_xTaskGetCurrentTaskHandle 1
#define INCLUDE_xTaskGetSchedulerState 1
#define INCLUDE_eTaskGetState 1
#define INCLUDE_xTimerPendFunctionCall 1
#define configASSERT(x)                                                        \
  do {                                                                         \
    if (!(x)) {                                                                \
      const char msg[] = "FreeRTOS assertion failed\n";                        \
      (void)write(2, msg, sizeof msg - 1);                                     \
      _Exit(2);                                                                \
    }                                                                          \
  } while (0)
#endif
