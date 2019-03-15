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
public: // Members
    struct Buffer
    {
        int  length;
        int  capacity;
        char characters[1];
    };
    Buffer* buffer;

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
    inline String(const char* buffer)
        : String(buffer, string::length(buffer))
    {
    }

    inline String(const char* buffer, int length)
    {
        if (buffer)
        {
            this->buffer = (Buffer*)memory::alloc(sizeof(Buffer) + length);
            this->buffer->length   = length;
            this->buffer->capacity = length;

            memory::copy(this->buffer->characters, buffer, length + 1);
        }
        else
        {
            this->buffer = NULL;
        }
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
            if (buffer->capacity < len)
            {
                buffer = (Buffer*)memory::realloc(buffer, sizeof(Buffer) + len);
                buffer->capacity = len;
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
    PROPERTY_READONLY(int, length, get_length);
    PROPERTY_READONLY(int, capacity, get_capacity);

    inline int get_length(void) const
    {
        return buffer ? buffer->length : 0;
    }

    inline int get_capacity(void) const
    {
        return buffer ? buffer->capacity : 0;
    }

    inline bool is_empty(void) const
    {
        return !buffer || buffer->characters[0] <= 0;
    }

public:
    inline operator char*(void)
    {
        return buffer ? buffer->characters : NULL;
    }

    inline operator const char*(void) const
    {
        return buffer ? buffer->characters : NULL;
    } 
};