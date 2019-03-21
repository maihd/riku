// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#pragma once

#include "./base.h"
#include "./int4.h"
#include "./bool4x4.h"

union int4x4
{
public: // @region: Constructors
    inline int4x4(void)
    {
        (*this)[0] = int4(1, 0, 0, 0);
        (*this)[1] = int4(0, 1, 0, 0);
        (*this)[2] = int4(0, 0, 1, 0);
        (*this)[3] = int4(0, 0, 0, 1);
    }

    inline int4x4(const int4& m0, const int4& m1, const int4& m2, const int4& m3)
    {
		(*this)[0] = m0;
		(*this)[1] = m1;
		(*this)[2] = m2;
		(*this)[3] = m3;
    }

    inline int4x4(int m00, int m01, int m02, int m03,
                  int m10, int m11, int m12, int m13,
                  int m20, int m21, int m22, int m23,
                  int m30, int m31, int m32, int m33)
    {
        (*this)[0] = int4(m00, m01, m02, m03);
        (*this)[1] = int4(m10, m11, m12, m13);
        (*this)[2] = int4(m20, m21, m22, m23);
        (*this)[3] = int4(m30, m31, m32, m33);
    }

    inline int4x4(int s)
    {
        (*this)[0] = int4(s, s, s, s);
        (*this)[1] = int4(s, s, s, s);
        (*this)[2] = int4(s, s, s, s);
        (*this)[3] = int4(s, s, s, s);
    }

public: // Constructors
    inline int4& operator[](int index)
    {
        ASSERT(index > -1 && index < 4, "Index out of range");
        return ((int4*)data)[index];
    }

    inline const int4& operator[](int index) const
    {
        ASSERT(index > -1 && index < 4, "Index out of range");
        return ((int4*)data)[index];
    }
    
private: // @region: Internal fields
    struct
    {
        int data[4][4];
    };
};

inline int4x4 operator-(const int4x4& m)
{
    int4x4 result;
    result[0] = -m[0];
    result[1] = -m[1];
    result[2] = -m[2];
    result[3] = -m[3];
    return result;
}

inline const int4x4& operator+(const int4x4& m)
{
    return m;
}

inline int4x4& operator--(int4x4& m)
{
    --m[0];
    --m[1];
    --m[2];
    --m[3];
    return m;
}

inline int4x4& operator++(int4x4& m)
{
    ++m[0];
    ++m[1];
    ++m[2];
    ++m[3];
    return m;
}

inline const int4x4& operator--(int4x4& m, int)
{
    m[0]--;
    m[1]--;
    m[2]--;
    m[3]--;
    return m;
}

inline const int4x4& operator++(int4x4& m, int)
{
    m[0]++;
    m[1]++;
    m[2]++;
    m[3]++;
    return m;
}

inline int4x4 operator+(const int4x4& a, const int4x4& b)
{
    int4x4 result;
    result[0] = a[0] + b[0];
    result[1] = a[1] + b[1];
    result[2] = a[2] + b[2];
    result[3] = a[3] + b[3];
    return result;
}

inline int4x4 operator+(const int4x4& a, int b)
{
    int4x4 result;
    result[0] = a[0] + b;
    result[1] = a[1] + b;
    result[2] = a[2] + b;
    result[3] = a[3] + b;
    return result;
}

inline int4x4 operator+(int a, const int4x4& b)
{
    int4x4 result;
    result[0] = a + b[0];
    result[1] = a + b[1];
    result[2] = a + b[2];
    result[3] = a + b[3];
    return result;
}

inline int4x4 operator-(const int4x4& a, const int4x4& b)
{
    int4x4 result;
    result[0] = a[0] - b[0];
    result[1] = a[1] - b[1];
    result[2] = a[2] - b[2];
    result[3] = a[3] - b[3];
    return result;
}

inline int4x4 operator-(const int4x4& a, int b)
{
    int4x4 result;
    result[0] = a[0] - b;
    result[1] = a[1] - b;
    result[2] = a[2] - b;
    result[3] = a[3] - b;
    return result;
}

inline int4x4 operator-(int a, const int4x4& b)
{
    int4x4 result;
    result[0] = a - b[0];
    result[1] = a - b[1];
    result[2] = a - b[2];
    result[3] = a - b[3];
    return result;
}

inline int4x4 operator*(const int4x4& a, const int4x4& b)
{
    int4x4 result;
    result[0] = a[0] * b[0];
    result[1] = a[1] * b[1];
    result[2] = a[2] * b[2];
    result[3] = a[3] * b[3];
    return result;
}

inline int4x4 operator*(const int4x4& a, int b)
{
    int4x4 result;
    result[0] = a[0] * b;
    result[1] = a[1] * b;
    result[2] = a[2] * b;
    result[3] = a[3] * b;
    return result;
}

inline int4x4 operator*(int a, const int4x4& b)
{
    int4x4 result;
    result[0] = a * b[0];
    result[1] = a * b[1];
    result[2] = a * b[2];
    result[3] = a * b[3];
    return result;
}

inline int4x4 operator/(const int4x4& a, const int4x4& b)
{
    int4x4 result;
    result[0] = a[0] / b[0];
    result[1] = a[1] / b[1];
    result[2] = a[2] / b[2];
    result[3] = a[3] / b[3];
    return result;
}

inline int4x4 operator/(const int4x4& a, int b)
{
    int4x4 result;
    result[0] = a[0] / b;
    result[1] = a[1] / b;
    result[2] = a[2] / b;
    result[3] = a[3] / b;
    return result;
}

inline int4x4 operator/(int a, const int4x4& b)
{
    int4x4 result;
    result[0] = a / b[0];
    result[1] = a / b[1];
    result[2] = a / b[2];
    result[3] = a / b[3];
    return result;
}

inline int4x4& operator+=(int4x4& a, const int4x4& b)
{
    return (a = a + b);
}

inline int4x4& operator+=(int4x4& a, int b)
{
    return (a = a + b);
}

inline int4x4& operator-=(int4x4& a, const int4x4& b)
{
    return (a = a - b);
}

inline int4x4& operator-=(int4x4& a, int b)
{
    return (a = a - b);
}

inline int4x4& operator*=(int4x4& a, const int4x4& b)
{
    return (a = a * b);
}

inline int4x4& operator*=(int4x4& a, int b)
{
    return (a = a * b);
}

inline int4x4& operator/=(int4x4& a, const int4x4& b)
{
    return (a = a / b);
}

inline int4x4& operator/=(int4x4& a, int b)
{
    return (a = a + b);
}

inline bool4x4 operator==(const int4x4& a, const int4x4& b)
{
    bool4x4 result;
    result[0] = a[0] == b[0];
    result[1] = a[1] == b[1];
    result[2] = a[2] == b[2];
    result[3] = a[3] == b[3];
    return result;
}

inline bool4x4 operator!=(const int4x4& a, const int4x4& b)
{
    bool4x4 result;
    result[0] = a[0] != b[0];
    result[1] = a[1] != b[1];
    result[2] = a[2] != b[2];
    result[3] = a[3] != b[3];
    return result;
}

inline bool4x4 operator<(const int4x4& a, const int4x4& b)
{
    bool4x4 result;
    result[0] = a[0] < b[0];
    result[1] = a[1] < b[1];
    result[2] = a[2] < b[2];
    result[3] = a[3] < b[3];
    return result;
}

inline bool4x4 operator>(const int4x4& a, const int4x4& b)
{
    bool4x4 result;
    result[0] = a[0] > b[0];
    result[1] = a[1] > b[1];
    result[2] = a[2] > b[2];
    result[3] = a[3] > b[3];
    return result;
}

inline bool4x4 operator<=(const int4x4& a, const int4x4& b)
{
    bool4x4 result;
    result[0] = a[0] <= b[0];
    result[1] = a[1] <= b[1];
    result[2] = a[2] <= b[2];
    result[3] = a[3] <= b[3];
    return result;
}

inline bool4x4 operator>=(const int4x4& a, const int4x4& b)
{
    bool4x4 result;
    result[0] = a[0] >= b[0];
    result[1] = a[1] >= b[1];
    result[2] = a[2] >= b[2];
    result[3] = a[3] >= b[3];
    return result;
}

namespace math
{
    inline bool all(const int4x4& v)
    {
        return
		    v[0][0] != 0 && v[0][1] != 0 && v[0][2] != 0 && v[0][3] != 0 &&
		    v[1][0] != 0 && v[1][1] != 0 && v[1][2] != 0 && v[1][3] != 0 &&
		    v[2][0] != 0 && v[2][1] != 0 && v[2][2] != 0 && v[2][3] != 0 &&
            v[3][0] != 0 && v[3][1] != 0 && v[3][2] != 0 && v[3][3] != 0;
    }

    inline bool any(const int4x4& v)
    {
        return 
            v[0][0] != 0 || v[0][1] != 0 || v[0][2] != 0 || v[0][3] != 0 ||
            v[1][0] != 0 || v[1][1] != 0 || v[1][2] != 0 || v[1][3] != 0 ||
            v[2][0] != 0 || v[2][1] != 0 || v[2][2] != 0 || v[2][3] != 0 ||
            v[3][0] != 0 || v[3][1] != 0 || v[3][2] != 0 || v[3][3] != 0;
    }
}

