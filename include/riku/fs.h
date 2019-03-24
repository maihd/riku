// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#pragma once

#include "./core.h"

namespace enums
{
    enum FileOpen
    {
        None        = 0,
        Sync        = 1 <<  0,
        Link        = 1 <<  1,
        NoLink      = 1 <<  2,
        Append      = 1 <<  3,
        Create      = 1 <<  4,
        Direct      = 1 <<  5,
        DataSync    = 1 <<  6,
        NonBlock    = 1 <<  7,
        Truncate    = 1 <<  8,
        ReadOnly    = 1 <<  9,
        WriteOnly   = 1 << 10,
        ReadWrite   = 1 << 11,
        Directory   = 1 << 12,
        CreateOnly  = 1 << 13,
    };
};
using FileOpen   = enums::FileOpen;
using FileHandle = void*;

enum struct FileSeek
{
    Set     = 0,
    End     = 2,
    Current = 1,
};

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

    RIKU_API FileHandle open(const char* path, Flags flags);
    RIKU_API FileHandle open(const char* path, const char* flags);
    RIKU_API int        seek(FileHandle handle, FileSeek whence, int count);
    RIKU_API int        tell(FileHandle handle);
    RIKU_API int        read(FileHandle handle, void* buffer, int length);
    RIKU_API int        write(FileHandle handle, const void* buffer, int length);
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