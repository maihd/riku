// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#pragma once

#include "./core.h"

namespace os
{
    struct CPU
    {
        int  speed;
        char model[64];
    };

    enum struct Endian
    {
        Big,
        Little,
    };

    enum struct Platform
    {
        WinRT,
        Windows,
        Android,
        Linux,
        iOS,
        OSX,
        AsmJS,
        WebAssembly,
    };

    enum struct PlatformFamily
    {
        Linux,
        Darwin,
        Windows,
        WebNative,
    };

    // Get cpu name
    constexpr const char* arch(void)
    {
        return CPU_NAME;
    }

    // Get edianness name
    constexpr Endian edianness(void)
    {
    #if CPU_LITTLE_ENDIAN
        return Endian::Little;
    #else
        return Endian::Big;
    #endif
    }

    // Get os name
    constexpr const char* name(void)
    {
        return PLATFORM_NAME;
    }

    // Get os family name
    constexpr const char* uname(void)
    {
        return PLATFORM_FAMILY;
    }

    // Get platform of os
    constexpr Platform platform(void)
    {
    #if PLATFORM_WINRT
        return Platform::WinRT;
    #elif PLATFORM_WINDOWS
        return Platform::Windows;
    #elif PLATFORM_ANDROID
        return Platform::Android;
    #elif PLATFORM_LINUX
        return Platform::Linux;
    #elif PLATFORM_ASMJS
        return Platform::AsmJS;
    #elif PLATFORM_WASM
        return Platform::WebAssembly;
    #elif PLATFORM_IOS
        return Platform::iOS;
    #elif PLATFORM_OSX
        return Platform::OSX;
    #endif
    }

    // Get platform family os os
    constexpr PlatformFamily family(void)
    {
    #if PLATFORM_WINRT || PLATFORM_WINDOWS
        return PlatformFamily::Windows;
    #elif PLATFORM_ANDROID || PLATFORM_LINUX
        return PlatformFamily::Linux;
    #elif PLATFORM_ASMJS || PLATFORM_WASM
        return PlatformFamily::WebNative;
    #elif PLATFORM_IOS || PLATFORM_OSX
        return PlatformFamily::Darwin;
    #endif
    }

    RIKU_API usize freemem(void);
    RIKU_API usize totalmem(void);

    RIKU_API const char*   tmpdir(void);
    RIKU_API const char*   homedir(void);
    RIKU_API const char*   tmpdir(char* buffer, int length);
    RIKU_API const char*   homedir(char* buffer, int length);

    RIKU_API const char*   hostname(void);
    RIKU_API const char*   hostname(char* buffer, int length);

    RIKU_API void          loadavg(float avgs[3]);
    RIKU_API void          loadavg(double avgs[3]);

    RIKU_API const char*   version(void);
    RIKU_API const char*   version(char* buffer, int length);

    RIKU_API u64           uptime(void);

    RIKU_API CPU*          cpus(int* count);
    RIKU_API int           cpus(CPU* buffer, int count);
}