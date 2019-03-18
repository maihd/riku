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
    
    usize read_file(const char* path, Buffer& buffer)
    {
        return read_file(path, buffer.data, buffer.get_length());
    }

    usize read_file(const char* path, void* buffer, usize length)
    {
        FILE* file = fopen(path, "r");
        if (file)
        {
            usize ret = fread(buffer, 1, length, file);
            fclose(file);
            return ret;
        }
        else
        {
            return false;
        }
    }
    
    usize write_file(const char* path, const Buffer& buffer)
    {
        return write_file(path, buffer.data, buffer.get_length());
    }

    usize write_file(const char* path, const void* buffer, usize length)
    {
        FILE* file = fopen(path, "w+");
        if (file)
        {
            usize ret = fwrite(buffer, 1, length, file);
            fclose(file);
            return ret;
        }
        else
        {
            return 0;
        }
    }
}