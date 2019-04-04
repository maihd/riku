// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#include <riku/array.h>

#include "./unit_test.h"

TEST_CASE("Temporary array testing", "[TempArray]")
{
    TempoArray<int> int_array = TempoArray<int>(64);

    REQUIRE(int_array.push(10));
    REQUIRE(int_array.push(10));
    REQUIRE(int_array.push(10));
    REQUIRE(int_array.push(10));
    REQUIRE(int_array.push(10));
    REQUIRE(int_array.push(10));
    REQUIRE(int_array.push(10));
    REQUIRE(int_array.push(10));

    REQUIRE(int_array.unshift(10));
    REQUIRE(int_array.unshift(10));
    REQUIRE(int_array.unshift(10));
    REQUIRE(int_array.unshift(10));
    REQUIRE(int_array.unshift(10));
    REQUIRE(int_array.unshift(10));
    REQUIRE(int_array.unshift(10));
    REQUIRE(int_array.unshift(10));

    REQUIRE(int_array.remove(10));
    REQUIRE(int_array.remove(10));
    REQUIRE(int_array.remove(10));
    REQUIRE(int_array.remove(10));
    REQUIRE(int_array.remove(10));
    REQUIRE(int_array.remove(10));
    REQUIRE(int_array.remove(10));
    REQUIRE(int_array.remove(10));

    REQUIRE(int_array.erase(0));
    REQUIRE(int_array.erase(0));
    REQUIRE(int_array.erase(0));
    REQUIRE(int_array.erase(0));
    REQUIRE(int_array.erase(0));
    REQUIRE(int_array.erase(0));
    REQUIRE(int_array.erase(0));
    REQUIRE(int_array.erase(0));
}