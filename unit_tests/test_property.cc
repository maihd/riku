// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#include <stdio.h>

#include "./unit_test.h"

#if (defined(_MSC_VER) || (defined(__has_declspec_attriute) && __has_declspec_attribute(property)))
#define test_assert(a, b) console::log(#a " = %d - " #b " = %d", a, b)

struct Type
{
public:
    PROPERTY(int, value, get_value, set_value);

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

[[noreturn]]
void force_exit()
{
    exit(1);
}

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
#endif