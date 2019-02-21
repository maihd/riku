#pragma once

#ifndef RIKU_API
#define RIKU_API
#endif

#if defined(_MSC_VER) || defined(__MINGW32__)
#define OS_WINDOWS
#endif

#if defined(__linux__)
#define OS_LINUX
#endif

#if defined(__unix__)
#define OS_UNIX
#endif

#if defined(__ANDROID__)
#define OS_ANDROID
#endif

#if defined(__MINGW64__) || defined(__x86_64__) || defined(__X86_64__) || defined(_M_X64)
#define RUNTIME_64BITS
#else
#define RUNTIME_32BITS
#endif