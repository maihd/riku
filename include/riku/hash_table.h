// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#pragma once

#include "./core.h"
#include "./array.h"

template <typename T>
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
        T*           values;
    };

public:
    Buffer* buffer;

public: // Properties
    PROPERTY_READONLY(ulong*, keys, get_keys);
    PROPERTY_READONLY(T*, values, get_values);
    PROPERTY_READONLY(int, length, get_length);
    PROPERTY_READONLY(int, hash_count, get_hash_count);

    inline const ulong* get_keys(void) const
    {
        return buffer ? buffer->keys : 0;
    }

    inline const T* get_values(void) const
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

        array::ensure(buffer->hashs, hash_count);
        for (int i = 0; i < hash_count; i++)
        {
            array::push(buffer->hashs, -1);
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
        }
    }

public: // Copy
    inline HashTable(const HashTable<T>& other)
        : buffer(other.buffer)
    {
        if (buffer)
        {
            buffer->retain();
        }
    }

    inline HashTable<T>& operator=(const HashTable<T>& other)
    {
        buffer = other.buffer;
        if (buffer)
        {
            buffer->retain();
        }

        return *this;
    }

public: // RAII
    inline HashTable(HashTable<T>&& other)
        : buffer(other.buffer)
    {
        other.buffer = NULL;
    }

    inline HashTable<T>& operator=(HashTable<T>&& other)
    {
        this->~HashTable();
        
        buffer = other.buffer;
        other.buffer = NULL;

        return *this;
    }
};

namespace table
{
    template <typename T>
    inline void unref(HashTable<T>& table)
    {
        table.~HashTable();
        table.buffer = NULL;
    }

    template <typename T>
    inline int hash_count(const HashTable<T>& table)
    {
        return table.buffer ? table.buffer->hashs.get_length() : 0;
    }

    template <typename T>
    int index_of(const HashTable<T>& table, ulong key, int* out_hash = NULL, int* out_prev = NULL)
    {
        int hash = (int)(ulong)(key % hash_count(table));
        int curr = table.buffer->hashs[hash];
        int prev = -1;

        while (curr > -1)
        {
            if (table.buffer->keys[curr] == key)
            {
                break;
            }

            prev = curr;
            curr = table.buffer->nexts[curr];
        }

        if (out_hash) *out_hash = hash;
        if (out_prev) *out_prev = prev;
        return curr;
    }

    template <typename T>
    const T& get(const HashTable<T>& table, ulong key)
    {
        int curr = index_of(table, key);
        return table.buffer->values[curr];
    }

    template <typename T>
    const T& get(const HashTable<T>& table, ulong key, const T& def_value)
    {
        int curr = index_of(table, key);
        return (curr > -1) ? table.buffer->values[curr] : def_value;
    }

    template <typename T>
    T& get_or_new(const HashTable<T>& table, ulong key)
    {
        int hash, prev;
        int curr = index_of(table, key, &hash, &prev);

        if (curr < 0)
        {
            if (table.buffer->length + 1 > table.buffer->capacity)
            {
                int new_size = table.buffer->capacity > 0 ? table.buffer->capacity * 2 : 8;
                table.buffer->nexts  = (int*)memory::realloc(table.buffer->nexts, sizeof(int) * new_size);
                table.buffer->keys   = (ulong*)memory::realloc(table.buffer->keys, sizeof(ulong) * new_size);
                table.buffer->values = (T*)memory::realloc(table.buffer->values, sizeof(T) * new_size);

                table.buffer->capacity = new_size;
                always_assert(!(!table.buffer->nexts || !table.buffer->keys || !table.buffer->values), "Out of memory");
            }

            curr = table.buffer->length++;
            if (prev > -1)
            {
                table.buffer->nexts[prev] = curr;
            }
            else
            {
                table.buffer->hashs[hash] = curr;
            }
            table.buffer->nexts[curr] = -1;
            table.buffer->keys[curr] = key;
        }

        return table.buffer->values[curr];
    }

    template <typename T>
    bool has(const HashTable<T>& table, ulong key)
    {
        return index_of(table, key) > -1;
    }

    template <typename T>
    bool try_get(const HashTable<T>& table, ulong key, T* out_value)
    {
        int curr = index_of(table, key);
        if (curr > -1)
        {
            *out_value = table.buffer->values[curr];
            return true;
        }
        else
        {
            return false;
        }
    }

    template <typename T>
    bool set(HashTable<T>& table, ulong key, const T& value)
    {
        int hash, prev;
        int curr = index_of(table, key, &hash, &prev);

        if (curr < 0)
        {
            if (table.buffer->length + 1 > table.buffer->capacity)
            {
                int new_size = table.buffer->capacity > 0 ? table.buffer->capacity * 2 : 8;
                table.buffer->nexts  = (int*)memory::realloc(table.buffer->nexts, sizeof(int) * new_size);
                table.buffer->keys   = (ulong*)memory::realloc(table.buffer->keys, sizeof(ulong) * new_size);
                table.buffer->values = (T*)memory::realloc(table.buffer->values, sizeof(T) * new_size);

                table.buffer->capacity = new_size;
                if (!table.buffer->nexts || !table.buffer->keys || !table.buffer->values)
                {
                    memory::dealloc(table.buffer->nexts);
                    memory::dealloc(table.buffer->keys);
                    memory::dealloc(table.buffer->values);

                    table.buffer->nexts  = NULL;
                    table.buffer->keys   = NULL;
                    table.buffer->values = NULL;
                    return false;
                }
            }

            curr = table.buffer->length++;
            if (prev > -1)
            {
                table.buffer->nexts[prev] = curr;
            }
            else
            {
                table.buffer->hashs[hash] = curr;
            }
            table.buffer->nexts[curr] = -1;
            table.buffer->keys[curr] = key;
        }

        table.buffer->values[curr] = value;
        return true;
    }
}