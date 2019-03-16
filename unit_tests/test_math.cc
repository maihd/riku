// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#include <riku/math.h> // Just compile

//#include <cmath>
#include "./unit_test.h"

TEST_CASE("HLSL Math", "[math]")
{
    auto a = fabsf(10);
    auto b = fabsf(10.0f);

    auto c = cos(10.0f);
}