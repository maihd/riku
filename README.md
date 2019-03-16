# Riku
Standard runtime and library for C++.

## Build
1. Pregenerated projects in `build/projects/*`
2. Require [GENie](https://github.com/bkaradzic/GENie) to generate your target project.

## Features and targets
Main purpose of this library for using as a standard library, replacement for C/C++ standard library.
1. Advise-safety, unlike Rust with strong and strict safety.
2. Easy to use, with common effort and familiar NodeJS-based and libuv API.
3. Multithreaded advise safety (not strong or strict safety)
4. Performance is also final target, but safety and easy-to-use must be present first.
5. Low-level and High-level is an yin-yang presentation of this library.
6. No lack, no redundant, no unneccessary features. That mean this library is enough to be a strong foundation for all software and application.
7. Base on above feature, this library must be cross-platform.
8. GENie toolchain for generate multiple cross-platform projects with no hard way.
9. VisualC's __declspec(property) for cross-platform, with -fdeclspec clang options

## Modules
* [x] Core: primitive types, `console`, `string`, `Date`, `memory`, ...
* [x] JSON
* [x] Dynamic string
* [x] Crypto: NodeJS's `crypto`
* [x] Thread, Mutex, Condition, Semaphore
* [ ] Fiber, TaskSystem, Coroutine
* [ ] Future and Promise/A+
* [x] High-level math
* [x] Operator System functions
* [ ] FileSystem: NodeJS's `fs`
* [ ] Path: NodeJS's `path`
* [ ] Net: NodeJS's `net`
* [ ] Http/Https: NodeJS's `http` and `https`
* [x] Dylib (low level)
* [ ] Zlib: NodeJS's `zlib`
* [ ] ArgsParse (parsing command line)
* [ ] Stream: NodeJS's `stream`
* [x] Func: fast delegate
* [x] EventEmitter: NodeJS's `EventEmitter`
* [x] List: high-level of Array
* [x] Array: POD continous container
* [ ] Table: POD table with generic key
* [x] HashTable: POD table with hashed key
* [x] Dictionary: high-level of Table

## License
1. Author: MaiHD @ 2019
2. Unlicense or public domain

## Acknowledge
1. Branimir Karadžić and GENie team
2. NodeJS and libuv team
3. Bitsquid foundation maker
4. ZLib software
5. Rust language developers
6. And many more open source projects