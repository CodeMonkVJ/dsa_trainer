const std = @import("std");
const Io = std.Io;
const Attempt = @import("attempts.zig").Attempt;

pub const Phase = enum { compilation, testing };

pub const Result = struct {
    phase: Phase,
    passed: bool,
    stdout: []u8,
    stderr: []u8,
    term: std.process.Child.Term,
    runtime_ms: ?i64,
    peak_memory_bytes: ?u64,

    pub fn deinit(self: *Result, allocator: std.mem.Allocator) void {
        allocator.free(self.stdout);
        allocator.free(self.stderr);
        self.* = undefined;
    }
};

pub fn run(
    allocator: std.mem.Allocator,
    io: Io,
    root_path: []const u8,
    trainer_path: []const u8,
    attempt: *const Attempt,
) !Result {
    if (!std.mem.eql(u8, attempt.language(), "cpp")) return error.UnsupportedLanguage;

    const topic_path = try std.fs.path.join(allocator, &.{ root_path, attempt.category(), attempt.topic() });
    defer allocator.free(topic_path);
    const attempt_path = try std.fs.path.join(allocator, &.{ topic_path, "workspace", "attempt.cpp" });
    defer allocator.free(attempt_path);
    const test_path = try std.fs.path.join(allocator, &.{ topic_path, "tests", "test.cpp" });
    defer allocator.free(test_path);
    const build_path = try std.fs.path.join(allocator, &.{ trainer_path, "state", "build" });
    defer allocator.free(build_path);
    try Io.Dir.cwd().createDirPath(io, build_path);
    const binary_path = try std.fs.path.join(allocator, &.{ build_path, attempt.id() });
    defer allocator.free(binary_path);
    const implementation_define = try std.fmt.allocPrint(
        allocator,
        "-DDSA_IMPLEMENTATION=\"{s}\"",
        .{attempt_path},
    );
    defer allocator.free(implementation_define);

    const compile = std.process.run(allocator, io, .{
        .argv = &.{
            "g++",
            "-std=c++20",
            "-Wall",
            "-Wextra",
            "-Wpedantic",
            implementation_define,
            test_path,
            "-o",
            binary_path,
        },
        .stdout_limit = .limited(256 * 1024),
        .stderr_limit = .limited(256 * 1024),
        .timeout = .{ .duration = .{ .raw = .fromSeconds(15), .clock = .awake } },
    }) catch |err| switch (err) {
        error.Timeout => return failureResult(
            allocator,
            .compilation,
            "Compilation timed out after 15 seconds.\n",
        ),
        error.StreamTooLong => return failureResult(
            allocator,
            .compilation,
            "Compiler output exceeded the 256 KiB limit.\n",
        ),
        else => return err,
    };
    if (!termSucceeded(compile.term)) {
        return .{
            .phase = .compilation,
            .passed = false,
            .stdout = compile.stdout,
            .stderr = compile.stderr,
            .term = compile.term,
            .runtime_ms = null,
            .peak_memory_bytes = null,
        };
    }
    allocator.free(compile.stdout);
    allocator.free(compile.stderr);

    const test_result = runMeasured(allocator, io, &.{binary_path}) catch |err| switch (err) {
        error.Timeout => return failureResult(
            allocator,
            .testing,
            "Execution timed out after 5 seconds. Check for an infinite loop or blocked input.\n",
        ),
        error.StreamTooLong => return failureResult(
            allocator,
            .testing,
            "Test output exceeded the 256 KiB limit. Check for an infinite loop that prints output.\n",
        ),
        else => return err,
    };
    return .{
        .phase = .testing,
        .passed = termSucceeded(test_result.term),
        .stdout = test_result.stdout,
        .stderr = test_result.stderr,
        .term = test_result.term,
        .runtime_ms = test_result.runtime_ms,
        .peak_memory_bytes = test_result.peak_memory_bytes,
    };
}

const MeasuredRunResult = struct {
    term: std.process.Child.Term,
    stdout: []u8,
    stderr: []u8,
    runtime_ms: i64,
    peak_memory_bytes: ?u64,
};

fn runMeasured(
    allocator: std.mem.Allocator,
    io: Io,
    argv: []const []const u8,
) !MeasuredRunResult {
    var child = try std.process.spawn(io, .{
        .argv = argv,
        .stdin = .ignore,
        .stdout = .pipe,
        .stderr = .pipe,
        .request_resource_usage_statistics = true,
    });
    defer child.kill(io);

    const started_ns = Io.Clock.awake.now(io).nanoseconds;
    var multi_reader_buffer: Io.File.MultiReader.Buffer(2) = undefined;
    var multi_reader: Io.File.MultiReader = undefined;
    multi_reader.init(allocator, io, multi_reader_buffer.toStreams(), &.{ child.stdout.?, child.stderr.? });
    defer multi_reader.deinit();

    const stdout_reader = multi_reader.reader(0);
    const stderr_reader = multi_reader.reader(1);
    const timeout: Io.Timeout = .{ .duration = .{ .raw = .fromSeconds(5), .clock = .awake } };
    while (multi_reader.fill(64, timeout)) |_| {
        if (stdout_reader.buffered().len > 256 * 1024 or stderr_reader.buffered().len > 256 * 1024) {
            return error.StreamTooLong;
        }
    } else |err| switch (err) {
        error.EndOfStream => {},
        else => |other| return other,
    }
    try multi_reader.checkAnyError();

    const term = try child.wait(io);
    const completed_ns = Io.Clock.awake.now(io).nanoseconds;
    const runtime_ms: i64 = @intCast(@max(0, @divTrunc(completed_ns - started_ns, std.time.ns_per_ms)));
    const max_rss = child.resource_usage_statistics.getMaxRss();
    const stdout = try multi_reader.toOwnedSlice(0);
    errdefer allocator.free(stdout);
    const stderr = try multi_reader.toOwnedSlice(1);
    errdefer allocator.free(stderr);

    return .{
        .term = term,
        .stdout = stdout,
        .stderr = stderr,
        .runtime_ms = runtime_ms,
        .peak_memory_bytes = if (max_rss) |bytes| @intCast(bytes) else null,
    };
}

fn failureResult(
    allocator: std.mem.Allocator,
    phase: Phase,
    message: []const u8,
) !Result {
    const stdout = try allocator.alloc(u8, 0);
    errdefer allocator.free(stdout);
    const stderr = try allocator.dupe(u8, message);
    return .{
        .phase = phase,
        .passed = false,
        .stdout = stdout,
        .stderr = stderr,
        .term = .{ .unknown = 0 },
        .runtime_ms = null,
        .peak_memory_bytes = null,
    };
}

pub fn persistResult(
    allocator: std.mem.Allocator,
    io: Io,
    root_path: []const u8,
    attempt: *const Attempt,
    result: *const Result,
    elapsed_ms: i64,
) ![]const u8 {
    const status = rate(result.passed, elapsed_ms, attempt.target_seconds, attempt.warning_seconds);
    const progress_path = try std.fs.path.join(
        allocator,
        &.{ root_path, attempt.category(), attempt.topic(), "progress" },
    );
    defer allocator.free(progress_path);
    try Io.Dir.cwd().createDirPath(io, progress_path);

    const snapshots_path = try std.fs.path.join(allocator, &.{ progress_path, "attempts" });
    defer allocator.free(snapshots_path);
    try Io.Dir.cwd().createDirPath(io, snapshots_path);
    const snapshot_filename = try std.fmt.allocPrint(allocator, "{s}.cpp", .{attempt.id()});
    defer allocator.free(snapshot_filename);
    const snapshot_path = try std.fs.path.join(allocator, &.{ snapshots_path, snapshot_filename });
    defer allocator.free(snapshot_path);
    const workspace_path = try std.fs.path.join(allocator, &.{ root_path, attempt.category(), attempt.topic(), "workspace", "attempt.cpp" });
    defer allocator.free(workspace_path);
    const source = try Io.Dir.cwd().readFileAlloc(io, workspace_path, allocator, .limited(1024 * 1024));
    defer allocator.free(source);
    try Io.Dir.cwd().writeFile(io, .{ .sub_path = snapshot_path, .data = source });

    var line_output: Io.Writer.Allocating = .init(allocator);
    defer line_output.deinit();
    var json: std.json.Stringify = .{ .writer = &line_output.writer, .options = .{} };
    try json.beginObject();
    try json.objectField("id");
    try json.write(attempt.id());
    try json.objectField("language");
    try json.write(attempt.language());
    try json.objectField("elapsed_ms");
    try json.write(elapsed_ms);
    try json.objectField("runtime_ms");
    try json.write(result.runtime_ms);
    try json.objectField("peak_memory_bytes");
    try json.write(result.peak_memory_bytes);
    try json.objectField("source_saved");
    try json.write(true);
    try json.objectField("reference_viewed");
    try json.write(attempt.reference_viewed);
    try json.objectField("result");
    try json.write(if (result.passed) "passed" else "failed");
    try json.objectField("status");
    try json.write(status);
    try json.objectField("phase");
    try json.write(@tagName(result.phase));
    try json.endObject();
    try line_output.writer.writeByte('\n');

    const history_path = try std.fs.path.join(allocator, &.{ progress_path, "attempts.ndjson" });
    defer allocator.free(history_path);
    const existing = Io.Dir.cwd().readFileAlloc(io, history_path, allocator, .limited(16 * 1024 * 1024)) catch |err| switch (err) {
        error.FileNotFound => try allocator.alloc(u8, 0),
        else => return err,
    };
    defer allocator.free(existing);
    var history: Io.Writer.Allocating = try .initCapacity(allocator, existing.len + line_output.written().len);
    defer history.deinit();
    try history.writer.writeAll(existing);
    try history.writer.writeAll(line_output.written());
    try Io.Dir.cwd().writeFile(io, .{ .sub_path = history_path, .data = history.written() });

    var summary: Io.Writer.Allocating = .init(allocator);
    defer summary.deinit();
    var summary_json: std.json.Stringify = .{ .writer = &summary.writer, .options = .{ .whitespace = .indent_2 } };
    try summary_json.beginObject();
    try summary_json.objectField("latest_attempt_id");
    try summary_json.write(attempt.id());
    try summary_json.objectField("language");
    try summary_json.write(attempt.language());
    try summary_json.objectField("elapsed_ms");
    try summary_json.write(elapsed_ms);
    try summary_json.objectField("runtime_ms");
    try summary_json.write(result.runtime_ms);
    try summary_json.objectField("peak_memory_bytes");
    try summary_json.write(result.peak_memory_bytes);
    try summary_json.objectField("passed");
    try summary_json.write(result.passed);
    try summary_json.objectField("status");
    try summary_json.write(status);
    try summary_json.objectField("reference_viewed");
    try summary_json.write(attempt.reference_viewed);
    try summary_json.endObject();
    const summary_path = try std.fs.path.join(allocator, &.{ progress_path, "summary.json" });
    defer allocator.free(summary_path);
    try Io.Dir.cwd().writeFile(io, .{ .sub_path = summary_path, .data = summary.written() });
    return status;
}

pub fn rate(passed: bool, elapsed_ms: i64, target_seconds: u32, warning_seconds: u32) []const u8 {
    if (!passed) return "red";
    if (elapsed_ms <= @as(i64, target_seconds) * 1000) return "green";
    if (elapsed_ms <= @as(i64, warning_seconds) * 1000) return "yellow";
    return "red";
}

fn termSucceeded(term: std.process.Child.Term) bool {
    return switch (term) {
        .exited => |code| code == 0,
        else => false,
    };
}

test "attempt ratings respect thresholds" {
    try std.testing.expectEqualStrings("red", rate(false, 10, 300, 450));
    try std.testing.expectEqualStrings("green", rate(true, 300_000, 300, 450));
    try std.testing.expectEqualStrings("yellow", rate(true, 300_001, 300, 450));
    try std.testing.expectEqualStrings("red", rate(true, 450_001, 300, 450));
}

test "measured process reports runtime and peak memory" {
    const result = try runMeasured(std.testing.allocator, std.testing.io, &.{"/usr/bin/true"});
    defer std.testing.allocator.free(result.stdout);
    defer std.testing.allocator.free(result.stderr);

    try std.testing.expect(termSucceeded(result.term));
    try std.testing.expect(result.runtime_ms >= 0);
    try std.testing.expect((result.peak_memory_bytes orelse 0) > 0);
}
