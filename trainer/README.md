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
5. Press **Submit** to persist the timed result, or **Cancel** to discard it.

After 15 minutes, the **Hint / answer after 15:00** action becomes available. It first shows a general implementation hint and offers an explicit confirmation before displaying the immutable `implementation.cpp` reference. Viewing it records `reference_viewed` on the attempt.

Submitted attempts appear in the topic history and on its dashboard tile. Each record includes the Start-to-Submit time, test-program runtime, peak resident memory, and its red/yellow/green rating.

Run and Submit compile the last version saved to disk. Unsaved Neovim changes are intentionally left under editor control.

If Neovim exits, the page displays **Editor exited — refresh the page to reopen it.** There is no fallback shell and no in-page restart. Refreshing creates a new Neovim process on the same attempt file.

## Topic contract

The binary-search pilot demonstrates the required layout:

```text
algos/binary_search/
├── topic.json
├── prompt.md
├── implementation.cpp
├── starter.cpp
└── tests/test.cpp
```

During practice, the app creates:

```text
workspace/attempt.cpp
progress/attempts.ndjson
progress/summary.json
progress/attempts/<attempt-id>.cpp
```

Submitted source snapshots are read-only. The attempt history can load one into a new timed attempt, which gets its own editable `workspace/attempt.cpp` and attempt ID.

Only topics with valid metadata, a prompt, a starter, and a test harness can be started. Other existing directories appear as not configured.

The current migrated catalog is C++-only. Existing C implementations are intentionally left in place and are not modified or started by this trainer until C support is added.

## Tests

```sh
zig build test
g++ -std=c++20 -Wall -Wextra -Wpedantic \
  algos/binary_search/tests/test.cpp \
  -o /tmp/dsa-binary-search-reference
```

The second command should be run from the repository root and validates the known-correct reference implementation through the pilot harness.
