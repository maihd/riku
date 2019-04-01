// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#pragma once

#include "./core.h"

// Dynamic and growable memory container
struct Buffer
{
public:
    byte* data;

public:
    inline Buffer()
        : data(NULL) {}

    inline ~Buffer()
    {
        memory::dealloc(data ? (int*)data - 1 : NULL);
    }

public:
    inline Buffer(Buffer&& buffer)
        : data(buffer.data)
    {
        buffer.data = NULL;
    }

    inline Buffer& operator=(Buffer&& buffer)
    {
        data = buffer.data;
        buffer.data = NULL;
        return *this;
    }

public:
    PROPERTY_READONLY(int, length, get_length);
    inline int get_length(void) const
    {
        return data ? *((int*)data - 1) : 0;
    }

public:
    inline operator byte*(void)
    {
        return data;
    }

    inline operator const byte*(void) const
    {
        return data;
    }

public: // Factory functions
    RIKU_API static Buffer alloc(int length);
};

// Compute hash of given buffer
template <>
inline u64 hashof(const Buffer& buffer)
{
    return calc_hash64(buffer.data, buffer.get_length());
}

// Get length of given buffer
template <>
inline int lengthof(const Buffer& buffer)
{
    return buffer.get_length();
}