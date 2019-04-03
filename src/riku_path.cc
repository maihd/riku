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
        __threadstatic char result[max_length];
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
        __threadstatic char result[max_length];
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
        if (!path)
        {
            return false;
        }

#if PLATFORM_WINDOWS
        return path[0] == '/' || path[0] == '\\' || (isalpha(path[0]) && path[1] == ':' && is_absolute(path + 2));
#else
        return path[0] == '/';
#endif
    }

    bool is_relative(const char* path)
    {
        return !is_absolute(path);
    }

    const char* normalize(const char* path)
    {
        __threadstatic char result[max_length];
        return normalize(path, result, sizeof(result));
    }

    const char* normalize(const char* path, char* buffer, int length)
    {
        if (string::is_empty(path))
        {
            if (buffer) buffer[0] = 0;
            return "";
        }

        const char* ptr = path;
        for (int i = 0, c = *ptr++; c && i < length; c = *ptr++, i++)
        {
            if (c == '.')
            {
                int c1 = ptr[0];
                if (!c1 || c1 == '/' || c1 == ::path::sep[0])
                {
                    i--;
                    ptr++;
                    if (!c1)
                    {
                        buffer[i] = 0;
                        return buffer;
                    }

                    continue;
                }

                int c2 = ptr[1];
                if (c1 == '.' && (!c2 || c2 == '/' || c2 == ::path::sep[0]))
                {
                    i -= 2;
                    while (i > -1 && buffer[i] != ::path::sep[0])
                    {
                        i--;
                    }

                    ptr += 2; 
                        
                    if (!c2)
                    {
                        buffer[i] = 0;
                        return buffer;
                    }

                    continue;
                }
            }

            //if (c == '/')
            //{
            //    c = ::path::sep[0];
            //}
            buffer[i] = (char)c;
        }

        return buffer;
    }

    const char* absolute(const char* path)
    {
        __threadstatic char result[max_length];
        return absolute(path, result, sizeof(result));
    }

    const char* absolute(const char* path, char* buffer, int length)
    {
        if (string::compare(path, ".") == 0)
        {
            return process::cwd(buffer, length);
        }
        else if (is_absolute(path))
        {
            return normalize(path, buffer, length);
        }
        else
        {
            char tmp[max_length] = "";
            return normalize(::path::join(tmp, max_length, process::cwd(), path, NULL), buffer, length);
        }
    }

    const char* relative(const char* from, const char* to)
    {
        __threadstatic char result[max_length];
        return relative(from, to, result, sizeof(result));
    }

    const char* relative(const char* from, const char* to, char* buffer, int length)
    {
        char _tmp0[max_length] = ""; 
        char _tmp1[max_length] = "";
        to   = absolute(to, _tmp0, max_length);
        from = absolute(from, _tmp1, max_length);

        const char* ptr0 = from;
        const char* ptr1 = to;
        
        while (*ptr0 && *ptr1 && *ptr0 == *ptr1)
        {
            ptr0++;
            ptr1++;
        }

        int sep_count = 0;
        if (*ptr1 == '/' || *ptr1 == ::path::sep[0] || *ptr1 == 0)
        {
            sep_count = (*ptr0 == '/' || *ptr0 == ::path::sep[0] || *ptr0 == 0);
        }

        while (*ptr0)
        {
            sep_count += *ptr0 == '/' || *ptr0 == ::path::sep[0];
            ptr0++;
        }

        int i = 0;
        while (sep_count-- > 0 && i < length)
        {
            buffer[i++] = '.';
            buffer[i++] = '.';
            buffer[i++] = ::path::sep[0];
        }
        
        if (length - i - 1 > 0 && *(++ptr1))
        {
            char c;
            while ((c = *ptr1++))
            {
                buffer[i++] = c;
            }
        }

        buffer[i] = 0;
        return buffer;
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
        __threadstatic char result[max_length];
        return join_args(result, sizeof(result), path, args_list);
    }

    const char* join_args(char* buffer, int length, const char* path, ArgsList args_list)
    {
        if (!buffer || length <= 0 || !path)
        {
            return "";
        }

        buffer[0] = 0;
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