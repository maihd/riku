// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#include <riku/core.h>
#include <riku/crypto.h>

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#if PLATFORM_WINDOWS
#include <Windows.h>
#elif PLATFORM_ANDROID
#include <unistd.h>
#elif PLATFORM_UNIX
#include <unistd.h>
#include <sys/time.h>
#endif

//
// Process
//

namespace process
{
    // Get environment variable
    const char* getenv(const char* name)
    {
        return ::getenv(name);    
    }

    // Set environment variable
    bool setenv(const char* name, const char* value)
    {
#if PLATFORM_WINDOWS
        return SetEnvironmentVariableA(name, value);
#elif PLATFORM_UNIX
        return ::setenv(name, value, true) == 0;
#endif
    }

    const char* cwd(void)
    {
        __threadstatic char path[1024];

        return cwd(path, sizeof(path));
    }

    const char* cwd(char* buffer, int length)
    {
    #if PLATFORM_WINDOWS
        GetCurrentDirectoryA((DWORD)length, buffer);
        return buffer;
    #elif PLATFORM_UNIX
        return ::getcwd(buffer, length);
    #endif
    }

    bool chdir(const char* directory)
    {
    #if PLATFORM_WINDOWS
        return SetCurrentDirectoryA(directory);
    #elif PLATFORM_WEB
        (void)(directory);
        return false;
    #elif PLATFORM_UNIX
        return ::chdir(directory) != 0;
    #endif
    }

    void exit(int code)
    {
        ::exit(code);
    }

    void abort(void)
    {
        ::abort();
    }
    
    int getpid(void)
    {
    #if PLATFORM_WINDOWS
        return (int)GetCurrentProcessId();
    #elif PLATFORM_WEB
        return -1;
    #elif PLATFORM_UNIX
        return (int)::getpid();
    #endif
    }
}

//
// Performance
// 

namespace performance
{
    i64 now(void)
    {
    #if PLATFORM_WINDOWS
        LARGE_INTEGER value;
        return QueryPerformanceCounter(&value) ? (i64)value.QuadPart : 0;
    #elif PLATFORM_WEB
        return 0; // Not implement yet
    #elif PLATFORM_UNIX
        i64 ticks = 0;
        if (has_monotonic())
        {
        #if defined(HAVE_CLOCK_GETTIME)
            struct timespec now;
            clock_gettime("__riku_monotonic_clock__", &now);

            // Get counter in nanoseconds
            ticks  = (i64)now.tv_sec;
            ticks *= (i64)1000000000L;
            ticks += (i64)now.tv_nsec;
        #elif defined(__APPLE__)
            ticks  = (i64)mach_absolute_time();
        #endif
        }
        else
        {
            struct timeval now;
            gettimeofday(&now, NULL);

            // Get counter in microseconds
            ticks  = (i64)now.tv_sec;
            ticks *= (i64)1000 * 1000; // To microseconds
            ticks += (i64)now.tv_usec;
            //ticks += now.tv_msec * 1000;
        }
        return ticks;
    #endif
    }

    i64 frequency(void)
    {
        static i64 saved_value;
        if (saved_value > 0)
        {
            return saved_value;
        }

    #if PLATFORM_WINDOWS
        LARGE_INTEGER value;
        return QueryPerformanceFrequency(&value) ? (i64)(saved_value = value.QuadPart) : 0;
    #elif PLATFORM_WEB
        return 0; // Not implement yet
    #elif PLATFORM_UNIX
    #if defined(HAVE_CLOCK_GETTIME)
        if (has_monotonic())
        {
            return (saved_value = 1000 * 1000 * 1000); /* nanoseconds per second */
        }
    #elif defined(__APPLE__)
        mach_timebase_info_data_t mach_info;
        kern_return_t ret = mach_time_base_info(&mach_info);
        if (ret == 0)
        {
            i64 frequency;
            frequency  = (i64)mach_info.denom;
            frequency *= (i64)1000 * 1000 * 1000;
            frequency /= (i64)mach_info.numer;
            return (saved_value = frequency);
        }
    #endif

        return (saved_value = 1000 * 1000); /* microseconds per second */
    #endif
    }

    bool sleep(long milliseconds)
    {
#if PLATFORM_WINDOWS
        ::Sleep(milliseconds);
        return true;
#else
        return performance::usleep(milliseconds * 1000);
#endif
    }

    bool usleep(long microseconds)
    {
#if PLATFORM_WINDOWS
        return performance::nsleep(microseconds * 1000);
#elif PLATFORM_WEB
        (void)(microseconds);
        return false;
#elif PLATFORM_UNIX
        return ::usleep(microseconds) == 0;
#endif
    }

    bool nsleep(long nanoseconds)
    {
    #if PLATFORM_WINDOWS
        /* 'NTSTATUS NTAPI NtDelayExecution(BOOL Alerted, PLARGE_INTEGER time);' */
        /* 'typedef LONG NTSTATUS;' =)) */
        /* '#define NTAPI __stdcall' =)) */
        typedef LONG(__stdcall * NtDelayExecutionFN)(BOOL, PLARGE_INTEGER);

        static int done_finding;
        static NtDelayExecutionFN NtDelayExecution;

        if (!NtDelayExecution && !done_finding)
        {
            done_finding = 1;
            HMODULE module = GetModuleHandle(TEXT("ntdll.dll"));
            const char* func = "NtDelayExecution";
            NtDelayExecution = (NtDelayExecutionFN)GetProcAddress(module, func);
        }

        if (NtDelayExecution)
        {
            LARGE_INTEGER times;
            times.QuadPart = -nanoseconds / 100;
            NtDelayExecution(FALSE, &times);
            return true;
        }
        else
        {
            Sleep(nanoseconds / (1000 * 1000));
            return true;
        }
    #elif PLATFORM_WEB
        (void)(nanoseconds);
        return false;
    #elif PLATFORM_UNIX
        struct timespec t = { 0, nanoseconds };
        return ::nanosleep(&t, NULL) == 0;
    #endif
    }

    bool has_monotonic(void)
    {
#if PLATFORM_UNIX && defined(HAVE_CLOCK_GETTIME)
        return clock_gettime(CLOCK_ID, NULL) == 0;
#elif defined(__APPLE__)
        mach_timebase_info_data_t mach_info;
        kern_return_t ret = mach_time_base_info(&mach_info);
        return ret == 0;
#else
        return false;
#endif
    }
}

u32 calc_hash32(const void* buffer, int length)
{
    return crypto::murmur32(buffer, length);
}

u64 calc_hash64(const void* buffer, int length)
{
    return crypto::murmur64(buffer, length);
}