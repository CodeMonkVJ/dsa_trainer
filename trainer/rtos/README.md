# RTOS Practice — Linux x86

These 15 C exercises run against the real [FreeRTOS GCC POSIX port](https://freertos.org/Documentation/02-Kernel/03-Supported-devices/04-Demos/03-Emulation-and-simulation/Linux/FreeRTOS-simulator-for-Linux), not a pthread imitation of its APIs.

The kernel subset is vendored at `third_party/freertos/`: V11.2.0, commit `0adc196d4bd52a2d91102b525b0aafc1e14a2386`, MIT license. See its `UPSTREAM.md`. No network, board, cross-compiler or ESP-IDF setup is needed to run a problem.

## Exercises

| Directory under systems/rtos/problems | Exercise |
| --- | --- |
| base | Task scheduling and blocking |
| periodic_tasks | Periodic releases without drift |
| safe_task_startup | Task parameter lifetime and creation failure |
| queue_command_response | Copied messages, routing, FIFO and timeouts |
| shared_state_mutex | Consistent multi-field snapshots |
| task_notifications | Counting, clearing and bit notifications |
| counting_semaphore_pool | Finite resource permits |
| producer_consumer | Semaphore-counted buffer, close and drain |
| dining_philosophers | Lock ordering and timeout cleanup |
| priority_inversion | Binary semaphore versus priority-inheriting mutex |
| event_groups | Wait-any/all and multi-waiter clearing |
| software_timers | Deferred events and synchronous timer shutdown |
| fixed_block_memory_pool | Ownership, exhaustion and reuse |
| watchdog_supervision | Independent per-task progress with logical time |
| initialization_shutdown | Partial acquisition unwind and blocked-worker exit |

The ESP32 experiments in the user's `esp-idf-template/main` informed the selection, especially notifications, producer/consumer semaphores, dining philosophers and priority inversion. They were not copied as known-correct references. The exercises here use standalone host APIs with finite contracts and tests; ESP-specific GPIO/UART/ADC/ISR operations and core affinity are excluded.

## How the trainer runs them

Each problem has a prompt, C starter, reference, metadata and `tests/test.c`. The browser's **Run tests** selects this compiler backend for `systems/rtos`. It compiles the attempt with GCC C17, the supplied configuration, kernel sources, heap_3, and POSIX port, then runs it with the trainer's usual five-second watchdog. Submission/history/filtering still use C attempt snapshots.

The Docker image includes `trainer/rtos` support. Mount the **whole repository**, including `third_party/`, at `/workspace`. When a session starts, the trainer writes workspace-local `compile_flags.txt` so clangd can resolve the FreeRTOS and lab headers both locally and in Docker.

The shared lab header exposes kernel APIs plus tracked factories used in failure-injection exercises. Factory failure counters are driven only by the controlling test task. References use blocking handshakes for task lifetime and shutdown. FreeRTOS lacks pthread-style join: the owned worker acknowledges its last shared access, then is deleted by the owner.

## Verification

From the repository root, with GCC, POSIX threads, coreutils and Node.js installed:

```sh
node trainer/rtos/verify.mjs --repeat=5
```

This compiles every reference, runs each five times, verifies every untouched starter fails cleanly, and compiles/runs one deliberately broken implementation per problem. Mutations cover wrong trace values, lost release phase, incorrect parameter copy, misrouting, invariant corruption, notification clearing, inverted permits, missing close, leaked partial lock, missing inheritance, incorrect event predicates, blocking timer callback, double return, ignored watchdog peers and dropped work. Runtime hangs are failures; compile errors do not count as successful mutation detection.

Compile an individual reference or your own source:

```sh
sh trainer/rtos/compile.sh "$PWD" \
  "$PWD/systems/rtos/problems/base/tests/test.c" \
  "$PWD/systems/rtos/problems/base/implementation.c" \
  /tmp/interview-rtos-scheduling
timeout 5s /tmp/interview-rtos-scheduling
```

## Simulator limits

- The configuration models a single-core preemptive FreeRTOS scheduler with 1,000 logical ticks/s. Do not infer actual microsecond deadlines from a Linux-host run.
- The priority inversion test gates tasks and checks logical priority/order, rather than benchmarking uncontrolled sleep intervals.
- Periodic tests preserve absolute phase even if a heavily loaded host misses a release. Unsigned wraparound is checked through injectable arithmetic instead of changing the live kernel tick.
- The watchdog exercise tests a software health policy using injected ticks; it does not claim to test a hardware watchdog.
- A signal-based POSIX port is not proof of arbitrary schedule correctness, SMP safety, ISR legality or MCU timing. Race sanitizers may not model its signal/context-switch mechanism; they are not the primary oracle.
- No stdio from preemptible RTOS tasks: glibc's internal locks can deadlock under this simulator. The harness stores results and prints `DSA_CASE`/`DSA_RESULT` only after the scheduler stops.
- Never start arbitrary foreign pthreads while the simulator is running; use FreeRTOS tasks. Keep student code within each exercise's API and context restrictions.
