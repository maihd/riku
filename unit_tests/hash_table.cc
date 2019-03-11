// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#include <riku/hash_table.h>
#include "./unit_test.h"

TEST_CASE("HashTable", "[hash_table]")
{
    HashTable<int> hash_table;

    table::set(hash_table, 10, 10);
    table::set(hash_table, 11, 10);
    table::set(hash_table, 12, 10);
    table::set(hash_table, 13, 10);
    table::set(hash_table, 14, 10);
    
    int value;
    table::try_get(hash_table, 14, &value);
}