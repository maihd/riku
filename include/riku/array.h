#pragma once

#include "./core.h"

#include <stdlib.h>
#include <string.h>

template <typename TItem>
struct Array 
{
public:
    struct Buffer
    {
        int   length;
        int   capacity;
        TItem items[1];
    };

public:
    Buffer* buffer;

public:
    __forceinline Array(void)
        : buffer(nullptr)
    {
    }

    __forceinline ~Array(void)
    {
        free(buffer);
    }

public: // RAII
    inline Array(Array<TItem>&& other)
        : buffer(other.buffer)
    {
        other.buffer = nullptr;
    }

    inline Array<TItem>& operator=(Array<TItem>&& other)
    {
        free(buffer);
        buffer = other.buffer;
        other.buffer = nullptr;

        return *this;
    }

public: // Properties
    propdef_readonly(get_length)   int length;
    propdef_readonly(get_capacity) int capacity;
    
    __forceinline int get_length(void) const
    {
        return buffer ? buffer->length : 0;
    }

    __forceinline int get_capacity(void) const
    {
        return buffer ? buffer->capacity : 0;
    }

public: // Indexor
    __forceinline TItem& operator[](int index)
    {
        return buffer->items[index];
    }

    __forceinline const TItem& operator[](int index) const
    {
        return buffer->items[index];
    }

public: // Conversion
    __forceinline operator TItem*(void)
    {
        return buffer->items;
    }

    __forceinline operator const TItem*(void) const
    {
        return buffer->items;
    }
};

template <typename TValue>
struct TempArray
{
public:
    int           length;
    const uint    capacity;
    TValue* const items;

public:
    __forceinline explicit TempArray(uint capacity = 64)
        : length(0)
        , capacity(capacity)
#if NDEBUG
        , items((TValue*)_alloca(capacity * sizeof(TValue)))
#else
        , items((TValue*)malloc(capacity * sizeof(TValue)))
#endif
    {
    }

    __forceinline ~TempArray(void)
    {
#if !defined(NDEBUG)
        free(items);
#endif
    }
}; 

template <typename TItem>
struct SmartArray
{
public:
    Array<TItem> items;
    Array<int>   free_items;

public:
    propdef_readonly(get_length) int length;

    __forceinline int get_length(void) const
    {
        return items.length - free_items.length;
    }

public:
    __forceinline TItem& operator[](int index)
    {
        return items[index];
    }

    __forceinline const TItem& operator[](int index) const
    {
        return items[index];
    }
};

namespace array 
{
    template <typename TItem>
    inline bool grow(Array<TItem>& array, int new_size)
    {
        auto old_buf = array.buffer;
        auto new_buf = (decltype(old_buf))realloc(old_buf, sizeof(*old_buf) + (new_size - 1) * sizeof(TItem));

        if (new_buf)
        {
            if (!old_buf)
            {
                new_buf->length = 0;
            }

            array.buffer           = new_buf;
            array.buffer->capacity = new_size;
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

        array.buffer->items[array.buffer->length++] = value;
        return true;   
    }

    template <typename TItem>
    inline const TItem& pop(Array<TItem>& array)
    {
        return array.buffer->items[--array.buffer->length];
    }

    template <typename TItem>
    inline TItem shift(Array<TItem>& array)
    {
        TItem result = array.buffer->items[0];

        array.buffer->length--;
        memmove(array.buffer->items, array.buffer->items + 1, array.buffer->length * sizeof(TItem));

        return result;
    }

    template <typename TItem>
    inline bool unshift(Array<TItem>& array, const TItem& value)
    {
        if (!ensure(array, array.length + 1))
        {
            return false;
        }

        memmove(array.buffer->items + 1, array.buffer->items, array.length * sizeof(TItem));
        array.buffer->length++;
        array.buffer->items[0] = value;
        return true;
    }

    template <typename TItem>
    inline int index_of(const Array<TItem>& array, const TItem& value)
    {
        for (int i = 0, n = array.length; i < n; i++)
        {
            if (array.buffer->items[i] == value)
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
            if (array.buffer->items[i] == value)
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
        if (src_len)
        {
            int new_len = dst_len + src_len;
            if (!ensure(dst, new_len))
            {
                return false;
            }

            memcpy(dst.buffer->items + dst.length, src.buffer->items, src_len * sizeof(TItem));
            dst.buffer->length = new_len;
        }
        return true;
    }
    
    template <typename TItem>
    inline void clear(Array<TItem>& array)
    {
        if (array.buffer) 
        {
            dst.buffer->length = 0;
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
                res.buffer->length = len;
                memcpy(res.buffer->items, array.buffer->items, len * sizeof(TItem));
            }
        }

        return make_rvalue(res);
    }

    template <typename TItem>
    inline int new_item(SmartArray<TItem>& array)
    {
        int index;
        if (array.free_items.length > 0)
        {
            index = array::pop(free_items);
        }
        else
        {
            if (!ensure(array, array.length + 1))
            {
                return -;
            }

            index = array.items.buffer->length++;
        }

        return index;
    }

    template <typename TItem>
    inline bool remove_at(int index)
    {
        if (index > -1 && index < items.length)
        {
            return free_items.push(index);
        }
        else
        {
            return false;
        }
    }
}