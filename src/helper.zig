//! see more:https://gist.github.com/andrewrk/752a1f4db1a3327ee21f684cc87026e7
//! by: Andrew Kelley

const std = @import("std");

/// Works on Linux, not Windows

// /home/kassane/zig/0.11.0-dev.1822+98508a12c/files/lib/std/start.zig:602:45: error: root struct of file 'helper' has no member named 'main'
//     switch (@typeInfo(@typeInfo(@TypeOf(root.main)).Fn.return_type.?)) {
//                                         ~~~~^~~~~
// /home/kassane/zig/0.11.0-dev.1822+98508a12c/files/lib/std/start.zig:551:12: note: called from here
//     return @call(.always_inline, callMain, .{});
//            ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// /home/kassane/zig/0.11.0-dev.1822+98508a12c/files/lib/std/start.zig:387:65: note: called from here
//     std.os.windows.kernel32.ExitProcess(initEventLoopAndCallMain());
//                                         ~~~~~~~~~~~~~~~~~~~~~~~~^~

export fn setup_debug_handlers() void {
    std.debug.maybeEnableSegfaultHandler();
}

export fn dump_stack_trace() void {
    std.debug.dumpCurrentStackTrace(@returnAddress());
}

// pub export fn __cxa_pure_virtual() void {
//     @panic("Error: Pure virtual function called!");
// }

/// Communicate to zig that main() will be provided elsewhere.
pub const _start = {};
