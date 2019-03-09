#include <riku/json.h>
#include "./unit_test.h"

TEST_CASE("JSON testing", "[JSON]")
{
    JSON::Value value = JSON::parse("[ 1 ]");
}