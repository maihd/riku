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

    struct ZlibOptions
    {
        int level;

        Allocator* allocator;
    };

    RIKU_API int inflate(void* buffer, int length, const void* data, int size);
    RIKU_API int deflate(void* buffer, int length, const void* data, int size);

    RIKU_API int inflate(void* buffer, int length, const void* data, int size, const ZlibOptions& options);
    RIKU_API int deflate(void* buffer, int length, const void* data, int size, const ZlibOptions& options);
}