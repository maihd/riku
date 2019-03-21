// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#pragma once

#include "./base.h"
#include "./bool3.h"

union uint3
{
public: // @region: Fields
    struct
    {
        uint x, y, z;
    };

public: // @region: Constructors
    inline uint3() : x(0), y(0), z(0) {}

    inline uint3(uint x, uint y, uint z)
        : x(x)
        , y(y) 
        , z(z) {}

    inline uint3(uint s)
        : x(s)
        , y(s)
        , z(s) {}

public: // @region: Operators
    inline uint& operator[](int index)
    {
        ASSERT(index > -1 && index < 3, "Index out of range");
        return ((uint*)this)[index];
    }

    inline uint  operator[](int index) const
    {
        ASSERT(index > -1 && index < 3, "Index out of range");
        return ((uint*)this)[index];
    }
};

inline uint3& operator++(uint3& v)
{
    ++v.x;
    ++v.y;
    ++v.z;
    return v;
}

inline uint3& operator--(uint3& v)
{
    --v.x;
    --v.y;
    --v.z;
    return v;
}

inline uint3 operator++(uint3& v, int)
{
    const uint3 result = v;
    v.x++;
    v.y++;
    v.z++;
    return result;
}

inline uint3 operator--(uint3& v, int)
{
    const uint3 result = v;
    v.x--;
    v.y--;
    v.z--;
    return result;
}

inline uint3 operator+(const uint3& a, const uint3& b)
{
    return uint3(a.x + b.x, a.y + b.y, a.z + b.z);
}

inline uint3 operator-(const uint3& a, const uint3& b)
{
    return uint3(a.x - b.x, a.y - b.y, a.z - b.z);
}

inline uint3 operator*(const uint3& a, const uint3& b)
{
    return uint3(a.x * b.x, a.y * b.y, a.z * b.z);
}

inline uint3 operator/(const uint3& a, const uint3& b)
{
    return uint3(a.x / b.x, a.y / b.y, a.z / b.z);
}

inline uint3 operator+(const uint3& a, uint b)
{
    return uint3(a.x + b, a.y + b, a.z + b);
}

inline uint3 operator-(const uint3& a, uint b)
{
    return uint3(a.x - b, a.y - b, a.z - b);
}

inline uint3 operator*(const uint3& a, uint b)
{
    return uint3(a.x * b, a.y * b, a.z * b);
}

inline uint3 operator/(const uint3& a, uint b)
{
    return uint3(a.x / b, a.y / b, a.z / b);
}

inline uint3 operator+(uint a, const uint3& b)
{
    return uint3(a + b.x, a + b.y, a + b.z);
}

inline uint3 operator-(uint a, const uint3& b)
{
    return uint3(a - b.x, a - b.y, a - b.z);
}

inline uint3 operator*(uint a, const uint3& b)
{
    return uint3(a * b.x, a * b.y, a * b.z);
}

inline uint3 operator/(uint a, const uint3& b)
{
    return uint3(a / b.x, a / b.y, a / b.z);
}

inline uint3& operator+=(uint3& a, uint b)
{
    return (a = a + b);
}

inline uint3& operator-=(uint3& a, uint b)
{
    return (a = a - b);
}

inline uint3& operator*=(uint3& a, uint b)
{
    return (a = a * b);
}

inline uint3& operator/=(uint3& a, uint b)
{
    return (a = a / b);
}

inline uint3& operator+=(uint3& a, const uint3& b)
{
    return (a = a + b);
}

inline uint3& operator-=(uint3& a, const uint3& b)
{
    return (a = a - b);
}

inline uint3& operator*=(uint3& a, const uint3& b)
{
    return (a = a * b);
}

inline uint3& operator/=(uint3& a, const uint3& b)
{
    return (a = a / b);
}

inline bool3 operator<(const uint3& a, const uint3& b)
{
    return bool3(a.x < b.x, a.y < b.y, a.z < b.z);
}

inline bool3 operator>(const uint3& a, const uint3& b)
{
    return bool3(a.x > b.x, a.y > b.y, a.z > b.z);
}

inline bool3 operator<=(const uint3& a, const uint3& b)
{
    return bool3(a.x <= b.x, a.y <= b.y, a.z <= b.z);
}

inline bool3 operator>=(const uint3& a, const uint3& b)
{
    return bool3(a.x >= b.x, a.y >= b.y, a.z >= b.z);
}

inline bool3 operator==(const uint3& a, const uint3& b)
{
    return bool3(a.x == b.x, a.y == b.y, a.z == b.z);
}

inline bool3 operator!=(const uint3& a, const uint3& b)
{
    return bool3(a.x != b.x, a.y != b.y, a.z != b.z);
}

namespace math
{
    inline bool all(const uint3& v)
    {
	    return v.x != 0 && v.y != 0 && v.z != 0;
    }

    inline bool any(const uint3& v)
    {
	    return v.x != 0 || v.y != 0 || v.z != 0;
    }
}
