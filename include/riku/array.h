// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#pragma once

#include "./core.h"

#include <stdlib.h>
#include <string.h>

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
        if (buffer && buffer->_ref_dec() <= 0)
        {
            memory::dealloc(buffer);
        }
    }

public:
    inline Array(const Array<TItem>& other)
        : buffer(other.buffer)
    {
        if (buffer)
        {
            buffer->_ref_inc();
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
            buffer->_ref_inc();
        }

        return *this;
    }
    
public:
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

public:
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

public:
    inline TItem& operator[](int index)
    {
        return buffer->items[index];
    }

    inline const TItem& operator[](int index) const
    {
        return buffer->items[index];
    }

public:
    // Checking array is empty or not
    inline bool is_empty(void) const
    {
        return !buffer || buffer->length <= 0;
    }

    // Checking array is valid or not
    inline bool is_valid(void) const
    {
        return buffer && buffer->length > 0;
    }

    // Leave buffer ownership free
    inline void unref(bool cleanup = true)
    {
        if (cleanup)
        {
            this->~Array();
        }

        buffer = NULL;
    }

    // Remove all items
    inline void clear(void)
    {
        if (buffer)
        {
            buffer->length = 0;
        }
    }

    // Grow the array's buffer that contains enough space with given size
    inline bool grow(int new_size)
    {
        ASSERT(new_size > 0, "Array::grow: new size must non-zero positive value.");

        if (new_size > get_capacity())
        {
            auto old_buf = buffer;
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

                buffer = new_buf;
                buffer->capacity = new_size;
                return true;
            }
            else
            {
                return false;
            }
        }

        return true;
    }

    // Ensure array is big enough, and grow if can
    inline bool ensure(int size)
    {
        if (get_capacity() >= size)
        {
            return true;
        }
        else
        {
            int new_size = get_capacity();
            new_size = new_size * 2 + (new_size <= 0) * 8; // no if statement or '?' operator (ternary operator)
            while (new_size < size) new_size *= 2;
            return grow(new_size);
        }
    }

    // Ensure array is big enough
    inline bool ensure(int size) const
    {
        return (get_capacity() >= size);
    }

    // Add new item to last position
    inline bool push(const TItem& value)
    {
        if (!ensure(get_length() + 1))
        {
            return false;
        }

        buffer->items[buffer->length++] = value;
        return true;   
    }

    // Remove an item from last position
    inline const TItem& pop(void)
    {
        ASSERT(is_valid(), "Array::pop: array must be has one or more items to pop.");
        return buffer->items[--buffer->length];
    }

    // Remove an item from first position
    inline TItem shift(void)
    {
        ASSERT(is_valid(), "Array::shift: array must be has one or more items to shift.");
        TItem result = buffer->items[0];

        buffer->length--;
        memory::move(buffer->items, buffer->items + 1, buffer->length * sizeof(TItem));

        return result;
    }

    // Add new item to first position
    inline bool unshift(const TItem& value)
    {
        if (!ensure(get_length() + 1))
        {
            return false;
        }

        memory::move(buffer->items + 1, buffer->items, get_length() * sizeof(TItem));
        buffer->length++;
        buffer->items[0] = value;
        return true;
    }

    // Get index of given item
    inline int index_of(const TItem& value) const
    {
        for (int i = 0, n = get_length(); i < n; i++)
        {
            if (buffer->items[i] == value)
            {
                return i;
            }
        }

        return -1;
    }

    // Get index of given item, with backward iteration
    inline int last_index_of(const TItem& value) const
    {
        int index = -1;
        for (int i = 0, n = get_length(); i < n; i++)
        {
            if (buffer->items[i] == value)
            {
                index = i;
            }
        }

        return index;
    }

    // Add other array items to this array, from the last position
    inline bool concat(const Array<TItem>& src)
    {
        int dst_len = get_length();
        int src_len = src.get_length();
        if (src_len)
        {
            int new_len = dst_len + src_len;
            if (!ensure(new_len))
            {
                return false;
            }

            memcpy(buffer->items + get_length(), src.buffer->items, src_len * sizeof(TItem));
            buffer->length = new_len;
        }

        return true;
    }

    // Create new array, which is the copy version of this
    inline Array<TItem> clone(void) const
    {
        Array<TItem> res;

        int len = get_length();
        int cap = get_capacity();
        if (len > 0 && cap > 0)
        {
            if (res.grow(cap))
            {
                res.buffer->length = len;
                memcpy(res.buffer->items, buffer->items, len * sizeof(TItem));
            }
        }

        return make_rvalue(res);
    }

    // Remove an item with given index
    inline int erase(int index)
    {
        if (index > -1 && index < get_length())
        {
            memory::move(buffer->items + index, buffer->items + index + 1, get_length() - index - 2);
            buffer->length--;
            return true;
        }
        else
        {
            return false;
        }
    }

    // Remove an item with given value
    inline int remove(const TItem& value)
    {
        return erase(index_of(value));
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

template <typename T>
inline u64 hashof(const Array<T>& array)
{
    return hashof(array.get_items(), array.get_length());
}

template <typename T>
inline u32 lengthof(const Array<T>& array)
{
    return (u32)array.get_length();
}