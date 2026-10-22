# FreeRTOS kernel dependency

Source: https://github.com/FreeRTOS/FreeRTOS-Kernel
Release: V11.2.0
Commit: 0adc196d4bd52a2d91102b525b0aafc1e14a2386
License: MIT; see LICENSE.md and individual source headers.

This is an unmodified subset: kernel C files, public headers, heap_3 and the GCC POSIX port. It is vendored so Run tests needs no network or ESP-IDF installation. Updating the pin requires rerunning all RTOS reference, starter and mutation checks.
