// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#include <riku/hash_table.h>
#include "./unit_test.h"

TEST_CASE("HashTable", "[hash_table]")
{
    HashTable<int> hash_table;

    REQUIRE(hash_table.set(10, 10));
    REQUIRE(hash_table.set(11, 10));
    REQUIRE(hash_table.set(12, 10));
    REQUIRE(hash_table.set(13, 10));
    REQUIRE(hash_table.set(14, 10));
    
    int value;
    REQUIRE(hash_table.try_get(14, &value));
    REQUIRE(value == 10);
}