#include <riku/dictionary.h>
#include "./unit_test.h"

TEST_CASE("Dictionary<> testing", "[dictionary]")
{
    Dictionary<int, int> dict;

    dict[0] = 10;
    dict[1] = 10;
    dict[2] = 10;
    dict[3] = 10;
    dict[4] = 10;
    dict[5] = 10;
    dict[6] = 10;
    dict[7] = 10;
    dict[8] = 10;
    dict[9] = 10;

    for (int i = 0; i < 10; i++)
    {
        REQUIRE(dict[i] == 10);
        console::log("dict[%d] = %d", i, dict[i]);
    }
}