const std = @import("std");

pub export fn puts(fmt: [*:0]const u8) void {
    const stdout = std.io.getStdOut().writer();
    stdout.print("{s}", .{fmt}) catch |err| std.log.err("{}", .{err});
}
