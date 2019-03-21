// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#pragma once

#include "./base.h"
#include "./int2.h"
#include "./bool2x2.h"

union int2x2
{
public: // @region: Constructors
    inline int2x2(void)
    {
        (*this)[0] = int2(1, 0);
        (*this)[1] = int2(0, 1);
    }

    inline int2x2(const int2& m0, const int2& m1)
    {
        (*this)[0] = m0;
        (*this)[1] = m1;
    }   

    inline int2x2(int m00, int m01, int m10, int m11)
    {
        (*this)[0] = int2(m00, m01);
        (*this)[1] = int2(m10, m11);
    }

    inline int2x2(int s)
    {
        (*this)[0] = int2(s, s);
        (*this)[1] = int2(s, s);
    }

public: // @region: Operators
    inline int2& operator[](int index)
    {
        ASSERT(index > -1 && index < 2, "Index out of range");
        return ((int2*)data)[index];
    }

    inline const int2& operator[](int index) const
    {
        ASSERT(index > -1 && index < 2, "Index out of range");
        return ((int2*)data)[index];
    }
    
private: // @region: Internal fields
    struct
    {
        int data[2][2];
    };
};

inline int2x2 operator-(const int2x2& m)
{
    return int2x2(
        -m[0][0], -m[0][1],
        -m[1][0], -m[1][1]);
}

inline int2x2& operator++(int2x2& m)
{
    ++m[0][0]; ++m[0][1];
    ++m[1][0]; ++m[1][1];
    return m;
}

inline int2x2& operator--(int2x2& m)
{
    --m[0][0]; --m[0][1];
    --m[1][0]; --m[1][1];
    return m;
}

inline int2x2 operator++(int2x2& m, int)
{
    const int2x2 result = m;
    ++m;
    return result;
}

inline int2x2 operator--(int2x2& m, int)
{
    const int2x2 result = m;
    --m;
    return result;
}

inline int2x2 operator+(const int2x2& a, const int2x2& b)
{
    return int2x2(
        a[0][0] + b[0][0], a[0][1] + b[0][1],
        a[1][0] + b[1][0], a[1][1] + b[1][1]);
}

inline int2x2 operator-(const int2x2& a, const int2x2& b)
{
    return int2x2(
        a[0][0] - b[0][0], a[0][1] - b[0][1],
        a[1][0] - b[1][0], a[1][1] - b[1][1]);
}

inline int2x2 operator*(const int2x2& a, const int2x2& b)
{
    return int2x2(
        a[0][0] * b[0][0], a[0][1] * b[0][1],
        a[1][0] * b[1][0], a[1][1] * b[1][1]);
}

inline int2x2 operator/(const int2x2& a, const int2x2& b)
{
    return int2x2(
        a[0][0] / b[0][0], a[0][1] / b[0][1],
        a[1][0] / b[1][0], a[1][1] / b[1][1]);
}

inline int2x2 operator+(const int2x2& a, int b)
{
    return int2x2(
        a[0][0] + b, a[0][1] + b,
        a[1][0] + b, a[1][1] + b);
}

inline int2x2 operator-(const int2x2& a, int b)
{
    return int2x2(
        a[0][0] - b, a[0][1] - b,
        a[1][0] - b, a[1][1] - b);
}

inline int2x2 operator*(const int2x2& a, int b)
{
    return int2x2(
        a[0][0] * b, a[0][1] * b,
        a[1][0] * b, a[1][1] * b);
}

inline int2x2 operator/(const int2x2& a, int b)
{
    return int2x2(
        a[0][0] / b, a[0][1] / b,
        a[1][0] / b, a[1][1] / b);
}

inline int2x2 operator+(int a, const int2x2& b)
{
    return int2x2(
        a + b[0][0], a + b[0][1],
        a + b[1][0], a + b[1][1]);
}

inline int2x2 operator-(int a, const int2x2& b)
{
    return int2x2(
        a - b[0][0], a - b[0][1],
        a - b[1][0], a - b[1][1]);
}

inline int2x2 operator*(int a, const int2x2& b)
{
    return int2x2(
        a * b[0][0], a * b[0][1],
        a * b[1][0], a * b[1][1]);
}

inline int2x2 operator/(int a, const int2x2& b)
{
    return int2x2(
        a / b[0][0], a / b[0][1],
        a / b[1][0], a / b[1][1]);
}

inline int2x2& operator+=(int2x2& a, int b)
{
    return (a = a + b);
}

inline int2x2& operator-=(int2x2& a, int b)
{
    return (a = a - b);
}

inline int2x2& operator*=(int2x2& a, int b)
{
    return (a = a * b);
}

inline int2x2& operator/=(int2x2& a, int b)
{
    return (a = a / b);
}

inline int2x2& operator+=(int2x2& a, const int2x2& b)
{
    return (a = a + b);
}

inline int2x2& operator-=(int2x2& a, const int2x2& b)
{
    return (a = a - b);
}

inline int2x2& operator*=(int2x2& a, const int2x2& b)
{
    return (a = a * b);
}

inline int2x2& operator/=(int2x2& a, const int2x2& b)
{
    return (a = a / b);
}

inline bool2x2 operator<(const int2x2& a, const int2x2& b)
{
    return bool2x2(
        a[0][0] < b[0][0], a[0][1] < b[0][1],
        a[1][0] < b[1][0], a[1][1] < b[1][1]);
}

inline bool2x2 operator>(const int2x2& a, const int2x2& b)
{
    return bool2x2(
        a[0][0] > b[0][0], a[0][1] > b[0][1],
        a[1][0] > b[1][0], a[1][1] > b[1][1]);
}

inline bool2x2 operator<=(const int2x2& a, const int2x2& b)
{
    return bool2x2(
        a[0][0] <= b[0][0], a[0][1] <= b[0][1],
        a[1][0] <= b[1][0], a[1][1] <= b[1][1]);
}

inline bool2x2 operator>=(const int2x2& a, const int2x2& b)
{
    return bool2x2(
        a[0][0] >= b[0][0], a[0][1] >= b[0][1],
        a[1][0] >= b[1][0], a[1][1] >= b[1][1]);
}

inline bool2x2 operator==(const int2x2& a, const int2x2& b)
{
    return bool2x2(
        a[0][0] == b[0][0], a[0][1] == b[0][1],
        a[1][0] == b[1][0], a[1][1] == b[1][1]);
}

inline bool2x2 operator!=(const int2x2& a, const int2x2& b)
{
    return bool2x2(
        a[0][0] != b[0][0], a[0][1] != b[0][1],
        a[1][0] != b[1][0], a[1][1] != b[1][1]);
}

namespace math
{
    inline bool all(const int2x2& v)
    {
	    return v[0][0] != 0 && v[0][1] != 0 && v[1][0] != 0 && v[1][1] != 0;
    }

    inline bool any(const int2x2& v)
    {
	    return v[0][0] != 0 || v[0][1] != 0 || v[1][0] != 0 || v[1][1] != 0;
    }
}