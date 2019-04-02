// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#include <riku/json.h>
#include "./unit_test.h"

TEST_CASE("JSON testing", "[JSON]")
{
    json::Value value = json::parse("[ 1 ]");
    REQUIRE(value.type == json::Type::Array);
    REQUIRE(value.get_length() == 1);
    REQUIRE(value[0].type == json::Type::Number);
    REQUIRE(value[0].number == 1.0);

    value = json::parse("{\"a\":\"b\"}");
    REQUIRE(value.type == json::Type::Object);
    REQUIRE(value.get_length() == 1);
    REQUIRE(value["a"].type == json::Type::String);
    REQUIRE(string::compare(value["a"].string, "b") == 0);
}   