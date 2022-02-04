# c-plus-minus
C+- is a subset of C++ that enables smaller binaries and reduces dependencies

------

Build alterations:

* build example with: `zig build`
* run example with: `zig build run`
* build release with: `zig build -Drelease-fast=true` or `zig build -Drelease-small=true`
* cross compile/retarget with: 
  * default but with gnu linkage: `zig build -Dtarget=native-native-gnu` 
  * default but with musl: `zig build -Dtarget=native-native-musl` 
  * full triple: `zig build -Dtarget=x86_64-linux-musl` 

-----

Zig tip - print out available targets with `zig targets` (WARNING: Large output)
