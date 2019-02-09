#pragma once

#include <limits.h>
#include <stdint.h>

// Redefine primitive types

#if (UINT_MAX != 0xffffffff)
#define int   int32_t
#define long  int64_t
#define short int16_t
#endif

using uint   = uint32_t;
using ulong  = uint64_t;
using ushort = uint16_t;

using byte   = uint8_t;
using sbyte  = int8_t;

using str    = const char*;

// Memory address and size

using iptr   = intptr_t;
using uptr   = uintptr_t;

#if __x86_64__ || UINTPTR_MAX == 0xffffffffffffffff
using usize  = uint64_t;
using isize  = int64_t;
#else 
using usize  = uint32_t;
using isize  = int32_t;
#endif