// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#pragma once

#include "./core.h"

#include <stdlib.h>
#include <string.h>

template <typename TItem>
struct Array;

namespace array 
{
    template <typename TItem>
    inline void unref(Array<TItem>& array);

    template <typename TItem>
    inline bool grow(Array<TItem>& array, int new_size);

    template <typename TItem>
    inline bool ensure(Array<TItem>& array, int size);

    template <typename TItem>
    inline bool ensure(const Array<TItem>& array, int size);

    template <typename TItem>
    inline bool push(Array<TItem>& array, const TItem& value);

    template <typename TItem>
    inline const TItem& pop(Array<TItem>& array);

    template <typename TItem>
    inline TItem shift(Array<TItem>& array);

    template <typename TItem>
    inline bool unshift(Array<TItem>& array, const TItem& value);

    template <typename TItem>
    inline int index_of(const Array<TItem>& array, const TItem& value);

    template <typename TItem>
    inline int last_index_of(const Array<TItem>& array, const TItem& value);

    template <typename TItem>
    inline bool concat(Array<TItem>& dst, const Array<TItem>& src);
    
    template <typename TItem>
    inline void clear(Array<TItem>& array);

    template <typename TItem>
    inline Array<TItem> clone(const Array<TItem>& array);

    template <typename TItem>
    inline int erase(const Array<TItem>& array, int index);

    template <typename TItem>
    inline int remove(const Array<TItem>& array, const TItem& value);
}

// Array: POD growable continuos-sequence container
// @note: Donot use pointer of this type
template <typename TItem>
struct Array
{
public:
    struct Buffer : RefCount
    {
        int   length;
        int   capacity;
        TItem items[1];
    };

public:
    Buffer* buffer;

public:
    constexpr Array(void)
        : buffer(NULL)
    {
    }

    inline ~Array(void)
    {
        if (buffer && buffer->release() <= 0)
        {
            memory::dealloc(buffer);
        }
    }

public: // Copy
    inline Array(const Array<TItem>& other)
        : buffer(other.buffer)
    {
        if (buffer)
        {
            buffer->retain();
        }
    }

    inline Array<TItem>& operator=(const Array<TItem>& other)
    {
        // Unref old buffer
        this->~Array();

        // Assign new buffer
        buffer = other.buffer;
        if (buffer)
        {
            buffer->retain();
        }

        return *this;
    }
    
public: // RAII
    inline Array(Array<TItem>&& other)
        : buffer(other.buffer)
    {
        other.buffer = NULL;
    }

    inline Array<TItem>& operator=(Array<TItem>&& other)
    {
        // Unref old buffer
        this->~Array();

        // Assign new buffer
        buffer = other.buffer;
        other.buffer = NULL;

        return *this;
    }

public: // Properties
    PROPERTY_READONLY(TItem*, items, get_items);
    PROPERTY_READONLY(int, length, get_length);
    PROPERTY_READONLY(int, capacity, get_capacity);
    
    inline TItem* get_items(void)
    {
        return buffer ? buffer->items : NULL;
    }

    inline const TItem* get_items(void) const
    {
        return buffer ? buffer->items : NULL;
    }

    inline int get_length(void) const
    {
        return buffer ? buffer->length : 0;
    }

    inline int get_capacity(void) const
    {
        return buffer ? buffer->capacity : 0;
    }

public: // Indexor
    inline TItem& operator[](int index)
    {
        return buffer->items[index];
    }

    inline const TItem& operator[](int index) const
    {
        return buffer->items[index];
    }
};

// TempoArray: POD temporary continuos-sequence container, unknown size at compile-time
// @note: Donot use pointer of this type
template <typename TValue>
struct TempoArray
{
public:
    int           length;
    const uint    capacity;
    TValue* const items;

public:
    inline explicit TempoArray(uint capacity = 64)
        : length(0)
        , capacity(capacity)
#ifdef NDEBUG
        , items((TValue*)stackalloc(capacity * sizeof(TValue)))
#else
        , items((TValue*)memory::alloc(capacity * sizeof(TValue)))
#endif
    {
    }

    inline ~TempoArray(void)
    {
#if !defined(NDEBUG)
        memory::dealloc(items);
#endif
    }
};

// StaticArray: POD temporary continuos-sequence container, fixed size at compile-time
// @note: Donot use pointer of this type
template <typename TValue, int capacity>
struct StaticArray
{
public:
    int    length;
    TValue items[capacity];

public:
    constexpr StaticArray(void)
        : length(0)
    {
    }

public: // Properties
    PROPERTY_READONLY(int, capacity, get_capacity);
    constexpr int get_capacity(void) const
    {
        return capacity;
    }
};

// SmartArray: Fast and safe, reuse memory Array
// @note: Donot use pointer of this type
template <typename TItem>
struct SmartArray
{
public:
    Array<TItem> items;
    Array<int>   free_items;

public:
    PROPERTY_READONLY(int, length, get_length);

    inline int get_length(void) const
    {
        return items.get_length() - free_items.get_length();
    }

public:
    inline TItem& operator[](int index)
    {
        return items[index];
    }

    inline const TItem& operator[](int index) const
    {
        return items[index];
    }
};

namespace array 
{
    template <typename TItem>
    inline void unref(Array<TItem>& array)
    {
        array.~Array();
        array.buffer = NULL;
    }

    template <typename TItem>
    inline bool grow(Array<TItem>& array, int new_size)
    {
        auto old_buf = array.buffer;
        auto new_buf = (decltype(old_buf))memory::realloc(old_buf, sizeof(*old_buf) + (new_size - 1) * sizeof(TItem));

        if (new_buf)
        {
            if (!old_buf)
            {
                // Initialize RefCount
                INIT(new_buf) RefCount();

                // Initialize Buffer
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
        if (array.get_capacity() >= size)
        {
            return true;
        }
        else
        {
            int new_size = array.get_capacity();
            new_size = new_size * 2 + (new_size <= 0) * 8; // no if statement or '?' operator (ternary operator)
            while (new_size < size) new_size *= 2;
            return grow(array, new_size);
        }
    }

    template <typename TItem>
    inline bool ensure(const Array<TItem>& array, int size)
    {
        return (array.get_capacity() >= size);
    }

    template <typename TItem>
    inline bool push(Array<TItem>& array, const TItem& value)
    {
        if (!ensure(array, array.get_length() + 1))
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
        memory::move(array.buffer->items, array.buffer->items + 1, array.buffer->length * sizeof(TItem));

        return result;
    }

    template <typename TItem>
    inline bool unshift(Array<TItem>& array, const TItem& value)
    {
        if (!ensure(array, array.get_length() + 1))
        {
            return false;
        }

        memory::move(array.buffer->items + 1, array.buffer->items, array.get_length() * sizeof(TItem));
        array.buffer->length++;
        array.buffer->items[0] = value;
        return true;
    }

    template <typename TItem>
    inline int index_of(const Array<TItem>& array, const TItem& value)
    {
        for (int i = 0, n = array.get_length(); i < n; i++)
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
        for (int i = 0, n = array.get_length(); i < n; i++)
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
        int dst_len = dst.get_length();
        int src_len = src.get_length();
        if (src_len)
        {
            int new_len = dst_len + src_len;
            if (!ensure(dst, new_len))
            {
                return false;
            }

            memcpy(dst.buffer->items + dst.get_length(), src.buffer->items, src_len * sizeof(TItem));
            dst.buffer->length = new_len;
        }
        return true;
    }
    
    template <typename TItem>
    inline void clear(Array<TItem>& array)
    {
        if (array.buffer) 
        {
            array.buffer->length = 0;
        }
    }

    template <typename TItem>
    inline Array<TItem> clone(const Array<TItem>& array)
    {
        Array<TItem> res;

        int len = array.get_length();
        int cap = array.get_capacity();
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
    inline int erase(const Array<TItem>& array, int index)
    {
        if (index > -1 && index < array.get_length())
        {
            memory::move(array.buffer->items + index, array.buffer->items + index + 1, array.get_length() - index - 2);
            array.buffer->length--;
            return true;
        }
        else
        {
            return false;
        }
    }

    template <typename TItem>
    inline int remove(const Array<TItem>& array, const TItem& value)
    {
        return array::erase(array, array::index_of(array, value));
    }

    template <typename TItem>
    inline int new_item(SmartArray<TItem>& array)
    {
        int index;
        if (array.free_items.get_length() > 0)
        {
            index = array::pop(array.free_items);
        }
        else
        {
            if (!ensure(array.items, array.items.get_length() + 1))
            {
                return -1;
            }

            index = array.items.buffer->length++;
        }

        return index;
    }

    template <typename TItem>
    inline bool remove_at(SmartArray<TItem>& array, int index)
    {
        if (index > -1 && index < array.items.get_length())
        {
            return array.free_items.push(index);
        }
        else
        {
            return false;
        }
    }
}