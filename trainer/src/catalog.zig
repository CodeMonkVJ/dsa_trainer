const std = @import("std");
const Io = std.Io;

pub const TopicMetadata = struct {
    schema_version: u32,
    name: []const u8,
    description: []const u8,
    difficulty: []const u8,
    languages: []const []const u8,
    target_seconds: u32,
    warning_seconds: u32,
    tags: []const []const u8,
};

const ProgressSummary = struct {
    status: []const u8,
    elapsed_ms: ?i64 = null,
    runtime_ms: ?i64 = null,
    peak_memory_bytes: ?u64 = null,
    passed: ?bool = null,
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
    const metadata_path = try std.fs.path.join(allocator, &.{ topic_id, "topic.json" });
    defer allocator.free(metadata_path);
    const bytes = category_dir.readFileAlloc(io, metadata_path, allocator, .limited(128 * 1024)) catch |err| {
        try writeInvalidTopic(json, category_id, topic_id, @errorName(err));
        return;
    };
    defer allocator.free(bytes);

    var parsed = std.json.parseFromSlice(TopicMetadata, allocator, bytes, .{}) catch |err| {
        try writeInvalidTopic(json, category_id, topic_id, @errorName(err));
        return;
    };
    defer parsed.deinit();
    const metadata = parsed.value;

    if (metadata.schema_version != 1 or metadata.target_seconds > metadata.warning_seconds) {
        try writeInvalidTopic(json, category_id, topic_id, "invalid_metadata");
        return;
    }

    var status: []const u8 = "gray";
    const summary_path = try std.fs.path.join(allocator, &.{ topic_id, "progress", "summary.json" });
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
            );
            return;
        } else |_| {}
    } else |_| {}
    try writeValidTopic(json, topic_id, category_id, metadata, status, null, null, null, null);
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
) !void {
    try json.beginObject();
    try json.objectField("id");
    try json.write(topic_id);
    try json.objectField("category");
    try json.write(category_id);
    try json.objectField("name");
    try json.write(metadata.name);
    try json.objectField("description");
    try json.write(metadata.description);
    try json.objectField("difficulty");
    try json.write(metadata.difficulty);
    try json.objectField("languages");
    try json.write(metadata.languages);
    try json.objectField("target_seconds");
    try json.write(metadata.target_seconds);
    try json.objectField("warning_seconds");
    try json.write(metadata.warning_seconds);
    try json.objectField("tags");
    try json.write(metadata.tags);
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
