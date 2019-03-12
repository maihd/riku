// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#pragma once

#include "./core.h"

// List: high-level, non-POD continuos-sequence container, call constructor and desctructor of object
// @note: Donot use pointer of this type
template <typename TItem>
struct List
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
    constexpr List(void)
        : buffer(NULL)
    {
    }

    __forceinline ~List(void)
    {
        if (buffer && buffer->release() <= 0)
        {
            this->clear();
        }
    }

public: // Copy
    inline List(const List<TItem>& other)
        : buffer(other.buffer)
    {
        if (buffer)
        {
            buffer->retain();
        }
    }

    inline List<TItem>& operator=(const List<TItem>& other)
    {
        // Unref old buffer
        this->~List();

        // Assign new buffer
        buffer = other.buffer;
        if (buffer)
        {
            buffer->retain();
        }

        return *this;
    }
    
public: // RAII
    inline List(List<TItem>&& other)
        : buffer(other.buffer)
    {
        other.buffer = NULL;
    }

    inline List<TItem>& operator=(List<TItem>&& other)
    {
        // Unref old buffer
        this->~List();

        // Assign new buffer
        buffer = other.buffer;
        other.buffer = NULL;

        return *this;
    }

public: // Properties
    propdef_readonly(get_items)    TItem* items;
    propdef_readonly(get_length)   int    length;
    propdef_readonly(get_capacity) int    capacity;

    __forceinline TItem* get_items(void)
    {
        return buffer ? buffer->items : NULL;
    }

    __forceinline const TItem* get_items(void) const
    {
        return buffer ? buffer->items : NULL;
    }

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

public: // Buffer sizing
    inline void clear(void)
    {
        if (buffer)
        {
            for (int i = 0, n = buffer->length; i < n; i++)
            {
                buffer->items[i].~TItem();
            }

            memory::dealloc(buffer);
            buffer = NULL;
        }
    }

    inline bool grow(int new_size)
    {
        int old_size = this->capacity;

        auto old_buf = buffer;
        auto new_buf = (decltype(old_buf))memory::realloc(old_buf, sizeof(*old_buf) + (new_size - 1) * sizeof(TItem));

        if (new_buf)
        {
            if (!old_buf)
            {
                // Initialize RefCount
                init<RefCount>(new_buf);

                // Initialize Buffer
                new_buf->length = 0;
            }

            if (new_size > old_size)
            {
                for (int i = old_size; i < new_size; i++)
                {
                    init<TItem>(&new_buf->items[i]);
                }
            }

            buffer           = new_buf;
            buffer->capacity = new_size;
            return true; 
        }
        else 
        {
            return false;
        }
    }

    inline bool ensure(int size)
    {
        if (this->capacity >= size)
        {
            return true;
        }
        else
        {
            int new_size = this->capacity;
            new_size = new_size * 2 + (new_size <= 0) * 8; // no if statement or '?' operator (ternary operator)
            while (new_size < size) new_size *= 2;
            return this->grow(new_size);
        }
    }

    inline bool ensure(int size) const
    {
        return (this->capacity >= size);
    }

public: // Buffer modifying
    inline bool push(const TItem& value)
    {
        if (!this->ensure(this->length + 1))
        {
            return false;
        }

        buffer->items[buffer->length++] = value;
        return true;
    }
    
    inline TItem pop(void)
    {
        assert(this->length > 0, "Attempt to pop the List<>, which is empty.");
        TItem item = buffer->items[--buffer->length];
        buffer->items[buffer->length].~TItem();
        return item;
    }

    inline TItem shift(void)
    {
        assert(this->length > 0, "Attempt to shift the List<>, which is empty.");

        TItem result = buffer->items[0];
        buffer->items[0].~TItem();

        buffer->length--;
        memory::move(buffer->items, buffer->items + 1, buffer->length * sizeof(TItem));

        return result;
    }

    inline bool unshift(const TItem& value)
    {
        if (!this->ensure(this->length + 1))
        {
            return false;
        }

        memory::move(buffer->items + 1, buffer->items, this->length * sizeof(TItem));
        
        buffer->length++;
        init<TItem>(&buffer->items[0], value);
        return true;
    }

public:
    inline int index_of(const TItem& value)
    {
        for (int i = 0, n = length; i < n; i++)
        {
            if (value == buffer->items[i])
            {
                return i;
            }
        }

        return -1;
    }

    inline int last_index_of(const TItem& value)
    {
        for (int i = length - 1; i > -1; i--)
        {
            if (value == buffer->items[i])
            {
                return i;
            }
        }

        return -1;
    }
};