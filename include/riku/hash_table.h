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
        int*         keys;
        T*           values;
    };

public:
    Buffer* buffer;

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

        new (buffer) RefCount();
        new (&buffer->hashs) Array<int>();

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

    inline HashTable<T>& operator=(const HashTable<T>&& other)
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
        return table.buffer ? table.buffer->hashs.length : 0;
    }

    template <typename T>
    int find(const HashTable<T>& table, int key, int* out_hash = NULL, int* out_prev = NULL)
    {
        int hash = key % hash_count(table);
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
    const T& get(const HashTable<T>& table, int key)
    {
        int curr = find(table, key);
        return table.buffer->values[curr];
    }

    template <typename T>
    const T& get(const HashTable<T>& table, int key, const T& def_value)
    {
        int curr = find(table, key);
        return (curr > -1) ? table.buffer->values[curr] : def_value;
    }

    template <typename T>
    T& get_ref(const HashTable<T>& table, int key)
    {
        int hash, prev;
        int curr = find(table, key, &hash, &prev);

        if (curr < 0)
        {
            if (table.buffer->length + 1 > table.buffer->capacity)
            {
                int new_size = table.buffer->capacity > 0 ? table.buffer->capacity : 8;
                table.buffer->nexts = (int*)memory::realloc(table.buffer->nexts, sizeof(int) * new_size);
                table.buffer->keys = (int*)memory::realloc(table.buffer->keys, sizeof(int) * new_size);
                table.buffer->values = (T*)memory::realloc(table.buffer->values, sizeof(T) * new_size);

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
    bool has(const HashTable<T>& table, int key)
    {
        return find(table, key) > -1;
    }

    template <typename T>
    bool try_get(const HashTable<T>& table, int key, T* out_value)
    {
        int curr = find(table, key);
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
    bool set(HashTable<T>& table, int key, const T& value)
    {
        int hash, prev;
        int curr = find(table, key, &hash, &prev);

        if (curr < 0)
        {
            if (table.buffer->length + 1 > table.buffer->capacity)
            {
                int new_size = table.buffer->capacity > 0 ? table.buffer->capacity : 8;
                table.buffer->nexts  = (int*)memory::realloc(table.buffer->nexts, sizeof(int) * new_size);
                table.buffer->keys   = (int*)memory::realloc(table.buffer->keys, sizeof(int) * new_size);
                table.buffer->values = (T*)memory::realloc(table.buffer->values, sizeof(T) * new_size);

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