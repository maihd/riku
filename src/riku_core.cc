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
#include <android/log.h>
#elif PLATFORM_UNIX
#include <unistd.h>
#include <sys/time.h>
#endif

//
// Buffer functions
//

Buffer Buffer::alloc(int length)
{
    Buffer buf;
    if (length)
    {
        buf.data = (byte*)memory::alloc(sizeof(int) + length);
        *(int*)buf.data = length;
        buf.data += sizeof(int);
    }
    return traits::make_rvalue(buf);
}

//
// Memory
// 

namespace memory
{
    void* alloc(int size)
    {
        return alloc(size, 16);
    }

    void dealloc(void* ptr)
    {
        if (ptr)
        {
            void* org_ptr = dealign(ptr);
            free(org_ptr);
        }
    }

    void* realloc(void* ptr, int size)
    {
        return realloc(ptr, size, 16);
    }

    void* alloc(int size, int align)
    {
        return memory::align(malloc((usize)size + align), align);
    }

    void* realloc(void* ptr, int size, int align)
    {
        if (ptr)
        {
            void* org_ptr = dealign(ptr);
            return memory::align(::realloc(org_ptr, (usize)(size + align)), align);
        }
        else
        {
            return alloc(size, align);
        }
    }

    void* init(void* dst, int val, int size)
    {
        return memset(dst, val, (usize)size);
    }

    void* copy(void* dst, const void* src, int size)
    {
        return memcpy(dst, src, (usize)size);
    }
    
    void* move(void* dst, const void* src, int size)
    {
        return memmove(dst, src, (usize)size);
    }

    int compare(const void* a, const void* b, int size)
    {
        return memcmp(a, b, (usize)size);
    }
}

//
// Console
//

namespace console
{
    static char s_log_tag[1024] = "Riku";

    const char* get_log_tag(void)
    {
        return s_log_tag;
    }

    const char* set_log_tag(const char* tag)
    {
        return string::copy(s_log_tag, tag, sizeof(s_log_tag));
    }

    void log(const char* fmt, ...)
    {
        ArgsList args_list;
        argslist_begin(args_list, fmt);
        log_args(fmt, args_list);
        argslist_end(args_list);
    }
    
    void info(const char* fmt, ...)
    {
        ArgsList args_list;
        argslist_begin(args_list, fmt);
        info_args(fmt, args_list);
        argslist_end(args_list);
    }

    void warn(const char* fmt, ...)
    {
        ArgsList args_list;
        argslist_begin(args_list, fmt);
        warn_args(fmt, args_list);
        argslist_end(args_list);
    }

    void error(const char* fmt, ...)
    {
        ArgsList args_list;
        argslist_begin(args_list, fmt);
        error_args(fmt, args_list);
        argslist_end(args_list);
    }

    void log_assert(const char* exp, const char* func, const char* file, int line, const char* fmt, ...)
    {
        ArgsList args_list;
        argslist_begin(args_list, fmt);
        log_assert_args(exp, func, file, line, fmt, args_list);
        argslist_end(args_list);
    }

    void log_args(const char* fmt, ArgsList args_list)
    {
    #if PLATFORM_ANDROID
        __android_log_vprint(ANDROID_LOG_DEFAULT, s_log_tag, fmt, args_list);
    #else
        vfprintf(stdout, fmt, args_list);
        fputc('\n', stdout);
    #endif
    }

    void info_args(const char* fmt, ArgsList args_list)
    {
    #if PLATFORM_ANDROID
        __android_log_vprint(ANDROID_LOG_INFO, s_log_tag, fmt, args_list);
    #else
        vfprintf(stdout, fmt, args_list);
        fputc('\n', stdout);
    #endif
    }

    void warn_args(const char* fmt, ArgsList args_list)
    {
    #if PLATFORM_ANDROID
        __android_log_vprint(ANDROID_LOG_WARN, s_log_tag, fmt, args_list);
    #else
        vfprintf(stdout, fmt, args_list);
        fputc('\n', stdout);
    #endif
    }

    void error_args(const char* fmt, ArgsList args_list)
    {
    #if PLATFORM_ANDROID
        __android_log_vprint(ANDROID_LOG_ERROR, s_log_tag, fmt, args_list);
    #else
        vfprintf(stderr, fmt, args_list);
        fputc('\n', stdout);
    #endif
    }

    void log_assert_args(const char* exp, const char* func, const char* file, int line, const char* fmt, ArgsList args_list)
    {
#if PLATFORM_ANDROID
        char final_fmt[4096];
        string::format(final_fmt, "Assertion failed!: %s\n\tIn %s:%s:%d\n\tMessage: %s", exp, func, file, line, fmt);

        __android_log_vprint(ANDROID_LOG_FATAL, s_log_tag, final_fmt, args_list);
#else
        console::error("Assertion failed!: %s\nIn %s:%s:%d", exp, func, file, line);

        console::error_args(fmt, args_list);
#endif

        process::abort();
    }
}

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
    long now(void)
    {
    #if PLATFORM_WINDOWS
        LARGE_INTEGER value;
        return QueryPerformanceCounter(&value) ? (long)value.QuadPart : 0;
    #elif PLATFORM_WEB
        return 0;
    #elif PLATFORM_UNIX
        long ticks = 0;
        if (has_monotonic())
        {
        #if defined(HAVE_CLOCK_GETTIME)
            struct timespec now;
            clock_gettime("__riku_monotonic_clock__", &now);

            // Get counter in nanoseconds
            ticks  = now.tv_sec;
            ticks *= 1000000000;
            ticks += now.tv_nsec;
        #elif defined(__APPLE__)
            ticks  = mach_absolute_time();
        #endif
        }
        else
        {
            struct timeval now;
            gettimeofday(&now, NULL);

            // Get counter in microseconds
            ticks  = now.tv_sec;
            ticks *= 1000 * 1000; // To microseconds
            ticks += now.tv_usec;
            //ticks += now.tv_msec * 1000;
        }
        return ticks;
    #endif
    }

    long frequency(void)
    {
    #if PLATFORM_WINDOWS
        LARGE_INTEGER value;
        return QueryPerformanceFrequency(&value) ? (long)value.QuadPart : 0;
    #elif PLATFORM_UNIX
    #if defined(HAVE_CLOCK_GETTIME)
        if (has_monotonic())
        {
            return 1000 * 1000 * 1000; /* nanoseconds per second */
        }
    #elif defined(__APPLE__)
        mach_timebase_info_data_t mach_info;
        kern_return_t ret = mach_time_base_info(&mach_info);
        if (ret == 0)
        {
            long frequency;
            frequency  = mach_info.denom;
            frequency *= 1000 * 1000 * 1000;
            frequency /= mach_info.numer;
            return frequency;
        }
    #endif

        return 1000 * 1000; /* microseconds per second */
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