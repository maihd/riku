// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#pragma once

#include "./core.h"

namespace fs
{
#if 0 && PREVIEWING
    enum struct FileType
    {
        None,
        File,
        Directory,
    };

    struct Stats
    {
        FileType type;
    };

    RIKU_API Stats stat(const char* path);
#endif
    
    RIKU_API bool   exists(const char* path);
    
    RIKU_API Buffer read_file(const char* path);
    RIKU_API usize  read_file(const char* path, Buffer& buffer);
    RIKU_API usize  read_file(const char* path, void* buffer, usize length);
    
    RIKU_API usize  write_file(const char* path, const Buffer& buffer);
    RIKU_API usize  write_file(const char* path, const void* buffer, usize length);
}