// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#pragma once

#include "./base.h"
#include "./uint2.h"
#include "./bool2x2.h"

union uint2x2
{
public: // @region: Constructors
    inline uint2x2(void)
    {
        (*this)[0] = uint2(1, 0);
        (*this)[1] = uint2(0, 1);
    }

    inline uint2x2(const uint2& m0, const uint2& m1)
    {
        (*this)[0] = m0;
        (*this)[1] = m1;
    }

    inline uint2x2(uint m00, uint m01, uint m10, uint m11)
    {
        (*this)[0] = uint2(m00, m01);
        (*this)[1] = uint2(m10, m11);
    }

    inline uint2x2(uint s)
    {
        (*this)[0] = uint2(s, s);
        (*this)[1] = uint2(s, s);
    }

public: // @region: Operators
    inline uint2& operator[](int index)
    {
        ASSERT(index > -1 && index < 2, "Index out of range");
        return ((uint2*)data)[index];
    }

    inline const uint2& operator[](int index) const
    {
        ASSERT(index > -1 && index < 2, "Index out of range");
        return ((uint2*)data)[index];
    }
    
private: // @region: Internal fields
    struct
    {
        uint data[2][2];
    };
};

inline uint2x2& operator++(uint2x2& m)
{
    ++m[0][0]; ++m[0][1];
    ++m[1][0]; ++m[1][1];
    return m;
}

inline uint2x2& operator--(uint2x2& m)
{
    --m[0][0]; --m[0][1];
    --m[1][0]; --m[1][1];
    return m;
}

inline uint2x2 operator++(uint2x2& m, int)
{
    const uint2x2 result = m;
    ++m;
    return result;
}

inline uint2x2 operator--(uint2x2& m, int)
{
    const uint2x2 result = m;
    --m;
    return result;
}

inline uint2x2 operator+(const uint2x2& a, const uint2x2& b)
{
    return uint2x2(
        a[0][0] + b[0][0], a[0][1] + b[0][1],
        a[1][0] + b[1][0], a[1][1] + b[1][1]);
}

inline uint2x2 operator-(const uint2x2& a, const uint2x2& b)
{
    return uint2x2(
        a[0][0] - b[0][0], a[0][1] - b[0][1],
        a[1][0] - b[1][0], a[1][1] - b[1][1]);
}

inline uint2x2 operator*(const uint2x2& a, const uint2x2& b)
{
    return uint2x2(
        a[0][0] * b[0][0], a[0][1] * b[0][1],
        a[1][0] * b[1][0], a[1][1] * b[1][1]);
}

inline uint2x2 operator/(const uint2x2& a, const uint2x2& b)
{
    return uint2x2(
        a[0][0] / b[0][0], a[0][1] / b[0][1],
        a[1][0] / b[1][0], a[1][1] / b[1][1]);
}

inline uint2x2 operator+(const uint2x2& a, uint b)
{
    return uint2x2(
        a[0][0] + b, a[0][1] + b,
        a[1][0] + b, a[1][1] + b);
}

inline uint2x2 operator-(const uint2x2& a, uint b)
{
    return uint2x2(
        a[0][0] - b, a[0][1] - b,
        a[1][0] - b, a[1][1] - b);
}

inline uint2x2 operator*(const uint2x2& a, uint b)
{
    return uint2x2(
        a[0][0] * b, a[0][1] * b,
        a[1][0] * b, a[1][1] * b);
}

inline uint2x2 operator/(const uint2x2& a, uint b)
{
    return uint2x2(
        a[0][0] / b, a[0][1] / b,
        a[1][0] / b, a[1][1] / b);
}

inline uint2x2 operator+(uint a, const uint2x2& b)
{
    return uint2x2(
        a + b[0][0], a + b[0][1],
        a + b[1][0], a + b[1][1]);
}

inline uint2x2 operator-(uint a, const uint2x2& b)
{
    return uint2x2(
        a - b[0][0], a - b[0][1],
        a - b[1][0], a - b[1][1]);
}

inline uint2x2 operator*(uint a, const uint2x2& b)
{
    return uint2x2(
        a * b[0][0], a * b[0][1],
        a * b[1][0], a * b[1][1]);
}

inline uint2x2 operator/(uint a, const uint2x2& b)
{
    return uint2x2(
        a / b[0][0], a / b[0][1],
        a / b[1][0], a / b[1][1]);
}

inline uint2x2& operator+=(uint2x2& a, uint b)
{
    return (a = a + b);
}

inline uint2x2& operator-=(uint2x2& a, uint b)
{
    return (a = a - b);
}

inline uint2x2& operator*=(uint2x2& a, uint b)
{
    return (a = a * b);
}

inline uint2x2& operator/=(uint2x2& a, uint b)
{
    return (a = a / b);
}

inline uint2x2& operator+=(uint2x2& a, const uint2x2& b)
{
    return (a = a + b);
}

inline uint2x2& operator-=(uint2x2& a, const uint2x2& b)
{
    return (a = a - b);
}

inline uint2x2& operator*=(uint2x2& a, const uint2x2& b)
{
    return (a = a * b);
}

inline uint2x2& operator/=(uint2x2& a, const uint2x2& b)
{
    return (a = a / b);
}

inline bool2x2 operator<(const uint2x2& a, const uint2x2& b)
{
    return bool2x2(
        a[0][0] < b[0][0], a[0][1] < b[0][1],
        a[1][0] < b[1][0], a[1][1] < b[1][1]);
}

inline bool2x2 operator>(const uint2x2& a, const uint2x2& b)
{
    return bool2x2(
        a[0][0] > b[0][0], a[0][1] > b[0][1],
        a[1][0] > b[1][0], a[1][1] > b[1][1]);
}

inline bool2x2 operator<=(const uint2x2& a, const uint2x2& b)
{
    return bool2x2(
        a[0][0] <= b[0][0], a[0][1] <= b[0][1],
        a[1][0] <= b[1][0], a[1][1] <= b[1][1]);
}

inline bool2x2 operator>=(const uint2x2& a, const uint2x2& b)
{
    return bool2x2(
        a[0][0] >= b[0][0], a[0][1] >= b[0][1],
        a[1][0] >= b[1][0], a[1][1] >= b[1][1]);
}

inline bool2x2 operator==(const uint2x2& a, const uint2x2& b)
{
    return bool2x2(
        a[0][0] == b[0][0], a[0][1] == b[0][1],
        a[1][0] == b[1][0], a[1][1] == b[1][1]);
}

inline bool2x2 operator!=(const uint2x2& a, const uint2x2& b)
{
    return bool2x2(
        a[0][0] != b[0][0], a[0][1] != b[0][1],
        a[1][0] != b[1][0], a[1][1] != b[1][1]);
}

namespace math
{
    inline bool all(const uint2x2& v)
    {
	    return v[0][0] != 0 && v[0][1] != 0 && v[1][0] != 0 && v[1][1] != 0;
    }

    inline bool any(const uint2x2& v)
    {
	    return v[0][0] != 0 || v[0][1] != 0 || v[1][0] != 0 || v[1][1] != 0;
    }
}
