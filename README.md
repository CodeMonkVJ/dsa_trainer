# DSA Trainer

A local, filesystem-backed practice tracker that renders your configured Neovim inside the browser and tests C++ attempts against topic-owned harnesses.

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
./zig-out/bin/dsa-trainer ..
```

Then open [http://127.0.0.1:8080](http://127.0.0.1:8080).

The optional first argument is the repository root. A second optional argument changes the port, for example `./zig-out/bin/dsa-trainer .. 8081`. The server intentionally binds only to `127.0.0.1`.

## Docker

Build the image from this directory:

```sh
docker build -t dsa-trainer .
```

Run it by mounting the DSA workspace—the directory containing `algos/` and `data-structures/`—at `/workspace`:

```sh
docker run --rm --init \
  -p 127.0.0.1:8080:8080 \
  -v /path/to/your/dsa:/workspace \
  dsa-trainer
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

## Tests

```sh
zig build test
g++ -std=c++20 -Wall -Wextra -Wpedantic \
  algos/binary_search/problems/base/tests/test.cpp \
  -o /tmp/dsa-binary-search-reference
```

The second command should be run from the repository root and validates the known-correct reference implementation through the pilot harness.
