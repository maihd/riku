#include <stdio.h>
#include <riku/array.h>

#include "./unit_test.h"

// Array size test
static_assert(sizeof(Array<int>) == sizeof(int*), "Sizeof Array<TItem> is too big, maybe contains hidden member");

TEST_CASE("Test array operations", "[Array]")
{
    Array<int> int_array, int_array1;

    if (true) // Test get items property
    {
        const Array<int>& tmp_array = int_array;
        int* items        = int_array.items;
        const int* citems = tmp_array.items;

        // should compile failed
        // items = tmp_array.items;
    }

    for (int i = 0, n = 10; i < n; i++)
    {
        array::push(int_array, i);
    }
    REQUIRE(int_array.length == 10);

    console::log("int_array after pushing...");
    for (int i = 0, n = int_array.length; i < n; i++)
    {
        REQUIRE(int_array[i] == i);
        console::log("\tint_array[%d] = %d", i, int_array[i]);
    }
    
    console::log("Clearing int_array with array::pop()");
    for (int i = 0, n = int_array.length; i < n; i++)
    {
        array::pop(int_array);
    }
    REQUIRE(int_array.length == 0);

    for (int i = 0, n = 10; i < n; i++)
    {
        array::unshift(int_array, i);
    }
    REQUIRE(int_array.length == 10);

    console::log("int_array after unshifting...");
    for (int i = 0, n = int_array.length; i < n; i++)
    {
        REQUIRE(int_array[i] == n - i - 1);
        console::log("\tint_array[%d] = %d", i, int_array[i]);
    }
    
    console::log("Clearing int_array with array::shift()");
    for (int i = 0, n = int_array.length; i < n; i++)
    {
        array::shift(int_array);
    }
    REQUIRE(int_array.length == 0);

    array::push(int_array, 0);
    array::push(int_array, 1);
    array::push(int_array, 2);
    array::push(int_array, 3);
    array::push(int_array, 4);
    array::push(int_array, 5);
    array::push(int_array, 6);
    array::push(int_array, 7);
    array::push(int_array, 8);
    array::push(int_array, 9);
    REQUIRE(int_array.length == 10);

    array::unshift(int_array1, 0);
    array::unshift(int_array1, 1);
    array::unshift(int_array1, 2);
    array::unshift(int_array1, 3);
    array::unshift(int_array1, 4);
    array::unshift(int_array1, 5);
    array::unshift(int_array1, 6);
    array::unshift(int_array1, 7);
    array::unshift(int_array1, 8);
    array::unshift(int_array1, 9);
    REQUIRE(int_array.length == 10);

    for (int i = 0, n = int_array.length; i < n; i++)
    {
        REQUIRE(array::index_of(int_array, int_array[i]) == i);
    }

    for (int i = 0, n = int_array1.length; i < n; i++)
    {
        REQUIRE(array::last_index_of(int_array1, int_array1[i]) == i);
    }

    console::log("Cloning int_array...");
    Array<int> concat_array = array::clone(int_array);
    REQUIRE(concat_array.length == int_array.length);
    REQUIRE(concat_array.capacity == int_array.capacity);
    for (int i = 0, n = concat_array.length; i < n; i++)
    {
        REQUIRE(concat_array[i] == int_array[i]);
    }

    console::log("Concat int_array1 to concat_array...");
    int new_length = concat_array.length + int_array1.length;
    REQUIRE(array::concat(concat_array, int_array1));
    REQUIRE(concat_array.length == new_length);

    console::log("int_array after concat...");
    for (int i = 0, n = concat_array.length; i < n; i++)
    {
        console::log("\tconcat_array[%d] = %d", i, concat_array[i]);
    }
}