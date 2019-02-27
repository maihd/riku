#include <riku/console.h>

#include <stdio.h>

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
    }

    void log_info_args(str fmt, ArgsList args_list)
    {
        vfprintf(stdout, fmt, args_list);
    }

    void log_warn_args(str fmt, ArgsList args_list)
    {
        vfprintf(stdout, fmt, args_list);
    }

    void log_error_args(str fmt, ArgsList args_list)
    {
        vfprintf(stderr, fmt, args_list);
    }
}