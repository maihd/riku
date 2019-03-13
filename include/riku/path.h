// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#pragma once

#include "./core.h"

namespace path
{
#if PLATFORM_WINDOWS
    const char* const delimiter = ";";
#else
    const char* const delimiter = ":";
#endif

    const char* basename(const char* path);
    const char* basename(const char* path, const char* ext);
    const char* basename(const char* path, char* buffer, usize length);
    const char* basename(const char* path, const char* ext, char* buffer, usize length);

    const char* dirname(const char* path, char* buffer, usize length);
    const char* dirname(const char* path);

    const char* extname(const char* path, char* buffer, usize length);
    const char* extname(const char* path);

    bool        is_absolute(const char* path);
    bool        is_relative(const char* path);

    const char* absolute(const char* path);
    const char* absolute(const char* path, char* buffer, usize length);

    const char* relative(const char* from, const char* to);
    const char* relative(const char* from, const char* to, char* buffer, usize length);

    const char* relative(const char* path, ...);
    const char* relative(char* buffer, usize length, const char* path, ...);

    const char* join(const char* path, ...);
    const char* join(char* buffer, usize length, const char* path, ...);
}