// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#pragma once

#include "./core.h"
#include "./array.h"

template <typename TKey, typename TValue, typename TAllocator = ::Allocator>
struct Dictionary
{
public:
    struct Buffer : RefCount
    {
        int          length;
        int          capacity;
        Array<int>   hashs;
        int*         nexts;
        TKey*        keys;
        TValue*      values;
    };

public:
    Buffer*     buffer;
    TAllocator* allocator;

public: // Properties
    PROPERTY_READONLY(TKey*, keys, get_keys);
    PROPERTY_READONLY(TValue*, values, get_values);
    PROPERTY_READONLY(int, length, get_length);
    PROPERTY_READONLY(int, hash_count, get_hash_count);

    // Get keys buffer
    inline const TKey* get_keys(void) const
    {
        return buffer ? buffer->keys : 0;
    }

    // Get values buffer
    inline TValue* get_values(void)
    {
        return buffer ? buffer->values : 0;
    }

    // Get values buffer
    inline const TValue* get_values(void) const
    {
        return buffer ? buffer->values : 0;
    }

    // Get length of dictionary
    inline int get_length(void) const
    {
        return buffer ? buffer->length : 0;
    }

    // Get number of entry contain in dictionary
    inline int get_hash_count(void) const
    {
        return buffer ? buffer->hashs.get_length() : 0;
    }

public:
    inline Dictionary(TAllocator* allocator = memory::allocator)
        : buffer(NULL)
        , allocator(allocator)
    {
    }

    inline ~Dictionary(void)
    {
        if (buffer && buffer->_ref_dec() < 0)
        {
            for (int i = 0, n = get_length(); i < n; i++)
            {
                buffer->keys[i].~TKey();
                buffer->values[i].~TValue();
            }

            allocator->dealloc(buffer->nexts);
            allocator->dealloc(buffer->keys);
            allocator->dealloc(buffer->values);

            buffer->hashs.~Array();
            allocator->dealloc(buffer);
        }
    }

public: // Copy
    inline Dictionary(const Dictionary& other)
        : buffer(other.buffer)
        , allocator(other.allocator)
    {
        if (buffer)
        {
            buffer->_ref_inc();
        }
    }

    inline Dictionary& operator=(const Dictionary& other)
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
    inline Dictionary(Dictionary&& other)
        : buffer(other.buffer)
        , allocator(other.allocator)
    {
        other.buffer = NULL;
    }

    inline Dictionary& operator=(Dictionary&& other)
    {
        this->~Dictionary();
        
        buffer = other.buffer;
        allocator = other.allocator;

        other.buffer = NULL;

        return *this;
    }

public: // Operators
    inline TValue& operator[](const TKey& key)
    {
        return get_or_new(key);
    }

    inline TValue  operator[](const TKey& key) const
    {
        TValue value;
        return try_get(key, &value) ? value : TValue();
    }

public:
    // Clear the buffer
    void clear(void)
    {
        if (buffer)
        {
            for (int i = 0, n = get_length(); i < n; i++)
            {
                buffer->keys[i].~TKey();
                buffer->values[i].~TValue();
            }
            
            buffer->length = 0;
        }
    }

    // Unref the buffer
    void unref(bool cleanup = true)
    {
        if (cleanup)
        {
            this->~Dictionary();
        }
        buffer = NULL;
    }

public:
    // Find index of entry with key
    int index_of(const TKey& key, int* out_hash = NULL, int* out_prev = NULL) const
    {
        if (!buffer || buffer->hashs.is_empty())
        {
            return -1;
        }

        int hash = (int)(hashof(key) % (u64)this->get_hash_count());
        int curr = buffer ? buffer->hashs[hash] : -1;
        int prev = -1;

        while (curr > -1)
        {
            if (traits::equals(buffer->keys[curr], key))
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
    const TValue& get(const TKey& key) const
    {
        int curr = index_of(key);
        return buffer->values[curr];
    }

    // Get value of entry with key
    const TValue& get(const TKey& key, const TValue& def_value) const
    {
        int curr = index_of(key);
        return (curr > -1) ? buffer->values[curr] : def_value;
    }

    // Get value of entry with key. If entry exists return true, false otherwise.
    bool try_get(const TKey& key, TValue* out_value) const
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
    bool get_or_new(const TKey& key, TValue** value)
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

                new (nullptr, buffer) RefCount();
                new (nullptr, &buffer->hashs) Array<int>(allocator);

                buffer->hashs.grow(64);
                for (int i = 0; i < 64; i++)
                {
                    buffer->hashs.push(-1);
                }

                // Re-calculate hash
                prev = -1;
                hash = (int)(uint)(hashof(key) % this->get_hash_count());
            }

            if (buffer->length + 1 > buffer->capacity)
            {
                int old_size     = buffer->capacity;
                int new_size     = (old_size << 1) + (old_size <= 0) * 8;
                void* new_nexts  = allocator->alloc(new_size * sizeof(int));
                void* new_keys   = allocator->alloc(new_size * sizeof(TKey));
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
                    memory::copy(new_nexts, buffer->nexts, old_size * sizeof(int));
                    memory::copy(new_keys, buffer->keys, old_size * sizeof(TKey));
                    memory::copy(new_values, buffer->values, old_size * sizeof(TValue));

                    allocator->dealloc(buffer->nexts);
                    allocator->dealloc(buffer->keys);
                    allocator->dealloc(buffer->values);
                
                    buffer->nexts  = (int*)new_nexts;
                    buffer->keys   = (TKey*)new_keys;
                    buffer->values = (TValue*)new_values;

                    buffer->capacity = new_size;
                    for (int i = buffer->length; i < new_size; i++)
                    {
                        buffer->nexts[i] = -1;
                        new (nullptr, &buffer->keys[i]) TKey();
                        new (nullptr, &buffer->values[i]) TValue();
                    }
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
    TValue& get_or_new(const TKey& key)
    {
        TValue* inner_value;
        if (!get_or_new(key, &inner_value))
        {
            ALWAYS_FALSE_ASSERT("Out of memory.");
        }
        return *inner_value;
    }

    // Set entry's value, if not exists create news
    bool set(const TKey& key, const TValue& value)
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
    bool remove(const TKey& key)
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

            buffer->keys[curr].~TKey();
            buffer->values[curr].~TValue();
            if (curr < get_length() - 1)
            {
                int last = get_length() - 1;
                index_of(buffer->keys[last], &hash, &prev);
                if (prev > -1)
                {
                    buffer->nexts[prev] = curr;
                }
                else
                {
                    buffer->hashs[hash] = curr;
                }

                buffer->nexts[curr] = buffer->nexts[last];
                new (nullptr, &buffer->keys[curr]) TKey(traits::make_rvalue(buffer->keys[last]));
                new (nullptr, &buffer->values[curr]) TValue(traits::make_rvalue(buffer->values[last]));
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
template <typename TKey, typename TValue>
inline u64 hashof(const Dictionary<TKey, TValue>& dictionary)
{
    return hashof(dictionary.get_keys(), dictionary.get_length()) ^ hashof(dictionary.get_values(), dictionary.get_length());
}

// Get length of given hash table
template <typename TKey, typename TValue>
inline int lengthof(const Dictionary<TKey, TValue>& dictionary)
{
    return dictionary.get_length();
}