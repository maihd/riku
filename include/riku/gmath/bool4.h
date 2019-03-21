// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#pragma once

#include "./base.h"

union bool4
{
public: // @region: Fields
    struct
    {
        bool x, y, z, w;
    };

public: // @region: Constructors
    constexpr bool4() : x(false), y(false), z(false), w(false) {}

	inline bool4(bool x, bool y, bool z, bool w)
        : x(x)
        , y(y) 
        , z(z)
        , w(w) {}

    inline bool4(bool s)
        : x(s)
        , y(s)
        , z(s)
        , w(s) {}

public: // @region: Operators
    inline bool& operator[](int index)
    {
        ASSERT(index > -1 && index < 4, "Index out of range");
        return ((bool*)this)[index];
    }

    inline bool  operator[](int index) const
    {
        ASSERT(index > -1 && index < 4, "Index out of range");
        return ((bool*)this)[index];
    }
};

namespace math
{
    inline bool all(const bool4& v)
    {
        return v.x && v.y && v.z && v.w;
    }

    inline bool any(const bool4& v)
    {
        return v.x || v.y || v.z || v.w;
    }
}