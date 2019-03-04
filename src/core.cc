#include <riku/core.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if OS_WINDOWS
#include <Windows.h>
#elif OS_ANDROID
#include <android/log.h>
#endif

Buffer Buffer::alloc(usize length)
{
    Buffer buf;
    if (length)
    {
        buf.data = (byte*)memory::alloc(sizeof(usize) + length);
        *(usize*)buf.data = length;
        buf.data += sizeof(usize);
    }
    return make_rvalue(buf);
}

namespace __riku 
{
    void __assert_print(const char* exp, const char* func, const char* file, int line, const char* fmt, ...)
    {
    #if OS_ANDROID
        char final_fmt[4096];
        sprintf(final_fmt, "Assertion failed!: %s\n\tIn %s:%s:%d\n\tMessage: %s", exp, func, file, line, fmt);

        ArgsList args_list;
        argslist_begin(args_list, fmt);
        __android_log_vprint(ANDROID_LOG_FATAL, "riku", final_fmt, args_list);
        argslist_end(args_list);
    #else
        console::error("Assertion failed!: %s\nIn %s:%s:%d", exp, func, file, line);

        ArgsList args_list;
        argslist_begin(args_list, fmt);
        console::error_args(fmt, args_list);
        argslist_end(args_list);
    #endif
    }
}

namespace memory
{
    void* alloc(usize size)
    {
        return malloc(size);
    }

    void dealloc(void* ptr)
    {
        free(ptr);    
    }

    void* realloc(void* ptr, usize size)
    {
        return ::realloc(ptr, size);
    }

    void* init(void* dst, int val, usize size)
    {
        return memset(dst, val, size);
    }

    void* copy(void* dst, const void* src, usize size)
    {
        return memcpy(dst, src, size);
    }
    
    void* move(void* dst, const void* src, usize size)
    {
        return memmove(dst, src, size);
    }
}

namespace string
{
    usize length(const char* s)
    {
        return strlen(s);
    }
}

namespace console
{
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

    void log_args(const char* fmt, ArgsList args_list)
    {
    #if OS_ANDROID
        __android_log_vprint(ANDROID_LOG_DEFAULT, "riku", fmt, args_list);
    #else
        vfprintf(stdout, fmt, args_list);
        fputc('\n', stdout);
    #endif
    }

    void info_args(const char* fmt, ArgsList args_list)
    {
    #if OS_ANDROID
        __android_log_vprint(ANDROID_LOG_INFO, "riku", fmt, args_list);
    #else
        vfprintf(stdout, fmt, args_list);
        fputc('\n', stdout);
    #endif
    }

    void warn_args(const char* fmt, ArgsList args_list)
    {
    #if OS_ANDROID
        __android_log_vprint(ANDROID_LOG_WARN, "riku", fmt, args_list);
    #else
        vfprintf(stdout, fmt, args_list);
        fputc('\n', stdout);
    #endif
    }

    void error_args(const char* fmt, ArgsList args_list)
    {
    #if OS_ANDROID
        __android_log_vprint(ANDROID_LOG_ERROR, "riku", fmt, args_list);
    #else
        vfprintf(stderr, fmt, args_list);
        fputc('\n', stdout);
    #endif
    }
}

namespace process
{
    const char* cwd(void)
    {
        __threadlocal static char path[1024];

        cwd(path, sizeof(path)); 
        return path;
    }

    usize cwd(char* buffer, usize length)
    {
    #if OS_WINDOWS
        uint size = GetCurrentDirectoryA(length, buffer);
        return size;
    #elif OS_ANDROID
        (void)buffer;
        (void)length;
        return 0;
    #endif
    }

    bool chdir(const char* directory)
    {
    #if OS_WINDOWS
        return SetCurrentDirectoryA(directory);
    #elif OS_ANDROID
        (void)directory;
        return false;
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
}