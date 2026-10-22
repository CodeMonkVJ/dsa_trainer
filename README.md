# Interview Trainer

A local, filesystem-backed practice tracker that renders your configured Neovim inside the browser and tests C and C++ attempts against topic-owned harnesses.

## Prerequisites

- Zig 0.16.0 or newer in the 0.16 series
- Neovim
- tmux
- GCC/G++
- Node.js and npm when rebuilding frontend assets

## Build

```sh
cd trainer
npm install
npm run build
zig build
```

The generated xterm.js bundle is stored in `web/dist`, so `npm` is not needed merely to run an already-built checkout.

## Run

From `trainer/`:

```sh
./zig-out/bin/interview-trainer ..
```

Then open [http://127.0.0.1:8080](http://127.0.0.1:8080).

The optional first argument is the repository root. A second optional argument changes the port, for example `./zig-out/bin/interview-trainer .. 8081`. The server intentionally binds only to `127.0.0.1`.

## Docker

Build the image from this directory:

```sh
docker build -t interview-trainer .
```

Run it by mounting the DSA workspace—the directory containing `algos/` and `data-structures/`—at `/workspace`:

```sh
docker run --rm --init \
  -p 127.0.0.1:8080:8080 \
  -v /path/to/your/dsa:/workspace \
  interview-trainer
```

The image includes Zig's compiled trainer, Node-built frontend assets, Neovim, tmux, and the C++ toolchain. Progress, workspaces, and submitted source snapshots are written into the mounted DSA directory. `DSA_ROOT`, `PORT`, `TRAINER_PATH`, and `BIND_HOST` can be overridden with Docker environment variables when needed. Native runs remain loopback-only; the Docker default is `0.0.0.0` so published ports are reachable.

## Practice workflow

1. Choose a configured topic.
2. Press **Start**. The workspace is reset from the topic's starter file.
3. Edit in the Neovim terminal and save with `:w`.
4. Press **Run tests** as often as needed.

### Test result details

The results panel classifies every run as one of **Passed**, **Tests did not pass**, **Compiler error**, **Runtime error**, or **Time limit exceeded**. Test failures can provide a test input and the expected and actual values through a structured marker:

```cpp
cout << "DSA_CASE {\"input\":{\"values\":[6,7,0,1,2,4,5],\"target\":5},\"expected\":6,\"actual\":-1,\"passed\":false}\n";
```

The UI displays those three values while walking through the cases. Existing `PASS name`/`FAIL name` harnesses remain supported, but they do not contain enough information to reconstruct input, expected, or actual values; those fields are shown as unavailable until the harness emits `DSA_CASE`.
5. Press **Submit** to persist the timed result, or **Cancel** to discard it.

The hint action becomes available once the attempt passes that problem's configured yellow-zone threshold and enters red. It first shows a general implementation hint and offers an explicit confirmation before displaying the immutable `implementation.cpp` reference. Viewing it records `reference_viewed` on the attempt.

Submitted attempts appear in the topic history and on its dashboard tile. Each record includes the Start-to-Submit time, test-program runtime, peak resident memory, and its red/yellow/green rating.

Run and Submit compile the last version saved to disk. Unsaved Neovim changes are intentionally left under editor control.

If Neovim exits, the page displays **Editor exited — refresh the page to reopen it.** There is no fallback shell and no in-page restart. Refreshing creates a new Neovim process on the same attempt file.

While an attempt is active, the practice screen is locked to that problem. The dashboard and Home control cannot be used to switch to another problem until the active attempt is submitted or canceled. This keeps the existing WebSocket and tmux/Neovim session associated with the visible problem.

## Problem timing configuration

Each problem configures its own timing zones in `topic.json`:

```json
{
  "schema_version": 1,
  "name": "Binary Search",
  "description": "Find the first occurrence of a target in a sorted array.",
  "difficulty": "easy",
  "languages": ["cpp"],
  "green_seconds": 300,
  "yellow_seconds": 600,
  "tags": ["search", "array"]
}
```

The thresholds must be ordered `green_seconds <= yellow_seconds`. A passing attempt is green through the green threshold, yellow after green through the yellow threshold, and red after that. Failed attempts are always red. The hint is locked until the attempt enters red.

## Problem groups

The dashboard treats each existing topic directory as a problem group. Its original problem is stored in the group's `base` directory, and the catalog response includes a `problems` array for additional problems in the same group.

## Topic contract

Each topic is a problem group. Every runnable problem, including the base problem, has its own directory:

```text
algos/binary_search/
└── problems/
    ├── base/
    │   ├── topic.json
    │   ├── prompt.md
    │   ├── implementation.cpp
    │   ├── starter.cpp
    │   └── tests/test.cpp
    └── first_occurrence/
        ├── topic.json
        ├── prompt.md
        ├── implementation.cpp
        ├── starter.cpp
        └── tests/test.cpp
```

To add another binary-search problem, copy a problem directory into `algos/binary_search/problems/<problem-id>/`, then customize its `topic.json`, prompt, starter, reference implementation, and tests. The next catalog load will show it in the problem picker inside the Binary Search topic page. Problem IDs may contain only letters, numbers, `_`, and `-`.

During practice, the app creates:

```text
problems/<problem-id>/workspace/attempt.cpp
problems/<problem-id>/progress/attempts.ndjson
problems/<problem-id>/progress/summary.json
problems/<problem-id>/progress/attempts/<attempt-id>.cpp
```

Submitted source snapshots are read-only. The attempt history can load one into a new timed attempt, which gets its own editable `workspace/attempt.cpp` and attempt ID.

Only topics with valid metadata, a prompt, a starter, and a test harness can be started. Other existing directories appear as not configured.

The current migrated catalog is C++-only. Existing C implementations are intentionally left in place and are not modified or started by this trainer until C support is added.

## Imported problem sheets

The initial segregation for Striver's SDE Sheet is recorded in [data/striver_sde_sheet.json](/home/codemonk263/Dev/my_projects/dsa_trainer/data/striver_sde_sheet.json). It records the 191-problem group structure, difficulty totals, source page, and the repository group each bucket will map to. The manifest is the import queue; problem folders become visible in the trainer as their prompts, starters, tests, and reference implementations are added.

The repository taxonomy keeps `algos/` and `data-structures/` separate while grouping related exercises together: linked-list variants share `data-structures/linkedList`, stack/queue/deque share `data-structures/stackQueue`, priority queues live under `data-structures/heaps`, segment trees under `data-structures/treeMisc`, and graph representations versus graph algorithms live under `data-structures/graphs` and `algos/graphs` respectively.

## Low level coding and systems design

Use the Difficulty and Attempt status filters above the catalog or problem picker to combine easy/medium/hard with attempted/not attempted. Topics with no matching problems are hidden from the catalog. Starting a problem counts as attempted even if it is canceled or never submitted; existing C/C++ workspaces and saved results also count. Filtering does not change or cancel the active exercise.

The **Low Level Coding** category contains a **Systems Programming** topic with twelve C exercises in `systems/programming/problems/`: `base` (bit utilities), `memory_copy_move`, `hexadecimal_parser`, `ring_buffer`, `buffered_reader`, `timer_service`, `message_parser`, `bounded_producer_consumer`, `checked_arithmetic`, `arena_allocator`, `posix_io_adapter`, and `recoverable_record_log`. Open the topic to select an exercise. Each includes `topic.json`, `prompt.md`, `starter.c`, `implementation.c`, and `tests/test.c`.

The separate **Systems Design** topic, also under **Low Level Coding**, contains five exercises in `systems/design/problems/`: `base` (ISR-to-Worker Pipeline), `driver_timer_api_design`, `ota_firmware_updater`, `persistent_configuration`, and `local_rpc_service`. The picker displays the base design's actual title rather than “Base implementation.” Each has `topic.json` (`languages: ["md"]`), `prompt.md`, `starter.md`, `review.md`, and a reference `implementation.md`. Start opens `workspace/attempt.md` in the same editor. Save your edits, use **Review checklist**, then **Save self-review** to record your assessment. There are no executable design tests or automated correctness grades. Completion records use `self_reviewed`, and saved Markdown snapshots can be loaded into a fresh attempt. Design exercises use hard timing limits (15/25 minutes) and the existing red-zone hint/reference rules. Self-reviewed designs count toward topic completion; they do not represent an automated correctness pass.

The driver/timer API design is deliberately distinct from the Timer Service coding exercise: it covers hardware/driver lifecycle, concurrent expiry/cancellation, synchronous cancellation guarantees, callback context ownership, stale handles and partial initialization. The existing service implementation is a deterministic single-threaded coding exercise.

The new host-only programming exercises cover overflow-safe size arithmetic/alignment, a caller-backed arena with epoch-checked checkpoints, an injected POSIX I/O adapter with real nonblocking-pipe checks, and a checksummed byte-snapshot record log. The log tests every interrupted prefix and independent CRC/byte-order golden vectors; it does not claim to simulate power-loss durability. The I/O contract preserves partial byte counts and absolute deadlines across `EINTR`/`EAGAIN`, and leaves buffering to the separate Buffered Reader exercise. Persistent Configuration and Local RPC are design exercises about storage guarantees, optimistic revisions, retry identity, framing, cancellation and bounded resource ownership.

Run `node trainer/tests/verify_systems_batch.mjs` to verify the four new references five times, reject their untouched starters and eight deliberate mutations, and validate the two design packages. Each C harness also builds with `-fsanitize=address,undefined` for memory/undefined-behavior checks. Checked Arithmetic and Arena Allocator use medium timing (10/20 minutes); POSIX I/O and Record Log use hard timing (15/25 minutes).

The trainer uses GCC with C17 for these exercises, opens `workspace/attempt.c`, and saves `.c` attempt snapshots. Existing C++ problems continue using C++20. Rebuild and restart the trainer image to enable the new category and C runner; mount the repository root so it includes `systems/`.

The bounded producer–consumer queue uses POSIX pthreads; the trainer links harnesses with `-pthread`. Its hard difficulty uses 15/25-minute green/yellow thresholds. The contract specifies blocking full/empty predicates, a mutex-protected closed flag, broadcast shutdown, draining pending items, and ownership transfer on push/pop. Close and join all users before destroying the queue; its disposer releases remaining payloads. Run its standalone harness with `gcc -std=c17 -Wall -Wextra -Wpedantic -Werror -pthread systems/programming/problems/bounded_producer_consumer/tests/test.c -o /tmp/bounded-queue`, then `/tmp/bounded-queue`.

Prompts define bounds, error results, ownership, overflow policies, and callback lifetimes. The timer service is a deterministic single-threaded event-loop exercise with explicit time supplied by the caller; its prompt explains why concurrent cancellation needs synchronization. The memory-move reference uses a temporary allocation for portable overlap handling. These are learning implementations with explicit contracts.

Run an individual reference harness from the repository root:

```sh
gcc -std=c17 -Wall -Wextra -Wpedantic -Werror -fsanitize=undefined \
  systems/programming/problems/message_parser/tests/test.c -o /tmp/systems-message-parser
/tmp/systems-message-parser
```

To test your implementation, add `-DDSA_IMPLEMENTATION='"/absolute/path/to/attempt.c"'` to that compile command. Harnesses emit the trainer's `DSA_CASE` and `DSA_RESULT` records. Easy exercises use green/yellow limits of 5/10 minutes, medium 10/20, and hard 15/25. Hints unlock in red, as for other exercises.

## RTOS practice on Linux x86

**Low Level Coding → RTOS Practice** contains 15 C exercises under `systems/rtos/problems/`. They cover scheduling, periodic tasks, task startup, command queues, shared state, notifications, resource permits, producer–consumer buffering, dining philosophers, priority inversion, event groups, software timers, fixed-block allocation, watchdog supervision, and clean initialization/shutdown.

**Run tests** uses the real FreeRTOS POSIX port with a pinned, MIT-licensed kernel subset in `third_party/freertos/`. No ESP32, ESP-IDF, QEMU, flashing or runtime download is needed. The full repository must be mounted when running Docker. The existing difficulty timing, attempt filters, history and red-zone hints work for these exercises too. The base problem is shown as **Task Scheduling and Blocking**.

Run `node trainer/rtos/verify.mjs --repeat=5` to check all reference implementations, reject untouched starters and known-broken mutations. The [RTOS harness documentation](trainer/rtos/README.md) explains contracts, build commands, provenance, and simulator limits. These tests validate logical RTOS behavior rather than hardware deadlines; they do not test SMP, peripherals or real interrupts.

## Development checks

```sh
zig build test
g++ -std=c++20 -Wall -Wextra -Wpedantic \
  algos/binary_search/problems/base/tests/test.cpp \
  -o /tmp/dsa-binary-search-reference
```

The second command should be run from the repository root and validates the known-correct reference implementation through the pilot harness.
