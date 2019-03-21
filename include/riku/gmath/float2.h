// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#pragma once

#include "./base.h"
#include "./bool2.h"

union float2
{
public: // @region: Fields
    struct
    {
        float x, y;
    };

public: // @region: Constructors
    inline float2() : x(0.0f), y(0.0f) {}

    inline float2(float x, float y)
        : x(x)
        , y(y) {}

    inline float2(float s)
        : x(s)
        , y(s) {}

public: // @region: Operators
    inline float& operator[](int index)
    {
        ASSERT(index > -1 && index < 2, "Index out of range");
        return ((float*)this)[index];
    }

    inline float  operator[](int index) const
    {
        ASSERT(index > -1 && index < 2, "Index out of range");
        return ((float*)this)[index];
    }

#if MATH_ENABLE_NEON       
public:
    inline float2(float32x2_t neon_simd)
        : neon_simd(neon_simd) {}

    inline operator float32x2_t(void) const
    {
        return neon_simd;
    }

private:
    float32x2_t neon_simd;
#endif
};

inline float2 operator-(const float2& v)
{
    return float2(-v.x, -v.y);
}

inline const float2& operator+(const float2& v)
{
    return v;
}

inline float2& operator--(float2& v)
{
    --v.x;
    --v.y;
    return v;
}

inline float2& operator++(float2& v)
{
    ++v.x;
    ++v.y;
    return v;
}

inline float2 operator--(float2& v, int)
{
    const float2 result = v;

    v.x--;
    v.y--;

    return result;
}

inline float2 operator++(float2& v, int)
{
    const float2 result = v;

    v.x++;
    v.y++;

    return result;
}

inline float2 operator+(const float2& a, const float2& b)
{
#if MATH_ENABLE_NEON   
    return float2(vadd_f32(a, b));
#else
    return float2(a.x + b.x, a.y + b.y);
#endif
}

inline float2 operator-(const float2& a, const float2& b)
{
#if MATH_ENABLE_NEON   
    return float2(vsub_f32(a, b));
#else
    return float2(a.x - b.x, a.y - b.y);
#endif
}

inline float2 operator*(const float2& a, const float2& b)
{
#if MATH_ENABLE_NEON   
    return float2(vmul_f32(a, b));
#else
    return float2(a.x * b.x, a.y * b.y);
#endif
}

inline float2 operator/(const float2& a, const float2& b)
{
#if MATH_ENABLE_NEON && 0 // experimental
    float2 res;
    __asm volatile(
    "vcvt.f32.u32  q0, q0     \n\t"
        "vrecpe.f32    q0, q0     \n\t"
        "vmul.f32      q0, q0, q1 \n\t"
        "vcvt.u32.f32  q0, q0     \n\t"
        :
    : "r"(dst), "r"()
        :
        );
#else
    return float2(a.x / b.x, a.y / b.y);
#endif
}

inline float2 operator+(const float2& a, float b)
{
    return a + float2(b);
}

inline float2 operator-(const float2& a, float b)
{
    return a - float2(b);
}

inline float2 operator*(const float2& a, float b)
{
    return a * float2(b);
}

inline float2 operator/(const float2& a, float b)
{
    return a / float2(b);
}

inline float2 operator+(float a, const float2& b)
{
    return float2(a) + b;
}

inline float2 operator-(float a, const float2& b)
{
    return float2(a) - b;
}

inline float2 operator*(float a, const float2& b)
{
    return float2(a) * b;
}

inline float2 operator/(float a, const float2& b)
{
    return float2(a) / b;
}

inline float2& operator+=(float2& a, const float2& b)
{
    return (a = a + b);
}

inline float2& operator+=(float2& a, float b)
{
    return (a = a + b);
}

inline float2& operator-=(float2& a, const float2& b)
{
    return (a = a - b);
}

inline float2& operator-=(float2& a, float b)
{
    return (a = a - b);
}

inline float2& operator*=(float2& a, const float2& b)
{
    return (a = a * b);
}

inline float2& operator*=(float2& a, float b)
{
    return (a = a * b);
}

inline float2& operator/=(float2& a, const float2& b)
{
    return (a = a / b);
}

inline float2& operator/=(float2& a, float b)
{
    return (a = a + b);
}

inline bool2 operator==(const float2& a, const float2& b)
{
    return bool2(a.x == b.x, a.y == b.y);
}

inline bool2 operator!=(const float2& a, const float2& b)
{
    return bool2(a.x != b.x, a.y != b.y);
}

inline bool2 operator<(const float2& a, const float2& b)
{
    return bool2(a.x < b.x, a.y < b.y);
}

inline bool2 operator>(const float2& a, const float2& b)
{
    return bool2(a.x > b.x, a.y > b.y);
}

inline bool2 operator<=(const float2& a, const float2& b)
{
    return bool2(a.x <= b.x, a.y <= b.y);
}

inline bool2 operator>=(const float2& a, const float2& b)
{
    return bool2(a.x >= b.x, a.y >= b.y);
}

namespace math
{
    inline bool all(const float2& v)
    {
	    return v.x != 0.0f && v.y != 0.0f;
    }

    inline bool any(const float2& v)
    {
	    return v.x != 0.0f || v.y != 0.0f;
    }
}