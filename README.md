# Riku [![Build Status](https://www.travis-ci.org/maihd/riku.svg?branch=master)](https://www.travis-ci.org/maihd/riku) [![License: Unlicense](https://img.shields.io/badge/license-Unlicense-blue.svg)](http://unlicense.org/)
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
* [ ] Allocator
* [x] Dynamic string
* [x] Dynamic buffer
* [x] Crypto: hashing, encrypt, decrypt, encode, decode
* [x] Thread, Mutex, Condition, Semaphore, Atomic, Fiber
* [ ] Tasks or jobs system
* [ ] Future and Promise/A+
* [x] Linear and graphics math, all with same module `math`
* [x] OS functions
* [x] File system
* [x] Path: helpers for working with filesystem path
* [ ] Url: helpers for working with network URL 
* [x] Net: sockets and streaming
* [ ] Http/Https: NodeJS's `http` and `https`
* [x] Dylib (low level)
* [ ] Zlib: NodeJS's `zlib`
* [ ] ArgsParse: parsing command line
* [x] Stream: base of all streaming type
* [x] Func<>: fast delegate
* [x] EventEmitter<N,F>: raise an event and callback to listeners
* [x] List<T>: high-level of Array
* [x] Array<T>: POD continous container
* [x] HashTable<V>: POD table with hashed key
* [x] Dictionary<K,V>: high-level of Table

[//]: <> (* [x] Table<K,V>: POD table with generic key)

## License
1. Author: MaiHD @ 2019
2. Unlicense or public domain