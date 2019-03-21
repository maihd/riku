// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#pragma once

#include "./base.h"
#include "./bool4.h"

union int4
{
public: // @region: Fields
    struct
    {
        int x, y, z, w;
    };

public: // @region: Constructors
    inline int4() : x(0), y(0), z(0), w(0) {}

    inline int4(int x, int y, int z, int w)
        : x(x)
        , y(y) 
        , z(z)
        , w(w) {}

    inline int4(int s)
        : x(s)
        , y(s)
        , z(s)
        , w(s) {}

public: // @region: Operators
    inline int& operator[](int index)
    {
        ASSERT(index > -1 && index < 4, "Index out of range");
        return ((int*)this)[index];
    }

    inline int  operator[](int index) const
    {
        ASSERT(index > -1 && index < 4, "Index out of range");
        return ((int*)this)[index];
    }
};

inline int4 operator-(const int4& v)
{
    return int4(-v.x, -v.y, -v.z, -v.w);
}

inline int4& operator++(int4& v)
{
    ++v.x;
    ++v.y;
    ++v.z;
    ++v.w;
    return v;
}

inline int4& operator--(int4& v)
{
    --v.x;
    --v.y;
    --v.z;
    --v.w;
    return v;
}

inline int4 operator++(int4& v, int)
{
    const int4 result = v;
    v.x++;
    v.y++;
    v.z++;
    v.w++;
    return result;
}

inline int4 operator--(int4& v, int)
{
    const int4 result = v;
    v.x--;
    v.y--;
    v.z--;
    v.w--;
    return result;
}

inline int4 operator+(const int4& a, const int4& b)
{
    return int4(a.x + b.x, a.y + b.y, a.z + b.z, a.w / b.w);
}

inline int4 operator-(const int4& a, const int4& b)
{
    return int4(a.x - b.x, a.y - b.y, a.z - b.z, a.w / b.w);
}

inline int4 operator*(const int4& a, const int4& b)
{
    return int4(a.x * b.x, a.y * b.y, a.z * b.z, a.w / b.w);
}

inline int4 operator/(const int4& a, const int4& b)
{
    return int4(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w);
}

inline int4 operator+(const int4& a, int b)
{
    return int4(a.x + b, a.y + b, a.z + b, a.w + b);
}

inline int4 operator-(const int4& a, int b)
{
    return int4(a.x - b, a.y - b, a.z - b, a.w - b);
}

inline int4 operator*(const int4& a, int b)
{
    return int4(a.x * b, a.y * b, a.z * b, a.w * b);
}

inline int4 operator/(const int4& a, int b)
{
    return int4(a.x / b, a.y / b, a.z / b, a.w / b);
}

inline int4 operator+(int a, const int4& b)
{
    return int4(a + b.x, a + b.y, a + b.z, a + b.w);
}

inline int4 operator-(int a, const int4& b)
{
    return int4(a - b.x, a - b.y, a - b.z, a - b.w);
}

inline int4 operator*(int a, const int4& b)
{
    return int4(a * b.x, a * b.y, a * b.z, a * b.w);
}

inline int4 operator/(int a, const int4& b)
{
    return int4(a / b.x, a / b.y, a / b.z, a / b.w);
}

inline int4& operator+=(int4& a, int b)
{
    return (a = a + b);
}

inline int4& operator-=(int4& a, int b)
{
    return (a = a - b);
}

inline int4& operator*=(int4& a, int b)
{
    return (a = a * b);
}

inline int4& operator/=(int4& a, int b)
{
    return (a = a / b);
}

inline int4& operator+=(int4& a, const int4& b)
{
    return (a = a + b);
}

inline int4& operator-=(int4& a, const int4& b)
{
    return (a = a - b);
}

inline int4& operator*=(int4& a, const int4& b)
{
    return (a = a * b);
}

inline int4& operator/=(int4& a, const int4& b)
{
    return (a = a / b);
}

inline bool4 operator<(const int4& a, const int4& b)
{
    return bool4(a.x < b.x, a.y < b.y, a.z < b.z, a.w < b.w);
}

inline bool4 operator>(const int4& a, const int4& b)
{
    return bool4(a.x > b.x, a.y > b.y, a.z > b.z, a.w > b.w);
}

inline bool4 operator<=(const int4& a, const int4& b)
{
    return bool4(a.x <= b.x, a.y <= b.y, a.z <= b.z, a.w <= b.w);
}

inline bool4 operator>=(const int4& a, const int4& b)
{
    return bool4(a.x >= b.x, a.y >= b.y, a.z >= b.z, a.w >= b.w);
}

inline bool4 operator==(const int4& a, const int4& b)
{
    return bool4(a.x == b.x, a.y == b.y, a.z == b.z, a.w == b.w);
}

inline bool4 operator!=(const int4& a, const int4& b)
{
    return bool4(a.x != b.x, a.y != b.y, a.z != b.z, a.w != b.w);
}

namespace math
{
    inline bool all(const int4& v)
    {
        return v.x != 0 && v.y != 0 && v.z != 0 && v.w != 0;
    }

    inline bool any(const int4& v)
    {
        return v.x != 0 || v.y != 0 || v.z != 0 || v.w != 0;
    }
}