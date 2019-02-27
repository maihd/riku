#pragma once

#include "./types.h"
#include "./define.h"

#include <stdlib.h>
#include <string.h>

template <typename T>
struct HashTable
{
public:
    int  length;
    int  capacity;
    int* hashs;
    int* nexts;
    int* keys;
    T*   values;

public:
    HashTable(int hash_count = 64)
        : length(0)
        , capacity(0)
        , nexts(NULL)
        , keys(NULL)
        , values(NULL)
    {
        hashs = (int*)malloc(sizeof(hash_count) + hash_count * sizeof(hashs[0]));
        memcpy(hashs, &hash_count, sizeof(hash_count));

        hashs = (int*)((char*)hashs + sizeof(hash_count));

        for (int i = 0; i < hash_count; i++)
        {
            hashs[i] = -1;
        }
    }

    inline ~HashTable()
    {
        free(nexts);
        free(keys);
        free(values);
        free(hashs ? hashs - 1 : NULL);
    }

public:
    inline HashTable(HashTable<T>&& table)
    {
        nexts  = table.nexts;
        keys   = table.keys;
        values = table.values;
        hashs  = table.hashs;

        table.nexts  = NULL;
        table.keys   = NULL;
        table.values = NULL;
        table.hashs  = NULL;
    }

    inline HashTable<T>& operator=(HashTable<T>&& table)
    {
        free(nexts);
        free(keys);
        free(values);
        free(hashs ? hashs - 1 : NULL);

        nexts  = table.nexts;
        keys   = table.keys;
        values = table.values;
        hashs  = table.hashs;

        table.nexts  = NULL;
        table.keys   = NULL;
        table.values = NULL;
        table.hashs  = NULL;
    }
};

namespace table
{
    template <typename T>
    inline void unref(HashTable<T>& table)
    {
        table.nexts  = NULL;
        table.keys   = NULL;
        table.values = NULL;
        table.hashs  = NULL;
    }

    template <typename T>
    inline int hash_count(const HashTable<T>& table)
    {
        return table.hashs[-1];
    }

    template <typename T>
    int find(const HashTable<T>& table, int key, int* out_hash = NULL, int* out_prev = NULL)
    {
        int hash = key % hash_count(table);
        int curr = table.hashs[hash];
        int prev = -1;

        while (curr > -1)
        {
            if (table.keys[curr] == key)
            {
                break;
            }

            prev = curr;
            curr = table.nexts[curr];
        }

        if (out_hash) *out_hash = hash;
        if (out_prev) *out_prev = prev;
        return curr;
    }

    template <typename T>
    const T& get(const HashTable<T>& table, int key)
    {
        int curr = find(table, key);
        return table.values[curr];
    }

    template <typename T>
    const T& get(const HashTable<T>& table, int key, const T& def_value)
    {
        int curr = find(table, key);
        return (curr > -1) ? table.values[curr] : def_value;
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
            *out_value = table.values[curr];
            return true;
        }
        else
        {
            return false;
        }
    }

    template <typename T>
    bool has(const HashTable<T>& table)
    {
        return find(table, key) > -1;
    }

    template <typename T>
    bool set(HashTable<T>& table, int key, const T& value)
    {
        int hash, prev;
        int curr = find(table, key, &hash, &prev);

        if (curr < 0)
        {
            if (table.length + 1 > table.capacity)
            {
                int new_size = table.capacity > 0 ? table.capacity : 8;
                table.nexts = (int*)realloc(table.nexts, sizeof(int) * new_size);
                table.keys = (int*)realloc(table.keys, sizeof(int) * new_size);
                table.values = (T*)realloc(table.values, sizeof(T) * new_size);

                if (!table.nexts || !table.keys || !table.values)
                {
                    free(table.nexts);
                    free(table.keys);
                    free(table.values);

                    table.nexts = NULL;
                    table.keys = NULL;
                    table.values = NULL;
                    return false;
                }
            }

            curr = table.length++;
            if (prev > -1)
            {
                table.nexts[prev] = curr;
            }
            else
            {
                table.hashs[hash] = curr;
            }
            table.nexts[curr] = -1;
            table.keys[curr] = key;
        }

        table.values[curr] = value;
        return true;
    }
}