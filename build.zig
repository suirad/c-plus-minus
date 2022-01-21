const std = @import("std");

// inspiration:
// zig c++ -nostdlib++ -fno-exceptions -fno-rtti -std=c++17 -c example.cpp -o example.o --target=native-native-msvc --static -O2
// zig cc example.o -o test.exe -O2 --target=native-native-msvc --static

const cpp_flags = .{
    "-nostdlib++",
    "-fno-exceptions",
    "-fno-rtti",
    "-std=c++2a",
    "--static",
    "-c",
};

pub fn build(b: *std.build.Builder) void {
    const mode = b.standardReleaseOptions();
    const target = b.standardTargetOptions(.{});

    const cppout = b.addObject("example", null);
    cppout.setBuildMode(mode);
    cppout.linkLibC();
    cppout.disable_sanitize_c = true;
    cppout.setTarget(target);
    cppout.addSystemIncludeDir("lib");

    if (mode == .Debug) {
        cppout.addCSourceFileSource(.{
            .source = .{ .path = "src/example.cpp" },
            .args = &(cpp_flags ++ .{"-O2"}),
        });
    } else if (mode == .ReleaseFast or mode == .ReleaseSafe) {
        cppout.addCSourceFileSource(.{
            .source = .{ .path = "src/example.cpp" },
            .args = &(cpp_flags ++ .{ "-s", "-Ofast" }),
        });
    } else if (mode == .ReleaseSmall) {
        cppout.addCSourceFileSource(.{
            .source = .{ .path = "src/example.cpp" },
            .args = &(cpp_flags ++ .{ "-s", "-O3" }),
        });
    }

    const exe = b.addExecutable("example", null);
    exe.setBuildMode(mode);
    exe.setTarget(target);
    exe.addObject(cppout);
    exe.install();

    const run_cmd = exe.run();
    run_cmd.step.dependOn(b.getInstallStep());

    const run_step = b.step("run", "build and run");
    run_step.dependOn(&run_cmd.step);
}
