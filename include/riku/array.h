// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#pragma once

#include "./core.h"

// Array: POD growable continuos-sequence container
// @note: Donot use pointer of this type
template <typename TItem, typename TAllocator = ::Allocator>
struct Array
{
//public:
    //static_assert(traits::is_pod<TItem>(), "TItem is not a POD type.");

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
    constexpr Array(TAllocator* allocator = NULL)
        : buffer(NULL)
        , allocator(allocator)
    {
    }

    inline ~Array(void)
    {
        if (buffer && buffer->_ref_dec() <= 0)
        {
            allocator->dealloc(buffer);
        }
    }

public:
    inline Array(const Array<TItem>& other)
        : buffer(other.buffer)
        , allocator(other.allocator)
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
        buffer    = other.buffer;
        allocator = other.allocator;
        if (buffer)
        {
            buffer->_ref_inc();
        }

        return *this;
    }
    
public:
    inline Array(Array<TItem>&& other)
        : buffer(other.buffer)
        , allocator(other.allocator)
    {
        other.buffer = NULL;
    }

    inline Array<TItem>& operator=(Array<TItem>&& other)
    {
        // Unref old buffer
        this->~Array();

        // Assign new buffer
        buffer = other.buffer;
        allocator = other.allocator;

        // Unref assigned buffer
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
    bool grow(int new_size)
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
        if (get_capacity() >= size)
        {
            return true;
        }
        else
        {
            int new_size = get_capacity();
            new_size = new_size * 2 + (new_size <= 0) * 64; // no if statement or '?' operator (ternary operator)
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
        memory::copy(buffer->items, buffer->items + 1, buffer->length * sizeof(TItem));

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
        buffer->items[0] = value;
        buffer->length++;
        return true;
    }

    // Get index of given item
    inline int index_of(const TItem& value) const
    {
        for (int i = 0, n = get_length(); i < n; i++)
        {
            if (traits::equals(buffer->items[i], value))
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
            if (traits::equals(buffer->items[i], value))
            {
                index = i;
            }
        }

        return index;
    }

    // Determines whether the contains given item
    inline bool contains(const TItem& item) const
    {
        return index_of(item) > 0;
    }

    // Add other array items to this array, from the last position
    inline bool concat(const Array<TItem>& src)
    {
        int dst_len = get_length();
        int src_len = src.get_length();
        if (src_len > 0)
        {
            int new_len = dst_len + src_len;
            if (!ensure(new_len))
            {
                return false;
            }

            memory::copy(buffer->items + get_length(), src.buffer->items, src_len * sizeof(TItem));
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
                memory::copy(res.buffer->items, buffer->items, len * sizeof(TItem));
            }
        }

        return traits::make_rvalue(res);
    }

    // Remove an item with given index
    inline int erase(int index)
    {
        if (index > -1 && index < get_length())
        {
            if (buffer->length > 1)
            {
                memory::copy(buffer->items + index, buffer->items + index + 1, (get_length() - index - 2) * sizeof(TItem));
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
    inline int remove(const TItem& value)
    {
        return erase(index_of(value));
    }
};

// TempoArray: POD temporary continuos-sequence container, unknown size at compile-time
// @note: Donot use pointer of this type
template <typename TItem>
struct TempoArray
{
//public:
    //static_assert(traits::is_pod<TItem>(), "TItem is not a POD type.");

public:
    int          length;
    const int    capacity;
    TItem* const items;

public:
    inline explicit TempoArray(int capacity = 64)
        : length(0)
        , capacity(capacity)
#ifdef NDEBUG
        , items((TItem*)stackalloc(capacity * sizeof(TItem)))
#else
        , items((TItem*)memory::alloc(capacity * sizeof(TItem)))
#endif
    {
    }

    inline ~TempoArray(void)
    {
#if !defined(NDEBUG)
        memory::dealloc(items);
#endif
    }

public:
    // Checking array is empty or not
    inline bool is_empty(void) const
    {
        return length <= 0;
    }

    // Checking array is valid or not
    inline bool is_valid(void) const
    {
        return length > 0;
    }

public:
    // Add an item at the last position
    inline bool push(const TItem& value)
    {
        if (length < capacity)
        {
            items[length++] = value;
            return true;
        }
        else
        {
            return false;
        }
    }

    // Remove the item at the last position
    inline TItem pop(void)
    {
        ASSERT(length > 0, "Attempt to pop the empty array.");
        return items[--length];
    }

    // Add an item at the first position
    inline bool unshift(const TItem& value)
    {
        if (length < capacity)
        {
            memory::move(items + 1, items, length * sizeof(TItem));
            items[0] = value;
            length++;
            return true;
        }
        else
        {
            return false;
        }
    }

    // Remove the item at the first position
    inline TItem shift(void)
    {
        ASSERT(length > 0, "Attempt to shift the empty array.");

        TItem result = items[--length];
        memory::copy(items, items + 1, length * sizeof(TItem));
        return result;
    }

public:
    // Get index of given item
    inline int index_of(const TItem& value) const
    {
        for (int i = 0, n = length; i < n; i++)
        {
            if (traits::equals(items[i], value))
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
        for (int i = 0, n = length; i < n; i++)
        {
            if (traits::equals(items[i], value))
            {
                index = i;
            }
        }

        return index;
    }

    // Determines whether the contains given item
    inline bool contains(const TItem& item) const
    {
        return index_of(item) > 0;
    }

    // Add other array items to this array, from the last position
    inline bool concat(const TempoArray& src)
    {
        int dst_len = length;
        int src_len = src.length;
        int new_len = dst_len + src_len;
        if (new_len <= capacity)
        {
            length = new_len;
            memory::copy(items + dst_len, src.items, src_len * sizeof(TItem));
            return true;
        }
        else
        {
            return false;
        }
    }

    // Remove an item with given index
    inline int erase(int index)
    {
        if (index > -1 && index < length)
        {
            if (length > 1)
            {
                memory::copy(items + index, items + index + 1, (length - index - 2) * sizeof(TItem));
            }
            length--;
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

// StaticArray: POD temporary continuos-sequence container, fixed size at compile-time
// @note: Donot use pointer of this type
template <typename TItem, int capacity>
struct StaticArray
{
//public:
    //static_assert(traits::is_pod<TItem>(), "TItem is not a POD type.");
    
public:
    int   length;
    TItem items[capacity];

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

public:
    // Checking array is empty or not
    inline bool is_empty(void) const
    {
        return length <= 0;
    }

    // Checking array is valid or not
    inline bool is_valid(void) const
    {
        return length > 0;
    }

public:
    // Add an item at the last position
    inline bool push(const TItem& value)
    {
        if (length < capacity)
        {
            items[length++] = value;
            return true;
        }
        else
        {
            return false;
        }
    }

    // Remove the item at the last position
    inline TItem pop(void)
    {
        ASSERT(length > 0, "Attempt to pop the empty array.");
        return items[--length];
    }

    // Add an item at the first position
    inline bool unshift(const TItem& value)
    {
        if (length < capacity)
        {
            memory::move(items + 1, items, length * sizeof(TItem));
            items[0] = value;
            length++;
            return true;
        }
        else
        {
            return false;
        }
    }

    // Remove the item at the first position
    inline TItem shift(void)
    {
        ASSERT(length > 0, "Attempt to pop the empty array.");
        TItem result = items[--length];
        memory::copy(items + 1, items, length * sizeof(TItem));
        return result;
    }

public:
    // Get index of given item
    inline int index_of(const TItem& value) const
    {
        for (int i = 0, n = length; i < n; i++)
        {
            if (traits::equals(items[i], value))
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
        for (int i = 0, n = length; i < n; i++)
        {
            if (traits::equals(items[i], value))
            {
                index = i;
            }
        }

        return index;
    }

    // Determines whether the contains given item
    inline bool contains(const TItem& item) const
    {
        return index_of(item) > 0;
    }

    // Add other array items to this array, from the last position
    inline bool concat(const StaticArray& src)
    {
        int dst_len = length;
        int src_len = src.length;
        int new_len = dst_len + src_len;
        if (new_len <= capacity)
        {
            length = new_len;
            memory::copy(items + dst_len, src.items, src_len * sizeof(TItem));
            return true;
        }
        else
        {
            return false;
        }
    }

    // Remove an item with given index
    inline int erase(int index)
    {
        if (index > -1 && index < length)
        {
            if (length > 1)
            {
                memory::copy(items + index, items + index + 1, (length - index - 1) * sizeof(TItem));
            }
            length--;
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

// Calculate hash of Array<>
template <typename T>
inline u64 hashof(const Array<T>& array)
{
    return hashof(array.get_items(), array.get_length());
}

// Get length of Array<>
template <typename T>
inline int lengthof(const Array<T>& array)
{
    return array.get_length();
}

// Calculate hash of TempoArray<>
template <typename T>
inline u64 hashof(const TempoArray<T>& array)
{
    return hashof(array.items, array.length);
}

// Get length of TempoArray<>
template <typename T>
inline int lengthof(const TempoArray<T>& array)
{
    return array.length;
}

// Calculate hash of StaticArray<>
template <typename T, int capacity>
inline u64 hashof(const StaticArray<T, capacity>& array)
{
    return hashof(array.items, array.length);
}

// Get length of StaticArray<>
template <typename T, int capacity>
inline int lengthof(const StaticArray<T, capacity>& array)
{
    return array.length;
}