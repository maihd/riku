// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#pragma once

#include "./core.h"
#include "./buffer.h"

namespace enums
{
    enum FileOpen
    {
        None        = 0,
        Sync        = 04000000 | 00010000,
        //Link        = 1 <<  1,
        NoLink      = 00400000,
        Append      = 00002000,
        Create      = 00000100,
        Direct      = 00040000,
        DataSync    = 00010000,
        NonBlock    = 00004000,
        Existing    = 00000200,
        Truncate    = 00001000,
        Directory   = 00200000,

        Read        = 00000000,
        Write       = 00000001,
        ReadWrite   = Read | Write,
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
    // Common file system operations
    //

    RIKU_API bool mkdir(const char* path);
    RIKU_API bool rmdir(const char* path);
    
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