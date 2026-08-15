# DSA Training Tracker — Implementation Plan

## 1. Goal

Build a fast, local-first training application for repeatedly implementing algorithms and data structures until they can be written correctly from memory within a target time.

The application is for one user, runs on the local machine, and uses the repository filesystem as its source of truth. It does not need a database, authentication, cloud hosting, or multi-user support.

The product should optimize for this loop:

1. Select a topic.
2. Start a timed attempt.
3. Implement it in C or C++.
4. Compile and run the implementation against the topic's tests.
5. See correctness, runtime output, and timing status immediately.
6. Save the result and use it to decide what to practise next.

## 2. Product principles

- **Filesystem first:** adding or removing a topic directory changes what the app displays.
- **Local first:** the server binds to `127.0.0.1` and works without an internet connection.
- **Reference code is immutable during practice:** attempts never overwrite the known-correct implementation.
- **Correctness before speed:** an attempt only earns a speed rating after all tests pass.
- **Low ceremony:** opening a topic and starting to type should take one click.
- **Terminal-first frontend:** the coding surface is the user's real local Neovim process rendered in the browser, with only minimal browser chrome around it.
- **Reproducible execution:** compiler versions, flags, test inputs, limits, and results are recorded.

## 3. Repository contract

The existing top-level categories remain:

```text
interviews/
├── algos/
├── data-structures/
├── trainer/
├── DESIGN.md
└── PLAN.md                   # this implementation plan
```

The server discovers topics by scanning the immediate child directories of `algos/` and `data-structures/`. Directory names are stable topic IDs. Display names and behavior come from a small metadata file inside each topic.

### 3.1 Topic directory

Every topic should converge on this layout:

```text
algos/binary_search/
├── topic.json
├── prompt.md
├── implementation.cpp       # known-correct reference implementation
├── implementation.c         # optional known-correct C implementation
├── starter.cpp              # optional starter shown for a new C++ attempt
├── starter.c                # optional starter shown for a new C attempt
├── tests/
│   ├── test.cpp             # C++ test harness
│   ├── test.c               # optional C test harness
│   └── fixtures/            # optional input/output fixtures
├── workspace/
│   ├── attempt.cpp          # current C++ work in progress
│   └── attempt.c            # current C work in progress
└── progress/
    ├── summary.json         # derived current state for quick reads
    └── attempts.ndjson      # append-only attempt history
```

Only `topic.json`, `prompt.md`, at least one reference implementation, and tests for the supported language are required. `workspace/` and `progress/` are created by the application when needed.

`implementation.cpp` and `implementation.c` are never used as the editable attempt files. This prevents a practice session from destroying the reference solution.

### 3.2 Topic metadata

Use JSON because Zig can parse it without introducing a separate TOML or YAML dependency.

Initial `topic.json` schema:

```json
{
  "schema_version": 1,
  "name": "Binary Search",
  "description": "Implement lower-bound binary search over a sorted array.",
  "difficulty": "basic",
  "languages": ["cpp"],
  "target_seconds": 300,
  "warning_seconds": 450,
  "tags": ["search", "array", "divide-and-conquer"]
}
```

Rules:

- The directory name is the machine-readable topic ID.
- `name` is the UI label.
- `languages` must match the available reference implementations and test harnesses.
- `target_seconds` is the green threshold.
- `warning_seconds` is the upper yellow threshold.
- Unknown schema versions produce a visible catalog error instead of being silently ignored.

### 3.3 Attempt history

Each line in `attempts.ndjson` is one immutable attempt event:

```json
{"id":"2026-08-15T11:04:12.381Z-cpp","started_at":"2026-08-15T11:04:12.381Z","finished_at":"2026-08-15T11:08:40.913Z","language":"cpp","elapsed_ms":268532,"result":"passed","status":"green","compiler":"g++","compiler_version":"...","tests_passed":12,"tests_total":12}
```

Store compilation failures, test failures, manual cancellations, and execution timeouts too. Error output should be truncated to a configured limit before it is persisted.

`summary.json` is a rebuildable cache containing:

- latest attempt
- fastest passing attempt per language
- current color per language
- total attempts and passing attempts
- last-practised timestamp
- next suggested review date

Writes to `summary.json` must use a temporary file followed by an atomic rename. If it is missing or corrupt, rebuild it from `attempts.ndjson`.

## 4. Training and status model

An attempt begins only when the user presses **Start**. Loading a topic does not start the timer.

Status rules:

| Result | Elapsed time | Status |
| --- | ---: | --- |
| All tests pass | `<= target_seconds` | Green |
| All tests pass | `> target_seconds` and `<= warning_seconds` | Yellow |
| All tests pass | `> warning_seconds` | Red |
| Compile/test failure or timeout | Any | Red |
| Never attempted | — | Gray |

The UI should display correctness and speed separately even though they contribute to one color. A fast incorrect submission must never look successful.

The timer shown in the browser is only a display. The server records the authoritative start and finish times using its monotonic clock so page reloads and browser clock changes cannot alter the result.

## 5. Architecture

```text
Browser
  ├── dashboard and topic screens
  └── xterm.js terminal
          │ HTTP / WebSocket
          ▼
Zig local server
  ├── catalog scanner
  ├── attempt/timer service
  ├── compiler and test runner
  ├── progress store
  └── PTY/tmux session manager
          │
          ▼
Local tmux + Neovim + filesystem topic directories
```

### 5.1 Backend

Implement the server in Zig under `trainer/`:

```text
trainer/
├── build.zig
├── build.zig.zon
├── src/
│   ├── main.zig
│   ├── config.zig
│   ├── catalog.zig
│   ├── topic.zig
│   ├── attempts.zig
│   ├── runner.zig
│   ├── progress.zig
│   ├── http.zig
│   └── pty.zig
├── web/
│   ├── index.html
│   ├── styles.css
│   ├── app.js
│   └── vendor/
└── tests/
    └── fixtures/
```

Backend responsibilities:

- Resolve the repository root at startup.
- Scan category and topic directories.
- Validate metadata and report malformed topics.
- Start, restore, cancel, and finish attempt timers.
- Save and load workspace files.
- Compile attempts and execute tests.
- Persist attempt history and rebuild summaries.
- Create, resize, reconnect to, and terminate local PTY sessions.
- Launch a topic-scoped tmux session running the user's local Neovim.
- Serve the static frontend and JSON API.
- Watch the filesystem or provide an explicit rescan endpoint during the MVP.

Do not hard-code the current topic list in Zig or JavaScript.

### 5.2 Frontend recommendation

Use static HTML, CSS, a small amount of JavaScript, and xterm.js. The only code editor is the user's local Neovim running inside a server-owned PTY. The browser does not implement editing behavior itself; it sends keystrokes to the PTY and renders the terminal output it receives.

Avoid React, Vue, CodeMirror, canvas UI frameworks, and a second browser-side editor model. The surrounding browser interface only needs topic selection, timer/status display, terminal sizing, and a small amount of attempt control.

Vendor and pin xterm.js and its fit addon so the app remains offline-capable. Its WebGL addon may be enabled as an optional rendering optimization, but the ordinary renderer is the default until measurement shows a need for it.

Relevant component documentation:

- [xterm.js](https://xtermjs.org/)
- [xterm.js addons](https://xtermjs.org/docs/guides/using-addons/)

### 5.3 Local terminal and Neovim model

Starting an attempt performs this flow:

1. Create `workspace/attempt.cpp` or `workspace/attempt.c` from the relevant starter file if it does not exist.
2. Create a PTY sized to the browser terminal.
3. Attach to or create a uniquely named tmux session for that attempt and enable tmux's dead-pane/`remain-on-exit` behavior.
4. Run the system's configured `nvim` executable directly on the attempt file. Neovim is the pane command; it is not followed by a shell.
5. Stream PTY output to xterm.js and browser input back to the PTY over WebSocket.
6. Forward terminal resize events to the PTY and tmux.
7. On browser refresh, reconnect to the same live Neovim process. If its pane is dead, destroy that attempt session and create a fresh Neovim process on the same attempt file.

This uses the real local executable, filesystem, Neovim configuration, plugins, LSP servers, formatters, compilers, and tools available in the Zig server's environment.

The tracker adds a small Neovim guard after loading the user's normal configuration:

- The attempt file is the only normal file buffer that may be modified or written.
- File-backed buffers outside the attempt path are read-only.
- `BufWritePre` verifies the canonical destination path on every write.
- Scratch buffers required by plugins, help, diagnostics, and quickfix remain available.
- Leaving Neovim does not reveal a shell.

If Neovim exits through `:q`, `:qa`, a crash, or a signal, the server marks the session `editor_exited`, disconnects terminal input, and replaces the terminal with: **Editor exited — refresh the page to reopen it.** It must not automatically drop into a shell or start a respawn loop. Refreshing the page is the only normal action that creates the replacement editor process.

The file guard is a workflow restriction, not a security sandbox: a sufficiently determined user with access to Neovim's Lua/process APIs could remove it. The operating-system runner sandbox remains responsible for security. For this personal local app, the guard's purpose is to prevent accidental navigation and writes outside the active exercise.

It does not mirror an arbitrary graphical terminal window that is already open. Terminal-emulator-specific behavior such as Kitty key mappings, fonts, image protocols, and native clipboard integration may differ in xterm.js. The tracker always creates an isolated attempt session; it never attaches the practice page to an unrelated shell or tmux session.

The tmux session name and attempt path must be generated from validated internal IDs, not raw client input. The Neovim executable and startup arguments are configured on the server.

## 6. HTTP API

Initial endpoints:

| Method | Path | Purpose |
| --- | --- | --- |
| `GET` | `/api/catalog` | Categories, topics, validation errors, and summaries |
| `GET` | `/api/topics/:category/:topic` | Metadata, prompt, supported languages, and progress |
| `POST` | `/api/topics/:category/:topic/attempts` | Start an attempt and return its ID |
| `GET` | `/api/attempts/:id` | Restore timer and attempt state after a reload |
| `POST` | `/api/attempts/:id/run` | Compile and run tests without ending the timer |
| `POST` | `/api/attempts/:id/submit` | Compile, test, finish, rate, and persist the attempt |
| `POST` | `/api/attempts/:id/cancel` | Cancel and persist an attempt |
| `POST` | `/api/catalog/rescan` | Refresh topics after filesystem changes |

Use structured JSON errors with a stable error code and a readable message. Never return an arbitrary filesystem path supplied by a client.

The terminal uses `/ws/attempts/:id/terminal`, a WebSocket endpoint scoped to an active attempt. It carries PTY input/output plus explicit resize messages. An attempt ID can connect only to its server-resolved topic workspace and tmux session.

## 7. Compile and test runner

### 7.1 Execution flow

1. Validate the category, topic, language, and active attempt ID.
2. Save the latest editor contents to the topic workspace file.
3. Create a unique temporary build directory.
4. Copy or reference only the selected attempt and its test harness.
5. Invoke the compiler using an argument array, never a shell command string.
6. Capture bounded stdout and stderr.
7. If compilation succeeds, execute the test binary with limits.
8. Parse the harness result into passed/failed test counts.
9. Delete the temporary build directory.
10. Return the result; persist it only on Submit or Cancel.

Initial compiler modes:

```text
C++: g++ -std=c++20 -Wall -Wextra -Wpedantic
C:   gcc -std=c17   -Wall -Wextra -Wpedantic
```

Compiler names and flags belong in application configuration, not in browser requests. Record the compiler version with each persisted attempt.

### 7.2 Test contract

Use a simple process exit contract for the first version:

- exit code `0`: all tests passed
- non-zero exit code: compilation or test failure
- harness stdout: readable per-test diagnostics
- final machine-readable line: `DSA_RESULT {"passed":12,"total":12}`

Each topic test harness includes the user's attempt using a documented interface. Before migrating all topics, define the expected API in `prompt.md` and normalize the existing reference implementation to that API.

Tests should cover:

- empty input
- singleton input
- ordinary cases
- duplicates where applicable
- boundary values
- already sorted/reversed inputs where applicable
- invalid operations for data structures
- complexity-sensitive large inputs where useful

Wall-clock speed of the submitted program is not the training timer. The training timer measures implementation time; runner timeouts only detect broken or pathological code.

### 7.3 Safety boundaries

Attempts are arbitrary native code, even in a local-only app. Apply these protections:

- Bind only to `127.0.0.1` by default.
- Reject path traversal and symlinks that escape the repository root.
- Invoke processes without shell interpolation.
- Use unique temporary directories.
- Enforce compilation and execution wall-time limits.
- Limit captured output, memory, file size, and child-process count where supported.
- Kill the whole process group on timeout or server shutdown.
- Never run the server or test binaries as root.
- Do not expose PTY mode on a non-loopback interface.
- Spawn Neovim as the direct tmux pane command, with no fallback shell after it exits.
- Resolve the writable attempt file to a canonical server-side path before launching Neovim.

An optional later hardening step can run tests through Bubblewrap or another local sandbox. This is useful defense in depth, but it should not delay the local MVP.

## 8. User interface

### 8.1 Dashboard

Show:

- Algorithms and Data Structures sections.
- Topic name and current gray/green/yellow/red state.
- Fastest passing time.
- Last practised time.
- Attempts and pass count.
- Filters for status, language, tag, and recently practised topics.
- A suggested-next queue prioritizing red, never-attempted, and overdue topics.

### 8.2 Practice screen

Show:

- Topic name, prompt, expected interface, and target times.
- Language selector.
- Start/Run/Submit/Cancel controls.
- Large timer with threshold-aware color.
- Full-size xterm.js surface running local Neovim.
- A terminal lifecycle state: connecting, editor running, disconnected, or editor exited.
- Compile output and individual test results.
- Attempt history and personal best.
- Reference implementation, hidden behind an explicit reveal action.

Revealing the reference implementation during an active attempt should require confirmation and mark the attempt as `reference_viewed`, so it does not count as an unaided personal best.

When Neovim has exited, replace the terminal surface with **Editor exited — refresh the page to reopen it.** Do not expose a terminal prompt or an in-page restart button.

### 8.3 Keyboard workflow

Provide shortcuts for the common loop:

- Start attempt
- Run tests
- Submit
- Focus terminal
- Move to next suggested topic

Saving remains Neovim's responsibility. Run and Submit first instruct Neovim to save the current buffer, or reject the action if the file still has unsaved changes. Browser shortcuts must not capture keys owned by Neovim; controls should be reachable through buttons and a small set of configurable escape-prefixed shortcuts.

## 9. Configuration

Add `trainer/config.json` with conservative defaults:

```json
{
  "host": "127.0.0.1",
  "port": 8080,
  "compile_timeout_seconds": 15,
  "run_timeout_seconds": 5,
  "max_output_bytes": 262144,
  "cpp_compiler": "g++",
  "c_compiler": "gcc",
  "editor": "nvim",
  "session_manager": "tmux",
  "shell": "/bin/bash",
  "restrict_editor_to_attempt": true,
  "reopen_editor": "on_page_refresh"
}
```

The repository root can be supplied as a CLI argument, defaulting to the parent of `trainer/`. Environment variables may override configuration for development, but topic behavior remains in each topic's `topic.json`.

## 10. Verification strategy

### Backend tests

- Catalog discovers both categories and ignores unrelated directories.
- Invalid or missing metadata is reported without crashing the server.
- Topic IDs cannot traverse outside their category.
- Timers survive page reloads and reject duplicate submissions.
- Green/yellow/red boundaries are exact.
- NDJSON append and summary rebuild produce the same state.
- Concurrent writes do not corrupt progress files.
- Compile errors, failed tests, output overflow, and timeouts are reported correctly.
- Timed-out process groups are terminated.

### Frontend tests

- Dashboard states match API data.
- A refresh restores the active timer.
- A refresh reconnects to the same tmux/Neovim session.
- Exiting Neovim leaves a dead pane, exposes no shell, and shows the refresh message.
- Refreshing a dead session creates exactly one replacement Neovim process on the same attempt file.
- The Neovim guard rejects writes to every file except the canonical attempt path.
- Terminal input, output, UTF-8, and resize events survive the WebSocket bridge.
- Run and Submit use the latest saved Neovim buffer.
- Network and compiler failures remain visible and actionable.
- Browser shortcuts do not interfere with Vim modes, mappings, or terminal input.

### End-to-end fixture

Create one small fixture topic with known passing, failing, non-compiling, and timing-out attempts. Use it to test the complete browser-to-runner flow without modifying real progress data.

## 11. Delivery phases

### Phase 0 — Normalize one pilot topic

- Choose `algos/binary_search` as the pilot.
- Add `topic.json`, `prompt.md`, a starter, and a deterministic test harness.
- Normalize `implementation.cpp` to the documented interface.
- Confirm the reference implementation passes every test.

**Exit criterion:** binary search can be compiled and tested through one repeatable command.

### Phase 1 — Zig catalog and command-line runner

- Create the Zig project under `trainer/`.
- Implement repository-root discovery, catalog scanning, JSON validation, and errors.
- Implement the isolated compiler/test runner.
- Add runner and catalog tests.

**Exit criterion:** a CLI command can list topics and run a supplied binary-search attempt safely.

### Phase 2 — Read-only web dashboard

- Serve static assets from Zig.
- Implement `/api/catalog` and topic detail endpoints.
- Build the dashboard, status colors, filters, and topic screen shell.

**Exit criterion:** opening the local URL accurately reflects the filesystem without a database.

### Phase 3 — Timed Neovim practice

- Add xterm.js and its terminal-fit behavior.
- Implement PTY creation, resizing, byte streaming, and cleanup in Zig.
- Launch Neovim in a topic-scoped tmux session on the workspace file.
- Launch it as the direct pane command with dead-pane behavior and no fallback shell.
- Add the single-file write guard and exited-editor refresh state.
- Reconnect to the same session after browser refreshes or brief disconnects.
- Implement authoritative attempt timers.
- Add Run, Submit, Cancel, compiler output, and test results.
- Persist attempt history and summaries.

**Exit criterion:** a full timed binary-search attempt can be written in the user's configured Neovim, submitted, and resumed after a browser reload.

### Phase 4 — Migrate the catalog

- Add metadata, prompts, starters, and tests topic by topic.
- Normalize reference implementation interfaces.
- Add C support where an `implementation.c` already exists.
- Add validation tooling that reports incomplete topic folders.

**Exit criterion:** every displayed topic has at least one runnable, tested language.

### Phase 5 — Training intelligence

- Add fastest times, history, status filters, and suggested-next ordering.
- Add spaced-review dates derived from attempt outcomes.
- Add reference-view tracking and personal-best eligibility.
- Add progress export and summary rebuild commands.

**Exit criterion:** the dashboard reliably answers “what should I practise next?”

### Phase 6 — Terminal workflow polish

- Add explicit session-health and cleanup diagnostics without exposing a shell or an in-page editor restart.
- Add configurable Neovim startup commands and environment diagnostics.
- Improve clipboard handling and browser keybinding compatibility.
- Add diagnostics for Neovim configuration, plugin, and LSP startup failures.
- Add an optional xterm.js WebGL renderer after measuring the ordinary renderer.

**Exit criterion:** terminal sessions behave predictably across disconnects, crashes, and daily use without leaving orphaned processes.

### Phase 7 — Hardening and polish

- Add optional Bubblewrap isolation.
- Add filesystem watching if manual rescans become annoying.
- Improve accessibility and responsive layout.
- Measure startup, catalog scan, page load, and test-run latency before optimizing.

**Exit criterion:** the app is dependable enough for daily use and has no known path-escape or orphan-process bugs.

## 12. MVP definition

The MVP consists of Phases 0–3 and is intentionally narrow:

- Zig server on localhost.
- Filesystem-derived catalog.
- One fully normalized topic.
- xterm.js connected to a local PTY.
- Local tmux session running the user's configured Neovim on the attempt file.
- Single-file write guard and no shell after Neovim exits.
- Dead editor screen that requires a page refresh to recreate Neovim.
- Server-authoritative timer.
- Compile, run, submit, and cancel actions.
- Green/yellow/red result.
- File-backed attempt history and summary.

The MVP does not include WebGL, automatic filesystem watching, spaced repetition, C support, or sandbox tooling beyond process limits. Attaching arbitrary existing terminal sessions is intentionally unsupported.

## 13. Immediate implementation sequence

1. Keep `data-structures/DESIGN.md` as the original rough notes and treat this root plan as the cross-category specification.
2. Normalize `algos/binary_search` as the pilot topic.
3. Specify the binary-search function signature and tests.
4. Scaffold `trainer/` and pin the Zig version used by the project.
5. Implement and test catalog scanning.
6. Implement and test compile/run execution.
7. Implement the PTY, tmux, Neovim, and WebSocket bridge.
8. Expose the catalog and runner through HTTP.
9. Build the minimal dashboard and terminal-based practice screen.
10. Add persistence and status calculation.
11. Use the app for several real sessions before migrating the remaining topics.

## 14. Decisions intentionally deferred

- Exact spaced-repetition formula.
- Whether attempt source snapshots should be retained forever or only for personal bests.
- Whether Bubblewrap is required by default.
- Whether terminal sessions should survive a Zig server restart by leaving tmux sessions alive.
- Whether to package the frontend assets into the Zig executable or serve them from disk during development.
- Whether topic metadata eventually needs per-language target times.

These decisions do not block the MVP and should be made from actual usage rather than speculation.
