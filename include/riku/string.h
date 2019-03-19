// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#pragma once

//
// Dynamic string is not commonly using by core module
// Show we move it outside from core for better compile speed
//

#include "./core.h"

// String: high-level string type, use to store dynamic string
struct String 
{
public:
    struct Buffer
    {
        int  length;
        int  capacity;
        char characters[1];
    };
    Buffer* buffer;


public:
    PROPERTY_READONLY(int, length, get_length);
    PROPERTY_READONLY(int, capacity, get_capacity);
    PROPERTY_READONLY(char*, characters, get_characters);

    inline int get_length(void) const
    {
        return buffer ? buffer->length : 0;
    }

    inline int get_capacity(void) const
    {
        return buffer ? buffer->capacity : 0;
    }

    inline char* get_characters(void)
    {
        return buffer ? buffer->characters : NULL;
    }

    inline const char* get_characters(void) const
    {
        return buffer ? buffer->characters : NULL;
    }

    inline bool is_empty(void) const
    {
        return get_length() <= 0;
    }

    inline bool is_valid(void) const
    {
        return get_length()  > 0;
    }

public:
    inline String() 
        : buffer(NULL) {}

    inline ~String() 
    { 
        if (buffer)
        {
            memory::dealloc(buffer); 
        }
    }

public:
    inline String(const char* str)
        : String(str, (int)string::length(str))
    {
    }

    inline String(const char* str, int len)
    {
        if (str && len > 0)
        {
            int target_size;
            int require_size = (sizeof(Buffer) + len);
            target_size  = require_size - 1;
            target_size |= target_size >> 1;
            target_size |= target_size >> 2;
            target_size |= target_size >> 4;
            target_size |= target_size >> 8;
            target_size |= target_size >> 16;
            target_size++;

            this->buffer = (Buffer*)memory::alloc(target_size);
            this->buffer->length   = (int)len;
            this->buffer->capacity = (int)(target_size - sizeof(Buffer));

            memory::copy(this->buffer->characters, str, len + 1);
        }
        else
        {
            this->buffer = NULL;
        }
    }

    inline String& operator=(const char* str)
    {
        int len = (int)string::length(str);
        if (str && len > 0)
        {
            if (get_capacity() < len)
            {
                int target_size;
                int require_size = (sizeof(Buffer) + len);
                target_size  = require_size - 1;
                target_size |= target_size >> 1;
                target_size |= target_size >> 2;
                target_size |= target_size >> 4;
                target_size |= target_size >> 8;
                target_size |= target_size >> 16;
                target_size++;

                buffer = (Buffer*)memory::realloc(buffer, target_size);
                buffer->capacity = target_size - sizeof(Buffer);
            }
            
            this->buffer->length = len;
            memory::copy(this->buffer->characters, str, len + 1);
        }
        else
        {
            buffer->length        = 0;
            buffer->characters[0] = 0;
        }
        return *this;
    }

public: // RAII
    inline String(String&& other)
        : buffer(other.buffer)
    {
        other.buffer = NULL;
    }

    inline String& operator=(String&& other)
    {
        memory::dealloc(buffer ? buffer - sizeof(int) : NULL);
        buffer = other.buffer;
        other.buffer = NULL;
        return *this;
    }

public: // Copy
    inline String(const String& other)
    {
        if (other.buffer)
        {
            int len = other.get_length();

            buffer = (Buffer*)memory::alloc(sizeof(Buffer) + len);
            buffer->length   = len;
            buffer->capacity = len;

            memory::copy(buffer->characters, other.buffer->characters, len + 1);
        }
        else
        {
            buffer = NULL;
        }
    }

    inline String& operator=(const String& other)
    {
        if (other.buffer)
        {
            int len = other.get_length();
            if (get_capacity() < len)
            {
                buffer = (Buffer*)memory::realloc(buffer, sizeof(Buffer) + other.get_capacity());
                buffer->capacity = other.get_capacity();
            }

            buffer->length = len;
            memory::copy(buffer->characters, other.buffer->characters, len + 1);
        }
        else if (buffer)
        {
            buffer->length        = 0;
            buffer->characters[0] = 0;
        }
        return *this;
    }

public:
    inline explicit operator char*(void)
    {
        return buffer ? buffer->characters : NULL;
    }

    inline explicit operator const char*(void) const
    {
        return buffer ? buffer->characters : NULL;
    } 
};

template <>
inline u64 hashof(const String& string)
{
    return hashof(string.get_characters(), string.get_length());
}

template <>
inline u32 lengthof<String>(const String& string)
{
    return (u32)string.get_length();
}

inline bool operator==(const String& a, const String& b)
{
    return string::compare(a.get_characters(), b.get_characters()) == 0;
}

inline bool operator!=(const String& a, const String& b)
{
    return string::compare(a.get_characters(), b.get_characters()) != 0;
}

inline bool operator>(const String& a, const String& b)
{
    return string::compare(a.get_characters(), b.get_characters()) > 0;
}

inline bool operator<(const String& a, const String& b)
{
    return string::compare(a.get_characters(), b.get_characters()) < 0;
}

inline bool operator>=(const String& a, const String& b)
{
    return string::compare(a.get_characters(), b.get_characters()) >= 0;
}

inline bool operator<=(const String& a, const String& b)
{
    return string::compare(a.get_characters(), b.get_characters()) <= 0;
}

inline bool operator==(const char* a, const String& b)
{
    return string::compare(a, b.get_characters()) == 0;
}

inline bool operator!=(const char* a, const String& b)
{
    return string::compare(a, b.get_characters()) != 0;
}

inline bool operator>(const char* a, const String& b)
{
    return string::compare(a, b.get_characters()) > 0;
}

inline bool operator<(const char* a, const String& b)
{
    return string::compare(a, b.get_characters()) < 0;
}

inline bool operator>=(const char* a, const String& b)
{
    return string::compare(a, b.get_characters()) >= 0;
}

inline bool operator<=(const char* a, const String& b)
{
    return string::compare(a, b.get_characters()) <= 0;
}

inline bool operator==(const String& a, const char* b)
{
    return string::compare(a.get_characters(), b) == 0;
}

inline bool operator!=(const String& a, const char* b)
{
    return string::compare(a.get_characters(), b) != 0;
}

inline bool operator>(const String& a, const char* b)
{
    return string::compare(a.get_characters(), b) > 0;
}

inline bool operator<(const String& a, const char* b)
{
    return string::compare(a.get_characters(), b) < 0;
}

inline bool operator>=(const String& a, const char* b)
{
    return string::compare(a.get_characters(), b) >= 0;
}

inline bool operator<=(const String& a, const char* b)
{
    return string::compare(a.get_characters(), b) <= 0;
}