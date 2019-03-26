#include <riku/core.h>

#include "./unit_test.h"

TEST_CASE("traits module testing", "[traits]")
{
    REQUIRE(string::equals(traits::nameof<int>(), "int"));
}