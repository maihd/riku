#include <stdio.h>
#include <riku/array.h>

#include "./unit-test.h"

// Array size test
static_assert(sizeof(Array<int>) == sizeof(int*), "Sizeof Array<TItem> is too big, maybe contains hidden member");

TEST_CASE("Test array operations", "[Array]")
{
    Array<int> int_array, int_array1;

    for (int i = 0, n = 10; i < n; i++)
    {
        array::push(int_array, i);
    }
    REQUIRE(int_array.length == 10);

    printf("int_array after pushing...\n");
    for (int i = 0, n = int_array.length; i < n; i++)
    {
        REQUIRE(int_array[i] == i);
        printf("\tint_array[%d] = %d\n", i, int_array[i]);
    }
    
    printf("Clearing int_array with array::pop()\n");
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

    printf("int_array after unshifting...\n");
    for (int i = 0, n = int_array.length; i < n; i++)
    {
        REQUIRE(int_array[i] == n - i - 1);
        printf("\tint_array[%d] = %d\n", i, int_array[i]);
    }
    
    printf("Clearing int_array with array::shift()\n");
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

    array::push(int_array1, 0);
    array::push(int_array1, 1);
    array::push(int_array1, 2);
    array::push(int_array1, 3);
    array::push(int_array1, 4);
    array::push(int_array1, 5);
    array::push(int_array1, 6);
    array::push(int_array1, 7);
    array::push(int_array1, 8);
    array::push(int_array1, 9);
    REQUIRE(int_array.length == 10);

    for (int i = 0, n = int_array.length; i < n; i++)
    {
        REQUIRE(array::index_of(int_array, int_array[i]) == i);
    }

    for (int i = 0, n = int_array1.length; i < n; i++)
    {
        REQUIRE(array::last_index_of(int_array1, int_array1[i]) == i);
    }

    int new_length = int_array.length + int_array1.length;
    array::concat(int_array, int_array1);
    REQUIRE(int_array.length == new_length);

    printf("int_array after concat...\n");
    for (int i = 0, n = int_array.length; i < n; i++)
    {
        printf("\tint_array[%d] = %d\n", i, int_array[i]);
    }
}