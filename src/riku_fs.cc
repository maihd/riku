#include <stdio.h>
#include <riku/fs.h>

#if PLATFORM_WINDOWS
#include <Windows.h>
#include <Shlwapi.h>
#pragma comment(lib, "Shlwapi.lib")
#undef  PLATFORM_WINDOWS
#define PLATFORM_WINDOWS 1
#elif PLATFORM_UNIX
#include <unistd.h>
#endif

namespace fs
{
    bool exists(const char* path)
    {
    #if PLATFORM_WINDOWS
        return PathFileExistsA(path);
    #elif PLATFORM_UNIX
        return access(path, F_OK) != -1 ;
    #endif
    }

    FileHandle open(const char* path, const char* flags)
    {
        return fopen(path, flags);
    }

    int read(FileHandle handle, void* buffer, int length)
    {
        return (int)fread(buffer, 1, (usize)length, (FILE*)handle);
    }

    int write(FileHandle handle, void* buffer, int length)
    {
        return (int)fwrite(buffer, 1, (usize)length, (FILE*)handle);
    }

    void close(FileHandle handle)
    {
        fclose((FILE*)handle);
    }

    Buffer read_file(const char* path)
    {
        FILE* file = fopen(path, "r");
        if (file)
        {
            fseek(file, SEEK_END, 0);
            usize size = ftell(file);
            fseek(file, SEEK_SET, 0);

            Buffer buffer = Buffer::alloc(size);
            fread(buffer.data, 1, size, file);

            fclose(file);

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
        FILE* file = fopen(path, "r");
        if (file)
        {
            usize ret = fread(buffer, 1, length, file);
            fclose(file);
            return (int)ret;
        }
        else
        {
            return false;
        }
    }
    
    int write_file(const char* path, const Buffer& buffer)
    {
        return write_file(path, buffer.data, buffer.get_length());
    }

    int write_file(const char* path, const void* buffer, int length)
    {
        FILE* file = fopen(path, "w+");
        if (file)
        {
            usize ret = fwrite(buffer, 1, length, file);
            fclose(file);
            return (int)ret;
        }
        else
        {
            return 0;
        }
    }
}