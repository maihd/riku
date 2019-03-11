// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#include <riku/json.h>
#include "./unit_test.h"

TEST_CASE("JSON testing", "[JSON]")
{
    json::Value value = json::parse("[ 1 ]");
    REQUIRE(value.type == json::Type::Array);
    REQUIRE(value.length == 1);
    REQUIRE(value[0].type == json::Type::Number);
    REQUIRE(value[0].number == 1.0);
}   