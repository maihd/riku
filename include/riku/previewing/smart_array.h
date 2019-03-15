// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#pragma once

#include "../array.h"

// SmartArray: Fast and safe, reuse memory Array
// @note: Donot use pointer of this type
template <typename TItem>
struct SmartArray
{
public:
    Array<TItem> items;
    Array<int>   free_items;

public:
    PROPERTY_READONLY(int, length, get_length);

    inline int get_length(void) const
    {
        return items.get_length() - free_items.get_length();
    }

public:
    inline TItem& operator[](int index)
    {
        return items[index];
    }

    inline const TItem& operator[](int index) const
    {
        return items[index];
    }
};

namespace array
{
    template <typename TItem>
    inline int new_item(SmartArray<TItem>& array)
    {
        int index;
        if (array.free_items.get_length() > 0)
        {
            index = array::pop(array.free_items);
        }
        else
        {
            if (!ensure(array.items, array.items.get_length() + 1))
            {
                return -1;
            }

            index = array.items.buffer->length++;
        }

        return index;
    }

    template <typename TItem>
    inline bool remove_at(SmartArray<TItem>& array, int index)
    {
        if (index > -1 && index < array.items.get_length())
        {
            return array.free_items.push(index);
        }
        else
        {
            return false;
        }
    }
}