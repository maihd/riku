#include <riku/core.h>
#include <riku/math.h>
#include <riku/string.h>

#include <stdio.h>
#include <string.h>

//
// UTF8 string
// 

namespace string
{
    __threadstatic char g_buffer[2048];

    char* clone(const char* str)
    {
#if PLATFORM_WINDOWS
        return _strdup(str);
#else
        return strdup(str);
#endif
    }

    int length(const char* str)
    {
        return (int)strlen(str);
    }

    const char* sub(const char* str, int start)
    {
        return sub(str, start, g_buffer, sizeof(g_buffer));
    }

    const char* sub(const char* str, int start, char* buffer, int length)
    {
        return string::copy(buffer, str + start, length);
    }

    const char* sub(const char* str, int start, int end)
    {
        return sub(str, start, end, g_buffer, sizeof(g_buffer));
    }

    const char* sub(const char* str, int start, int end, char* buffer, int length)
    {
        if (end > start)
        {
            return string::copy(buffer, str + start, math::min(length, end - start));
        }
        else
        {
            buffer[0] = 0;
            return buffer;
        }
    }

    const char* copy(char* dst, const char* src)
    {
        return strcpy(dst, src);
    }

    const char* copy(char* dst, const char* src, int length)
    {
        return strncpy(dst, src, (usize)length);
    }

    const char* concat(char* dst, const char* src)
    {
        return strcat(dst, src);
    }

    const char* concat(char* dst, const char* src, int length)
    {
        return strncat(dst, src, (usize)length);
    }

    int compare(const char* dst, const char* src)
    {
        return strcmp(dst, src);
    }

    int compare(const char* dst, const char* src, int length)
    {
        return strncmp(dst, src, (usize)length);
    }

    const char* format(const char* fmt, ...)
    {
        ArgsList args_list;
        argslist_begin(args_list, fmt);
        const char* result = format_args(fmt, args_list);
        argslist_end(args_list);

        return result;
    }

    const char* format(char* buffer, int length, const char* fmt, ...)
    {
        ArgsList args_list;
        argslist_begin(args_list, fmt);
        const char* result = format_args(buffer, (usize)length, fmt, args_list);
        argslist_end(args_list);

        return result;
    }

    const char* format_args(const char* fmt, ArgsList args_list)
    {
        return format_args(g_buffer, sizeof(g_buffer), fmt, args_list);
    }

    const char* format_args(char* buffer, int length, const char* fmt, ArgsList args_list)
    {
        vsnprintf(buffer, (usize)length, fmt, args_list);
        return buffer;
    }

    int index_of(const char* str, char value)
    {
        for (int i = 0, c; (c = *str++); i++)
        {
            if (c == value)
            {
                return i;
            }
        }

        return -1;
    }

    int index_of(const char* str, const char* value)
    {
        int length = string::length(value);
        for (int i = 0, c; (c = *str++); i++)
        {
            if (equals(str, value, length))
            {
                return i;
            }
        }

        return -1;
    }

    int last_index_of(const char* str, char value)
    {
        int r = -1;
        for (int i = 0, c; (c = *str++); i++)
        {
            if (c == value)
            {
                r = i;
            }
        }

        return r;
    }

    int last_index_of(const char* str, const char* value)
    {
        int r = -1;
        int length = string::length(value);
        for (int i = 0, c; (c = *str++); i++)
        {
            if (equals(str, value, length))
            {
                return i;
            }
        }

        return r;
    }
}