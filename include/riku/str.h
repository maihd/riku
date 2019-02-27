#pragma once

#include "./types.h"
#include "./define.h"

#include <stdlib.h>
#include <string.h>

struct String;
struct HeapString;

struct HeapString 
{
public: // Members
    char* buffer; 

public:
    inline HeapString() : buffer(nullptr) {}
    inline ~HeapString() 
    { 
        if (buffer)
        {
            free(buffer - sizeof(int)); 
        }
    }

public:
    inline HeapString(HeapString&& other) 
        : buffer(other.buffer)
    {
        other.buffer = nullptr;
    }

    inline HeapString(const HeapString& other) 
    {
        if (other.buffer)
        {
            buffer = (char*)malloc(sizeof(int) + other.length + 1);
            memcpy(buffer, other.buffer - sizeof(int), sizeof(int) + other.length + 1);
        }
        else
        {
            buffer = nullptr;
        }
    }

    inline HeapString(str buffer)
        : HeapString(buffer, strlen(buffer))
    {
    }

    inline HeapString(str buffer, int length)
    {
        if (buffer)
        {
            this->buffer = (char*)malloc(sizeof(int) + length + 1) + sizeof(int);

            *((int*)this->buffer - 1) = length;
            memcpy(this->buffer, buffer, length + 1);
        }
        else
        {
            this->buffer = nullptr;
        }
    }
    
    inline HeapString(const String& string);

public:
    propdef_readonly(get_length) int length;
    inline int get_length() const
    {
        return buffer ? ((int*)buffer - 1)[0] : 0;
    }

public:
    inline operator str() const
    {
        return buffer;
    } 
};

struct String
{
public: // Members
    str buffer;
    int length;

public:
    inline String(void) : buffer(nullptr) {}
    inline ~String(void) {}

    inline String(str buffer)
        : buffer(buffer)
        , length(strlen(buffer)) {}

    inline String(const HeapString& heap_string)
        : buffer(heap_string.buffer)
        , length(heap_string.length) {}

    inline String& operator=(str buffer)
    {
        this->buffer = buffer;
        this->length = strlen(buffer);
        return *this;
    }

    inline String& operator=(const HeapString& heap_string)
    {
        this->buffer = heap_string.buffer;
        this->length = heap_string.length;
        return *this;
    }

public: // Compile-time string
    template <int length>
    inline String(const char(&buffer)[length])
        : length(length)
        , buffer(buffer) {}

    template <int length>
    inline String& operator=(const char(&buffer)[length])
    {
        this->buffer = buffer;
        this->length = length;
        return *this;
    }

public:
    inline operator str() const
    {
        return buffer;
    } 
};

inline HeapString::HeapString(const String& string)
    : HeapString(string.buffer, string.length)
{
}

namespace string
{
    
}