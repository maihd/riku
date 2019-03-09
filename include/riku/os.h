#pragma once

#include "./core.h"

namespace os
{
    constexpr const char* arch(void)
    {
    #if defined(__mips__)
        return "mips";
    #elif defined(__MIPSEL__)
        return "mipsel";
    #elif defined(__aarch64__)
        return "arm64";
    #elif defined(__arm__)
        return "arm";
    #elif defined(__i386__)
        return "x32";
    #elif defined(__powerpc__)
        return "ppc";
    #elif defined(__powerpc64__)
        return "ppc64";
    #elif defined(__x86_64__) || defined(_M_X64)
        return "x64";
    #else
        return "x32";
    #endif
    }

    constexpr const char* edianness(void)
    {
    #if OS_LITTLE_ENDIAN
        return "LE";
    #else
        return "BE";
    #endif
    }

    constexpr const char* platform(void)
    {
    #if OS_WINDOWS
        return "windows";
    #elif OS_ANDROID
        return "android";
    #elif OS_LINUX
        return "linux";
    #elif __asmjs__
        return "asmjs";
    #elif __EMSCRIPTEN__
        return "wasm";
    #endif
    }

    constexpr const char* type(void)
    {
    #if OS_WINDOWS
        return "Windows_NT";
    #elif OS_ANDROID
        return "Android";
    #elif OS_LINUX
        return "Linux";
    #elif __asmjs__
        return "AsmJS";
    #elif __EMSCRIPTEN__
        return "WebAssembly";
    #endif
    }

    RIKU_API usize freemem(void);
    RIKU_API usize totalmem(void);

    RIKU_API usize tmpdir(char* buffer, usize length);
    RIKU_API usize homedir(char* buffer, usize length);
    RIKU_API const char* tmpdir(void);
    RIKU_API const char* homedir(void);
}