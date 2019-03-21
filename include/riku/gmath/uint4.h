// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#pragma once

#include "./base.h"
#include "./bool4.h"

union uint4
{
public: // @region: Fields
    struct
    {
        uint x, y, z, w;
    };

public: // @region: Constructors
    inline uint4() : x(0), y(0), z(0), w(0) {}

    inline uint4(uint x, uint y, uint z, uint w)
        : x(x)
        , y(y) 
        , z(z)
        , w(w) {}

    inline uint4(int s)
        : x(s)
        , y(s)
        , z(s)
        , w(s) {}

public: // @region: Operators
    inline uint& operator[](int index)
    {
        ASSERT(index > -1 && index < 4, "Index out of range");
        return ((uint*)this)[index];
    }

    inline uint  operator[](int index) const
    {
        ASSERT(index > -1 && index < 4, "Index out of range");
        return ((uint*)this)[index];
    }
};

inline uint4& operator++(uint4& v)
{
    ++v.x;
    ++v.y;
    ++v.z;
    ++v.w;
    return v;
}

inline uint4& operator--(uint4& v)
{
    --v.x;
    --v.y;
    --v.z;
    --v.w;
    return v;
}

inline uint4 operator++(uint4& v, int)
{
    const uint4 result = v;
    v.x++;
    v.y++;
    v.z++;
    v.w++;
    return result;
}

inline uint4 operator--(uint4& v, int)
{
    const uint4 result = v;
    v.x--;
    v.y--;
    v.z--;
    v.w--;
    return result;
}

inline uint4 operator+(const uint4& a, const uint4& b)
{
    return uint4(a.x + b.x, a.y + b.y, a.z + b.z, a.w / b.w);
}

inline uint4 operator-(const uint4& a, const uint4& b)
{
    return uint4(a.x - b.x, a.y - b.y, a.z - b.z, a.w / b.w);
}

inline uint4 operator*(const uint4& a, const uint4& b)
{
    return uint4(a.x * b.x, a.y * b.y, a.z * b.z, a.w / b.w);
}

inline uint4 operator/(const uint4& a, const uint4& b)
{
    return uint4(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w);
}

inline uint4 operator+(const uint4& a, uint b)
{
    return uint4(a.x + b, a.y + b, a.z + b, a.w + b);
}

inline uint4 operator-(const uint4& a, uint b)
{
    return uint4(a.x - b, a.y - b, a.z - b, a.w - b);
}

inline uint4 operator*(const uint4& a, uint b)
{
    return uint4(a.x * b, a.y * b, a.z * b, a.w * b);
}

inline uint4 operator/(const uint4& a, uint b)
{
    return uint4(a.x / b, a.y / b, a.z / b, a.w / b);
}

inline uint4 operator+(uint a, const uint4& b)
{
    return uint4(a + b.x, a + b.y, a + b.z, a + b.w);
}

inline uint4 operator-(uint a, const uint4& b)
{
    return uint4(a - b.x, a - b.y, a - b.z, a - b.w);
}

inline uint4 operator*(uint a, const uint4& b)
{
    return uint4(a * b.x, a * b.y, a * b.z, a * b.w);
}

inline uint4 operator/(uint a, const uint4& b)
{
    return uint4(a / b.x, a / b.y, a / b.z, a / b.w);
}

inline uint4& operator+=(uint4& a, uint b)
{
    return (a = a + b);
}

inline uint4& operator-=(uint4& a, uint b)
{
    return (a = a - b);
}

inline uint4& operator*=(uint4& a, uint b)
{
    return (a = a * b);
}

inline uint4& operator/=(uint4& a, uint b)
{
    return (a = a / b);
}

inline uint4& operator+=(uint4& a, const uint4& b)
{
    return (a = a + b);
}

inline uint4& operator-=(uint4& a, const uint4& b)
{
    return (a = a - b);
}

inline uint4& operator*=(uint4& a, const uint4& b)
{
    return (a = a * b);
}

inline uint4& operator/=(uint4& a, const uint4& b)
{
    return (a = a / b);
}

inline bool4 operator<(const uint4& a, const uint4& b)
{
    return bool4(a.x < b.x, a.y < b.y, a.z < b.z, a.w < b.w);
}

inline bool4 operator>(const uint4& a, const uint4& b)
{
    return bool4(a.x > b.x, a.y > b.y, a.z > b.z, a.w > b.w);
}

inline bool4 operator<=(const uint4& a, const uint4& b)
{
    return bool4(a.x <= b.x, a.y <= b.y, a.z <= b.z, a.w <= b.w);
}

inline bool4 operator>=(const uint4& a, const uint4& b)
{
    return bool4(a.x >= b.x, a.y >= b.y, a.z >= b.z, a.w >= b.w);
}

inline bool4 operator==(const uint4& a, const uint4& b)
{
    return bool4(a.x == b.x, a.y == b.y, a.z == b.z, a.w == b.w);
}

inline bool4 operator!=(const uint4& a, const uint4& b)
{
    return bool4(a.x != b.x, a.y != b.y, a.z != b.z, a.w != b.w);
}

namespace math
{
    inline bool all(const uint4& v)
    {
	    return v.x != 0 && v.y != 0 && v.z != 0 && v.w != 0;
    }

    inline bool any(const uint4& v)
    {
	    return v.x != 0 || v.y != 0 || v.z != 0 || v.w != 0;
    }
}
