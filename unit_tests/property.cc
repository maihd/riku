// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#include <stdio.h>

#include "./unit_test.h"

#define test_assert(a, b) console::log(#a " = %d - " #b " = %d", a, b)

struct Type
{
public:
    propdef(get_value, set_value) int value;

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
static_assert(sizeof(Type) == sizeof(int), "property should not create new member in data structure, it's just syntax sugar man.");

TEST_CASE("Property testing", "[property]")
{
    Type test;
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
}