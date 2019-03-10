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

            return make_rvalue(buffer);
        }

        return make_rvalue(Buffer());
    }
    
    bool read_file(const char* path, Buffer& buffer)
    {
        return read_file(path, buffer.data, buffer.length);
    }

    bool read_file(const char* path, void* buffer, int length)
    {
        FILE* file = fopen(path, "r");
        if (file)
        {
            fread(buffer, 1, length, file);
            fclose(file);
            return true;
        }
        else
        {
            return false;
        }
    }
    
    bool write_file(const char* path, const Buffer& buffer)
    {
        return write_file(path, buffer.data, buffer.length);
    }

    bool write_file(const char* path, const void* buffer, int length)
    {
        FILE* file = fopen(path, "w+");
        if (file)
        {
            fwrite(buffer, 1, length, file);
            fclose(file);
            return true;
        }
        else
        {
            return false;
        }
    }
}