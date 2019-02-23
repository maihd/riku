#pragma once

#include <riku.h>
#include "./catch2/catch.hpp"

struct UnitTest
{
    virtual void execute() = 0;
};