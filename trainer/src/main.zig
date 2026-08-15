const std = @import("std");
const Io = std.Io;
const catalog = @import("catalog.zig");
const attempts = @import("attempts.zig");
const runner = @import("runner.zig");
const session = @import("session.zig");

const App = struct {
    allocator: std.mem.Allocator,
    io: Io,
    root_path: []const u8,
    trainer_path: []const u8,
    attempt_store: attempts.Store = .{},
};

pub fn main(init: std.process.Init) !void {
    const allocator = init.gpa;
    const arena = init.arena.allocator();
    const io = init.io;

    const args = try init.minimal.args.toSlice(arena);
    const requested_root = if (args.len > 1) args[1] else "..";
    const port = if (args.len > 2) try std.fmt.parseInt(u16, args[2], 10) else 8080;
    const requested_trainer = if (args.len > 3) args[3] else try std.fs.path.join(arena, &.{ requested_root, "trainer" });
    const bind_host = if (args.len > 4) args[4] else "127.0.0.1";
    const root_path = try Io.Dir.cwd().realPathFileAlloc(io, requested_root, arena);
    const trainer_path = try Io.Dir.cwd().realPathFileAlloc(io, requested_trainer, arena);

    var app: App = .{
        .allocator = allocator,
        .io = io,
        .root_path = root_path,
        .trainer_path = trainer_path,
    };

    const address = Io.net.IpAddress.parse(bind_host, port) catch unreachable;
    var http_server = try address.listen(io, .{ .reuse_address = true });
    defer http_server.deinit(io);

    std.debug.print("DSA trainer: http://127.0.0.1:{d}\n", .{port});
    std.debug.print("DSA root: {s}\n", .{root_path});
    std.debug.print("Trainer: {s}\n", .{trainer_path});

    var group: Io.Group = .init;
    defer group.cancel(io);
    while (true) {
        const stream = try http_server.accept(io);
        group.async(io, acceptConnection, .{ &app, stream });
    }
}

fn acceptConnection(app: *App, stream: Io.net.Stream) void {
    defer stream.close(app.io);

    var receive_buffer: [16 * 1024]u8 = undefined;
    var send_buffer: [16 * 1024]u8 = undefined;
    var connection_reader = stream.reader(app.io, &receive_buffer);
    var connection_writer = stream.writer(app.io, &send_buffer);
    var server = std.http.Server.init(&connection_reader.interface, &connection_writer.interface);

    while (server.reader.state == .ready) {
        var request = server.receiveHead() catch return;
        serveRequest(app, &request) catch |err| {
            std.log.err("request {s} failed: {t}", .{ request.head.target, err });
            return;
        };
    }
}

fn serveRequest(app: *App, request: *std.http.Server.Request) !void {
    const target = request.head.target;
    if (request.head.method == .GET and std.mem.eql(u8, target, "/api/health")) {
        return respondJson(request, "{\"ok\":true}", .ok);
    }
    if (request.head.method == .GET and std.mem.eql(u8, target, "/api/catalog")) {
        var output: Io.Writer.Allocating = .init(app.allocator);
        defer output.deinit();
        try catalog.writeCatalog(app.allocator, app.io, app.root_path, &output.writer);
        return respondJson(request, output.written(), .ok);
    }
    if (request.head.method == .GET and std.mem.startsWith(u8, target, "/ws/attempts/")) {
        return serveTerminal(app, request);
    }
    if (std.mem.startsWith(u8, target, "/api/topics/")) {
        return serveTopicRoute(app, request);
    }
    if (std.mem.startsWith(u8, target, "/api/attempts/")) {
        return serveAttemptRoute(app, request);
    }
    if (request.head.method == .GET and std.mem.eql(u8, target, "/")) {
        return respondFile(app, request, "web/index.html", "text/html; charset=utf-8");
    }
    if (request.head.method == .GET and std.mem.eql(u8, target, "/styles.css")) {
        return respondFile(app, request, "web/styles.css", "text/css; charset=utf-8");
    }
    if (request.head.method == .GET and std.mem.eql(u8, target, "/dist/app.js")) {
        return respondFile(app, request, "web/dist/app.js", "text/javascript; charset=utf-8");
    }
    if (request.head.method == .GET and std.mem.eql(u8, target, "/dist/xterm.css")) {
        return respondFile(app, request, "web/dist/xterm.css", "text/css; charset=utf-8");
    }
    return respondJson(request, "{\"error\":\"not_found\"}", .not_found);
}

fn serveTopicRoute(app: *App, request: *std.http.Server.Request) !void {
    const suffix = request.head.target["/api/topics/".len..];
    var parts = std.mem.splitScalar(u8, suffix, '/');
    const category_id = parts.next() orelse return respondApiError(request, .bad_request, "invalid_topic_path");
    const topic_id = parts.next() orelse return respondApiError(request, .bad_request, "invalid_topic_path");
    const action = parts.next();
    const modifier = parts.next();
    const source_attempt_id = parts.next();
    if (parts.next() != null or !validTopic(category_id, topic_id)) {
        return respondApiError(request, .bad_request, "invalid_topic_path");
    }

    if (request.head.method == .GET and action == null and modifier == null and source_attempt_id == null) {
        return serveTopicDetails(app, request, category_id, topic_id);
    }
    if (request.head.method == .POST and action != null and std.mem.eql(u8, action.?, "attempts")) {
        if (modifier == null and source_attempt_id == null) {
            return startAttempt(app, request, category_id, topic_id, null);
        }
        if (modifier != null and std.mem.eql(u8, modifier.?, "from") and source_attempt_id != null and
            catalog.validId(source_attempt_id.?))
        {
            return startAttempt(app, request, category_id, topic_id, source_attempt_id.?);
        }
    }
    return respondApiError(request, .not_found, "not_found");
}

fn serveAttemptRoute(app: *App, request: *std.http.Server.Request) !void {
    const suffix = request.head.target["/api/attempts/".len..];
    var parts = std.mem.splitScalar(u8, suffix, '/');
    const attempt_id = parts.next() orelse return respondApiError(request, .bad_request, "invalid_attempt_path");
    const action = parts.next();
    if (parts.next() != null or !catalog.validId(attempt_id)) {
        return respondApiError(request, .bad_request, "invalid_attempt_path");
    }

    if (request.head.method == .GET and action == null) {
        const attempt = app.attempt_store.get(app.io, attempt_id) orelse
            return respondApiError(request, .not_found, "attempt_not_found");
        const editor_state = session.editorState(app.allocator, app.io, &attempt) catch .not_started;
        return respondAttempt(app, request, &attempt, @tagName(editor_state));
    }
    if (request.head.method == .POST and action != null and std.mem.eql(u8, action.?, "run")) {
        return runAttempt(app, request, attempt_id, false);
    }
    if (request.head.method == .POST and action != null and std.mem.eql(u8, action.?, "submit")) {
        return runAttempt(app, request, attempt_id, true);
    }
    if (request.head.method == .POST and action != null and std.mem.eql(u8, action.?, "cancel")) {
        const attempt = app.attempt_store.finish(app.io, attempt_id, .canceled) catch
            return respondApiError(request, .conflict, "attempt_not_active");
        session.terminate(app.allocator, app.io, &attempt) catch |err|
            std.log.warn("failed to terminate canceled editor session: {t}", .{err});
        return respondAttempt(app, request, &attempt, "unknown");
    }
    if (request.head.method == .POST and action != null and std.mem.eql(u8, action.?, "reveal")) {
        return revealReference(app, request, attempt_id);
    }
    return respondApiError(request, .not_found, "not_found");
}

fn revealReference(app: *App, request: *std.http.Server.Request, attempt_id: []const u8) !void {
    const attempt = app.attempt_store.reveal(app.io, attempt_id) catch |err| switch (err) {
        error.AttemptNotFound => return respondApiError(request, .not_found, "attempt_not_found"),
        error.AttemptAlreadyFinished => return respondApiError(request, .conflict, "attempt_not_active"),
        error.RevealLocked => return respondApiError(request, .forbidden, "reveal_locked_until_15_minutes"),
    };
    const topic_path = try checkedTopicPath(app, attempt.category(), attempt.topic());
    defer app.allocator.free(topic_path);
    const implementation_path = try std.fs.path.join(app.allocator, &.{ topic_path, "implementation.cpp" });
    defer app.allocator.free(implementation_path);
    const implementation = Io.Dir.cwd().readFileAlloc(
        app.io,
        implementation_path,
        app.allocator,
        .limited(1024 * 1024),
    ) catch return respondApiError(request, .not_found, "reference_not_available");
    defer app.allocator.free(implementation);

    var output: Io.Writer.Allocating = .init(app.allocator);
    defer output.deinit();
    var json: std.json.Stringify = .{ .writer = &output.writer, .options = .{} };
    try json.beginObject();
    try json.objectField("hint");
    try json.write("Start from the required interface in the prompt. Write down the invariant your loop or data structure must preserve, then test the smallest boundary cases before optimizing.");
    try json.objectField("implementation");
    try json.write(implementation);
    try json.objectField("reference_viewed");
    try json.write(attempt.reference_viewed);
    try json.objectField("elapsed_ms");
    try json.write(attempt.elapsedMs(app.io));
    try json.endObject();
    return respondJson(request, output.written(), .ok);
}

fn serveTerminal(app: *App, request: *std.http.Server.Request) !void {
    const attempt_id = request.head.target["/ws/attempts/".len..];
    if (!catalog.validId(attempt_id)) return respondApiError(request, .bad_request, "invalid_attempt_id");
    const attempt = app.attempt_store.get(app.io, attempt_id) orelse
        return respondApiError(request, .not_found, "attempt_not_found");
    if (attempt.state != .active) return respondApiError(request, .conflict, "attempt_not_active");

    const upgrade_key = switch (request.upgradeRequested()) {
        .websocket => |key| key orelse return respondApiError(request, .bad_request, "missing_websocket_key"),
        else => return respondApiError(request, .bad_request, "websocket_required"),
    };

    var terminal = session.open(app.allocator, app.io, app.root_path, app.trainer_path, &attempt, 120, 36) catch |err| {
        std.log.err("terminal session failed: {t}", .{err});
        return respondApiError(request, .internal_server_error, "terminal_start_failed");
    };
    errdefer terminal.close();

    var websocket = try request.respondWebSocket(.{ .key = upgrade_key });
    try websocket.flush();

    const output_thread = try std.Thread.spawn(.{}, streamTerminalOutput, .{ &terminal, &websocket });
    while (true) {
        const message = websocket.readSmallMessage() catch break;
        switch (message.opcode) {
            .binary => terminal.write(message.data) catch break,
            .text => handleTerminalControl(&terminal, message.data) catch {},
            .ping, .pong => {},
            else => break,
        }
    }

    terminal.disconnect();
    output_thread.join();
    terminal.reap();
}

fn streamTerminalOutput(terminal: *session.Terminal, websocket: *std.http.Server.WebSocket) void {
    var buffer: [16 * 1024]u8 = undefined;
    while (true) {
        const count = terminal.read(&buffer) catch return;
        if (count == 0) return;
        websocket.writeMessage(buffer[0..count], .binary) catch return;
    }
}

fn handleTerminalControl(terminal: *session.Terminal, message: []const u8) !void {
    if (!std.mem.startsWith(u8, message, "resize:")) return;
    var values = std.mem.splitScalar(u8, message["resize:".len..], ':');
    const columns = try std.fmt.parseInt(u16, values.next() orelse return error.InvalidResize, 10);
    const rows = try std.fmt.parseInt(u16, values.next() orelse return error.InvalidResize, 10);
    if (values.next() != null) return error.InvalidResize;
    try terminal.resize(columns, rows);
}

fn serveTopicDetails(
    app: *App,
    request: *std.http.Server.Request,
    category_id: []const u8,
    topic_id: []const u8,
) !void {
    const topic_path = try checkedTopicPath(app, category_id, topic_id);
    defer app.allocator.free(topic_path);
    const metadata_path = try std.fs.path.join(app.allocator, &.{ topic_path, "topic.json" });
    defer app.allocator.free(metadata_path);
    const prompt_path = try std.fs.path.join(app.allocator, &.{ topic_path, "prompt.md" });
    defer app.allocator.free(prompt_path);
    const metadata_bytes = Io.Dir.cwd().readFileAlloc(app.io, metadata_path, app.allocator, .limited(128 * 1024)) catch
        return respondApiError(request, .not_found, "topic_not_ready");
    defer app.allocator.free(metadata_bytes);
    const prompt = Io.Dir.cwd().readFileAlloc(app.io, prompt_path, app.allocator, .limited(512 * 1024)) catch
        return respondApiError(request, .not_found, "topic_not_ready");
    defer app.allocator.free(prompt);
    var parsed = std.json.parseFromSlice(catalog.TopicMetadata, app.allocator, metadata_bytes, .{}) catch
        return respondApiError(request, .unprocessable_entity, "invalid_topic_metadata");
    defer parsed.deinit();

    var output: Io.Writer.Allocating = .init(app.allocator);
    defer output.deinit();
    var json: std.json.Stringify = .{ .writer = &output.writer, .options = .{} };
    try json.beginObject();
    try json.objectField("id");
    try json.write(topic_id);
    try json.objectField("category");
    try json.write(category_id);
    try json.objectField("metadata");
    try json.write(parsed.value);
    try json.objectField("prompt");
    try json.write(prompt);
    try json.objectField("history");
    try writeAttemptHistory(app, topic_path, &json);
    try json.objectField("active_attempt");
    if (app.attempt_store.current(app.io)) |active| {
        try json.beginObject();
        try json.objectField("id");
        try json.write(active.id());
        try json.objectField("category");
        try json.write(active.category());
        try json.objectField("topic");
        try json.write(active.topic());
        try json.objectField("state");
        try json.write(@tagName(active.state));
        try json.endObject();
    } else {
        const no_active: ?u8 = null;
        try json.write(no_active);
    }
    try json.endObject();
    return respondJson(request, output.written(), .ok);
}

fn writeAttemptHistory(app: *App, topic_path: []const u8, json: *std.json.Stringify) !void {
    try json.beginArray();
    const history_path = try std.fs.path.join(app.allocator, &.{ topic_path, "progress", "attempts.ndjson" });
    defer app.allocator.free(history_path);
    const history = Io.Dir.cwd().readFileAlloc(
        app.io,
        history_path,
        app.allocator,
        .limited(16 * 1024 * 1024),
    ) catch |err| switch (err) {
        error.FileNotFound => {
            try json.endArray();
            return;
        },
        else => return err,
    };
    defer app.allocator.free(history);

    var lines = std.mem.splitScalar(u8, history, '\n');
    while (lines.next()) |line| {
        const trimmed = std.mem.trim(u8, line, " \t\r");
        if (trimmed.len == 0) continue;
        var parsed = std.json.parseFromSlice(std.json.Value, app.allocator, trimmed, .{}) catch |err| {
            std.log.warn("ignoring malformed attempt history entry: {t}", .{err});
            continue;
        };
        defer parsed.deinit();
        try json.write(parsed.value);
    }
    try json.endArray();
}

fn startAttempt(
    app: *App,
    request: *std.http.Server.Request,
    category_id: []const u8,
    topic_id: []const u8,
    source_attempt_id: ?[]const u8,
) !void {
    const topic_path = try checkedTopicPath(app, category_id, topic_id);
    defer app.allocator.free(topic_path);
    const metadata_path = try std.fs.path.join(app.allocator, &.{ topic_path, "topic.json" });
    defer app.allocator.free(metadata_path);
    const metadata_bytes = Io.Dir.cwd().readFileAlloc(app.io, metadata_path, app.allocator, .limited(128 * 1024)) catch
        return respondApiError(request, .not_found, "topic_not_ready");
    defer app.allocator.free(metadata_bytes);
    var parsed = std.json.parseFromSlice(catalog.TopicMetadata, app.allocator, metadata_bytes, .{}) catch
        return respondApiError(request, .unprocessable_entity, "invalid_topic_metadata");
    defer parsed.deinit();
    if (!containsString(parsed.value.languages, "cpp")) {
        return respondApiError(request, .unprocessable_entity, "cpp_not_supported");
    }

    const starter_path = try std.fs.path.join(app.allocator, &.{ topic_path, "starter.cpp" });
    defer app.allocator.free(starter_path);
    var previous_path: ?[]u8 = null;
    defer if (previous_path) |path| app.allocator.free(path);
    const source_path = if (source_attempt_id) |previous_id| blk: {
        const filename = try std.fmt.allocPrint(app.allocator, "{s}.cpp", .{previous_id});
        defer app.allocator.free(filename);
        previous_path = try std.fs.path.join(app.allocator, &.{ topic_path, "progress", "attempts", filename });
        break :blk previous_path.?;
    } else starter_path;
    const source = Io.Dir.cwd().readFileAlloc(app.io, source_path, app.allocator, .limited(1024 * 1024)) catch |err| switch (err) {
        error.FileNotFound => return respondApiError(
            request,
            .not_found,
            if (source_attempt_id != null) "previous_attempt_not_found" else "starter_not_found",
        ),
        else => return err,
    };
    defer app.allocator.free(source);
    const workspace_path = try std.fs.path.join(app.allocator, &.{ topic_path, "workspace" });
    defer app.allocator.free(workspace_path);
    try Io.Dir.cwd().createDirPath(app.io, workspace_path);
    const attempt_path = try std.fs.path.join(app.allocator, &.{ workspace_path, "attempt.cpp" });
    defer app.allocator.free(attempt_path);
    try Io.Dir.cwd().writeFile(app.io, .{ .sub_path = attempt_path, .data = source });

    const attempt = app.attempt_store.start(
        app.io,
        category_id,
        topic_id,
        "cpp",
        parsed.value.target_seconds,
        parsed.value.warning_seconds,
    ) catch |err| switch (err) {
        error.AttemptAlreadyActive => return respondApiError(request, .conflict, "attempt_already_active"),
        else => return err,
    };
    return respondAttempt(app, request, &attempt, "not_started");
}

fn runAttempt(app: *App, request: *std.http.Server.Request, attempt_id: []const u8, submit: bool) !void {
    const attempt = app.attempt_store.get(app.io, attempt_id) orelse
        return respondApiError(request, .not_found, "attempt_not_found");
    if (attempt.state != .active) return respondApiError(request, .conflict, "attempt_not_active");

    var result = runner.run(app.allocator, app.io, app.root_path, app.trainer_path, &attempt) catch |err| {
        std.log.err("runner failed: {t}", .{err});
        return respondApiError(request, .internal_server_error, "runner_failed");
    };
    defer result.deinit(app.allocator);
    const elapsed_ms = attempt.elapsedMs(app.io);
    var status: []const u8 = runner.rate(
        result.passed,
        elapsed_ms,
        attempt.target_seconds,
        attempt.warning_seconds,
    );
    if (submit) {
        if (!result.passed) {
            return respondApiError(request, .unprocessable_entity, "tests_not_passed");
        }
        status = try runner.persistResult(app.allocator, app.io, app.root_path, &attempt, &result, elapsed_ms);
        _ = app.attempt_store.finish(app.io, attempt_id, .submitted) catch {};
        session.terminate(app.allocator, app.io, &attempt) catch |err|
            std.log.warn("failed to terminate submitted editor session: {t}", .{err});
    }

    var output: Io.Writer.Allocating = .init(app.allocator);
    defer output.deinit();
    var json: std.json.Stringify = .{ .writer = &output.writer, .options = .{} };
    try json.beginObject();
    try json.objectField("passed");
    try json.write(result.passed);
    try json.objectField("phase");
    try json.write(@tagName(result.phase));
    try json.objectField("status");
    try json.write(status);
    try json.objectField("elapsed_ms");
    try json.write(elapsed_ms);
    try json.objectField("runtime_ms");
    try json.write(result.runtime_ms);
    try json.objectField("peak_memory_bytes");
    try json.write(result.peak_memory_bytes);
    try json.objectField("submitted");
    try json.write(submit);
    try json.objectField("stdout");
    try json.write(result.stdout);
    try json.objectField("stderr");
    try json.write(result.stderr);
    try json.endObject();
    return respondJson(request, output.written(), .ok);
}

fn respondAttempt(
    app: *App,
    request: *std.http.Server.Request,
    attempt: *const attempts.Attempt,
    editor_state: []const u8,
) !void {
    var output: Io.Writer.Allocating = .init(app.allocator);
    defer output.deinit();
    var json: std.json.Stringify = .{ .writer = &output.writer, .options = .{} };
    try json.beginObject();
    try json.objectField("id");
    try json.write(attempt.id());
    try json.objectField("category");
    try json.write(attempt.category());
    try json.objectField("topic");
    try json.write(attempt.topic());
    try json.objectField("language");
    try json.write(attempt.language());
    try json.objectField("state");
    try json.write(@tagName(attempt.state));
    try json.objectField("editor_state");
    try json.write(editor_state);
    try json.objectField("elapsed_ms");
    try json.write(attempt.elapsedMs(app.io));
    try json.objectField("target_seconds");
    try json.write(attempt.target_seconds);
    try json.objectField("warning_seconds");
    try json.write(attempt.warning_seconds);
    try json.objectField("reference_viewed");
    try json.write(attempt.reference_viewed);
    try json.objectField("reveal_available");
    try json.write(attempt.elapsedMs(app.io) >= @as(i64, attempts.reveal_seconds) * 1000);
    try json.endObject();
    return respondJson(request, output.written(), .ok);
}

fn checkedTopicPath(app: *App, category_id: []const u8, topic_id: []const u8) ![:0]u8 {
    if (!validTopic(category_id, topic_id)) return error.InvalidTopic;
    const unresolved = try std.fs.path.join(app.allocator, &.{ app.root_path, category_id, topic_id });
    defer app.allocator.free(unresolved);
    const resolved = try Io.Dir.cwd().realPathFileAlloc(app.io, unresolved, app.allocator);
    errdefer app.allocator.free(resolved);
    if (!std.mem.startsWith(u8, resolved, app.root_path) or
        (resolved.len > app.root_path.len and resolved[app.root_path.len] != std.fs.path.sep))
    {
        return error.PathEscapesRoot;
    }
    return resolved;
}

fn validTopic(category_id: []const u8, topic_id: []const u8) bool {
    const category_valid = std.mem.eql(u8, category_id, "algos") or
        std.mem.eql(u8, category_id, "data-structures");
    return category_valid and catalog.validId(topic_id);
}

fn containsString(values: []const []const u8, needle: []const u8) bool {
    for (values) |value| if (std.mem.eql(u8, value, needle)) return true;
    return false;
}

fn respondApiError(request: *std.http.Server.Request, status: std.http.Status, code: []const u8) !void {
    var buffer: [256]u8 = undefined;
    const body = try std.fmt.bufPrint(&buffer, "{{\"error\":\"{s}\"}}", .{code});
    return respondJson(request, body, status);
}

fn respondJson(request: *std.http.Server.Request, body: []const u8, status: std.http.Status) !void {
    return request.respond(body, .{
        .status = status,
        .keep_alive = false,
        .extra_headers = &.{.{ .name = "content-type", .value = "application/json; charset=utf-8" }},
    });
}

fn respondFile(
    app: *App,
    request: *std.http.Server.Request,
    relative_path: []const u8,
    content_type: []const u8,
) !void {
    const path = try std.fs.path.join(app.allocator, &.{ app.trainer_path, relative_path });
    defer app.allocator.free(path);
    const body = try Io.Dir.cwd().readFileAlloc(app.io, path, app.allocator, .limited(4 * 1024 * 1024));
    defer app.allocator.free(body);
    return request.respond(body, .{
        .keep_alive = false,
        .extra_headers = &.{.{ .name = "content-type", .value = content_type }},
    });
}

test {
    _ = catalog;
    _ = attempts;
    _ = runner;
    _ = session;
}
