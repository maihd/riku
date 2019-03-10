// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#pragma once

#include "./core.h"

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

namespace os
{
    // Get cpu name
    constexpr const char* arch(void)
    {
        return CPU_NAME;
    }

    // Get edianness name
    constexpr const char* edianness(void)
    {
    #if CPU_LITTLE_ENDIAN
        return "LE";
    #else
        return "BE";
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

    __rikuapi usize freemem(void);
    __rikuapi usize totalmem(void);

    __rikuapi usize tmpdir(char* buffer, usize length);
    __rikuapi usize homedir(char* buffer, usize length);
    __rikuapi const char* tmpdir(void);
    __rikuapi const char* homedir(void);
}