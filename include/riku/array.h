#pragma once

#include "./types.h"
#include "./define.h"
#include "./property.h"

#include <stdlib.h>
#include <string.h>

template <typename TItem>
struct Array 
{
public:
    TItem* buffer;

public:
    inline Array()
        : buffer(nullptr)
    {
    }

    inline ~Array()
    {
        if (buffer)
        {
            free((int*)buffer - 2);
        }
    }

public:
    propdef_readonly(get_length)   int length;
    propdef_readonly(get_capacity) int capacity;
    
    inline int get_length() const
    {
        return buffer ? ((int*)buffer - 2)[1] : 0;
    }

    inline int get_capacity() const
    {
        return buffer ? ((int*)buffer - 2)[0] : 0;
    }

public:
    inline TItem& operator[](int index)
    {
        return buffer[index];
    }

    inline const TItem& operator[](int index) const
    {
        return buffer[index];
    }
};

namespace array 
{
    template <typename TItem>
    inline int* raw(const Array<TItem>& array)
    {
        return (int*)array.buffer - 2;
    }

    template <typename TItem>
    inline bool grow(Array<TItem>& array, int new_size)
    {
        int  old_size = array.capacity;
        int* old_raw  = array.buffer ? raw(array) : nullptr;
        int* new_raw  = (int*)realloc(old_raw, sizeof(int) * 2 + new_size * sizeof(TItem));

        if (new_raw)
        {
            new_raw[0]   = new_size;
            array.buffer = new_raw + 2;
            return true; 
        }
        else 
        {
            return false;
        }
    }

    template <typename TItem>
    inline bool ensure(Array<TItem>& array, int size)
    {
        if (array.capacity >= size)
        {
            return true;
        }
        else
        {
            return grow(array, array.capacity * 2);
        }
    }

    template <typename TItem>
    inline bool ensure(const Array<TItem>& array, int size)
    {
        return (array.capacity >= size);
    }

    template <typename TItem>
    inline bool push(Array<TItem>& array, const TItem& value)
    {
        if (!ensure(array, array.length + 1))
        {
            return false;
        }

        int index = array.length;
        raw(array)[1] = index + 1;
        array.buffer[index] = value;
        return true;   
    }

    template <typename TItem>
    inline const TItem& pop(Array<TItem>& array)
    {
        return array.buffer[--raw(array)[1]];
    }

    template <typename TItem>
    inline TItem shift(Array<TItem>& array)
    {
        TItem result = array.buffer[0];
        raw(array)[1] = array.length - 1;
        memmove(array.buffer, array.buffer + 1, array.length * sizeof(TItem));
        return result;
    }

    template <typename TItem>
    inline bool unshift(Array<TItem>& array, const TItem& value)
    {
        if (!ensure(array, array.length + 1))
        {
            return false;
        }

        memmove(array.buffer + 1, array.buffer, array.length * sizeof(TItem));
        raw(array)[1] = array.length + 1;
        array.buffer[0] = value;
        return true;
    }

    template <typename TItem>
    inline int index_of(const Array<TItem>& array, const TItem& value)
    {
        for (int i = 0, n = array.length; i < n; i++)
        {
            if (array.buffer[i] == value)
            {
                return i;
            }
        }

        return -1;
    }

    template <typename TItem>
    inline int last_index_of(const Array<TItem>& array, const TItem& value)
    {
        int index = -1;
        for (int i = 0, n = array.length; i < n; i++)
        {
            if (array.buffer[i] == value)
            {
                index = i;
            }
        }

        return index;
    }

    template <typename TItem>
    inline bool concat(Array<TItem>& dst, const Array<TItem>& src)
    {
        if (!ensure(dst, dst.length + src.length))
        {
            return false;
        }

        memcpy(dst.buffer + dst.length, src.buffer, src.length * sizeof(TItem));
        raw(dst)[1] = dst.length + src.length;
        return true;
    }
}