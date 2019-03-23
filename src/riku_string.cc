#include <riku/core.h>
#include <riku/string.h>

#include <stdio.h>
#include <string.h>

//
// UTF8 string
// 

namespace string
{
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

#if 0 && PREVIEWING
    const char* sub(const char* str, int start)
    {
        return "";
    }

    const char* sub(const char* str, int start, char* buffer, usize length)
    {
        return "";
    }

    const char* sub(const char* str, int start, int end)
    {
        return "";
    }

    const char* sub(const char* str, int start, int end, char* buffer, usize length)
    {
        return "";
    }
#endif

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
        __threadstatic char buffer[2048];
        vsnprintf(buffer, sizeof(buffer), fmt, args_list);
        return buffer;
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