// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#pragma once

#include "./base.h"
#include "./float3.h"
#include "./bool3x3.h"

union float3x3
{
public: // @region: Constructors
    inline float3x3(void)
    {
        (*this)[0] = float3(1, 0, 0);
        (*this)[1] = float3(0, 1, 0);
        (*this)[2] = float3(0, 0, 1);
    }

	inline float3x3(const float3& m0, const float3& m1, const float3& m2)
	{
		(*this)[0] = m0;
		(*this)[1] = m1;
		(*this)[2] = m2;
	}

    inline float3x3(float m00, float m01, float m02,
                    float m10, float m11, float m12,
                    float m20, float m21, float m22)
    {
        (*this)[0] = float3(m00, m01, m02);
        (*this)[1] = float3(m10, m11, m12);
        (*this)[2] = float3(m20, m21, m22);
    }

    inline float3x3(float s)
    {
        (*this)[0] = float3(s, s, s);
        (*this)[1] = float3(s, s, s);
        (*this)[2] = float3(s, s, s);
    }
    
public: // @region: Operators
    inline float3& operator[](int index)
    {
        ASSERT(index > -1 && index < 3, "float3x3[]: Index out of range");
        return ((float3*)data)[index];
    }

    inline const float3& operator[](int index) const
    {
        ASSERT(index > -1 && index < 3, "float3x3[]: Index out of range");
        return ((float3*)data)[index];
    }

public: // @region: Create functions
    inline static float3x3 identity()
    {
        return float3x3(1, 0, 0, 0, 1, 0, 0, 0, 1);
    }

public: // @region: Graphics functions
    inline static float3x3 translate(const float2& v);
    inline static float3x3 translate(float x, float y);

    inline static float3x3 rotate(float angle);

    inline static float3x3 scale(const float2& v);
    inline static float3x3 scale(float x, float y);

    inline static float3x3 ortho(float l, float r, float b, float t);
    
private: // @region: Internal fields
    struct
    {
        float data[3][3];
    };
};

//
// @region: Operators overloading
//

inline float3x3 operator-(const float3x3& m)
{
    float3x3 result;
    result[0] = -m[0];
    result[1] = -m[1];
    result[2] = -m[2];
    return result;
}

inline const float3x3& operator+(const float3x3& m)
{
    return m;
}

inline float3x3& operator--(float3x3& m)
{
    --m[0];
    --m[1];
    --m[2];
    return m;
}

inline float3x3& operator++(float3x3& m)
{
    ++m[0];
    ++m[1];
    ++m[2];
    return m;
}

inline const float3x3& operator--(float3x3& m, int)
{
    m[0]--;
    m[1]--;
    m[2]--;
    return m;
}

inline const float3x3& operator++(float3x3& m, int)
{
    m[0]++;
    m[1]++;
    m[2]++;
    return m;
}

inline float3x3 operator+(const float3x3& a, const float3x3& b)
{
    float3x3 result;
    result[0] = a[0] + b[0];
    result[1] = a[1] + b[1];
    result[2] = a[2] + b[2];
    return result;
}

inline float3x3 operator-(const float3x3& a, const float3x3& b)
{
    float3x3 result;
    result[0] = a[0] - b[0];
    result[1] = a[1] - b[1];
    result[2] = a[2] - b[2];
    return result;
}

inline float3x3 operator*(const float3x3& a, const float3x3& b)
{
    float3x3 result;
    result[0] = a[0] * b[0];
    result[1] = a[1] * b[1];
    result[2] = a[2] * b[2];
    return result;
}

inline float3x3 operator/(const float3x3& a, const float3x3& b)
{
    float3x3 result;
    result[0] = a[0] / b[0];
    result[1] = a[1] / b[1];
    result[2] = a[2] / b[2];
    return result;
}

inline float3x3 operator+(const float3x3& a, float b)
{
    float3x3 result;
    result[0] = a[0] + b;
    result[1] = a[1] + b;
    result[2] = a[2] + b;
    return result;
}

inline float3x3 operator-(const float3x3& a, float b)
{
    float3x3 result;
    result[0] = a[0] - b;
    result[1] = a[1] - b;
    result[2] = a[2] - b;
    return result;
}

inline float3x3 operator*(const float3x3& a, float b)
{
    float3x3 result;
    result[0] = a[0] * b;
    result[1] = a[1] * b;
    result[2] = a[2] * b;
    return result;
}

inline float3x3 operator/(const float3x3& a, float b)
{
    float3x3 result;
    result[0] = a[0] / b;
    result[1] = a[1] / b;
    result[2] = a[2] / b;
    return result;
}

inline float3x3 operator+(float a, const float3x3& b)
{
    float3x3 result;
    result[0] = a + b[0];
    result[1] = a + b[1];
    result[2] = a + b[2];
    return result;
}

inline float3x3 operator-(float a, const float3x3& b)
{
    float3x3 result;
    result[0] = a - b[0];
    result[1] = a - b[1];
    result[2] = a - b[2];
    return result;
}

inline float3x3 operator*(float a, const float3x3& b)
{
    float3x3 result;
    result[0] = a * b[0];
    result[1] = a * b[1];
    result[2] = a * b[2];
    return result;
}

inline float3x3 operator/(float a, const float3x3& b)
{
    float3x3 result;
    result[0] = a / b[0];
    result[1] = a / b[1];
    result[2] = a / b[2];
    return result;
}

inline float3x3& operator+=(float3x3& a, const float3x3& b)
{
    return (a = a + b);
}

inline float3x3& operator+=(float3x3& a, float b)
{
    return (a = a + b);
}

inline float3x3& operator-=(float3x3& a, const float3x3& b)
{
    return (a = a - b);
}

inline float3x3& operator-=(float3x3& a, float b)
{
    return (a = a - b);
}

inline float3x3& operator*=(float3x3& a, const float3x3& b)
{
    return (a = a * b);
}

inline float3x3& operator*=(float3x3& a, float b)
{
    return (a = a * b);
}

inline float3x3& operator/=(float3x3& a, const float3x3& b)
{
    return (a = a / b);
}

inline float3x3& operator/=(float3x3& a, float b)
{
    return (a = a + b);
}

inline bool3x3 operator==(const float3x3& a, const float3x3& b)
{
    bool3x3 result;
    result[0] = a[0] == b[0];
    result[1] = a[1] == b[1];
    result[2] = a[2] == b[2];
    return result;
}

inline bool3x3 operator!=(const float3x3& a, const float3x3& b)
{
    bool3x3 result;
    result[0] = a[0] != b[0];
    result[1] = a[1] != b[1];
    result[2] = a[2] != b[2];
    return result;
}

inline bool3x3 operator<(const float3x3& a, const float3x3& b)
{
    bool3x3 result;
    result[0] = a[0] < b[0];
    result[1] = a[1] < b[1];
    result[2] = a[2] < b[2];
    return result;
}

inline bool3x3 operator>(const float3x3& a, const float3x3& b)
{
    bool3x3 result;
    result[0] = a[0] > b[0];
    result[1] = a[1] > b[1];
    result[2] = a[2] > b[2];
    return result;
}

inline bool3x3 operator<=(const float3x3& a, const float3x3& b)
{
    bool3x3 result;
    result[0] = a[0] <= b[0];
    result[1] = a[1] <= b[1];
    result[2] = a[2] <= b[2];
    return result;
}

inline bool3x3 operator>=(const float3x3& a, const float3x3& b)
{
    bool3x3 result;
    result[0] = a[0] >= b[0];
    result[1] = a[1] >= b[1];
    result[2] = a[2] >= b[2];
    return result;
}

namespace math
{
    inline bool all(const float3x3& v)
    {
        return
            v[0][0] != 0.0f && v[0][1] != 0.0f && v[0][2] != 0.0f &&
            v[1][0] != 0.0f && v[1][1] != 0.0f && v[1][2] != 0.0f &&
            v[2][0] != 0.0f && v[2][1] != 0.0f && v[2][2] != 0.0f;
    }

    inline bool any(const float3x3& v)
    {
        return
            v[0][0] != 0.0f || v[0][1] != 0.0f || v[0][2] != 0.0f ||
            v[1][0] != 0.0f || v[1][1] != 0.0f || v[1][2] != 0.0f ||
            v[2][0] != 0.0f || v[2][1] != 0.0f || v[2][2] != 0.0f;
    }
}