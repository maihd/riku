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

    inline ~List(void)
    {
        if (buffer && buffer->_ref_dec() <= 0)
        {
            for (int i = 0, n = buffer->length; i < n; i++)
            {
                buffer->items[i].~TItem();
            }

            memory::dealloc(buffer);
        }
    }

public: // Copy
    inline List(const List<TItem>& other)
        : buffer(other.buffer)
    {
        if (buffer)
        {
            buffer->_ref_inc();
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
            buffer->_ref_inc();
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

public: // Buffer sizing
    inline void clear(void)
    {
        if (buffer)
        {
            for (int i = 0, n = buffer->length; i < n; i++)
            {
                buffer->items[i].~TItem();
            }

            buffer->length = 0;
        }
    }

    inline void unref(bool cleanup = true)
    {
        if (cleanup)
        {
            this->~List();
        }
        buffer = NULL;
    }

    inline bool grow(int new_size)
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
        if (this->get_capacity() >= size)
        {
            return true;
        }
        else
        {
            int new_size = this->get_capacity();
            new_size = new_size * 2 + (new_size <= 0) * 8; // no if statement or '?' operator (ternary operator)
            while (new_size < size) new_size *= 2;
            return this->grow(new_size);
        }
    }

    inline bool ensure(int size) const
    {
        return (this->get_capacity() >= size);
    }

public: // Buffer modifying
    inline bool push(const TItem& value)
    {
        if (!this->ensure(this->get_length() + 1))
        {
            return false;
        }

        INIT(&buffer->items[buffer->length++]) TItem(value);
        return true;
    }
    
    inline TItem pop(void)
    {
        ASSERT(this->get_length() > 0, "Attempt to pop the List<>, which is empty.");

        TItem item = buffer->items[--buffer->length];
        buffer->items[buffer->length].~TItem();
        return item;
    }

    inline TItem shift(void)
    {
        ASSERT(this->get_length() > 0, "Attempt to shift the List<>, which is empty.");

        TItem result = buffer->items[0];
        buffer->items[0].~TItem();

        buffer->length--;
        memory::move(buffer->items, buffer->items + 1, buffer->length * sizeof(TItem));

        return result;
    }

    inline bool unshift(const TItem& value)
    {
        if (!this->ensure(this->get_length() + 1))
        {
            return false;
        }

        memory::move(buffer->items + 1, buffer->items, this->get_length() * sizeof(TItem));
        
        buffer->length++;
        INIT(&buffer->items[0]) TItem(value);
        return true;
    }

public:
    inline int index_of(const TItem& value)
    {
        for (int i = 0, n = get_length(); i < n; i++)
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
        for (int i = get_length() - 1; i > -1; i--)
        {
            if (value == buffer->items[i])
            {
                return i;
            }
        }

        return -1;
    }

public:
    inline bool erase(int index)
    {
        if (index > -1 && index < this->get_length())
        {
            memory::move(buffer->items + index, buffer->items + index + 1, this->get_length() - index - 2);
            buffer->length--;
            return true;
        }
        else
        {
            return false;
        }
    }

    inline bool remove(const TItem& value)
    {
        return erase(index_of(value));
    }
};

template <typename T>
inline u64 hashof(const List<T>& list)
{
    return hashof(list.get_items(), list.get_length());
}

template <typename T>
inline u32 lengthof(const List<T>& list)
{
    return (u32)list.get_length();
}