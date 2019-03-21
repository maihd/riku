// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#pragma once

#include "./base.h"

union bool3
{
public: // @region: Fields
    struct
    {
        bool x, y, z;
    };

public: // @region: Constructors
    inline bool3() : x(false), y(false), z(false) {}

    inline bool3(bool x, bool y, bool z)
        : x(x)
        , y(y) 
        , z(z) {}

    inline bool3(bool s)
        : x(s)
        , y(s)
        , z(s) {}

public: // @region: Operators
    inline bool& operator[](int index)
    {
        ASSERT(index > -1 && index < 3, "Index out of range");
        return ((bool*)this)[index];
    }

    inline bool  operator[](int index) const
    {
        ASSERT(index > -1 && index < 3, "Index out of range");
        return ((bool*)this)[index];
    }
};

namespace math
{
    inline bool all(const bool3& v)
    {
        return v.x && v.y && v.z;
    }

    inline bool any(const bool3& v)
    {
        return v.x || v.y || v.z ;
    }
}

