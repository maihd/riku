#include <riku/core.h>
#include <riku/math.h>
#include <riku/string.h>

#include <stdio.h>
#include <stdlib.h>
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

    const char* substr(const char* str, int start)
    {
        return substr(str, start, g_buffer, sizeof(g_buffer));
    }

    const char* substr(const char* str, int start, char* buffer, int length)
    {
        return string::copy(buffer, str + start, length);
    }

    const char* substr(const char* str, int start, int end)
    {
        return substr(str, start, end, g_buffer, sizeof(g_buffer));
    }

    const char* substr(const char* str, int start, int end, char* buffer, int length)
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

    i32 to_i32(const char* str)
    {
        return atoi(str);
    }

    u32 to_u32(const char* str)
    {
        return (u32)atoi(str);
    }

    i64 to_i64(const char* str)
    {
        return atoll(str);
    }

    u64 to_u64(const char* str)
    {
        return (u64)atoll(str);
    }

    int to_int(const char* str)
    {
        return string::to_i32(str);
    }

    uint to_uint(const char* str)
    {
        return string::to_u32(str);
    }

    float to_float(const char* str)
    {
        return (float)atof(str);
    }

    double to_double(const char* str)
    {
        return atof(str);
    }
}

String String::substr(int start) const
{
    return String(string::substr(this->get_characters(), start));
}

String String::substr(int start, int end) const
{
    return String(string::substr(this->get_characters(), start, end));
}

int String::index_of(char value) const
{
    return string::index_of(this->get_characters(), value);
}

int String::index_of(const char* value) const
{
    return string::index_of(this->get_characters(), value);
}

int String::last_index_of(char value) const
{
    return string::last_index_of(this->get_characters(), value);
}

int String::last_index_of(const char* value) const
{
    return string::last_index_of(this->get_characters(), value);
}

String& String::concat(const char* other)
{
    int length = string::length(other);
    int new_length = this->get_length() + length;
    if (this->get_capacity() < new_length)
    {
        int target_size;
        int require_size = (new_length);
        target_size = require_size - 1;
        target_size |= target_size >> 1;
        target_size |= target_size >> 2;
        target_size |= target_size >> 4;
        target_size |= target_size >> 8;
        target_size |= target_size >> 16;
        target_size++;

        bool success = buffer.grow(target_size);
        ASSERT(success, "Out of memory when grow buffer of string.");
    }

    string::concat(this->get_characters(), other, length);
    return *this;
}

String& String::concat(const String& other)
{
    int length = other.get_length();
    int new_length = this->get_length() + length;
    if (this->get_capacity() < new_length)
    {
        int target_size;
        int require_size = (new_length);
        target_size = require_size - 1;
        target_size |= target_size >> 1;
        target_size |= target_size >> 2;
        target_size |= target_size >> 4;
        target_size |= target_size >> 8;
        target_size |= target_size >> 16;
        target_size++;

        bool success = buffer.grow(target_size);
        ASSERT(success, "Out of memory when grow buffer of string.");
    }

    string::concat(this->get_characters(), other.get_characters(), length);
    return *this;
}