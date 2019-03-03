#include <stdio.h>
#include <riku/fs.h>

#if OS_WINDOWS
#include <Windows.h>
#include <Shlwapi.h>
#pragma comment(lib, "Shlwapi.lib")
#undef  OS_WINDOWS
#define OS_WINDOWS 1
#endif

namespace fs
{
    bool exists(const char* path)
    {
#if OS_WINDOWS
        return PathFileExistsA(path);
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
}