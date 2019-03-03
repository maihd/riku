#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <riku/core.h>

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
        console::log_error("Assertion failed!\nIn %s:%s:%d", func, file, line);

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
        vfprintf(stdout, fmt, args_list);
        fputc('\n', stdout);
    }

    void log_info_args(const char* fmt, ArgsList args_list)
    {
        vfprintf(stdout, fmt, args_list);
        fputc('\n', stdout);
    }

    void log_warn_args(const char* fmt, ArgsList args_list)
    {
        vfprintf(stdout, fmt, args_list);
        fputc('\n', stdout);
    }

    void log_error_args(const char* fmt, ArgsList args_list)
    {
        vfprintf(stderr, fmt, args_list);
        fputc('\n', stdout);
    }
}

namespace process
{
    HeapString cwd(void)
    {
        char path[1024];
        uint size = GetCurrentDirectoryA(sizeof(path), path);

        return make_rvalue(HeapString(path, size));
    }
}