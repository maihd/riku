// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#pragma once

#include "./base.h"

union bool2
{
public: // @region: Fields
    struct
    {
        bool x, y;
    };

public: // @region: Constructors
    constexpr bool2() : x(false), y(false) {}

    inline bool2(bool x, bool y)
        : x(x)
        , y(y) {}

    inline bool2(bool s)
        : x(s)
        , y(s) {}

public: // @region: Operators
    inline bool& operator[](int index)
    {
        ASSERT(index > -1 && index < 2, "Index out of range");
        return ((bool*)this)[index];
    }

    inline int  operator[](int index) const
    {
        ASSERT(index > -1 && index < 2, "Index out of range");
        return ((bool*)this)[index];
    }
};

namespace math
{
    inline bool all(const bool2& v)
    {
        return v.x && v.y;
    }

    inline bool any(const bool2& v)
    {
        return v.x || v.y;
    }
}
