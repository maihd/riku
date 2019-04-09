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

        Read        = 00000001,
        Write       = 00000010,
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

// File system
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

    // Make new directory at given path
    RIKU_API bool mkdir(const char* path);

    // Remove the directory at given path
    RIKU_API bool rmdir(const char* path);

    // Is file or directory exist at path
    RIKU_API bool exists(const char* path);

    // Open file handle at given path
    RIKU_API FileHandle open(const char* path, Flags flags);

    // Open file handle at given path
    RIKU_API FileHandle open(const char* path, const char* flags);

    // Set the position of file pointer
    RIKU_API int        seek(FileHandle handle, FileSeek whence, int count);

    // Tell the position of file pointer
    RIKU_API int        tell(FileHandle handle);
    
    // Read content of file with handle
    RIKU_API int        read(FileHandle handle, void* buffer, int length);

    // Read content of file with handle
    RIKU_API int        write(FileHandle handle, const void* buffer, int length);

    // Close file handle
    RIKU_API void       close(FileHandle handle);
    
    // Read content of file at given path
    RIKU_API Buffer read_file(const char* path);

    // Read content of file at given path
    RIKU_API int    read_file(const char* path, Buffer& buffer);

    // Read content of file at given path
    RIKU_API int    read_file(const char* path, void* buffer, int length);

    // Write content to file at given path
    RIKU_API int    write_file(const char* path, const Buffer& buffer);

    // Write content to file at given path
    RIKU_API int    write_file(const char* path, const void* buffer, int length);
}