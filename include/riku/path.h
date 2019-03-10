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

    usize basename(const char* path, char* buffer, usize length);
    usize basename(const char* path, const char* ext, char* buffer, usize length);

    const char* basename(const char* path);
    const char* basename(const char* path, const char* ext);

    usize       dirname(const char* path, char* buffer, usize length);
    const char* dirname(const char* path);

    usize       extname(const char* path, char* buffer, usize length);
    const char* extname(const char* path);

    bool        is_absolute(const char* path);
    const char* get_absolute(const char* path);
    usize       get_absolute(const char* path, char* buffer, usize length);

    const char* join(const char* path, ...);
    usize       join(char* buffer, usize length, const char* path, ...);

    const char* relative(const char* from, const char* to);
    usize       relative(const char* from, const char* to, char* buffer, usize length);

    const char* relative(const char* path, ...);
    usize       relative(char* buffer, usize length, const char* path, ...);
}