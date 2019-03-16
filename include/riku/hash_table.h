// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#pragma once

#include "./core.h"
#include "./array.h"

template <typename TValue>
struct HashTable
{
public: 
    struct Buffer : RefCount
    {
        int          length;
        int          capacity;
        Array<int>   hashs;
        int*         nexts;
        ulong*       keys;
        TValue*      values;
    };

public:
    Buffer* buffer;

public: // Properties
    PROPERTY_READONLY(ulong*, keys, get_keys);
    PROPERTY_READONLY(TValue*, values, get_values);
    PROPERTY_READONLY(int, length, get_length);
    PROPERTY_READONLY(int, hash_count, get_hash_count);

    inline const ulong* get_keys(void) const
    {
        return buffer ? buffer->keys : 0;
    }

    inline TValue* get_values(void)
    {
        return buffer ? buffer->values : 0;
    }

    inline const TValue* get_values(void) const
    {
        return buffer ? buffer->values : 0;
    }

    inline int get_length(void) const
    {
        return buffer ? buffer->length : 0;
    }

    inline int get_hash_count(void) const
    {
        return buffer ? buffer->hashs.length : 0;
    }

public:
    inline HashTable(int hash_count = 64)
        : buffer((Buffer*)memory::alloc(sizeof(Buffer)))
    {
        assert(buffer, "Out of memory");

        buffer->length   = 0;
        buffer->capacity = 0;
        buffer->nexts    = NULL;
        buffer->keys     = NULL;
        buffer->values   = NULL;

        INIT(buffer) RefCount();
        INIT(&buffer->hashs) Array<int>();

        buffer->hashs.ensure(hash_count);
        for (int i = 0; i < hash_count; i++)
        {
            buffer->hashs.push(-1);
        }
    }

    inline ~HashTable()
    {
        if (buffer && buffer->release() < 0)
        {
            memory::dealloc(buffer->nexts);
            memory::dealloc(buffer->keys);
            memory::dealloc(buffer->values);

            buffer->hashs.~Array();
            memory::dealloc(buffer);
        }
    }

public: // Copy
    inline HashTable(const HashTable<TValue>& other)
        : buffer(other.buffer)
    {
        if (buffer)
        {
            buffer->retain();
        }
    }

    inline HashTable<TValue>& operator=(const HashTable<TValue>& other)
    {
        buffer = other.buffer;
        if (buffer)
        {
            buffer->retain();
        }

        return *this;
    }

public: // RAII
    inline HashTable(HashTable<TValue>&& other)
        : buffer(other.buffer)
    {
        other.buffer = NULL;
    }

    inline HashTable<TValue>& operator=(HashTable<TValue>&& other)
    {
        this->~HashTable();
        
        buffer = other.buffer;
        other.buffer = NULL;

        return *this;
    }

public: // Methods
    void clear(void)
    {
        if (buffer)
        {
            buffer->length = 0;
        }
    }

    inline void unref(bool cleanup = true)
    {
        if (cleanup)
        {
            ~HashTable();
        }

        buffer = NULL;
    }

    int index_of(ulong key, int* out_hash = NULL, int* out_prev = NULL) const
    {
        int hash = (int)(ulong)(key % get_hash_count());
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

    TValue get(ulong key, const TValue& def_value = TValue()) const
    {
        int curr = index_of(key);
        return (curr > -1) ? buffer->values[curr] : def_value;
    }

    TValue& get_or_new(ulong key)
    {
        int hash, prev;
        int curr = index_of(key, &hash, &prev);

        if (curr < 0)
        {
            always_assert(this->set(key, TValue()), "Out of memory");
        }

        return buffer->values[curr];
    }

    template <typename TValue>
    bool has(ulong key) const
    {
        return index_of(key) > -1;
    }

    template <typename TValue>
    bool try_get(ulong key, TValue* out_value) const
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

    template <typename TValue>
    bool set(ulong key, const TValue& value)
    {
        int hash, prev;
        int curr = index_of(key, &hash, &prev);

        if (curr < 0)
        {
            if (buffer->length + 1 > buffer->capacity)
            {
                int new_size   = buffer->capacity > 0 ? buffer->capacity * 2 : 8;
                buffer->nexts  = (int*)memory::realloc(buffer->nexts, sizeof(int) * new_size);
                buffer->keys   = (ulong*)memory::realloc(buffer->keys, sizeof(ulong) * new_size);
                buffer->values = (TValue*)memory::realloc(buffer->values, sizeof(TValue) * new_size);

                if (!buffer->nexts || !buffer->keys || !buffer->values)
                {
                    memory::dealloc(buffer->nexts);
                    memory::dealloc(buffer->keys);
                    memory::dealloc(buffer->values);
                    return false;
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

        buffer->values[curr] = value;
        return true;
    }

    bool remove(ulong key)
    {
        int prev;
        int hash;
        int curr = index_of(key, &hash, &prev);
        if (curr > -1)
        {
            if (prev > -1)
            {
                nexts[prev] = -1;
            }
            else
            {
                nexts[hash] = -1;
            }

            if (curr < get_length() - 1)
            {
                int last = get_length() - 1;
                buffer->nexts[curr]  = buffer->nexts[last];
                buffer->keys[curr]   = buffer->keys[last];
                buffer->values[curr] = buffer->values[last];

                index_of(buffer->keys[curr], &hash, &prev);
                if (prev > -1)
                {
                    nexts[prev] = curr;
                }
                else
                {
                    nexts[hash] = curr;
                }
            }
            buffer->length--;
        }
    }
};