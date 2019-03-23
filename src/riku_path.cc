// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#include <riku/path.h>
#include <ctype.h>

namespace path
{
    const char* basename(const char* path)
    {
        int index = string::last_index_of(path, ::path::sep);
        if (index)
        {
            return path + index + 1;
        }
        else
        {
            return path;
        }
    }

    const char* basename(const char* path, const char* ext)
    {
        __threadstatic char result[max_size];
        return basename(path, ext, result, sizeof(result));
    }

    const char* basename(const char* path, char* buffer, int length)
    {
        const char* result = ::path::basename(path);
        return string::copy(buffer, result, length);
    }

    const char* basename(const char* path, const char* ext, char* buffer, int length)
    {
        ::path::basename(path, buffer, length); 
        int index = string::last_index_of(buffer, ext);
        if (index)
        {
            buffer[index - 1] = 0;
        }
        return buffer;
    }

    const char* dirname(const char* path)
    {
        __threadstatic char result[max_size];
        return dirname(path, result, sizeof(result));
    }

    const char* dirname(const char* path, char* buffer, int length)
    {
        string::copy(buffer, path, length);
        int index = string::last_index_of(path, ::path::sep);
        if (index)
        {
            buffer[index] = 0;
        }
        return buffer;
    }

    const char* extname(const char* path)
    {
        int index = string::last_index_of(path, '.');
        if (index)
        {
            return path + index + 1;
        }
        else
        {
            return "";
        }
    }

    const char* extname(const char* path, char* buffer, int length)
    {
        const char* result = ::path::extname(path);
        return string::copy(buffer, result, length);
    }

    bool is_absolute(const char* path)
    {
#if PLATFORM_WINDOWS
        return path[0] == '/' || path[0] == '\\' || (isalpha(path[0]) && path[1] == ':');
#else
        return path[0] == '/';
#endif
    }

    bool is_relative(const char* path)
    {
        return !is_absolute(path);
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