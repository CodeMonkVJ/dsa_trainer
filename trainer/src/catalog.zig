const std = @import("std");
const Io = std.Io;

pub const TopicMetadata = struct {
    schema_version: u32,
    name: []const u8,
    description: []const u8,
    difficulty: []const u8,
    languages: []const []const u8,
    green_seconds: u32,
    yellow_seconds: u32,
    tags: []const []const u8,
};

const ProgressSummary = struct {
    status: []const u8,
    elapsed_ms: ?i64 = null,
    runtime_ms: ?i64 = null,
    peak_memory_bytes: ?u64 = null,
    passed: ?bool = null,
};

const ProblemProgress = struct {
    solved: bool,
    status: []const u8,
    attempted: bool = false,
};

pub fn writeCatalog(
    allocator: std.mem.Allocator,
    io: Io,
    root_path: []const u8,
    output: *Io.Writer,
) !void {
    var json: std.json.Stringify = .{ .writer = output, .options = .{} };
    try json.beginObject();
    try json.objectField("categories");
    try json.beginArray();

    inline for (.{
        .{ "algos", "Algorithms" },
        .{ "data-structures", "Data Structures" },
        .{ "systems", "Low Level Coding" },
    }) |category| {
        try writeCategory(allocator, io, root_path, category[0], category[1], &json);
    }

    try json.endArray();
    try json.endObject();
}

fn writeCategory(
    allocator: std.mem.Allocator,
    io: Io,
    root_path: []const u8,
    id: []const u8,
    name: []const u8,
    json: *std.json.Stringify,
) !void {
    try json.beginObject();
    try json.objectField("id");
    try json.write(id);
    try json.objectField("name");
    try json.write(name);
    try json.objectField("topics");
    try json.beginArray();

    const category_path = try std.fs.path.join(allocator, &.{ root_path, id });
    defer allocator.free(category_path);

    var category_dir = Io.Dir.openDirAbsolute(io, category_path, .{ .iterate = true }) catch |err| {
        try writeCatalogError(json, id, @errorName(err));
        try json.endArray();
        try json.endObject();
        return;
    };
    defer category_dir.close(io);

    var iterator = category_dir.iterate();
    while (try iterator.next(io)) |entry| {
        if (entry.kind != .directory or !validId(entry.name)) continue;
        if (std.mem.eql(u8, id, "data-structures") and std.mem.eql(u8, entry.name, "treeMisc")) continue;
        try writeTopic(allocator, io, category_dir, id, entry.name, json);
    }

    try json.endArray();
    try json.endObject();
}

fn writeTopic(
    allocator: std.mem.Allocator,
    io: Io,
    category_dir: Io.Dir,
    category_id: []const u8,
    topic_id: []const u8,
    json: *std.json.Stringify,
) !void {
    const metadata_path = try std.fs.path.join(allocator, &.{ topic_id, "problems", "base", "topic.json" });
    defer allocator.free(metadata_path);
    const bytes = category_dir.readFileAlloc(io, metadata_path, allocator, .limited(128 * 1024)) catch |err| switch (err) {
        error.FileNotFound => return,
        else => {
            try writeInvalidTopic(json, category_id, topic_id, @errorName(err));
            return;
        },
    };
    defer allocator.free(bytes);

    var parsed = std.json.parseFromSlice(TopicMetadata, allocator, bytes, .{}) catch |err| {
        try writeInvalidTopic(json, category_id, topic_id, @errorName(err));
        return;
    };
    defer parsed.deinit();
    const metadata = parsed.value;

    if (metadata.schema_version != 1 or metadata.green_seconds > metadata.yellow_seconds) {
        try writeInvalidTopic(json, category_id, topic_id, "invalid_metadata");
        return;
    }

    var status: []const u8 = "gray";
    const summary_path = try std.fs.path.join(allocator, &.{ topic_id, "problems", "base", "progress", "summary.json" });
    defer allocator.free(summary_path);
    if (category_dir.readFileAlloc(io, summary_path, allocator, .limited(128 * 1024))) |summary_bytes| {
        defer allocator.free(summary_bytes);
        if (std.json.parseFromSlice(ProgressSummary, allocator, summary_bytes, .{ .ignore_unknown_fields = true })) |summary| {
            defer summary.deinit();
            if (std.mem.eql(u8, summary.value.status, "green") or
                std.mem.eql(u8, summary.value.status, "yellow") or
                std.mem.eql(u8, summary.value.status, "red"))
            {
                status = summary.value.status;
            }
            try writeValidTopic(
                json,
                topic_id,
                category_id,
                metadata,
                status,
                summary.value.elapsed_ms,
                summary.value.runtime_ms,
                summary.value.peak_memory_bytes,
                summary.value.passed,
                allocator,
                io,
                category_dir,
                topic_id,
            );
            return;
        } else |_| {}
    } else |_| {}
    try writeValidTopic(json, topic_id, category_id, metadata, status, null, null, null, null, allocator, io, category_dir, topic_id);
}

fn writeValidTopic(
    json: *std.json.Stringify,
    topic_id: []const u8,
    category_id: []const u8,
    metadata: TopicMetadata,
    status: []const u8,
    elapsed_ms: ?i64,
    runtime_ms: ?i64,
    peak_memory_bytes: ?u64,
    passed: ?bool,
    allocator: std.mem.Allocator,
    io: Io,
    category_dir: Io.Dir,
    group_id: []const u8,
) !void {
    try json.beginObject();
    try json.objectField("id");
    try json.write(topic_id);
    try json.objectField("category");
    try json.write(category_id);
    try json.objectField("name");
    if (std.mem.eql(u8, category_id, "systems") and std.mem.eql(u8, group_id, "design")) {
        try json.write("Systems Design");
    } else if (std.mem.eql(u8, category_id, "systems") and std.mem.eql(u8, group_id, "rtos")) {
        try json.write("RTOS Practice");
    } else if (std.mem.eql(u8, group_id, "greedy")) {
        try json.write("Greedy");
    } else if (std.mem.eql(u8, group_id, "recursion")) {
        try json.write("Recursion and Backtracking");
    } else if (std.mem.eql(u8, group_id, "stackQueue")) {
        try json.write("Stack and Queue");
    } else if (std.mem.eql(u8, group_id, "strings")) {
        try json.write("Strings");
    } else if (std.mem.eql(u8, group_id, "binaryTree")) {
        try json.write("Binary Tree");
    } else if (std.mem.eql(u8, group_id, "graphs")) {
        try json.write("Graphs");
    } else if (std.mem.eql(u8, group_id, "dynamic_programming")) {
        try json.write("Dynamic Programming");
    } else if (std.mem.eql(u8, group_id, "linkedList")) {
        try json.write("Linked Lists");
    } else {
        try json.write(metadata.name);
    }
    try json.objectField("description");
    try json.write(if (std.mem.eql(u8, category_id, "systems") and std.mem.eql(u8, group_id, "design")) "Practice interrupt pipelines, driver APIs, and firmware update architecture with self-review." else if (std.mem.eql(u8, category_id, "systems") and std.mem.eql(u8, group_id, "rtos")) "Practice FreeRTOS scheduling and synchronization on Linux x86, with real POSIX-port harnesses." else metadata.description);
    try json.objectField("difficulty");
    try json.write(metadata.difficulty);
    try json.objectField("languages");
    try json.write(metadata.languages);
    try json.objectField("target_seconds");
    try json.write(metadata.green_seconds);
    try json.objectField("warning_seconds");
    try json.write(metadata.yellow_seconds);
    try json.objectField("green_seconds");
    try json.write(metadata.green_seconds);
    try json.objectField("yellow_seconds");
    try json.write(metadata.yellow_seconds);
    try json.objectField("tags");
    try json.write(metadata.tags);
    try json.objectField("problems");
    try json.beginArray();
    var problem_count: u32 = 0;
    var solved_count: u32 = 0;
    const base_progress = problemProgress(allocator, io, category_dir, group_id, "base");
    problem_count += 1;
    if (base_progress.solved) solved_count += 1;
    try json.beginObject();
    try json.objectField("id");
    try json.write("base");
    try json.objectField("name");
    try json.write(if (std.mem.eql(u8, category_id, "systems") and (std.mem.eql(u8, group_id, "design") or std.mem.eql(u8, group_id, "rtos"))) metadata.name else "Base implementation");
    try json.objectField("languages");
    try json.write(metadata.languages);
    try json.objectField("description");
    try json.write(metadata.description);
    try json.objectField("difficulty");
    try json.write(metadata.difficulty);
    try json.objectField("solved");
    try json.write(base_progress.solved);
    try json.objectField("attempted");
    try json.write(base_progress.attempted);
    try json.objectField("status");
    try json.write(base_progress.status);
    try json.endObject();
    const problems_path = try std.fs.path.join(allocator, &.{ group_id, "problems" });
    defer allocator.free(problems_path);
    var problems_dir = category_dir.openDir(io, problems_path, .{ .iterate = true }) catch {
        try json.endArray();
        try json.endObject();
        return;
    };
    defer problems_dir.close(io);
    var iterator = problems_dir.iterate();
    while (try iterator.next(io)) |entry| {
        if (entry.kind != .directory or !validId(entry.name) or std.mem.eql(u8, entry.name, "base")) continue;
        if (std.mem.eql(u8, group_id, "dynamic_programming") and
            (std.mem.eql(u8, entry.name, "distinct_subsequences") or
                std.mem.eql(u8, entry.name, "partition_equal") or
                std.mem.eql(u8, entry.name, "stock_buy_sell") or
                std.mem.eql(u8, entry.name, "wildcard_matching"))) continue;
        if (std.mem.eql(u8, group_id, "trie") and std.mem.eql(u8, entry.name, "word_break")) continue;
        const progress = problemProgress(allocator, io, category_dir, group_id, entry.name);
        problem_count += 1;
        if (progress.solved) solved_count += 1;
        try writeProblemRef(allocator, io, problems_dir, entry.name, progress, json);
    }
    try json.endArray();
    try json.objectField("solved_count");
    try json.write(solved_count);
    try json.objectField("problem_count");
    try json.write(problem_count);
    try json.objectField("status");
    try json.write(status);
    try json.objectField("elapsed_ms");
    try json.write(elapsed_ms);
    try json.objectField("runtime_ms");
    try json.write(runtime_ms);
    try json.objectField("peak_memory_bytes");
    try json.write(peak_memory_bytes);
    try json.objectField("passed");
    try json.write(passed);
    try json.endObject();
}

fn writeProblemRef(allocator: std.mem.Allocator, io: Io, problems_dir: Io.Dir, problem_id: []const u8, progress: ProblemProgress, json: *std.json.Stringify) !void {
    const metadata_path = try std.fs.path.join(allocator, &.{ problem_id, "topic.json" });
    defer allocator.free(metadata_path);
    const bytes = problems_dir.readFileAlloc(io, metadata_path, allocator, .limited(128 * 1024)) catch return;
    defer allocator.free(bytes);
    var parsed = std.json.parseFromSlice(TopicMetadata, allocator, bytes, .{}) catch return;
    defer parsed.deinit();
    const metadata = parsed.value;
    if (metadata.schema_version != 1 or metadata.green_seconds > metadata.yellow_seconds) return;
    try json.beginObject();
    try json.objectField("id");
    try json.write(problem_id);
    try json.objectField("languages");
    try json.write(metadata.languages);
    try json.objectField("name");
    try json.write(metadata.name);
    try json.objectField("description");
    try json.write(metadata.description);
    try json.objectField("difficulty");
    try json.write(metadata.difficulty);
    try json.objectField("solved");
    try json.write(progress.solved);
    try json.objectField("attempted");
    try json.write(progress.attempted);
    try json.objectField("status");
    try json.write(progress.status);
    try json.objectField("green_seconds");
    try json.write(metadata.green_seconds);
    try json.objectField("yellow_seconds");
    try json.write(metadata.yellow_seconds);
    try json.endObject();
}

fn problemProgress(allocator: std.mem.Allocator, io: Io, category_dir: Io.Dir, group_id: []const u8, problem_id: []const u8) ProblemProgress {
    var empty = ProblemProgress{ .solved = false, .status = "gray" };
    // Starting any attempt creates a workspace, even if it is later canceled
    // or never submitted. A solved-only summary misses those attempts.
    for ([_][]const u8{ "attempt.c", "attempt.cpp", "attempt.md" }) |filename| {
        const path = std.fs.path.join(allocator, &.{ group_id, "problems", problem_id, "workspace", filename }) catch continue;
        defer allocator.free(path);
        if (category_dir.openFile(io, path, .{})) |file| {
            file.close(io);
            empty.attempted = true;
        } else |_| {}
    }
    const summary_path = std.fs.path.join(allocator, &.{ group_id, "problems", problem_id, "progress", "summary.json" }) catch return empty;
    defer allocator.free(summary_path);
    const bytes = category_dir.readFileAlloc(io, summary_path, allocator, .limited(128 * 1024)) catch return empty;
    defer allocator.free(bytes);
    var parsed = std.json.parseFromSlice(ProgressSummary, allocator, bytes, .{ .ignore_unknown_fields = true }) catch return empty;
    defer parsed.deinit();
    const status = if (std.mem.eql(u8, parsed.value.status, "green")) "green" else if (std.mem.eql(u8, parsed.value.status, "yellow")) "yellow" else if (std.mem.eql(u8, parsed.value.status, "red")) "red" else "gray";
    return .{ .solved = parsed.value.passed orelse false, .status = status, .attempted = true };
}

fn writeInvalidTopic(
    json: *std.json.Stringify,
    category: []const u8,
    topic: []const u8,
    message: []const u8,
) !void {
    try json.beginObject();
    try json.objectField("id");
    try json.write(topic);
    try json.objectField("category");
    try json.write(category);
    try json.objectField("invalid");
    try json.write(true);
    try json.objectField("error");
    try json.write(message);
    try json.endObject();
}

fn writeCatalogError(json: *std.json.Stringify, category: []const u8, message: []const u8) !void {
    try writeInvalidTopic(json, category, "_catalog", message);
}

pub fn validId(value: []const u8) bool {
    if (value.len == 0 or value.len > 80) return false;
    for (value) |char| {
        if (!std.ascii.isAlphanumeric(char) and char != '-' and char != '_') return false;
    }
    return true;
}

test "topic identifiers reject traversal" {
    try std.testing.expect(validId("binary_search"));
    try std.testing.expect(validId("binarySearchTree"));
    try std.testing.expect(!validId("../binary_search"));
    try std.testing.expect(!validId("has space"));
    try std.testing.expect(!validId(""));
}

test "attempted includes unsubmitted C and C++ workspaces and saved summaries" {
    var tmp = std.testing.tmpDir(.{});
    defer tmp.cleanup();
    const io = std.testing.io;
    const allocator = std.testing.allocator;
    const fresh = problemProgress(allocator, io, tmp.dir, "group", "fresh");
    try std.testing.expect(!fresh.attempted and !fresh.solved);
    inline for (.{ "attempt.c", "attempt.cpp", "attempt.md" }) |filename| {
        const directory = "group/problems/" ++ filename ++ "/workspace";
        try tmp.dir.createDirPath(io, directory);
        try tmp.dir.writeFile(io, .{ .sub_path = directory ++ "/" ++ filename, .data = "" });
        const progress = problemProgress(allocator, io, tmp.dir, "group", filename);
        try std.testing.expect(progress.attempted and !progress.solved);
    }
    try tmp.dir.createDirPath(io, "group/problems/saved/progress");
    try tmp.dir.writeFile(io, .{
        .sub_path = "group/problems/saved/progress/summary.json",
        .data = "{\"status\":\"red\",\"passed\":false}",
    });
    const failed = problemProgress(allocator, io, tmp.dir, "group", "saved");
    try std.testing.expect(failed.attempted and !failed.solved);
}
