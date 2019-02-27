#include <functional>
#include <riku/func.h>
#include "./unit_test.h"

void simple_print(str s)
{
    printf("%s", s);
}

TEST_CASE("Testing Func<...>", "[Func<>]")
{
    Func<void(str)> print = simple_print;

    print("Hello world\n");
}