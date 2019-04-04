// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#pragma once

#include "./core.h"
#include "./array.h"

template <typename TValue, typename TAllocator = ::Allocator>
struct HashTable
{
//public:
    //static_assert(traits::is_pod<TValue>(), "TValue is not a POD type.");

public: 
    struct Buffer : RefCount
    {
        int          length;
        int          capacity;
        Array<int>   hashs;
        int*         nexts;
        u64*         keys;
        TValue*      values;
    };

public:
    Buffer*     buffer;
    TAllocator* allocator;

public: // Properties
    PROPERTY_READONLY(u64*, keys, get_keys);
    PROPERTY_READONLY(TValue*, values, get_values);
    PROPERTY_READONLY(int, length, get_length);
    PROPERTY_READONLY(int, hash_count, get_hash_count);

    // Get keys buffer of hash table
    inline const u64* get_keys(void) const
    {
        return buffer ? buffer->keys : 0;
    }

    // Get values buffer of hash table
    inline TValue* get_values(void)
    {
        return buffer ? buffer->values : 0;
    }

    // Get values buffer of hash table
    inline const TValue* get_values(void) const
    {
        return buffer ? buffer->values : 0;
    }

    // Get length of hash table
    inline int get_length(void) const
    {
        return buffer ? buffer->length : 0;
    }

    // Get number of hash entry of hash table
    inline int get_hash_count(void) const
    {
        return buffer ? buffer->hashs.get_length() : 0;
    }

public:
    inline HashTable(TAllocator* allocator = memory::allocator)
        : buffer(NULL)
        , allocator(allocator)
    {
    }

    inline ~HashTable()
    {
        if (buffer && buffer->_ref_dec() < 0)
        {
            allocator->dealloc(buffer->nexts);
            allocator->dealloc(buffer->keys);
            allocator->dealloc(buffer->values);

            buffer->hashs.~Array();
            allocator->dealloc(buffer);
        }
    }

public: // Copy
    inline HashTable(const HashTable<TValue>& other)
        : buffer(other.buffer)
        , allocator(other.allocator)
    {
        if (buffer)
        {
            buffer->_ref_inc();
        }
    }

    inline HashTable<TValue>& operator=(const HashTable<TValue>& other)
    {
        buffer = other.buffer;
        allocator = other.allocator;
        if (buffer)
        {
            buffer->_ref_inc();
        }

        return *this;
    }

public: // RAII
    inline HashTable(HashTable<TValue>&& other)
        : buffer(other.buffer)
        , allocator(other.allocator)
    {
        other.buffer = NULL;
    }

    inline HashTable<TValue>& operator=(HashTable<TValue>&& other)
    {
        this->~HashTable();
        
        buffer = other.buffer;
        allocator = other.allocator;

        other.buffer = NULL;

        return *this;
    }

public:
    // Clear the buffer
    inline void clear(void)
    {
        if (buffer)
        {
            buffer->length = 0;
        }
    }

    // Unref the buffer
    inline void unref(bool cleanup = true)
    {
        if (cleanup)
        {
            ~HashTable();
        }

        buffer = NULL;
    }

public:
    // Find index of entry with key
    int index_of(u64 key, int* out_hash = NULL, int* out_prev = NULL) const
    {
        if (!buffer || buffer->hashs.is_empty())
        {
            return -1;
        }

        int hash = (int)(key % (u64)get_hash_count());
        int curr = buffer->hashs[hash];
        int prev = -1;

        while (curr > -1)
        {
            if (buffer->keys[curr] == key)
            {
                break;
            }

            prev = curr;
            curr = buffer->nexts[curr];
        }

        if (out_hash) *out_hash = hash;
        if (out_prev) *out_prev = prev;
        return curr;
    }

    // Determine if hash table contains the entry with key
    inline bool contains(u64 key) const
    {
        return index_of(key) > -1;
    }

public:
    // Get value of entry with key
    const TValue& get(u64 key) const
    {
        int curr = index_of(key);
        return buffer->values[curr];
    }

    // Get value of entry with key
    const TValue& get(u64 key, const TValue& def_value) const
    {
        int curr = index_of(key);
        return (curr > -1) ? buffer->values[curr] : def_value;
    }

    // Get value of entry with key. If entry exists return true, false otherwise.
    bool try_get(u64 key, TValue* out_value) const
    {
        int curr = index_of(key);
        if (curr > -1)
        {
            *out_value = buffer->values[curr];
            return true;
        }
        else
        {
            return false;
        }
    }

public:
    // Get value entry, if not exists create new. 
    // Return true if success, false otherwise.
    bool get_or_new(u64 key, TValue** value)
    {
        int hash, prev;
        int curr = index_of(key, &hash, &prev);

        if (curr < 0)
        {
            if (!buffer)
            {
                buffer = (Buffer*)allocator->alloc(sizeof(Buffer));
                ASSERT(buffer, "Out of memory");

                buffer->length   = 0;
                buffer->capacity = 0;
                buffer->nexts    = NULL;
                buffer->keys     = NULL;
                buffer->values   = NULL;

                INIT(buffer) RefCount();
                INIT(&buffer->hashs) Array<int>(allocator);

                buffer->hashs.ensure(64);
                for (int i = 0; i < 64; i++)
                {
                    buffer->hashs.push(-1);
                }

                // Re-calculate hash
                prev = -1;
                hash = (int)(hashof(key) % (u64)this->get_hash_count());
            }

            if (buffer->length + 1 > buffer->capacity)
            {
                int old_size     = buffer->capacity;
                int new_size     = (old_size << 1) + (old_size <= 0) * 8;
                void* new_nexts  = allocator->alloc(new_size * sizeof(int));
                void* new_keys   = allocator->alloc(new_size * sizeof(u64));
                void* new_values = allocator->alloc(new_size * sizeof(TValue));

                if (!new_nexts || !new_keys || !new_values)
                {
                    allocator->dealloc(new_nexts);
                    allocator->dealloc(new_keys);
                    allocator->dealloc(new_values);
                    return false;
                }
                else
                {
                    buffer->capacity = new_size;
                    memory::copy(new_nexts, buffer->nexts, old_size * sizeof(int));
                    memory::copy(new_keys, buffer->keys, old_size * sizeof(u64));
                    memory::copy(new_values, buffer->values, old_size * sizeof(TValue));

                    allocator->dealloc(buffer->nexts);
                    allocator->dealloc(buffer->keys);
                    allocator->dealloc(buffer->values);
                
                    buffer->nexts  = (int*)new_nexts;
                    buffer->keys   = (u64*)new_keys;
                    buffer->values = (TValue*)new_values;
                }
            }

            curr = buffer->length++;
            if (prev > -1)
            {
                buffer->nexts[prev] = curr;
            }
            else
            {
                buffer->hashs[hash] = curr;
            }
            buffer->nexts[curr] = -1;
            buffer->keys[curr] = key;
        }

        *value = &buffer->values[curr];
        return true;
    }

    // Get value entry, if not exists create new.
    // Return a reference to value entry if success, otherwise abort the process.
    TValue& get_or_new(u64 key)
    {
        TValue* inner_value;
        if (!get_or_new(key, &inner_value))
        {
            ALWAYS_FALSE_ASSERT("Out of memory.");
        }
        return *inner_value;
    }

    // Set entry's value, if not exists create new
    bool set(u64 key, const TValue& value)
    {
        TValue* inner_value;
        if (get_or_new(key, &inner_value))
        {
            *inner_value = value;
            return true;
        }
        else
        {
            return false;
        }
    }

public:
    // Remove an entry that has given key
    bool remove(u64 key)
    {
        int prev;
        int hash;
        int curr = index_of(key, &hash, &prev);
        return erase(curr, hash, prev);
    }
    
    // Remove the entry at given index
    bool erase(int index)
    {
        if (index > -1 && index < get_length())
        {
            return remove(buffer->keys[index]);
        }
        else
        {
            return false;
        }
    }

    // Remove the entry at given index, hash entry, and previous entry
    bool erase(int curr, int hash, int prev)
    {
        if (curr > -1)
        {
            if (prev > -1)
            {
                buffer->nexts[prev] = -1;
            }
            else
            {
                buffer->hashs[hash] = -1;
            }

            if (curr < get_length() - 1)
            {
                int last = get_length() - 1;
                buffer->nexts[curr] = buffer->nexts[last];
                buffer->keys[curr] = buffer->keys[last];
                buffer->values[curr] = buffer->values[last];

                index_of(buffer->keys[curr], &hash, &prev);
                if (prev > -1)
                {
                    buffer->nexts[prev] = curr;
                }
                else
                {
                    buffer->hashs[hash] = curr;
                }
            }
            buffer->length--;
            return true;
        }
        else
        {
            return false;
        }
    }
};

// Compute hash of given hash table
template <typename TKey>
inline u64 hashof(const HashTable<TKey>& table)
{
    return hashof(table.get_keys(), table.get_length()) ^ hashof(table.get_values(), table.get_length());
}

// Get length of given hash table
template <typename TKey>
inline int lengthof(const HashTable<TKey>& table)
{
    return table.get_length();
}