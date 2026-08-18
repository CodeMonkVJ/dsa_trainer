const std = @import("std");
const Io = std.Io;

pub const State = enum { active, submitted, canceled };

pub const Attempt = struct {
    id_buffer: [48]u8 = undefined,
    id_len: usize = 0,
    category_buffer: [32]u8 = undefined,
    category_len: usize = 0,
    topic_buffer: [81]u8 = undefined,
    topic_len: usize = 0,
    problem_buffer: [81]u8 = undefined,
    problem_len: usize = 0,
    language_buffer: [8]u8 = undefined,
    language_len: usize = 0,
    started_awake_ns: i96,
    started_real_ns: i96,
    green_seconds: u32,
    yellow_seconds: u32,
    state: State = .active,
    reference_viewed: bool = false,

    pub fn id(self: *const Attempt) []const u8 {
        return self.id_buffer[0..self.id_len];
    }

    pub fn category(self: *const Attempt) []const u8 {
        return self.category_buffer[0..self.category_len];
    }

    pub fn topic(self: *const Attempt) []const u8 {
        return self.topic_buffer[0..self.topic_len];
    }

    pub fn language(self: *const Attempt) []const u8 {
        return self.language_buffer[0..self.language_len];
    }

    pub fn problem(self: *const Attempt) []const u8 {
        return self.problem_buffer[0..self.problem_len];
    }

    pub fn elapsedMs(self: *const Attempt, io: Io) i64 {
        const now = Io.Clock.awake.now(io).nanoseconds;
        return @intCast(@max(0, @divTrunc(now - self.started_awake_ns, std.time.ns_per_ms)));
    }
};

pub const Store = struct {
    mutex: Io.Mutex = .init,
    active: ?Attempt = null,

    pub fn start(
        self: *Store,
        io: Io,
        category: []const u8,
        topic: []const u8,
        problem: []const u8,
        language: []const u8,
        green_seconds: u32,
        yellow_seconds: u32,
    ) !Attempt {
        self.mutex.lockUncancelable(io);
        defer self.mutex.unlock(io);

        if (self.active) |attempt| {
            if (attempt.state == .active) return error.AttemptAlreadyActive;
        }

        var attempt: Attempt = .{
            .started_awake_ns = Io.Clock.awake.now(io).nanoseconds,
            .started_real_ns = Io.Clock.real.now(io).nanoseconds,
            .green_seconds = green_seconds,
            .yellow_seconds = yellow_seconds,
        };
        attempt.id_len = (try std.fmt.bufPrint(&attempt.id_buffer, "{d}", .{attempt.started_real_ns})).len;
        try copyField(32, &attempt.category_buffer, &attempt.category_len, category);
        try copyField(81, &attempt.topic_buffer, &attempt.topic_len, topic);
        try copyField(81, &attempt.problem_buffer, &attempt.problem_len, problem);
        try copyField(8, &attempt.language_buffer, &attempt.language_len, language);
        self.active = attempt;
        return attempt;
    }

    pub fn get(self: *Store, io: Io, id: []const u8) ?Attempt {
        self.mutex.lockUncancelable(io);
        defer self.mutex.unlock(io);
        const attempt = self.active orelse return null;
        if (!std.mem.eql(u8, attempt.id(), id)) return null;
        return attempt;
    }

    pub fn current(self: *Store, io: Io) ?Attempt {
        self.mutex.lockUncancelable(io);
        defer self.mutex.unlock(io);
        const attempt = self.active orelse return null;
        if (attempt.state != .active) return null;
        return attempt;
    }

    pub fn reveal(self: *Store, io: Io, id: []const u8) !Attempt {
        self.mutex.lockUncancelable(io);
        defer self.mutex.unlock(io);
        var attempt = self.active orelse return error.AttemptNotFound;
        if (!std.mem.eql(u8, attempt.id(), id)) return error.AttemptNotFound;
        if (attempt.state != .active) return error.AttemptAlreadyFinished;
        if (attempt.elapsedMs(io) <= @as(i64, attempt.yellow_seconds) * 1000) return error.RevealLocked;
        attempt.reference_viewed = true;
        self.active = attempt;
        return attempt;
    }

    pub fn finish(self: *Store, io: Io, id: []const u8, state: State) !Attempt {
        self.mutex.lockUncancelable(io);
        defer self.mutex.unlock(io);
        var attempt = self.active orelse return error.AttemptNotFound;
        if (!std.mem.eql(u8, attempt.id(), id)) return error.AttemptNotFound;
        if (attempt.state != .active) return error.AttemptAlreadyFinished;
        attempt.state = state;
        self.active = attempt;
        return attempt;
    }
};

fn copyField(comptime N: usize, destination: *[N]u8, length: *usize, source: []const u8) !void {
    if (source.len > destination.len) return error.ValueTooLong;
    @memcpy(destination[0..source.len], source);
    length.* = source.len;
}

test "attempt store permits one active attempt" {
    var store: Store = .{};
    const first = try store.start(std.testing.io, "algos", "binary_search", "base", "cpp", 300, 450);
    try std.testing.expectEqualStrings("binary_search", first.topic());
    try std.testing.expectError(
        error.AttemptAlreadyActive,
        store.start(std.testing.io, "algos", "binary_search", "base", "cpp", 300, 450),
    );
    _ = try store.finish(std.testing.io, first.id(), .canceled);
    _ = try store.start(std.testing.io, "algos", "binary_search", "base", "cpp", 300, 450);
}
