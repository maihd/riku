#pragma once

#include "./types.h"
#include "./define.h"

#include <stdlib.h>
#include <string.h>

template <typename TItem>
struct Array 
{
public:
    TItem* buffer;

public:
    inline Array(void)
        : buffer(nullptr)
    {
    }

    inline ~Array(void)
    {
        if (buffer)
        {
            free((int*)buffer - 2);
        }
    }

public: // RAII
    inline Array(Array<TItem>&& other)
        : buffer(other.buffer)
    {
        other.buffer = nullptr;
    }

    inline Array<TItem>& operator=(Array<TItem>&& other)
    {
        if (buffer)
        {
            free((int*)buffer - 2);
        }

        buffer = other.buffer;
        other.buffer = nullptr;

        return *this;
    }

public: // Properties
    propdef_readonly(get_length)   int length;
    propdef_readonly(get_capacity) int capacity;
    
    inline int get_length(void) const
    {
        return buffer ? ((int*)buffer - 2)[1] : 0;
    }

    inline int get_capacity(void) const
    {
        return buffer ? ((int*)buffer - 2)[0] : 0;
    }

public: // Indexor
    inline TItem& operator[](int index)
    {
        return buffer[index];
    }

    inline const TItem& operator[](int index) const
    {
        return buffer[index];
    }

public: // Conversion
    inline operator TItem*(void)
    {
        return buffer;
    }

    inline operator const TItem*(void) const
    {
        return buffer;
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
        int* old_raw = array.buffer ? raw(array) : nullptr;
        int* new_raw = (int*)realloc(old_raw, sizeof(int) * 2 + new_size * sizeof(TItem));

        if (new_raw)
        {
            if (!old_raw)
            {
                new_raw[1] = 0;
            }

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
            int new_size = array.capacity;
            new_size = new_size * 2 + (new_size <= 0) * 8; // no if statement or '?' operator (ternary operator)
            while (new_size < size) new_size *= 2;
            return grow(array, new_size);
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
        int dst_len = dst.length;
        int src_len = src.length;
        int new_len = dst_len + src_len;
        if (!ensure(dst, new_len))
        {
            return false;
        }

        memcpy(dst.buffer + dst.length, src.buffer, src_len * sizeof(TItem));
        raw(dst)[1] = new_len;
        return true;
    }
    
    template <typename TItem>
    inline void clear(Array<TItem>& array)
    {
        if (array.buffer) 
        {
            raw(res)[1] = 0;
        }
    }

    template <typename TItem>
    inline Array<TItem> clone(const Array<TItem>& array)
    {
        Array<TItem> res;

        int len = array.length;
        int cap = array.capacity;
        if (len > 0 && cap > 0)
        {
            if (grow(res, cap))
            {
                raw(res)[1] = len;
                memcpy(res.buffer, array.buffer, len * sizeof(TItem));
            }
        }

        return make_rvalue(res);
    }
}