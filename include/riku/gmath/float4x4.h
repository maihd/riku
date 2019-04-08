// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#pragma once

#include "./base.h"
#include "./quat.h"
#include "./float4.h"
#include "./bool4x4.h"

union float4x4
{
public: // @region: Constructors
    inline float4x4(void)
    {
        (*this)[0] = float4(1, 0, 0, 0);
        (*this)[1] = float4(0, 1, 0, 0);
        (*this)[2] = float4(0, 0, 1, 0);
        (*this)[3] = float4(0, 0, 0, 1);
    }

	inline float4x4(const float4& m0, const float4& m1, const float4& m2, const float4& m3)
	{
		(*this)[0] = m0;
		(*this)[1] = m1;
		(*this)[2] = m2;
		(*this)[3] = m3;
	}
    
    inline float4x4(float m00, float m01, float m02, float m03,
                    float m10, float m11, float m12, float m13,
                    float m20, float m21, float m22, float m23,
                    float m30, float m31, float m32, float m33)
    {
        (*this)[0] = float4(m00, m01, m02, m03);
        (*this)[1] = float4(m10, m11, m12, m13);
        (*this)[2] = float4(m20, m21, m22, m23);
        (*this)[3] = float4(m30, m31, m32, m33);
    }

    inline float4x4(float s)
    {
        (*this)[0] = float4(s, s, s, s);
        (*this)[1] = float4(s, s, s, s);
        (*this)[2] = float4(s, s, s, s);
        (*this)[3] = float4(s, s, s, s);
    }
    
public: // @region: Operators
    inline float4& operator[](int index)
    {
        ASSERT(index > -1 && index < 4, "Index out of range");
        return ((float4*)data)[index];
    }

    inline const float4& operator[](int index) const
    {
        ASSERT(index > -1 && index < 4, "Index out of range");
        return ((float4*)data)[index];
    }

public: // @region: Constants
    inline static float4x4 identity()
    {
        return float4x4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
    }

public: // @region: Graphics functions
    static float4x4 scalation(float s);
    static float4x4 scalation(const float2& v);
    static float4x4 scalation(const float3& v);
    static float4x4 scalation(float x, float y, float z = 1.0f);

    static float4x4 translation(const float2& v);
    static float4x4 translation(const float3& v);
    static float4x4 translation(float x, float y, float z = 0.0f);

    static float4x4 rotation(const quat& quaternion);
    static float4x4 rotation(const float3& axis, float angle);
    static float4x4 rotation(float x, float y, float z, float angle);

    static float4x4 rotation_x(float angle);
    static float4x4 rotation_y(float angle);
    static float4x4 rotation_z(float angle);

    static float4x4 lookat(const float3& eye, const float3& target, const float3& up);

    static float4x4 ortho(float l, float r, float b, float t, float n, float f);
    static float4x4 frustum(float l, float r, float b, float t, float n, float f);
    static float4x4 perspective(float fov, float aspect, float znear, float zfar);

    RIKU_API static void decompose(const float4x4& m, float3* scalation, quat* quaternion, float3* translation);
    RIKU_API static void decompose(const float4x4& m, float3* scalation, float3* axis, float* angle, float3* translation);
    
private: // @region: Internal fields
    struct
    {
        float data[4][4];
    };
};

inline bool4x4 operator==(const float4x4& a, const float4x4& b)
{
    bool4x4 result;
    result[0] = a[0] == b[0];
    result[1] = a[1] == b[1];
    result[2] = a[2] == b[2];
    result[3] = a[3] == b[3];
    return result;
}

inline bool4x4 operator!=(const float4x4& a, const float4x4& b)
{
    bool4x4 result;
    result[0] = a[0] != b[0];
    result[1] = a[1] != b[1];
    result[2] = a[2] != b[2];
    result[3] = a[3] != b[3];
    return result;
}

inline bool4x4 operator<(const float4x4& a, const float4x4& b)
{
    bool4x4 result;
    result[0] = a[0] < b[0];
    result[1] = a[1] < b[1];
    result[2] = a[2] < b[2];
    result[3] = a[3] < b[3];
    return result;
}

inline bool4x4 operator>(const float4x4& a, const float4x4& b)
{
    bool4x4 result;
    result[0] = a[0] > b[0];
    result[1] = a[1] > b[1];
    result[2] = a[2] > b[2];
    result[3] = a[3] > b[3];
    return result;
}

inline bool4x4 operator<=(const float4x4& a, const float4x4& b)
{
    bool4x4 result;
    result[0] = a[0] <= b[0];
    result[1] = a[1] <= b[1];
    result[2] = a[2] <= b[2];
    result[3] = a[3] <= b[3];
    return result;
}

inline bool4x4 operator>=(const float4x4& a, const float4x4& b)
{
    bool4x4 result;
    result[0] = a[0] >= b[0];
    result[1] = a[1] >= b[1];
    result[2] = a[2] >= b[2];
    result[3] = a[3] >= b[3];
    return result;
}

inline float4x4 operator-(const float4x4& m)
{
    float4x4 result;
    result[0] = -m[0];
    result[1] = -m[1];
    result[2] = -m[2];
    result[3] = -m[3];
    return result;
}

inline const float4x4& operator+(const float4x4& m)
{
    return m;
}

inline float4x4& operator--(float4x4& m)
{
    --m[0];
    --m[1];
    --m[2];
    --m[3];
    return m;
}

inline float4x4& operator++(float4x4& m)
{
    ++m[0];
    ++m[1];
    ++m[2];
    ++m[3];
    return m;
}

inline const float4x4& operator--(float4x4& m, int)
{
    m[0]--;
    m[1]--;
    m[2]--;
    m[3]--;
    return m;
}

inline const float4x4& operator++(float4x4& m, int)
{
    m[0]++;
    m[1]++;
    m[2]++;
    m[3]++;
    return m;
}

inline float4x4 operator+(const float4x4& a, const float4x4& b)
{
    float4x4 result;
    result[0] = a[0] + b[0];
    result[1] = a[1] + b[1];
    result[2] = a[2] + b[2];
    result[3] = a[3] + b[3];
    return result;
}

inline float4x4 operator+(const float4x4& a, float b)
{
    float4x4 result;
    result[0] = a[0] + b;
    result[1] = a[1] + b;
    result[2] = a[2] + b;
    result[3] = a[3] + b;
    return result;
}

inline float4x4 operator+(float a, const float4x4& b)
{
    float4x4 result;
    result[0] = a + b[0];
    result[1] = a + b[1];
    result[2] = a + b[2];
    result[3] = a + b[3];
    return result;
}

inline float4x4 operator-(const float4x4& a, const float4x4& b)
{
    float4x4 result;
    result[0] = a[0] - b[0];
    result[1] = a[1] - b[1];
    result[2] = a[2] - b[2];
    result[3] = a[3] - b[3];
    return result;
}

inline float4x4 operator-(const float4x4& a, float b)
{
    float4x4 result;
    result[0] = a[0] - b;
    result[1] = a[1] - b;
    result[2] = a[2] - b;
    result[3] = a[3] - b;
    return result;
}

inline float4x4 operator-(float a, const float4x4& b)
{
    float4x4 result;
    result[0] = a - b[0];
    result[1] = a - b[1];
    result[2] = a - b[2];
    result[3] = a - b[3];
    return result;
}

inline float4x4 operator*(const float4x4& a, const float4x4& b)
{
    float4x4 result;
    result[0] = a[0] * b[0];
    result[1] = a[1] * b[1];
    result[2] = a[2] * b[2];
    result[3] = a[3] * b[3];
    return result;
}

inline float4x4 operator*(const float4x4& a, float b)
{
    float4x4 result;
    result[0] = a[0] * b;
    result[1] = a[1] * b;
    result[2] = a[2] * b;
    result[3] = a[3] * b;
    return result;
}

inline float4x4 operator*(float a, const float4x4& b)
{
    float4x4 result;
    result[0] = a * b[0];
    result[1] = a * b[1];
    result[2] = a * b[2];
    result[3] = a * b[3];
    return result;
}

inline float4x4 operator/(const float4x4& a, const float4x4& b)
{
    float4x4 result;
    result[0] = a[0] / b[0];
    result[1] = a[1] / b[1];
    result[2] = a[2] / b[2];
    result[3] = a[3] / b[3];
    return result;
}

inline float4x4 operator/(const float4x4& a, float b)
{
    float4x4 result;
    result[0] = a[0] / b;
    result[1] = a[1] / b;
    result[2] = a[2] / b;
    result[3] = a[3] / b;
    return result;
}

inline float4x4 operator/(float a, const float4x4& b)
{
    float4x4 result;
    result[0] = a / b[0];
    result[1] = a / b[1];
    result[2] = a / b[2];
    result[3] = a / b[3];
    return result;
}

inline float4x4& operator+=(float4x4& a, const float4x4& b)
{
    return (a = a + b);
}

inline float4x4& operator+=(float4x4& a, float b)
{
    return (a = a + b);
}

inline float4x4& operator-=(float4x4& a, const float4x4& b)
{
    return (a = a - b);
}

inline float4x4& operator-=(float4x4& a, float b)
{
    return (a = a - b);
}

inline float4x4& operator*=(float4x4& a, const float4x4& b)
{
    return (a = a * b);
}

inline float4x4& operator*=(float4x4& a, float b)
{
    return (a = a * b);
}

inline float4x4& operator/=(float4x4& a, const float4x4& b)
{
    return (a = a / b);
}

inline float4x4& operator/=(float4x4& a, float b)
{
    return (a = a + b);
}

namespace math
{
    inline bool all(const float4x4& v)
    {
        return
            v[0][0] != 0.0f && v[0][1] != 0.0f && v[0][2] != 0.0f && v[0][3] != 0.0f &&
            v[1][0] != 0.0f && v[1][1] != 0.0f && v[1][2] != 0.0f && v[1][3] != 0.0f &&
            v[2][0] != 0.0f && v[2][1] != 0.0f && v[2][2] != 0.0f && v[2][3] != 0.0f &&
            v[3][0] != 0.0f && v[3][1] != 0.0f && v[3][2] != 0.0f && v[3][3] != 0.0f;
    }

    inline bool any(const float4x4& v)
    {
        return 
            v[0][0] != 0.0f || v[0][1] != 0.0f || v[0][2] != 0.0f || v[0][3] != 0.0f ||
            v[1][0] != 0.0f || v[1][1] != 0.0f || v[1][2] != 0.0f || v[1][3] != 0.0f ||
            v[2][0] != 0.0f || v[2][1] != 0.0f || v[2][2] != 0.0f || v[2][3] != 0.0f ||
            v[3][0] != 0.0f || v[3][1] != 0.0f || v[3][2] != 0.0f || v[3][3] != 0.0f;
    }
}