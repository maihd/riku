// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#include <riku/path.h>

namespace path
{
    const char* basename(const char* path)
    {
        __threadstatic char result[max_size];
        return basename(path, result, sizeof(result));
    }

    const char* basename(const char* path, const char* ext)
    {
        __threadstatic char result[max_size];
        return basename(path, ext, result, sizeof(result));
    }

    const char* basename(const char* path, char* buffer, int length)
    {
        return basename(path, "", buffer, length);
    }

    const char* basename(const char* path, const char* ext, char* buffer, int length)
    {
        ALWAYS_FALSE_ASSERT("path::basename is not implemented!");
        return "";
    }

    const char* dirname(const char* path, char* buffer, int length)
    {
        ALWAYS_FALSE_ASSERT("path::dirname is not implemented!");
        return "";
    }

    const char* dirname(const char* path)
    {
        __threadstatic char result[max_size];
        return dirname(path, result, sizeof(result));
    }

    const char* extname(const char* path, char* buffer, int length)
    {
        ALWAYS_FALSE_ASSERT("path::extname is not implemented!");
        return "";
    }

    const char* extname(const char* path)
    {
        ALWAYS_FALSE_ASSERT("path::extname is not implemented!");
        return "";
    }

    bool is_absolute(const char* path)
    {
        ALWAYS_FALSE_ASSERT("path::is_absolute is not implemented!");
        return "";
    }

    bool is_relative(const char* path)
    {
        ALWAYS_FALSE_ASSERT("path::is_relative is not implemented!");
        return "";
    }

    const char* absolute(const char* path)
    {
        __threadstatic char result[max_size];
        return absolute(path, result, sizeof(result));
    }

    const char* absolute(const char* path, char* buffer, int length)
    {
        ALWAYS_FALSE_ASSERT("path::absolute is not implemented!");
        return "";
    }

    const char* relative(const char* from, const char* to)
    {
        __threadstatic char result[max_size];
        return relative(from, to, result, sizeof(result));
    }

    const char* relative(const char* from, const char* to, char* buffer, int length)
    {
        ALWAYS_FALSE_ASSERT("path::relative is not implemented!");
        return "";
    }

    //const char* relative(const char* path, ...);
    //const char* relative(char* buffer, usize length, const char* path, ...);

    const char* join(const char* path, ...)
    {
        ArgsList args_list;
        argslist_begin(args_list, path);
        const char* ret = join_args(path, args_list);
        argslist_end(args_list);

        return ret;
    }

    const char* join(char* buffer, int length, const char* path, ...)
    {
        ArgsList args_list;
        argslist_begin(args_list, path);
        const char* ret = join_args(buffer, length, path, args_list);
        argslist_end(args_list);

        return ret;
    }

    const char* join_args(const char* path, ArgsList args_list)
    {
        __threadstatic char result[max_size];
        return join_args(result, sizeof(result), path, args_list);
    }

    const char* join_args(char* buffer, int length, const char* path, ArgsList args_list)
    {
        if (!buffer || length <= 0 || !path)
        {
            return "";
        }

        while (true)
        {
            string::concat(buffer, path, length);
            length -= string::length(path);

            path = argslist_next(args_list, const char*);
            if (path)
            {
                string::concat(buffer, ::path::sep, length);
                length -= string::length(::path::sep);
            }
            else
            {
                break;
            }
        }
    
        return buffer;
    }
}