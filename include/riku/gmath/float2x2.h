// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#pragma once

#include "./base.h"
#include "./float2.h"
#include "./bool2x2.h"

union float2x2
{
public: // @region: Constructors
    inline float2x2(void)
    {
        (*this)[0] = float2(1, 0);
        (*this)[1] = float2(0, 1);
    }

	inline float2x2(const float2& m0, const float2& m1)
	{
		(*this)[0] = m0;
		(*this)[1] = m1;
	}

    inline float2x2(float m00, float m01, 
                    float m10, float m11)
    {
        (*this)[0] = float2(m00, m01);
        (*this)[1] = float2(m10, m11);
    }

    inline float2x2(float s)    
    {
        (*this)[0] = float2(s, s);
        (*this)[1] = float2(s, s);
    }

public: // @region: Operators
    inline float2& operator[](int index)
    {
        ASSERT(index > -1 && index < 2, "Index out of range");
        return ((float2*)data)[index];
    }

    inline const float2& operator[](int index) const
    {
        ASSERT(index > -1 && index < 2, "Index out of range");
        return ((float2*)data)[index];
    }
   
public: // @region: Create functions
    inline static float2x2 identity()
    {
        return float2x2(1, 0, 0, 1);
    }

public: // @region: Graphics functions
    inline static float2x2 rotate(float angle);

    inline static float2x2 scale(float x);
    inline static float2x2 scale(const float2& v);
    inline static float2x2 scale(float x, float y);
    
private: // @region: Internal fields
    struct
    {
        float data[2][2];
    };
};

//
// @region: Operators overloading
//

inline float2x2 operator-(const float2x2& m)
{
    float2x2 result;
    result[0] = -m[0];
    result[1] = -m[1];
    return result;
}

inline const float2x2& operator+(const float2x2& m)
{
    return m;
}

inline float2x2& operator--(float2x2& m)
{
    --m[0];
    --m[1];
    return m;
}

inline float2x2& operator++(float2x2& m)
{
    ++m[0];
    ++m[1];
    return m;
}

inline const float2x2& operator--(float2x2& m, int)
{
    m[0]--;
    m[1]--;
    return m;
}

inline const float2x2& operator++(float2x2& m, int)
{
    m[0]++;
    m[1]++;
    return m;
}

inline float2x2 operator+(const float2x2& a, const float2x2& b)
{
    float2x2 result;
    result[0] = a[0] + b[0];
    result[1] = a[1] + b[1];
    return result;
}

inline float2x2 operator-(const float2x2& a, const float2x2& b)
{
    float2x2 result;
    result[0] = a[0] - b[0];
    result[1] = a[1] - b[1];
    return result;
}

inline float2x2 operator*(const float2x2& a, const float2x2& b)
{
    float2x2 result;
    result[0] = a[0] * b[0];
    result[1] = a[1] * b[1];
    return result;
}

inline float2x2 operator/(const float2x2& a, const float2x2& b)
{
    float2x2 result;
    result[0] = a[0] / b[0];
    result[1] = a[1] / b[1];
    return result;
}

inline float2x2 operator+(const float2x2& a, float b)
{
    float2x2 result;
    result[0] = a[0] + b;
    result[1] = a[1] + b;
    return result;
}

inline float2x2 operator-(const float2x2& a, float b)
{
    float2x2 result;
    result[0] = a[0] - b;
    result[1] = a[1] - b;
    return result;
}

inline float2x2 operator*(const float2x2& a, float b)
{
    float2x2 result;
    result[0] = a[0] * b;
    result[1] = a[1] * b;
    return result;
}

inline float2x2 operator/(const float2x2& a, float b)
{
    float2x2 result;
    result[0] = a[0] / b;
    result[1] = a[1] / b;
    return result;
}

inline float2x2 operator+(float a, const float2x2& b)
{
    float2x2 result;
    result[0] = a + b[0];
    result[1] = a + b[1];
    return result;
}

inline float2x2 operator-(float a, const float2x2& b)
{
    float2x2 result;
    result[0] = a - b[0];
    result[1] = a - b[1];
    return result;
}

inline float2x2 operator*(float a, const float2x2& b)
{
    float2x2 result;
    result[0] = a * b[0];
    result[1] = a * b[1];
    return result;
}

inline float2x2 operator/(float a, const float2x2& b)
{
    float2x2 result;
    result[0] = a / b[0];
    result[1] = a / b[1];
    return result;
}

inline float2x2& operator+=(float2x2& a, const float2x2& b)
{
    return (a = a + b);
}

inline float2x2& operator+=(float2x2& a, float b)
{
    return (a = a + b);
}

inline float2x2& operator-=(float2x2& a, const float2x2& b)
{
    return (a = a - b);
}

inline float2x2& operator-=(float2x2& a, float b)
{
    return (a = a - b);
}

inline float2x2& operator*=(float2x2& a, const float2x2& b)
{
    return (a = a * b);
}

inline float2x2& operator*=(float2x2& a, float b)
{
    return (a = a * b);
}

inline float2x2& operator/=(float2x2& a, const float2x2& b)
{
    return (a = a / b);
}

inline float2x2& operator/=(float2x2& a, float b)
{
    return (a = a + b);
}

inline bool2x2 operator==(const float2x2& a, const float2x2& b)
{
    bool2x2 result;
    result[0] = a[0] == b[0];
    result[1] = a[1] == b[1];
    return result;
}

inline bool2x2 operator!=(const float2x2& a, const float2x2& b)
{
    bool2x2 result;
    result[0] = a[0] != b[0];
    result[1] = a[1] != b[1];
    return result;
}

inline bool2x2 operator<(const float2x2& a, const float2x2& b)
{
    bool2x2 result;
    result[0] = a[0] < b[0];
    result[1] = a[1] < b[1];
    return result;
}

inline bool2x2 operator>(const float2x2& a, const float2x2& b)
{
    bool2x2 result;
    result[0] = a[0] > b[0];
    result[1] = a[1] > b[1];
    return result;
}

inline bool2x2 operator<=(const float2x2& a, const float2x2& b)
{
    bool2x2 result;
    result[0] = a[0] <= b[0];
    result[1] = a[1] <= b[1];
    return result;
}

inline bool2x2 operator>=(const float2x2& a, const float2x2& b)
{
    bool2x2 result;
    result[0] = a[0] >= b[0];
    result[1] = a[1] >= b[1];
    return result;
}

namespace math
{
    inline bool all(const float2x2& v)
    {
	    return v[0][0] != 0.0f && v[0][1] != 0.0f && v[1][0] != 0.0f && v[1][1] != 0.0f;
    }

    inline bool any(const float2x2& v)
    {
	    return v[0][0] != 0.0f || v[0][1] != 0.0f || v[1][0] != 0.0f || v[1][1] != 0.0f;
    }
}