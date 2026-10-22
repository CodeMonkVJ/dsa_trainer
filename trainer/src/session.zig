const std = @import("std");
const Io = std.Io;
const Attempt = @import("attempts.zig").Attempt;

const c = @cImport({
    @cInclude("errno.h");
    @cInclude("pty.h");
    @cInclude("signal.h");
    @cInclude("stdlib.h");
    @cInclude("sys/ioctl.h");
    @cInclude("sys/wait.h");
    @cInclude("unistd.h");
});

pub const EditorState = enum { not_started, running, exited };

pub const Terminal = struct {
    master_fd: c_int,
    child_pid: c.pid_t,

    pub fn close(self: *Terminal) void {
        self.disconnect();
        self.reap();
    }

    pub fn disconnect(self: *Terminal) void {
        _ = c.kill(self.child_pid, c.SIGHUP);
        _ = c.close(self.master_fd);
    }

    pub fn reap(self: *Terminal) void {
        var status: c_int = 0;
        _ = c.waitpid(self.child_pid, &status, 0);
        self.* = undefined;
    }

    pub fn read(self: *Terminal, buffer: []u8) !usize {
        while (true) {
            const count = c.read(self.master_fd, buffer.ptr, buffer.len);
            if (count >= 0) return @intCast(count);
            if (c.__errno_location().* == c.EINTR) continue;
            if (c.__errno_location().* == c.EIO) return 0;
            return error.PtyReadFailed;
        }
    }

    pub fn write(self: *Terminal, bytes: []const u8) !void {
        var offset: usize = 0;
        while (offset < bytes.len) {
            const count = c.write(self.master_fd, bytes.ptr + offset, bytes.len - offset);
            if (count > 0) {
                offset += @intCast(count);
                continue;
            }
            if (count < 0 and c.__errno_location().* == c.EINTR) continue;
            return error.PtyWriteFailed;
        }
    }

    pub fn resize(self: *Terminal, columns: u16, rows: u16) !void {
        if (columns == 0 or rows == 0 or columns > 1000 or rows > 500) return error.InvalidTerminalSize;
        var size: c.struct_winsize = .{
            .ws_row = rows,
            .ws_col = columns,
            .ws_xpixel = 0,
            .ws_ypixel = 0,
        };
        if (c.ioctl(self.master_fd, c.TIOCSWINSZ, &size) != 0) return error.TerminalResizeFailed;
    }
};

pub fn editorState(
    allocator: std.mem.Allocator,
    io: Io,
    attempt: *const Attempt,
) !EditorState {
    const name = try sessionName(allocator, attempt);
    defer allocator.free(name);
    if (!try hasSession(allocator, io, name)) return .not_started;
    return if (try paneDead(allocator, io, name)) .exited else .running;
}

pub fn terminate(
    allocator: std.mem.Allocator,
    io: Io,
    attempt: *const Attempt,
) !void {
    const name = try sessionName(allocator, attempt);
    defer allocator.free(name);
    if (!try hasSession(allocator, io, name)) return;
    killSession(allocator, io, name) catch |err| {
        // The attached terminal can remove the session while cancellation is
        // racing with the websocket close. Treat that already-gone state as
        // successfully terminated, but surface any session that still exists.
        if (err == error.TmuxCommandFailed and !try hasSession(allocator, io, name)) return;
        return err;
    };
}

pub fn open(
    allocator: std.mem.Allocator,
    io: Io,
    root_path: []const u8,
    trainer_path: []const u8,
    attempt: *const Attempt,
    columns: u16,
    rows: u16,
) !Terminal {
    const name = try sessionName(allocator, attempt);
    defer allocator.free(name);

    if (try hasSession(allocator, io, name)) {
        if (try paneDead(allocator, io, name)) {
            try killSession(allocator, io, name);
            try createSession(allocator, io, root_path, trainer_path, attempt, name, columns, rows);
        }
    } else {
        try createSession(allocator, io, root_path, trainer_path, attempt, name, columns, rows);
    }

    const name_z = try allocator.dupeZ(u8, name);
    defer allocator.free(name_z);
    var size: c.struct_winsize = .{
        .ws_row = rows,
        .ws_col = columns,
        .ws_xpixel = 0,
        .ws_ypixel = 0,
    };
    var master_fd: c_int = -1;
    const pid = c.forkpty(&master_fd, null, null, &size);
    if (pid < 0) return error.ForkPtyFailed;
    if (pid == 0) {
        _ = c.setenv("TERM", "xterm-256color", 1);
        _ = c.setenv("COLORTERM", "truecolor", 1);
        var argv = [_:null]?[*:0]const u8{
            "tmux",
            "attach-session",
            "-t",
            name_z.ptr,
        };
        _ = c.execvp(argv[0].?, @ptrCast(&argv));
        c._exit(127);
    }
    return .{ .master_fd = master_fd, .child_pid = pid };
}

fn createSession(
    allocator: std.mem.Allocator,
    io: Io,
    root_path: []const u8,
    trainer_path: []const u8,
    attempt: *const Attempt,
    name: []const u8,
    columns: u16,
    rows: u16,
) !void {
    const topic_path = try problemPath(allocator, root_path, attempt);
    defer allocator.free(topic_path);
    const attempt_path = try std.fs.path.join(allocator, &.{ topic_path, "workspace", if (std.mem.eql(u8, attempt.language(), "md")) "attempt.md" else if (std.mem.eql(u8, attempt.language(), "c")) "attempt.c" else "attempt.cpp" });
    defer allocator.free(attempt_path);
    const guard_path = try std.fs.path.join(allocator, &.{ trainer_path, "nvim", "guard.lua" });
    defer allocator.free(guard_path);
    const config_path = try std.fs.path.join(allocator, &.{ trainer_path, "nvim-config" });
    defer allocator.free(config_path);
    const data_path = try std.fs.path.join(allocator, &.{ trainer_path, "nvim-data" });
    defer allocator.free(data_path);
    const columns_text = try std.fmt.allocPrint(allocator, "{d}", .{columns});
    defer allocator.free(columns_text);
    const rows_text = try std.fmt.allocPrint(allocator, "{d}", .{rows});
    defer allocator.free(rows_text);

    var command: Io.Writer.Allocating = .init(allocator);
    defer command.deinit();
    try command.writer.writeAll("exec env DSA_ATTEMPT_FILE=");
    try shellQuote(&command.writer, attempt_path);
    try command.writer.writeAll(" XDG_CONFIG_HOME=");
    try shellQuote(&command.writer, config_path);
    try command.writer.writeAll(" XDG_DATA_HOME=");
    try shellQuote(&command.writer, data_path);
    try command.writer.writeAll(" nvim -c ");
    const guard_command = try std.fmt.allocPrint(allocator, "luafile {s}", .{guard_path});
    defer allocator.free(guard_command);
    try shellQuote(&command.writer, guard_command);
    try command.writer.writeAll(" -- ");
    try shellQuote(&command.writer, attempt_path);

    var result = try std.process.run(allocator, io, .{
        .argv = &.{
            "tmux",
            "new-session",
            "-d",
            "-s",
            name,
            "-x",
            columns_text,
            "-y",
            rows_text,
            "-c",
            topic_path,
            command.written(),
        },
        .stdout_limit = .limited(64 * 1024),
        .stderr_limit = .limited(64 * 1024),
    });
    defer freeRunResult(allocator, &result);
    if (!termSucceeded(result.term)) return error.TmuxCreateFailed;

    try runTmuxCommand(allocator, io, &.{ "tmux", "set-option", "-t", name, "remain-on-exit", "on" });
    try runTmuxCommand(allocator, io, &.{ "tmux", "set-option", "-t", name, "status", "off" });
}

fn hasSession(allocator: std.mem.Allocator, io: Io, name: []const u8) !bool {
    const target = try exactTarget(allocator, name);
    defer allocator.free(target);
    var result = try std.process.run(allocator, io, .{
        .argv = &.{ "tmux", "has-session", "-t", target },
        .stdout_limit = .limited(4096),
        .stderr_limit = .limited(4096),
    });
    defer freeRunResult(allocator, &result);
    return termSucceeded(result.term);
}

fn paneDead(allocator: std.mem.Allocator, io: Io, name: []const u8) !bool {
    const target = try exactTarget(allocator, name);
    defer allocator.free(target);
    var result = try std.process.run(allocator, io, .{
        .argv = &.{ "tmux", "list-panes", "-t", target, "-F", "#{pane_dead}" },
        .stdout_limit = .limited(4096),
        .stderr_limit = .limited(4096),
    });
    defer freeRunResult(allocator, &result);
    if (!termSucceeded(result.term)) return error.TmuxQueryFailed;
    return std.mem.eql(u8, std.mem.trim(u8, result.stdout, " \t\r\n"), "1");
}

fn killSession(allocator: std.mem.Allocator, io: Io, name: []const u8) !void {
    const target = try exactTarget(allocator, name);
    defer allocator.free(target);
    try runTmuxCommand(allocator, io, &.{ "tmux", "kill-session", "-t", target });
}

fn exactTarget(allocator: std.mem.Allocator, name: []const u8) ![]u8 {
    return std.fmt.allocPrint(allocator, "={s}", .{name});
}

fn runTmuxCommand(allocator: std.mem.Allocator, io: Io, argv: []const []const u8) !void {
    var result = try std.process.run(allocator, io, .{
        .argv = argv,
        .stdout_limit = .limited(64 * 1024),
        .stderr_limit = .limited(64 * 1024),
    });
    defer freeRunResult(allocator, &result);
    if (!termSucceeded(result.term)) return error.TmuxCommandFailed;
}

fn sessionName(allocator: std.mem.Allocator, attempt: *const Attempt) ![]u8 {
    return std.fmt.allocPrint(allocator, "dsa_{s}", .{attempt.id()});
}

fn problemPath(allocator: std.mem.Allocator, root_path: []const u8, attempt: *const Attempt) ![]u8 {
    return std.fs.path.join(allocator, &.{ root_path, attempt.category(), attempt.topic(), "problems", attempt.problem() });
}

fn shellQuote(writer: *Io.Writer, value: []const u8) !void {
    try writer.writeByte('\'');
    for (value) |char| {
        if (char == '\'') {
            try writer.writeAll("'\\''");
        } else {
            try writer.writeByte(char);
        }
    }
    try writer.writeByte('\'');
}

fn termSucceeded(term: std.process.Child.Term) bool {
    return switch (term) {
        .exited => |code| code == 0,
        else => false,
    };
}

fn freeRunResult(allocator: std.mem.Allocator, result: *std.process.RunResult) void {
    allocator.free(result.stdout);
    allocator.free(result.stderr);
}

test "session shell quoting handles apostrophes" {
    var output: Io.Writer.Allocating = .init(std.testing.allocator);
    defer output.deinit();
    try shellQuote(&output.writer, "a'b");
    try std.testing.expectEqualStrings("'a'\\''b'", output.written());
}
