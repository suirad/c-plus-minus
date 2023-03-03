const std = @import("std");

// inspiration:
// zig c++ -nostdlib++ -fno-exceptions -fno-rtti -std=c++17 -c example.cpp -o example.o --target=native-native-msvc --static -O2
// zig cc example.o -o test.exe -O2 --target=native-native-msvc --static

/// Main Build
pub fn build(b: *std.Build.Builder) !void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const lib = b.addStaticLibrary(.{
        .name = "ztdio",
        .optimize = optimize,
        .target = target,
        .root_source_file = .{ .path = "lib/ztdio.zig" },
    });
    if (optimize == .ReleaseSafe or optimize == .Debug) {
        lib.bundle_compiler_rt = true; // -fcompiler-rt
    } else lib.strip = true;
    lib.install();

    switch (target.getOsTag()) {
        .windows => @panic("TODO: Windows don't work - segfault!"),
        else => build_header(b, lib),
    }
    // need clang-format installed
    try fmt(b);
}

/// Normal Build
fn build_header(b: *std.Build.Builder, stepEx: *std.Build.CompileStep) void {
    const exe = b.addExecutable(.{
        .name = "example",
        .optimize = stepEx.optimize,
        .target = stepEx.target,
        .root_source_file = .{ .path = "src/helper.zig" },
    });

    exe.strip = true;
    exe.disable_sanitize_c = true;
    exe.addIncludePath("lib");
    exe.linkLibrary(stepEx);
    exe.addCSourceFile("src/example.cpp", switch (stepEx.optimize) {
        .Debug, .ReleaseSafe => cpp_flags ++ [_][]const u8{
            "-g",
        },
        .ReleaseFast => cpp_flags ++ [_][]const u8{
            "-O3",
        },
        else => cpp_flags ++ [_][]const u8{
            "-Oz",
        },
    });
    exe.linkLibCpp();
    exe.install();

    const run_cmd = exe.run();
    run_cmd.step.dependOn(b.getInstallStep());

    const run_step = b.step("run", "build and run example");
    run_step.dependOn(&run_cmd.step);
}

fn fmt(b: *std.Build.Builder) !void {
    const zig_fmt = b.addFmt(&.{ @src().file, "src", "lib" });
    const clang_format = if (b.findProgram(&.{"clang-format"}, &.{})) |executable| command: {
        const command = b.addSystemCommand(&.{ executable, "--style=file", "-i" });
        const initial_command_len = command.argv.items.len;

        const filter = std.ComptimeStringMap(void, .{ .{ ".hpp", {} }, .{ ".cpp", {} } });
        for ([_][]const u8{ "lib", "src" }) |dir| {
            var iterable_dir = try std.fs.cwd().openIterableDir(b.pathFromRoot(dir), .{});
            defer iterable_dir.close();

            var src_walker = try iterable_dir.walk(b.allocator);
            defer src_walker.deinit();

            while (try src_walker.next()) |entry|
                if (entry.kind == .File and filter.has(std.fs.path.extension(entry.basename)))
                    command.addArg(b.pathFromRoot(b.pathJoin(&.{ dir, entry.path })));
        }

        break :command if (command.argv.items.len > initial_command_len) command else null;
    } else |err| command: {
        std.debug.print("Could not find clang-format because of {}, skipping formatting.\n", .{err});
        break :command null;
    };

    const fmt_step = b.step("fmt", "Format C/C++ code");
    fmt_step.dependOn(&zig_fmt.step);
    if (clang_format) |command|
        fmt_step.dependOn(&command.step);
}

const cpp_flags: []const []const u8 = &.{
    "-fno-exceptions",
    "-fno-rtti",
    "-std=c++20",
    "-Wall",
    "-Werror",
};
