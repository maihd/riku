// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#include <riku/os.h>

#if PLATFORM_WINDOWS
#include <Windows.h>
#elif PLATFORM_UNIX
#include <pwd.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/sysinfo.h>
#endif

namespace os
{
    usize freemem(void)
    {
    #if PLATFORM_WINDOWS
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
    #elif PLATFORM_UNIX
        struct sysinfo info;
        if (sysinfo(&info) == 0)
        {
            return (usize)(info.freeram * info.mem_unit);
        }
        else
        {
            return 0;
        }
    #endif
    }

    usize totalmem(void)
    {
    #if PLATFORM_WINDOWS
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
    #elif PLATFORM_UNIX
        struct sysinfo info;
        if (sysinfo(&info) == 0)
        {
            return (usize)(info.totalram * info.mem_unit);
        }
        else
        {
            return 0;
        }
    #endif
    }

    usize tmpdir(char* buffer, usize length)
    {
    #if PLATFORM_WINDOWS
        return ::GetTempPathA(length, buffer);
    #elif PLATFORM_UNIX
        const char* envbuf;
        #define GET_ENV_VAR(name)           \
            do {                            \
                envbuf = getenv(name);      \
                if (envbuf)                 \
                    goto return_buffer;     \
            } while (0)

        GET_ENV_VAR("TMPDIR");
        GET_ENV_VAR("TMP");
        GET_ENV_VAR("TEMP");
        GET_ENV_VAR("TEMPDIR");

    return_buffer:
        strncpy(buffer, envbuf, length);
        return string::length(buffer);
    #endif
    }

    usize homedir(char* buffer, usize length)
    {
    #if PLATFORM_WINDOWS
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
    #elif PLATFORM_UNIX 
        const char* homedir = getenv("HOME");
        if (!homedir) 
        {
            homedir = getpwuid(getuid())->pw_dir;
        }
        strncpy(buffer, homedir, length);
        return string::length(buffer);
    #endif
    }

    const char* tmpdir(void)
    {
        __threadstatic char path[1024];
        tmpdir(path, sizeof(path));
        return path;
    }

    const char* homedir(void)
    {
        __threadstatic char path[1024];
        homedir(path, sizeof(path));
        return path;
    }
}