// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#pragma once

#include "./core.h"
#include "./array.h"

template <typename TKey, typename TValue>
struct Table
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
    PROPERTY_READONLY(TKey*, keys, get_keys);
    PROPERTY_READONLY(TValue*, values, get_values);
    PROPERTY_READONLY(int, length, get_length);
    PROPERTY_READONLY(int, hash_count, get_hash_count);

    inline const TKey* get_keys(void) const
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
        return buffer ? buffer->hashs.get_length() : 0;
    }

public:
    inline Table(int hash_count = 64)
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

    inline ~Table()
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
    inline Table(const Table& other)
        : buffer(other.buffer)
    {
        if (buffer)
        {
            buffer->retain();
        }
    }

    inline Table& operator=(const Table& other)
    {
        buffer = other.buffer;
        if (buffer)
        {
            buffer->retain();
        }

        return *this;
    }

public: // RAII
    inline Table(Table&& other)
        : buffer(other.buffer)
    {
        other.buffer = NULL;
    }

    inline Table& operator=(Table&& other)
    {
        this->~Dictionary();
        
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

    void unref(void)
    {
        this->~Table();
        buffer = NULL;
    }

    int index_of(const TKey& key, int* out_hash = NULL, int* out_prev = NULL) const
    {
        int hash = (int)((uint)calc_hash(key) % this->get_hash_count());
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

    TValue& get_or_new(const TKey& key)
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

    bool remove(const TKey& key)
    {
        int prev;
        int hash;
        int curr = index_of(key, &hash, &prev);
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
                buffer->nexts[curr]  = buffer->nexts[last];
                buffer->keys[curr]   = buffer->keys[last];
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