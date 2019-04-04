// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#pragma once

#include "./core.h"

// List: high-level, non-POD continuos-sequence container, call constructor and desctructor of object
// @note: Donot use pointer of this type
template <typename TItem, typename TAllocator = ::Allocator>
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
    Buffer*     buffer;
    TAllocator* allocator;

public:
    inline List(TAllocator* allocator = memory::allocator)
        : buffer(NULL)
        , allocator(allocator)
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

            allocator->dealloc(buffer);
        }
    }

public: // Copy
    inline List(const List<TItem>& other)
        : buffer(other.buffer)
        , allocator(other.allocator)
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
        buffer    = other.buffer;
        allocator = other.allocator;
        if (buffer)
        {
            buffer->_ref_inc();
        }

        return *this;
    }
    
public: // RAII
    inline List(List<TItem>&& other)
        : buffer(other.buffer)
        , allocator(other.allocator)
    {
        other.buffer = NULL;
    }

    inline List<TItem>& operator=(List<TItem>&& other)
    {
        // Unref old buffer
        this->~List();

        // Assign new buffer
        buffer    = other.buffer;
        allocator = other.allocator;

        // Unref assigned buffer from ohter
        other.buffer = NULL;

        return *this;
    }

public: // Properties
    PROPERTY_READONLY(TItem*, items, get_items);
    PROPERTY_READONLY(int, length, get_length);
    PROPERTY_READONLY(int, capacity, get_capacity);

    // Get items buffer
    inline TItem* get_items(void)
    {
        return buffer ? buffer->items : NULL;
    }

    // Get items buffer
    inline const TItem* get_items(void) const
    {
        return buffer ? buffer->items : NULL;
    }

    // Get length of list
    inline int get_length(void) const
    {
        return buffer ? buffer->length : 0;
    }

    // Get capacity of buffer
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

    // Remove all items
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

    // Leave buffer ownership free
    inline void unref(bool cleanup = true)
    {
        if (cleanup)
        {
            this->~List();
        }
        buffer = NULL;
    }

    // Grow the array's buffer that contains enough space with given size
    inline bool grow(int new_size)
    {
        ASSERT(new_size > 0, "Array::grow: new size must non-zero positive value.");

        if (new_size > get_capacity())
        {
            const auto old_buf = buffer;
            const auto new_len = get_length();
            const auto new_buf = (decltype(old_buf))allocator->alloc(sizeof(*old_buf) + (new_size - 1) * sizeof(TItem));

            if (new_buf)
            {
                // Initialize RefCount
                INIT(new_buf) RefCount();

                // Copy content of old buffer
                memory::copy(new_buf->items, old_buf->items, (new_len) * sizeof(TItem));

                // Unref old buffer
                this->unref(true);

                // Set buffer
                buffer           = new_buf;
                buffer->length   = new_len;
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

    // Ensure array is big enough
    inline bool ensure(int size) const
    {
        return (this->get_capacity() >= size);
    }

public:
    // Add an item at the last position
    inline bool push(const TItem& value)
    {
        if (!this->ensure(this->get_length() + 1))
        {
            return false;
        }

        INIT(&buffer->items[buffer->length++]) TItem(value);
        return true;
    }

    // Remove the item at the last position
    inline TItem pop(void)
    {
        ASSERT(this->get_length() > 0, "Attempt to pop the List<>, which is empty.");

        return traits::make_rvalue(buffer->items[--buffer->length]);
    }

    // Remove the item at the first position
    inline TItem shift(void)
    {
        ASSERT(this->get_length() > 0, "Attempt to shift the List<>, which is empty.");

        TItem result = traits::make_rvalue(buffer->items[0]);

        buffer->length--;
        memory::copy(buffer->items, buffer->items + 1, buffer->length * sizeof(TItem));

        return traits::make_rvalue(result);
    }

    // Add an item at the first position
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
    // Get index of given item
    inline int index_of(const TItem& value)
    {
        for (int i = 0, n = get_length(); i < n; i++)
        {
            if (traits::equals(value, buffer->items[i]))
            {
                return i;
            }
        }

        return -1;
    }

    // Get index of given item, with backward iteration
    inline int last_index_of(const TItem& value)
    {
        for (int i = get_length() - 1; i > -1; i--)
        {
            if (traits::equals(value, buffer->items[i]))
            {
                return i;
            }
        }

        return -1;
    }

    // Determines whether the contains given item
    inline bool contains(const TItem& item) const
    {
        return index_of(item) > 0;
    }

public:
    // Remove an item with given index
    inline bool erase(int index)
    {
        if (index > -1 && index < this->get_length())
        {
            if (buffer->length > 1)
            {
                memory::copy(buffer->items + index, buffer->items + index + 1, (this->get_length() - index - 2) * sizeof(TItem));
            }
            buffer->length--;
            return true;
        }
        else
        {
            return false;
        }
    }

    // Remove an item with given value
    inline bool remove(const TItem& value)
    {
        return erase(index_of(value));
    }
};

// Calculate hash of List<>
template <typename T>
inline u64 hashof(const List<T>& list)
{
    return hashof(list.get_items(), list.get_length());
}

// Get length of List<>
template <typename T>
inline int lengthof(const List<T>& list)
{
    return list.get_length();
}