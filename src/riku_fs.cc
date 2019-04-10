#include <stdio.h>
#include <riku/fs.h>

#if PLATFORM_WINDOWS
#include <Windows.h>
#include <Shlwapi.h>
#include <fcntl.h>
#include <direct.h>
#pragma comment(lib, "Shlwapi.lib")
#undef  PLATFORM_WINDOWS
#define PLATFORM_WINDOWS 1
#elif PLATFORM_UNIX
#include <unistd.h>
#include <sys/stat.h>
#endif

namespace fs
{
    bool mkdir(const char* path)
    {
#if PLATFORM_WINDOWS
        return _mkdir(path) == 0;
#else
        return ::mkdir(path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == 0;
#endif
    }

    bool rmdir(const char* path)
    {
#if PLATFORM_WINDOWS
        return _rmdir(path) == 0;
#else
        return ::rmdir(path) == 0;
#endif
    }

    bool exists(const char* path)
    {
    #if PLATFORM_WINDOWS
        return PathFileExistsA(path);
    #elif PLATFORM_UNIX
        return access(path, F_OK) != -1 ;
    #endif
    }

#if !PLATFORM_WINDOWS && !PLATFORM_LINUX
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
            if (flags & FileOpen::Read)
            {
                *ptr++ = 'r';
            }

            if (flags & FileOpen::Write)
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

    int seek(FileHandle context, FileSeek whence, int count)
    {
        return fseek((FILE*)context, count, (int)whence);
    }

    int tell(FileHandle context)
    {
        return (int)ftell((FILE*)context);
    }

    int read(FileHandle context, void* buffer, int length)
    {
        return (int)fread(buffer, 1, (usize)length, (FILE*)context);
    }

    int write(FileHandle context, const void* buffer, int length)
    {
        return (int)fwrite(buffer, 1, (usize)length, (FILE*)context);
    }

    void close(FileHandle context)
    {
        fclose((FILE*)context);
    }
#endif

    Buffer read_file(const char* path)
    {
        FileHandle file = fs::open(path, "r");
        if (file)
        {
            fs::seek(file, FileSeek::End, 0);
            usize size = fs::tell(file);
            fs::seek(file, FileSeek::Set, 0);

            Buffer buffer = Buffer::alloc(size);
            fs::read(file, buffer.data, size);

            fs::close(file);

            return traits::make_rvalue(buffer);
        }

        return traits::make_rvalue(Buffer());
    }
    
    int read_file(const char* path, Buffer& buffer)
    {
        return read_file(path, buffer.data, buffer.get_length());
    }

    int read_file(const char* path, void* buffer, int length)
    {
        FileHandle file = fs::open(path, "r");
        if (file)
        {
            int ret = fs::read(file, buffer, length);
            fs::close(file);
            return (int)ret;
        }
        else
        {
            return 0;
        }
    }
    
    int write_file(const char* path, const Buffer& buffer)
    {
        return write_file(path, buffer.data, buffer.get_length());
    }

    int write_file(const char* path, const void* buffer, int length)
    {
        FileHandle file = fs::open(path, "w+");
        if (file)
        {
            int ret = fs::write(file, buffer, length);
            fs::close(file);
            return (int)ret;
        }
        else
        {
            return 0;
        }
    }
}