// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#pragma once

#include "./core.h"

namespace zlib
{
#if 0
    struct ZlibBase
    {

    };

    struct GZip
    {

    };

    struct Gunzip
    {

    };

    struct Unzip
    {

    };
#endif

    struct Options
    {
        int level;

        Allocator* allocator;

        inline Options(void)
            : level(1)
            , allocator(memory::allocator)
        {
        }

        inline Options(int level, Allocator* allocator = memory::allocator) 
            : level(level)
            , allocator(allocator)
        {
        }
    };

    RIKU_API int inflate(void* buffer, int length, const void* data, int size);
    RIKU_API int deflate(void* buffer, int length, const void* data, int size);

    RIKU_API int inflate(void* buffer, int length, const void* data, int size, const Options& options);
    RIKU_API int deflate(void* buffer, int length, const void* data, int size, const Options& options);
}