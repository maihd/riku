// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#include <riku/core.h>
#include "./unit_test.h"

TEST_CASE("Date modules", "[date]")
{
    Date date = Date::now();
    console::log("Current date: %s", date.to_string());
}