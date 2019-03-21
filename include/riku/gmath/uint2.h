// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#pragma once

#include "./base.h"
#include "./bool2.h"

union uint2
{
public: // @region: Fields
    struct
    {
        uint x, y;
    };

public: // @region: Constructors
    inline uint2() : x(0), y(0) {}

    inline uint2(uint x, uint y)
        : x(x)
        , y(y) {}

    inline uint2(uint s)
        : x(s)
        , y(s) {}

public: // @region: Operators
    inline uint& operator[](int index)
    {
        ASSERT(index > -1 && index < 2, "Index out of range");
        return ((uint*)this)[index];
    }

    inline uint  operator[](int index) const
    {
        ASSERT(index > -1 && index < 2, "Index out of range");
        return ((uint*)this)[index];
    }
};inline uint2& operator++(uint2& v)
{
    ++v.x;
    ++v.y;
    return v;
}

inline uint2& operator--(uint2& v)
{
    --v.x;
    --v.y;
    return v;
}

inline uint2 operator++(uint2& v, int)
{
    const uint2 result = v;
    v.x++;
    v.y++;
    return result;
}

inline uint2 operator--(uint2& v, int)
{
    const uint2 result = v;
    v.x--;
    v.y--;
    return result;
}

inline uint2 operator+(const uint2& a, const uint2& b)
{
    return uint2(a.x + b.x, a.y + b.y);
}

inline uint2 operator-(const uint2& a, const uint2& b)
{
    return uint2(a.x - b.x, a.y - b.y);
}

inline uint2 operator*(const uint2& a, const uint2& b)
{
    return uint2(a.x * b.x, a.y * b.y);
}

inline uint2 operator/(const uint2& a, const uint2& b)
{
    return uint2(a.x / b.x, a.y / b.y);
}

inline uint2 operator+(const uint2& a, uint b)
{
    return uint2(a.x + b, a.y + b);
}

inline uint2 operator-(const uint2& a, uint b)
{
    return uint2(a.x - b, a.y - b);
}

inline uint2 operator*(const uint2& a, uint b)
{
    return uint2(a.x * b, a.y * b);
}

inline uint2 operator/(const uint2& a, uint b)
{
    return uint2(a.x / b, a.y / b);
}

inline uint2 operator+(uint a, const uint2& b)
{
    return uint2(a + b.x, a + b.y);
}

inline uint2 operator-(uint a, const uint2& b)
{
    return uint2(a - b.x, a - b.y);
}

inline uint2 operator*(uint a, const uint2& b)
{
    return uint2(a * b.x, a * b.y);
}

inline uint2 operator/(uint a, const uint2& b)
{
    return uint2(a / b.x, a / b.y);
}

inline uint2& operator+=(uint2& a, uint b)
{
    return (a = a + b);
}

inline uint2& operator-=(uint2& a, uint b)
{
    return (a = a - b);
}

inline uint2& operator*=(uint2& a, uint b)
{
    return (a = a * b);
}

inline uint2& operator/=(uint2& a, uint b)
{
    return (a = a / b);
}

inline uint2& operator+=(uint2& a, const uint2& b)
{
    return (a = a + b);
}

inline uint2& operator-=(uint2& a, const uint2& b)
{
    return (a = a - b);
}

inline uint2& operator*=(uint2& a, const uint2& b)
{
    return (a = a * b);
}

inline uint2& operator/=(uint2& a, const uint2& b)
{
    return (a = a / b);
}

inline bool2 operator<(const uint2& a, const uint2& b)
{
    return bool2(a.x < b.x, a.y < b.y);
}

inline bool2 operator>(const uint2& a, const uint2& b)
{
    return bool2(a.x > b.x, a.y > b.y);
}

inline bool2 operator<=(const uint2& a, const uint2& b)
{
    return bool2(a.x <= b.x, a.y <= b.y);
}

inline bool2 operator>=(const uint2& a, const uint2& b)
{
    return bool2(a.x >= b.x, a.y >= b.y);
}

inline bool2 operator==(const uint2& a, const uint2& b)
{
    return bool2(a.x == b.x, a.y == b.y);
}

inline bool2 operator!=(const uint2& a, const uint2& b)
{
    return bool2(a.x != b.x, a.y != b.y);
}

namespace math
{
    inline bool all(const uint2& v)
    {
	    return v.x != 0 && v.y != 0;
    }

    inline bool any(const uint2& v)
    {
	    return v.x != 0 || v.y != 0;
    }
}
