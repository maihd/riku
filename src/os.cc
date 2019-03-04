#include <riku/os.h>

#if OS_WINDOWS
#include <Windows.h>
#undef  OS_WINDOWS
#define OS_WINDOWS 1
#endif

namespace os
{
    int getpid(void)
    {
        return (int)GetCurrentProcessId();
    }

    usize freemem(void)
    {
    #if OS_WINDOWS
        MEMORYSTATUSEX mem;
        mem.dwLength = sizeof(mem);
        if (::GlobalMemoryStatusEx(&mem))
        {
            return (usize)mem.ullAvailPhys;
        }
        else
        {
            return 0;
        }
    #endif
    }

    usize totalmem(void)
    {
    #if OS_WINDOWS
        MEMORYSTATUSEX mem;
        mem.dwLength = sizeof(mem);
        if (::GlobalMemoryStatusEx(&mem))
        {
            return (usize)mem.ullTotalPhys;
        }
        else
        {
            return 0;
        }
    #endif
    }

    usize tmpdir(char* buffer, usize length)
    {
    #if OS_WINDOWS
        return ::GetTempPathA(length, buffer);
    #endif
    }

    usize homedir(char* buffer, usize length)
    {
    #if OS_WINDOWS
        usize drive_size = ::GetEnvironmentVariableA("HOMEDRIVE", buffer, length);
        usize path_size  = ::GetEnvironmentVariableA("HOMEPATH", buffer + drive_size, length - drive_size);

        if (!path_size)
        {
            buffer[0] = 0;
            return 0;
        }
        else
        {
            return path_size;
        }
    #endif
    }

    const char* tmpdir(void)
    {
        __threadlocal static char path[1024];
        tmpdir(path, sizeof(path));
        return path;
    }

    const char* homedir(void)
    {
        __threadlocal static char path[1024];
        homedir(path, sizeof(path));
        return path;
    }
}