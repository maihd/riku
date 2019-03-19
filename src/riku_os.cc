// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#include <riku/os.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if PLATFORM_WINDOWS
#include <Windows.h>
#elif PLATFORM_UNIX
#include <pwd.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/sysinfo.h>
#include <sys/utsname.h>
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

    const char* tmpdir(char* buffer, int length)
    {
    #if PLATFORM_WINDOWS
        ::GetTempPathA((DWORD)length, buffer);
        return buffer;
    #elif PLATFORM_UNIX
        const char* envbuf;
        #define GET_ENV_VAR(name) if ((envbuf = getenv(name))) goto success
        GET_ENV_VAR("TMPDIR");
        GET_ENV_VAR("TMP");
        GET_ENV_VAR("TEMP");
        GET_ENV_VAR("TEMPDIR");
        #undef GET_ENV_VAR

    //failed:
        buffer[0] = 0;
        return buffer;

    success:
        strncpy(buffer, envbuf, length);
        return buffer;
    #endif
    }

    const char* homedir(char* buffer, int length)
    {
    #if PLATFORM_WINDOWS
        usize drive_size = (usize)::GetEnvironmentVariableA("HOMEDRIVE", buffer, (DWORD)length);
        usize path_size  = (usize)::GetEnvironmentVariableA("HOMEPATH", buffer + drive_size, (DWORD)(length - drive_size));

        if (!path_size)
        {
            buffer[0] = 0;
            return buffer;
        }
        else
        {
            return buffer;
        }
    #elif PLATFORM_UNIX 
        const char* homedir = getenv("HOME");
        if (!homedir) 
        {
            homedir = getpwuid(getuid())->pw_dir;
        }
        strncpy(buffer, homedir, length);
        return buffer;
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

    const char* hostname(void)
    {
        __threadstatic char name[1024];
        hostname(name, sizeof(name));
        return name;
    }

    const char* hostname(char* buffer, int length)
    {
    #if PLATFORM_WINDOWS
        DWORD size = (DWORD)length;
        if (!GetComputerNameExA(ComputerNameDnsHostname, buffer, &size))
        {
            buffer[0] = 0;
        }
        return buffer;
    #elif PLATFORM_UNIX
        gethostname(buffer, length);
        return buffer;
    #endif
    }

    void loadavg(float avgs[3])
    {
    #if PLATFORM_WINDOWS
        avgs[0] = avgs[1] = avgs[2] = 0.0f;
    #elif PLATFORM_UNIX
        struct sysinfo info;
        if (sysinfo(&info) < 0)
        {
            avgs[0] = avgs[1] = avgs[2] = 0.0f;
        }
        else
        {
            avgs[0] = (float)info.loads[0] / 65536.0f;
            avgs[1] = (float)info.loads[1] / 65536.0f;
            avgs[2] = (float)info.loads[2] / 65536.0f;
        }
    #endif
    }

    void loadavg(double avgs[3])
    {
    #if PLATFORM_WINDOWS
        avgs[0] = avgs[1] = avgs[2] = 0.0;
    #elif PLATFORM_UNIX
        struct sysinfo info;
        if (sysinfo(&info) < 0)
        {
            avgs[0] = avgs[1] = avgs[2] = 0.0;
        }
        else
        {
            avgs[0] = (double)info.loads[0] / 65536.0;
            avgs[1] = (double)info.loads[1] / 65536.0;
            avgs[2] = (double)info.loads[2] / 65536.0;
        }
    #endif
    }

    const char* version(void)
    {
        __threadstatic char buffer[1024];
        version(buffer, sizeof(buffer));
        return buffer;
    }

    const char* version(char* buffer, int length)
    {
    #if PLATFORM_WINDOWS
        OSVERSIONINFOA os_info;
        #pragma warning(suppress : 4996)
        if (!GetVersionExA(&os_info))
        {
            buffer[0] = 0;
            return 0;
        }

        return string::format(buffer, length,
            "Windows_NT-%u.%u",
            (u32)os_info.dwMajorVersion,
            (u32)os_info.dwMinorVersion);
    #elif PLATFORM_UNIX
        struct utsname buf;
        if (::uname(&buf) == -1)
        {
            buffer[0] = 0;
            return 0;
        }

        return string::format(buffer, length, "%s.%s", buf.version, buf.release);
    #endif
    }

    u64 uptime(void)
    {
    #if PLATFORM_WINDOWS
        return (u64)(GetTickCount64() / 1000);
    #elif PLATFORM_UNIX
        struct sysinfo info;
        return sysinfo(&info) == 0 ? (u64)info.uptime : 0;
    #endif
    }

    CPU* cpus(int* count)
    {
        return NULL;
    }

    int cpus(CPU* buffer, int length)
    {
        (void)buffer;
        (void)length;
        return 0;
    }
}