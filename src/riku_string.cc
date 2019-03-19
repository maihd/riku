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

    usize length(const char* str)
    {
        return strlen(str);
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

    const char* copy(char* dst, const char* src, usize length)
    {
        return strncpy(dst, src, length);
    }

    const char* concat(char* dst, const char* src)
    {
        return strcat(dst, src);
    }

    const char* concat(char* dst, const char* src, usize length)
    {
        return strncat(dst, src, length);
    }

    int compare(const char* dst, const char* src)
    {
        return strcmp(dst, src);
    }

    int compare(const char* dst, const char* src, usize length)
    {
        return strncmp(dst, src, length);
    }

    const char* format(const char* fmt, ...)
    {
        ArgsList args_list;
        argslist_begin(args_list, fmt);
        const char* result = format_args(fmt, args_list);
        argslist_end(args_list);

        return result;
    }

    const char* format(char* buffer, usize length, const char* fmt, ...)
    {
        ArgsList args_list;
        argslist_begin(args_list, fmt);
        const char* result = format_args(buffer, length, fmt, args_list);
        argslist_end(args_list);

        return result;
    }

    const char* format_args(const char* fmt, ArgsList args_list)
    {
        __threadstatic char buffer[2048];
        vsnprintf(buffer, sizeof(buffer), fmt, args_list);
        return buffer;
    }

    const char* format_args(char* buffer, usize length, const char* fmt, ArgsList args_list)
    {
        vsnprintf(buffer, length, fmt, args_list);
        return buffer; 
    }
}