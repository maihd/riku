#include <stdio.h>
#include <riku/array.h>

#include "./unit-test.h"

// Array size test
static_assert(sizeof(Array<int>) == sizeof(int*), "Sizeof Array<TItem> is too big, maybe contains hidden member");

TEST_CASE("Test array operations", "[Array]")
{
    Array<int> int_array, int_array1;

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

    printf("int_array after pushing...\n");
    for (int i = 0, n = int_array.length; i < n; i++)
    {
        printf("\tint_array[%d] = %d\n", i, int_array[i]);
    }

    array::pop(int_array);
    array::pop(int_array);
    array::pop(int_array);
    array::pop(int_array);
    array::pop(int_array);
    array::pop(int_array);
    array::pop(int_array);
    array::pop(int_array);
    array::pop(int_array);
    array::pop(int_array);

    array::unshift(int_array, 0);
    array::unshift(int_array, 1);
    array::unshift(int_array, 2);
    array::unshift(int_array, 3);
    array::unshift(int_array, 4);
    array::unshift(int_array, 5);
    array::unshift(int_array, 6);
    array::unshift(int_array, 7);
    array::unshift(int_array, 8);
    array::unshift(int_array, 9);

    printf("int_array after unshifting...\n");
    for (int i = 0, n = int_array.length; i < n; i++)
    {
        printf("\tint_array[%d] = %d\n", i, int_array[i]);
    }

    array::shift(int_array);
    array::shift(int_array);
    array::shift(int_array);
    array::shift(int_array);
    array::shift(int_array);
    array::shift(int_array);
    array::shift(int_array);
    array::shift(int_array);
    array::shift(int_array);
    array::shift(int_array);

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

    array::index_of(int_array, 0);
    array::index_of(int_array, 1);
    array::index_of(int_array, 2);
    array::index_of(int_array, 3);
    array::index_of(int_array, 4);
    array::index_of(int_array, 5);
    array::index_of(int_array, 6);
    array::index_of(int_array, 6);
    array::index_of(int_array, 7);
    array::index_of(int_array, 8);
    array::index_of(int_array, 9);
    array::last_index_of(int_array1, 0);
    array::last_index_of(int_array1, 1);
    array::last_index_of(int_array1, 2);
    array::last_index_of(int_array1, 3);
    array::last_index_of(int_array1, 4);
    array::last_index_of(int_array1, 5);
    array::last_index_of(int_array1, 6);
    array::last_index_of(int_array1, 6);
    array::last_index_of(int_array1, 7);
    array::last_index_of(int_array1, 8);
    array::last_index_of(int_array1, 9);

    array::concat(int_array, int_array1);

    printf("int_array after concat...\n");
    for (int i = 0, n = int_array.length; i < n; i++)
    {
        printf("\tint_array[%d] = %d\n", i, int_array[i]);
    }
}