// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#include <stdio.h>
#include <riku/array.h>

#include "./unit_test.h"

// Array size test
//static_assert(sizeof(Array<int>) == sizeof(int*), "Sizeof Array<TItem> is too big, maybe contains hidden member");

TEST_CASE("Test array operations", "[Array]")
{
    Array<int> int_array, int_array1;

    if (true) // Test get items property
    {
        const Array<int>& tmp_array = int_array;
        int* items        = int_array.get_items();
        const int* citems = tmp_array.get_items();

        // should compile failed
        // items = tmp_array.items;
    }

    for (int i = 0, n = 10; i < n; i++)
    {
        int_array.push(i);
    }
    REQUIRE(int_array.get_length() == 10);

    console::log("int_array after pushing...");
    for (int i = 0, n = int_array.get_length(); i < n; i++)
    {
        REQUIRE(int_array[i] == i);
        console::log("\tint_array[%d] = %d", i, int_array[i]);
    }
    
    console::log("Clearing int_array with array::pop()");
    for (int i = 0, n = int_array.get_length(); i < n; i++)
    {
        int_array.pop();
    }
    REQUIRE(int_array.get_length() == 0);

    for (int i = 0, n = 10; i < n; i++)
    {
        int_array.unshift(i);
    }
    REQUIRE(int_array.get_length() == 10);

    console::log("int_array after unshifting...");
    for (int i = 0, n = int_array.get_length(); i < n; i++)
    {
        REQUIRE(int_array[i] == n - i - 1);
        console::log("\tint_array[%d] = %d", i, int_array[i]);
    }
    
    console::log("Clearing int_array with array::shift()");
    for (int i = 0, n = int_array.get_length(); i < n; i++)
    {
        int_array.shift();
    }
    REQUIRE(int_array.get_length() == 0);

    int_array.push(0);
    int_array.push(1);
    int_array.push(2);
    int_array.push(3);
    int_array.push(4);
    int_array.push(5);
    int_array.push(6);
    int_array.push(7);
    int_array.push(8);
    int_array.push(9);
    REQUIRE(int_array.get_length() == 10);

    int_array1.unshift(0);
    int_array1.unshift(1);
    int_array1.unshift(2);
    int_array1.unshift(3);
    int_array1.unshift(4);
    int_array1.unshift(5);
    int_array1.unshift(6);
    int_array1.unshift(7);
    int_array1.unshift(8);
    int_array1.unshift(9);
    REQUIRE(int_array1.get_length() == 10);

    for (int i = 0, n = int_array.get_length(); i < n; i++)
    {
        REQUIRE(int_array.index_of(int_array[i]) == i);
    }

    for (int i = 0, n = int_array1.get_length(); i < n; i++)
    {
        REQUIRE(int_array1.last_index_of(int_array1[i]) == i);
    }

    console::log("Cloning int_array...");
    Array<int> concat_array = int_array.clone();
    REQUIRE(concat_array.get_length() == int_array.get_length());
    REQUIRE(concat_array.get_capacity() == int_array.get_capacity());
    for (int i = 0, n = concat_array.get_length(); i < n; i++)
    {
        REQUIRE(concat_array[i] == int_array[i]);
    }

    console::log("Concat int_array1 to concat_array...");
    int new_length = concat_array.get_length() + int_array1.get_length();
    REQUIRE(concat_array.concat(int_array1));
    REQUIRE(concat_array.get_length() == new_length);

    console::log("int_array after concat...");
    for (int i = 0, n = concat_array.get_length(); i < n; i++)
    {
        console::log("\tconcat_array[%d] = %d", i, concat_array[i]);
    }
}