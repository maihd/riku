// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#pragma once

#include "./core.h"
#include "./array.h"
#include "./crypto.h"

template <typename TKey, typename TValue>
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
    Buffer* buffer;

public: // Properties
    propdef_readonly(get_hash_count) int hash_count;
    __forceinline int get_hash_count(void) const
    {
        return buffer ? buffer->hashs.length : 0;
    }

public:
    inline Dictionary(int hash_count = 64)
        : buffer((Buffer*)memory::alloc(sizeof(Buffer)))
    {
        assert(buffer, "Out of memory");

        buffer->length   = 0;
        buffer->capacity = 0;
        buffer->nexts    = NULL;
        buffer->keys     = NULL;
        buffer->values   = NULL;

        init<RefCount>(buffer);
        init<Array<int>>(&buffer->hashs);

        array::ensure(buffer->hashs, hash_count);
        for (int i = 0; i < hash_count; i++)
        {
            array::push(buffer->hashs, -1);
        }
    }

    inline ~Dictionary()
    {
        if (buffer && buffer->release() < 0)
        {
            memory::dealloc(buffer->nexts);
            memory::dealloc(buffer->keys);
            memory::dealloc(buffer->values);

            buffer->hashs.~Array();
        }
    }

public: // Copy
    inline Dictionary(const Dictionary& other)
        : buffer(other.buffer)
    {
        if (buffer)
        {
            buffer->retain();
        }
    }

    inline Dictionary& operator=(const Dictionary& other)
    {
        buffer = other.buffer;
        if (buffer)
        {
            buffer->retain();
        }

        return *this;
    }

public: // RAII
    inline Dictionary(Dictionary&& other)
        : buffer(other.buffer)
    {
        other.buffer = NULL;
    }

    inline Dictionary& operator=(Dictionary&& other)
    {
        this->~Dictionary();
        
        buffer = other.buffer;
        other.buffer = NULL;

        return *this;
    }

public: // Methods
    int index_of(const TKey& key, int* out_hash = NULL, int* out_prev = NULL) const
    {
        int hash = crypto::murmur(&key, sizeof(key)) % hash_count;
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

    const TValue& get(const TKey& key) const
    {
        int curr = index_of(key);
        return buffer->values[curr];
    }

    const TValue& get(const TKey& key, const TValue& def_value) const
    {
        int curr = index_of(key);
        return (curr > -1) ? buffer->values[curr] : def_value;
    }

    TValue& get_or_add(const TKey& key)
    {
        int hash, prev;
        int curr = index_of(key, &hash, &prev);

        if (curr < 0)
        {
            if (buffer->length + 1 > buffer->capacity)
            {
                int new_size   = buffer->capacity > 0 ? buffer->capacity * 2 : 8;
                buffer->nexts  = (int*)memory::realloc(buffer->nexts, sizeof(int) * new_size);
                buffer->keys   = (TKey*)memory::realloc(buffer->keys, sizeof(TKey) * new_size);
                buffer->values = (TValue*)memory::realloc(buffer->values, sizeof(TValue) * new_size);

                always_assert(!(!buffer->nexts || !buffer->keys || !buffer->values), "Out of memory");

                buffer->capacity = new_size;
                for (int i = buffer->length; i < new_size; i++)
                {
                    init<TKey>(&buffer->keys[i]);
                    init<TValue>(&buffer->values[i]);
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
            buffer->keys[curr]  = key;
        }

        return buffer->values[curr];
    }

    bool has(const TKey& key) const
    {
        return index_of(key) > -1;
    }

    bool try_get(const TKey& key, TValue* out_value) const
    {
        int curr = index_of(table, key);
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

    bool set(const TKey& key, const TValue& value)
    {
        int hash, prev;
        int curr = index_of(key, &hash, &prev);

        if (curr < 0)
        {
            if (buffer->length + 1 > buffer->capacity)
            {
                int new_size   = buffer->capacity > 0 ? buffer->capacity * 2 : 8;
                buffer->nexts  = (int*)memory::realloc(buffer->nexts, sizeof(int) * new_size);
                buffer->keys   = (TKey*)memory::realloc(buffer->keys, sizeof(TKey) * new_size);
                buffer->values = (TValue*)memory::realloc(buffer->values, sizeof(TValue) * new_size);

                always_assert(!(!buffer->nexts || !buffer->keys || !buffer->values), "Out of memory");

                buffer->capacity = new_size;
                for (int i = buffer->length; i < new_size; i++)
                {
                    init<TKey>(&buffer->keys[i]);
                    init<TValue>(&buffer->values[i]);
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
            buffer->keys[curr]  = key;
        }

        buffer->values[curr] = value;
        return true;
    }

public: // Operator 
    inline TValue& operator[](const TKey& key)
    {
        return get_or_add(key);
    }

    inline TValue operator[](const TValue& key) const
    {
        TValue value;
        return try_get(key, &value) ? value : TValue();
    }
};