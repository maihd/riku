#pragma once

#include "./core"

namespace os
{
    constexpr const char* arch(void)
    {
    #if OS_ANDROID
        #if RUNTIME_64BITS
        return "arm64";
        #else
        return "arm";
        #endif
    #else
        #if RUNTIME_64BITS
        return "x64";
        #else
        return "x32";
        #endif
    #endif
    }
}