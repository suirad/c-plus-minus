const std = @import("std");

// inspiration:
// zig c++ -nostdlib++ -fno-exceptions -fno-rtti -std=c++17 -c example.cpp -o example.o --target=native-native-msvc --static -O2
// zig cc example.o -o test.exe -O2 --target=native-native-msvc --static

const cpp_flags: []const []const u8 = &.{
    "-fno-exceptions",
    "-fno-rtti",
    "-std=c++20",
    "-Wall",
    "-Werror",
};

pub fn build(b: *std.Build.Builder) void {
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

    const exe = switch (target.getOsTag()) {
        .windows => b.addExecutable(.{
            .name = "example",
            .optimize = optimize,
            .target = target,
        }),
        else => b.addExecutable(.{
            .name = "example",
            .optimize = optimize,
            .target = target,
            .root_source_file = .{ .path = "src/helper.zig" },
        }),
    };

    exe.strip = true;
    exe.disable_sanitize_c = true;
    exe.addIncludePath("lib");
    exe.linkLibrary(lib);
    exe.addCSourceFile("src/example.cpp", switch (optimize) {
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
