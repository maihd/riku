// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#pragma once

#include "./base.h"
#include "./uint3.h"
#include "./bool3x3.h"

union uint3x3
{
public: // @region: Constructors
    inline uint3x3(void)
    {
        (*this)[0] = uint3(1, 0, 0);
        (*this)[1] = uint3(0, 1, 0);
        (*this)[2] = uint3(0, 0, 1);
    }

    inline uint3x3(const uint3& m0, const uint3& m1, const uint3& m2)
    {
        (*this)[0] = m0;
        (*this)[1] = m1;
        (*this)[2] = m2;
    }

    inline uint3x3(uint m00, uint m01, uint m02,
                  uint m10, uint m11, uint m12,
                  uint m20, uint m21, uint m22)
    {
        (*this)[0] = uint3(m00, m01, m02);
        (*this)[1] = uint3(m10, m11, m12);
        (*this)[2] = uint3(m20, m21, m22);
    }

    inline uint3x3(uint s)
    {
        (*this)[0] = uint3(s, s, s);
        (*this)[1] = uint3(s, s, s);
        (*this)[2] = uint3(s, s, s);
    }

public: // @region: Operators
    inline uint3& operator[](int index)
    {
        ASSERT(index > -1 && index < 3, "Index out of range");
        return ((uint3*)data)[index];
    }

    inline const uint3& operator[](int index) const
    {
        ASSERT(index > -1 && index < 3, "Index out of range");
        return ((uint3*)data)[index];
    }
    
private: // @region: Internal fields
    struct
    {
        uint data[3][3];
    };
};

inline const uint3x3& operator+(const uint3x3& m)
{
    return m;
}

inline uint3x3& operator--(uint3x3& m)
{
    --m[0];
    --m[1];
    --m[2];
    return m;
}

inline uint3x3& operator++(uint3x3& m)
{
    ++m[0];
    ++m[1];
    ++m[2];
    return m;
}

inline const uint3x3& operator--(uint3x3& m, int)
{
    m[0]--;
    m[1]--;
    m[2]--;
    return m;
}

inline const uint3x3& operator++(uint3x3& m, int)
{
    m[0]++;
    m[1]++;
    m[2]++;
    return m;
}

inline uint3x3 operator+(const uint3x3& a, const uint3x3& b)
{
    uint3x3 result;
    result[0] = a[0] + b[0];
    result[1] = a[1] + b[1];
    result[2] = a[2] + b[2];
    return result;
}

inline uint3x3 operator-(const uint3x3& a, const uint3x3& b)
{
    uint3x3 result;
    result[0] = a[0] - b[0];
    result[1] = a[1] - b[1];
    result[2] = a[2] - b[2];
    return result;
}

inline uint3x3 operator*(const uint3x3& a, const uint3x3& b)
{
    uint3x3 result;
    result[0] = a[0] * b[0];
    result[1] = a[1] * b[1];
    result[2] = a[2] * b[2];
    return result;
}

inline uint3x3 operator/(const uint3x3& a, const uint3x3& b)
{
    uint3x3 result;
    result[0] = a[0] / b[0];
    result[1] = a[1] / b[1];
    result[2] = a[2] / b[2];
    return result;
}

inline uint3x3 operator+(const uint3x3& a, uint b)
{
    uint3x3 result;
    result[0] = a[0] + b;
    result[1] = a[1] + b;
    result[2] = a[2] + b;
    return result;
}

inline uint3x3 operator-(const uint3x3& a, uint b)
{
    uint3x3 result;
    result[0] = a[0] - b;
    result[1] = a[1] - b;
    result[2] = a[2] - b;
    return result;
}

inline uint3x3 operator*(const uint3x3& a, uint b)
{
    uint3x3 result;
    result[0] = a[0] * b;
    result[1] = a[1] * b;
    result[2] = a[2] * b;
    return result;
}

inline uint3x3 operator/(const uint3x3& a, uint b)
{
    uint3x3 result;
    result[0] = a[0] / b;
    result[1] = a[1] / b;
    result[2] = a[2] / b;
    return result;
}

inline uint3x3 operator+(uint a, const uint3x3& b)
{
    uint3x3 result;
    result[0] = a + b[0];
    result[1] = a + b[1];
    result[2] = a + b[2];
    return result;
}

inline uint3x3 operator-(uint a, const uint3x3& b)
{
    uint3x3 result;
    result[0] = a - b[0];
    result[1] = a - b[1];
    result[2] = a - b[2];
    return result;
}

inline uint3x3 operator*(uint a, const uint3x3& b)
{
    uint3x3 result;
    result[0] = a * b[0];
    result[1] = a * b[1];
    result[2] = a * b[2];
    return result;
}

inline uint3x3 operator/(uint a, const uint3x3& b)
{
    uint3x3 result;
    result[0] = a / b[0];
    result[1] = a / b[1];
    result[2] = a / b[2];
    return result;
}

inline uint3x3& operator+=(uint3x3& a, const uint3x3& b)
{
    return (a = a + b);
}

inline uint3x3& operator+=(uint3x3& a, uint b)
{
    return (a = a + b);
}

inline uint3x3& operator-=(uint3x3& a, const uint3x3& b)
{
    return (a = a - b);
}

inline uint3x3& operator-=(uint3x3& a, uint b)
{
    return (a = a - b);
}

inline uint3x3& operator*=(uint3x3& a, const uint3x3& b)
{
    return (a = a * b);
}

inline uint3x3& operator*=(uint3x3& a, uint b)
{
    return (a = a * b);
}

inline uint3x3& operator/=(uint3x3& a, const uint3x3& b)
{
    return (a = a / b);
}

inline uint3x3& operator/=(uint3x3& a, uint b)
{
    return (a = a + b);
}

inline bool3x3 operator==(const uint3x3& a, const uint3x3& b)
{
    bool3x3 result;
    result[0] = a[0] == b[0];
    result[1] = a[1] == b[1];
    result[2] = a[2] == b[2];
    return result;
}

inline bool3x3 operator!=(const uint3x3& a, const uint3x3& b)
{
    bool3x3 result;
    result[0] = a[0] != b[0];
    result[1] = a[1] != b[1];
    result[2] = a[2] != b[2];
    return result;
}

inline bool3x3 operator<(const uint3x3& a, const uint3x3& b)
{
    bool3x3 result;
    result[0] = a[0] < b[0];
    result[1] = a[1] < b[1];
    result[2] = a[2] < b[2];
    return result;
}

inline bool3x3 operator>(const uint3x3& a, const uint3x3& b)
{
    bool3x3 result;
    result[0] = a[0] > b[0];
    result[1] = a[1] > b[1];
    result[2] = a[2] > b[2];
    return result;
}

inline bool3x3 operator<=(const uint3x3& a, const uint3x3& b)
{
    bool3x3 result;
    result[0] = a[0] <= b[0];
    result[1] = a[1] <= b[1];
    result[2] = a[2] <= b[2];
    return result;
}

inline bool3x3 operator>=(const uint3x3& a, const uint3x3& b)
{
    bool3x3 result;
    result[0] = a[0] >= b[0];
    result[1] = a[1] >= b[1];
    result[2] = a[2] >= b[2];
    return result;
}

namespace math
{
    inline bool all(const uint3x3& v)
    {
        return
            v[0][0] != 0 && v[0][1] != 0 && v[0][2] != 0 &&
            v[1][0] != 0 && v[1][1] != 0 && v[1][2] != 0 &&
            v[2][0] != 0 && v[2][1] != 0 && v[2][2] != 0;
    }

    inline bool any(const uint3x3& v)
    {
        return
            v[0][0] != 0 || v[0][1] != 0 || v[0][2] != 0 ||
            v[1][0] != 0 || v[1][1] != 0 || v[1][2] != 0 ||
            v[2][0] != 0 || v[2][1] != 0 || v[2][2] != 0;
    }
}

