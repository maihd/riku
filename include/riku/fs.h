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

    __rikuapi Stats stat(const char* path);
#endif
    
    __rikuapi bool   exists(const char* path);
    
    __rikuapi Buffer read_file(const char* path);
    __rikuapi bool   read_file(const char* path, Buffer& buffer);
    __rikuapi bool   read_file(const char* path, void* buffer, int length);
    
    __rikuapi bool   write_file(const char* path, const Buffer& buffer);
    __rikuapi bool   write_file(const char* path, const void* buffer, int length);
}