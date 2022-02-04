# c-plus-minus
C+- is a subset of C++ that enables smaller binaries and reduces dependencies

------

### Features added/enabled:

* Custom/slimmed down std lib with essentials (`slimstd`)
* malloc provided `new`/`new[]`/`delete`/`delete[]`
* Smaller binaries vs normal c++ compiled programs
* Programs only linked against libc(if not statically compiled)
* Classes
* Constructors/destructors & RAII
* virtual functions
* Iterators
* Templates (with support of reflection, see `type_traits.h`)

### Features removed/disabled:
* RTTI; Cannot `dynamic_cast` or call `typeid()`
* Exceptions; need to perform alternative error strategies
* C++ normal stdlib; need to reimplement common data structures

------

### Build alterations:

* build example with: `zig build`
* run example with: `zig build run`
* build release with: `zig build -Drelease-fast=true` or `zig build -Drelease-small=true`
* cross compile/retarget with: 
  * default but with gnu linkage: `zig build -Dtarget=native-native-gnu` 
  * default but with musl: `zig build -Dtarget=native-native-musl` 
  * full triple: `zig build -Dtarget=x86_64-linux-musl` 

------

Zig tip - print out available targets with `zig targets` (WARNING: Large output)
