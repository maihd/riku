// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#pragma once

//
// Dynamic string is not commonly using by core module
// Show we move it outside from core for better compile speed
//

#include "./core.h"
#include "./array.h"

// Dynamic and growable string
// @note: should use to store dynamic string only
struct String 
{
public:
    Array<char> buffer;

public:
    PROPERTY_READONLY(int, length, get_length);
    PROPERTY_READONLY(int, capacity, get_capacity);
    PROPERTY_READONLY(char*, characters, get_characters);

    // Get length of string
    inline int get_length(void) const
    {
        return buffer.get_length();
    }

    // Get capacity of buffer
    inline int get_capacity(void) const
    {
        return buffer.get_capacity();
    }

    // Get character array
    inline char* get_characters(void)
    {
        return buffer.get_items();
    }

    // Get character array
    inline const char* get_characters(void) const
    {
        return buffer.get_items();
    }

    // Is string empty
    inline bool is_empty(void) const
    {
        return get_length() <= 0;
    }

    // Is string valid
    inline bool is_valid(void) const
    {
        return get_length()  > 0;
    }

public:
    inline String(void) 
    {
    }

    inline ~String(void) 
    {
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
            int require_size = len;
            target_size  = require_size - 1;
            target_size |= target_size >> 1;
            target_size |= target_size >> 2;
            target_size |= target_size >> 4;
            target_size |= target_size >> 8;
            target_size |= target_size >> 16;
            target_size++;

            bool success = buffer.grow(target_size);
            ASSERT(success, "Out of memory when create buffer for string.");

            buffer.buffer->length = len;
            memory::copy(buffer.buffer->items, str, len + 1);
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
                int require_size = len;
                target_size  = require_size - 1;
                target_size |= target_size >> 1;
                target_size |= target_size >> 2;
                target_size |= target_size >> 4;
                target_size |= target_size >> 8;
                target_size |= target_size >> 16;
                target_size++; 
                
                bool success = buffer.grow(target_size);
                ASSERT(success, "Out of memory when grow buffer of string.");
            }

            buffer.buffer->length = len;
            memory::copy(buffer.buffer->items, str, len + 1);
        }
        else if (buffer.buffer)
        {
            buffer.buffer->length   = 0;
            buffer.buffer->items[0] = 0;
        }
        return *this;
    }

public: // RAII
    inline String(String&& other)
        : buffer(traits::make_rvalue(other.buffer))
    {
        other.buffer.buffer = NULL;
    }

    inline String& operator=(String&& other)
    {
        this->~String();

        buffer.buffer = other.buffer.buffer;
        other.buffer.buffer = NULL;
        return *this;
    }

public: // Copy
    inline String(const String& other)
    {
        if (other.get_length() > 0)
        {
            bool success = buffer.grow(other.get_capacity());
            ASSERT(success, "Out of memory when grow buffer of string.");

            buffer.buffer->length = other.get_length();
            memory::copy(buffer.buffer->items, other.get_characters(), other.get_length() + 1);
        }
    }

    inline String& operator=(const String& other)
    {
        if (other.get_length() > 0)
        {
            bool success = buffer.grow(other.get_capacity());
            ASSERT(success, "Out of memory when grow buffer of string.");

            buffer.buffer->length = other.get_length();
            memory::copy(buffer.buffer->items, other.get_characters(), other.get_length() + 1);
        }
        else if (buffer.buffer)
        {
            buffer.buffer->length = 0;
            buffer.buffer->items[0] = 0;
        }
        return *this;
    }

public:
    inline explicit operator char*(void)
    {
        return this->get_characters();
    }

    inline explicit operator const char*(void) const
    {
        return this->get_characters();
    }

public: // No side-effect functions

    // Get substring
    RIKU_API String  substr(int start) const;
    
    // Get substring
    RIKU_API String  substr(int start, int end) const;

    // Index of character in string
    RIKU_API int     index_of(char value) const;

    // Index of substring in string
    RIKU_API int     index_of(const char* value) const;

    // Last index of character in string
    RIKU_API int     last_index_of(char value) const;

    // Last index of character in string
    RIKU_API int     last_index_of(const char* value) const; 

public: // Side-effect function

    // Concatenate the string the last position
    RIKU_API String& concat(const char* other);

    // Concatenate the string the last position
    RIKU_API String& concat(const String& other);
};

//
// @region: Function-like operators
//

// Compute hash of given string
template <>
inline u64 hashof(const String& string)
{
    return hashof(string.get_characters(), string.get_length());
}

// Get length of given string
template <>
inline int lengthof<String>(const String& string)
{
    return (u32)string.get_length();
}

//
// @region: Operator overloading
//

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