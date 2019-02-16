#include <stdio.h>

#include "../include/riku/property.h"

#define test_assert(a, b) printf(#a " = %d - " #b " = %d\n", a, b)

struct PropertyTest
{
public:
    property(int, get_value, set_value) value;
    
public:
    int get_value()
    {
        return real_value;
    }

    void set_value(int v)
    {
        real_value = v;
    }

public:
    int real_value;
};

int main()
{
    PropertyTest test;
    test.value = 0;
    test_assert(test.value, test.real_value);

    test.value = 1;
    test_assert(test.value, test.real_value);

    test.value = 1;
    test_assert(test.value, test.real_value);

    test.value = 2;
    test_assert(test.value, test.real_value);

    test.value = 3;
    test_assert(test.value, test.real_value);

    test.value = 4;
    test_assert(test.value, test.real_value);

    test.value = 5;
    test_assert(test.value, test.real_value);

    test.value = 6;
    test_assert(test.value, test.real_value);

    test.value = 7;
    test_assert(test.value, test.real_value);

    test.value = 8;
    test_assert(test.value, test.real_value);

    test.value = 9;
    test_assert(test.value, test.real_value);

    return 0;
}