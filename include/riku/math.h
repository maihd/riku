// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#pragma once

#include "./core.h"

namespace math
{
    constexpr float pi        = 3.14159265358979f;
    constexpr float epsilon   = 0.00001f;
    constexpr float tolerance = 2e-0037f;

    /* Computes cosine
     */
    RIKU_API float cos(float x);

    /* Computes sine
     */
    RIKU_API float sin(float x);

    /* Computes tangent
     */
    RIKU_API float tan(float x);

    /* Computes hyperbolic cosine
     */
    RIKU_API float cosh(float x);

    /* Computes hyperbolic sine
     */
    RIKU_API float sinh(float x);

    /* Computes hyperbolic tangent
     */
    RIKU_API float tanh(float x);

    /* Computes inverse cosine
     */
    RIKU_API float acos(float x);

    /* Computes inverse sine
     */
    RIKU_API float asin(float x);

    /* Computes inverse tangent
     */
    RIKU_API float atan(float x);

    /* Computes inverse tangent with 2 args
     */
    RIKU_API float atan2(float y, float x);

    /* Computes Euler number raised to the power 'x'
     */
    RIKU_API float exp(float x);

    /* Computes 2 raised to the power 'x'
     */
    RIKU_API float exp2(float x);

    /* Computes the base Euler number logarithm
     */
    RIKU_API float log(float x);

    /* Computes the base 2 logarithm
     */
    RIKU_API float log2(float x);

    /* Computes the base 10 logarithm
     */
    RIKU_API float log10(float x);

    /* Computes the value of base raised to the power exponent
     */
    RIKU_API float pow(float x, float y);

    /* Computes the floating-point remainder of the division operation x/y
     */
    RIKU_API float fmod(float x, float y);

    /* Computes the smallest integer value not less than 'x'
     */
    RIKU_API float ceil(float x);

    /* Computes the largest integer value not greater than 'x'
     */
    RIKU_API float floor(float x);

    /* Computes the nearest integer value
     */
    RIKU_API float round(float x);

    /* Computes the nearest integer not greater in magnitude than 'x'
     */
    RIKU_API float trunc(float x);

    /* Get the fractal part of floating point
    */
    RIKU_API float frac(float x);

    /* Computes square root of 'x'.
     */
    RIKU_API float sqrt(float x);

    inline bool all(bool v)
    {
        return v;
    }

    inline bool any(bool v)
    {
        return v;
    }

    inline bool all(int v)
    {
        return v != 0;
    }

    inline bool any(int v)
    {
        return v != 0;
    }

    inline bool all(uint v)
    {
	    return v != 0;
    }

    inline bool any(uint v)
    {
	    return v != 0;
    }

    inline bool all(float v)
    {
	    return v != 0.0f;
    }

    inline bool any(float v)
    {
	    return v != 0.0f;
    }

    /* Convert radians to degrees
     */
    inline float degrees(float x)
    {
        const float factor = 180.0f / pi;
        return x * factor;
    }

    /* Convert degrees to radians
     */
    inline float radians(float x)
    {
        const float factor = pi / 180.0f;
        return x * factor;
    }

    inline int asint(float x)
    {
        union
        {
            int   ival;
            float fval;
        } cvt;
        cvt.fval = x;
        return cvt.ival;
    }

    inline int asint(uint x)
    {
        union
        {
            int  ival;
            uint uval;
        } cvt;
        cvt.uval = x;
        return cvt.ival;
    }

    inline uint asuint(int x)
    {
        union
        {
            int  ival;
            uint uval;
        } cvt;
        cvt.ival = x;
        return cvt.uval;
    }

    inline uint asuint(float x)
    {
        union
        {
            uint  uval;
            float fval;
        } cvt;
        cvt.fval = x;
        return cvt.uval;
    }

    inline float asfloat(int x)
    {
        union
        {
            int   ival;
            float fval;
        } cvt;
        cvt.ival = x;
        return cvt.fval;
    }

    inline float asfloat(uint x)
    {
        union
        {
            uint  uval;
            float fval;
        } cvt;
        cvt.uval = x;
        return cvt.fval;
    }

    inline float asfloat(float x)
    {
        return x;
    }

    inline int abs(int x)
    {
        return x > 0 ? x : -x;
    }

    /* Compute the sign of 'x'
     */
    inline int sign(int x)
    {
        return x >> 31;
    }

    /* Get the smaller value
     */
    inline int min(int x, int y)
    {
        return x < y ? x : y;
    }

    /* Get the larger value
     */
    inline int max(int x, int y)
    {
        return x > y ? x : y;
    }

    /* Clamps the 'x' to the [min, max]
     */
    inline int clamp(int x, int min, int max)
    {
        return x < min ? min : (x > max ? max : x);
    }

    /* Get the smaller value
     */
    inline uint min(uint x, uint y)
    {
        return x < y ? x : y;
    }

    /* Get the larger value
     */
    inline uint max(uint x, uint y)
    {
        return x > y ? x : y;
    }

    /* Clamps the 'x' to the [min, max]
     */
    inline uint clamp(uint x, uint min, uint max)
    {
        return x < min ? min : (x > max ? max : x);
    }

    /* Computes sign of 'x'
     */
    inline int sign(float x)
    {
        union
        {
            float f;
            int   i;
        } cvt;
        cvt.f = x;
        return sign(cvt.i);
    }

    /* Computes absolute value
     */
    inline float abs(float x)
    {
        return (x > 0.0f ? x : -x);
    }

    /* Get the smaller value
     */ 
    inline float min(float x, float y)
    {
        return x < y ? x : y;
    }

    /* Get the larger value
     */ 
    inline float max(float x, float y)
    {
        return x > y ? x : y;
    }

    /* Clamps the 'x' value to the [min, max].
     */
    inline float clamp(float x, float min, float max)
    {
        return x < min ? min : (x > max ? max : x);
    }

    /* Clamps the specified value within the range of 0 to 1
     */
    inline float saturate(float x)
    {
        return clamp(x, 0.0f, 1.0f);
    }

    /* Compares two values, returning 0 or 1 based on which value is greater.
     */
    inline float step(float y, float x)
    {
        return x >= y;
    }

    /* Performs a linear interpolation.
     */
    inline float lerp(float x, float y, float s)
    {
        return x + (y - x) * s;
    }

    /* Compute a smooth Hermite interpolation
     * @return: 0 if x <= min
     *          1 if x >= max
     *          (0, 1) otherwise
     */
    inline float smoothstep(float min, float max, float x)
    {
        return (clamp(x, min, max) - min) / (max - min);
    }

    /* Computes inverse square root of 'x'.
     */
    inline float rsqrt(float x)
    {
        return 1.0f / sqrt(x);
    }

    /* Computes fast inverse square root of 'x'.
     */
    inline float frsqrt(float x)
    {
        union
        {
            float f;
            int   i;
        } cvt;

        cvt.f = x;
        cvt.i = 0x5F3759DF - (cvt.i >> 1);
        cvt.f = cvt.f * (1.5f - (0.5f * x * cvt.f * cvt.f));
        return cvt.f;
    }

    /* Computes fast inverse square root of 'x'.
     */
    inline float fsqrt(float x)
    {
        return x == 0.0f ? 0.0f : 1.0f / frsqrt(x);
    }
}