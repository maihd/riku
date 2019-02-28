#include <stdio.h>
#include <riku/core.h>

#if OS_WINDOWS
#include <Windows.h>
#endif

Buffer Buffer::alloc(usize length)
{
    Buffer buf;
    if (length)
    {
        buf.data = (byte*)malloc(sizeof(usize) + length);
        *(usize*)buf.data = length;
        buf.data += sizeof(usize);
    }
    return make_rvalue(buf);
}

namespace __riku 
{
    void __assert_print(str exp, str func, str file, int line, str fmt, ...)
    {
        console::log_error("Assertion failed!\nIn %s:%s:%d", func, file, line);

        ArgsList args_list;
        argslist_begin(args_list, fmt);
        console::log_error_args(fmt, args_list);
        argslist_end(args_list);
    }
}

namespace console
{
    void log(str fmt, ...)
    {
        ArgsList args_list;
        argslist_begin(args_list, fmt);
        log_args(fmt, args_list);
        argslist_end(args_list);
    }
    
    void log_info(str fmt, ...)
    {
        ArgsList args_list;
        argslist_begin(args_list, fmt);
        log_info_args(fmt, args_list);
        argslist_end(args_list);
    }

    void log_warn(str fmt, ...)
    {
        ArgsList args_list;
        argslist_begin(args_list, fmt);
        log_warn_args(fmt, args_list);
        argslist_end(args_list);
    }

    void log_error(str fmt, ...)
    {
        ArgsList args_list;
        argslist_begin(args_list, fmt);
        log_error_args(fmt, args_list);
        argslist_end(args_list);
    }

    void log_args(str fmt, ArgsList args_list)
    {
        vfprintf(stdout, fmt, args_list);
        fputc('\n', stdout);
    }

    void log_info_args(str fmt, ArgsList args_list)
    {
        vfprintf(stdout, fmt, args_list);
        fputc('\n', stdout);
    }

    void log_warn_args(str fmt, ArgsList args_list)
    {
        vfprintf(stdout, fmt, args_list);
        fputc('\n', stdout);
    }

    void log_error_args(str fmt, ArgsList args_list)
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