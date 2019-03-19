// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#pragma once

#include "./core.h"

namespace enums
{
    enum FileOpen
    {
        Sync,
        Link,
        NoLink,
        Append,
        Create,
        Direct,
        DataSync,
        NonBlock,
        Truncate,
        ReadOnly,
        WriteOnly,
        ReadWrite,
        Directory,
        CreateOnly,
    };
};
using FileOpen = enums::FileOpen;
using FileHandle = void*;

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
    
    //
    // File stats
    //

    RIKU_API bool exists(const char* path);

    //
    // Low-level file working functions
    //

    //RIKU_API FileHandle open(const char* path, FileOpen flags);
    RIKU_API FileHandle open(const char* path, const char* flags);
    RIKU_API int        read(FileHandle handle, void* buffer, int length);
    RIKU_API int        write(FileHandle handle, void* buffer, int length);
    RIKU_API void       close(FileHandle handle);

    //
    // High-level, easily file working functions
    //

    RIKU_API Buffer read_file(const char* path);
    RIKU_API int    read_file(const char* path, Buffer& buffer);
    RIKU_API int    read_file(const char* path, void* buffer, int length);
    
    RIKU_API int    write_file(const char* path, const Buffer& buffer);
    RIKU_API int    write_file(const char* path, const void* buffer, int length);
}