#include <riku/core.h>

#include "./unit_test.h"

TEST_CASE("traits module testing", "[traits]")
{
    console::log("traits::nameof<int>() = %s", traits::nameof<int>());
    REQUIRE(string::equals(traits::nameof<int>(), "int"));
}