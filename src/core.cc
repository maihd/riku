#include <riku/core.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if OS_WINDOWS
#include <Windows.h>
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
        console::log_error("Assertion failed!: %s\nIn %s:%s:%d", exp, func, file, line);

        ArgsList args_list;
        argslist_begin(args_list, fmt);
        console::log_error_args(fmt, args_list);
        argslist_end(args_list);
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
    
    void log_info(const char* fmt, ...)
    {
        ArgsList args_list;
        argslist_begin(args_list, fmt);
        log_info_args(fmt, args_list);
        argslist_end(args_list);
    }

    void log_warn(const char* fmt, ...)
    {
        ArgsList args_list;
        argslist_begin(args_list, fmt);
        log_warn_args(fmt, args_list);
        argslist_end(args_list);
    }

    void log_error(const char* fmt, ...)
    {
        ArgsList args_list;
        argslist_begin(args_list, fmt);
        log_error_args(fmt, args_list);
        argslist_end(args_list);
    }

    void log_args(const char* fmt, ArgsList args_list)
    {
    #if OS_ANDROID

    #else
        vfprintf(stdout, fmt, args_list);
        fputc('\n', stdout);
    #endif
    }

    void log_info_args(const char* fmt, ArgsList args_list)
    {
    #if OS_ANDROID

    #else
        vfprintf(stdout, fmt, args_list);
        fputc('\n', stdout);
    #endif
    }

    void log_warn_args(const char* fmt, ArgsList args_list)
    {
    #if OS_ANDROID

    #else
        vfprintf(stdout, fmt, args_list);
        fputc('\n', stdout);
    #endif
    }

    void log_error_args(const char* fmt, ArgsList args_list)
    {
    #if OS_ANDROID

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