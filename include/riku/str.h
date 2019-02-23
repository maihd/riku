#pragma once

#include "./types.h"
#include "./define.h"

#include <stdlib.h>
#include <string.h>

struct String;
struct HeapString;

struct String
{
public: // Members
    char* buffer;

public:
    inline String() : buffer(nullptr) {}
    inline ~String() {}

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
    inline HeapString(HeapString&& other) : buffer(other.buffer)
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

    inline HeapString(const String& other)
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

namespace string
{
    
}