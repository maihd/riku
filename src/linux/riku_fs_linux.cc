#include <riku/fs.h>
#include <riku/path.h>

#include <stdio.h>

namespace fs
{
    FileHandle open(const char* path, Flags flags)
    {
        char string_flags[80];
        char* ptr = string_flags;

        if (flags & FileOpen::ReadWrite)
        {
            *ptr++ = 'r';
            *ptr++ = 'w';
        }
        else
        {
            if (flags & FileOpen::ReadOnly)
            {
                *ptr++ = 'r';
            }

            if (flags & FileOpen::WriteOnly)
            {
                *ptr++ = 'w';
            }
        }

        if (flags & FileOpen::Append)
        {
            *ptr++ = 'a';
        }

        if (flags & FileOpen::Create) 
        {
            *ptr++ = '+';
        }

        *ptr = 0;
        return fopen(path, string_flags);
    }

    FileHandle open(const char* path, const char* flags)
    {
        return fopen(path, flags);
    }

    int seek(FileHandle handle, FileSeek whence, int count)
    {
        return fseek((FILE*)handle, count, (int)whence);
    }

    int tell(FileHandle handle)
    {
        return (int)ftell((FILE*)handle);
    }

    int read(FileHandle handle, void* buffer, int length)
    {
        return (int)fread(buffer, 1, (usize)length, (FILE*)handle);
    }

    int write(FileHandle handle, const void* buffer, int length)
    {
        return (int)fwrite(buffer, 1, (usize)length, (FILE*)handle);
    }

    void close(FileHandle handle)
    {
        fclose((FILE*)handle);
    }
}