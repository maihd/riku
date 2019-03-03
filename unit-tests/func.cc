#include <functional>
#include <riku/func.h>
#include "./unit_test.h"

void simple_print(const char* s)
{
    console::log("%s", s);
}

TEST_CASE("Testing Func<...>", "[Func<>]")
{
    Func<void(const char*)> print = simple_print;

    print("Hello world");
}