#pragma once

#include <limits.h>
#include <stdint.h>

// Redefine primitive types

#if (UINT32_MAX != 0xffffffff)
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