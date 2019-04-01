// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#pragma once

#include "./core.h"
#include "./array.h"

template <typename TKey, typename TValue>
struct Table
{
//public:
    //static_assert(traits::is_pod<TKey>(), "TKey is not a POD type.");
    //static_assert(traits::is_pod<TValue>(), "TValue is not a POD type.");

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
        ASSERT(buffer, "Out of memory");

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
        if (buffer && buffer->_ref_dec() < 0)
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
            buffer->_ref_inc();
        }
    }

    inline Table& operator=(const Table& other)
    {
        buffer = other.buffer;
        if (buffer)
        {
            buffer->_ref_inc();
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
        int hash = (int)(uint)(hashof(key) % this->get_hash_count());
        int curr = buffer->hashs[hash];
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
            ALWAYS_ASSERT(this->set(key, TValue()), "Out of memory");
        }

        return buffer->values[curr];
    }

    bool contains(const TKey& key) const
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

                if (!buffer->nexts || !buffer->keys || !buffer->values)
                {
                    memory::dealloc(buffer->nexts);
                    memory::dealloc(buffer->keys);
                    memory::dealloc(buffer->values);
                    return false;
                }
                else
                {
                    buffer->capacity = new_size;
                    memory::init(buffer->nexts + buffer->length, -1, (buffer->capacity - buffer->length) * sizeof(int));
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
                index_of(buffer->keys[last], &hash, &prev);
                if (prev > -1)
                {
                    buffer->nexts[prev] = curr;
                }
                else
                {
                    buffer->hashs[hash] = curr;
                }

                buffer->nexts[curr]  = buffer->nexts[last];
                buffer->keys[curr]   = buffer->keys[last];
                buffer->values[curr] = buffer->values[last];
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

template <typename TKey, typename TValue>
inline u64 hashof(const Table<TKey, TValue>& table)
{
    return hashof(table.get_keys(), table.get_length()) ^ hashof(table.get_values(), table.get_length());
}

template <typename TKey, typename TValue>
inline int lengthof(const Table<TKey, TValue>& table)
{
    return table.get_length();
}