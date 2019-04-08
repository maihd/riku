// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#pragma once

#include "./core.h"
#include "./math.h"

#include "./gmath/int2.h"
#include "./gmath/int3.h"
#include "./gmath/int4.h"
#include "./gmath/uint2.h"
#include "./gmath/uint3.h"
#include "./gmath/uint4.h"
#include "./gmath/bool2.h"
#include "./gmath/bool3.h"
#include "./gmath/bool4.h"
#include "./gmath/float2.h"
#include "./gmath/float3.h"
#include "./gmath/float4.h"

#include "./gmath/int2x2.h"
#include "./gmath/int3x3.h"
#include "./gmath/int4x4.h"
#include "./gmath/uint2x2.h"
#include "./gmath/uint3x3.h"
#include "./gmath/uint4x4.h"
#include "./gmath/bool2x2.h"
#include "./gmath/bool3x3.h"
#include "./gmath/bool4x4.h"
#include "./gmath/float2x2.h"
#include "./gmath/float3x3.h"
#include "./gmath/float4x4.h"

#undef min // When Windows.h is included, min is an macro
#undef max // When Windows.h is included, max is an macro

namespace math
{
    inline int2 asint(const float2& v)
    {
        return int2(asint(v.x), asint(v.y));
    }

    inline int3 asint(const float3& v)
    {
        return int3(asint(v.x), asint(v.y), asint(v.z));
    }

    inline int4 asint(const float4& v)
    {
        return int4(asint(v.x), asint(v.y), asint(v.z), asint(v.w));
    }

    inline int2x2 asint(const float2x2& m)
    {
        return int2x2(
            asint(m[0][0]), asint(m[0][1]),
            asint(m[1][0]), asint(m[1][1]));
    }

    inline int3x3 asint(const float3x3& m)
    {
        return int3x3(
            asint(m[0][0]), asint(m[0][1]), asint(m[0][2]),
            asint(m[1][0]), asint(m[1][1]), asint(m[1][2]),
            asint(m[2][0]), asint(m[2][1]), asint(m[2][2]));
    }

    inline int4x4 asint(const float4x4& m)
    {
        return int4x4(
            asint(m[0][0]), asint(m[0][1]), asint(m[0][2]), asint(m[0][3]),
            asint(m[1][0]), asint(m[1][1]), asint(m[1][2]), asint(m[1][3]),
            asint(m[2][0]), asint(m[2][1]), asint(m[2][2]), asint(m[2][3]),
            asint(m[3][0]), asint(m[3][1]), asint(m[3][2]), asint(m[3][3]));
    }

    inline int2 asint(const uint2& v)
    {
        return int2(asint(v.x), asint(v.y));
    }

    inline int3 asint(const uint3& v)
    {
        return int3(asint(v.x), asint(v.y), asint(v.z));
    }

    inline int4 asint(const uint4& v)
    {
        return int4(asint(v.x), asint(v.y), asint(v.z), asint(v.w));
    }

    inline int2x2 asint(const uint2x2& m)
    {
        return int2x2(
            asint(m[0][0]), asint(m[0][1]),
            asint(m[1][0]), asint(m[1][1]));
    }

    inline int3x3 asint(const uint3x3& m)
    {
        return int3x3(
            asint(m[0][0]), asint(m[0][1]), asint(m[0][2]),
            asint(m[1][0]), asint(m[1][1]), asint(m[1][2]),
            asint(m[2][0]), asint(m[2][1]), asint(m[2][2]));
    }

    inline int4x4 asint(const uint4x4& m)
    {
        return int4x4(
            asint(m[0][0]), asint(m[0][1]), asint(m[0][2]), asint(m[0][3]),
            asint(m[1][0]), asint(m[1][1]), asint(m[1][2]), asint(m[1][3]),
            asint(m[2][0]), asint(m[2][1]), asint(m[2][2]), asint(m[2][3]),
            asint(m[3][0]), asint(m[3][1]), asint(m[3][2]), asint(m[3][3]));
    }

    inline uint2 asuint(const int2& v)
    {
        return uint2(asuint(v.x), asuint(v.y));
    }

    inline uint3 asuint(const int3& v)
    {
        return uint3(asuint(v.x), asuint(v.y), asuint(v.z));
    }

    inline uint4 asuint(const int4& v)
    {
        return uint4(asuint(v.x), asuint(v.y), asuint(v.z), asuint(v.w));
    }

    inline uint2x2 asuint(const int2x2& v)
    {
        return uint2x2(
            asuint(v[0][0]), asuint(v[0][1]),
            asuint(v[1][0]), asuint(v[1][1]));
    }

    inline uint3x3 asuint(const int3x3& v)
    {
        return uint3x3(
            asuint(v[0][0]), asuint(v[0][1]), asuint(v[0][2]),
            asuint(v[1][0]), asuint(v[1][1]), asuint(v[1][2]),
            asuint(v[2][0]), asuint(v[2][1]), asuint(v[2][2]));
    }

    inline uint4x4 asuint(const int4x4& v)
    {
        return uint4x4(
            asuint(v[0][0]), asuint(v[0][1]), asuint(v[0][2]), asuint(v[0][3]),
            asuint(v[1][0]), asuint(v[1][1]), asuint(v[1][2]), asuint(v[1][3]),
            asuint(v[2][0]), asuint(v[2][1]), asuint(v[2][2]), asuint(v[2][3]),
            asuint(v[3][0]), asuint(v[3][1]), asuint(v[3][2]), asuint(v[3][3]));
    }

    inline uint2 asuint(const float2& v)
    {
        return uint2(asuint(v.x), asuint(v.y));
    }

    inline uint3 asuint(const float3& v)
    {
        return uint3(asuint(v.x), asuint(v.y), asuint(v.z));
    }

    inline uint4 asuint(const float4& v)
    {
        return uint4(asuint(v.x), asuint(v.y), asuint(v.z), asuint(v.w));
    }

    inline uint2x2 asuint(const float2x2& v)
    {
        return uint2x2(
            asuint(v[0][0]), asuint(v[0][1]),
            asuint(v[1][0]), asuint(v[1][1]));
    }

    inline uint3x3 asuint(const float3x3& v)
    {
        return uint3x3(
            asuint(v[0][0]), asuint(v[0][1]), asuint(v[0][2]),
            asuint(v[1][0]), asuint(v[1][1]), asuint(v[1][2]),
            asuint(v[2][0]), asuint(v[2][1]), asuint(v[2][2]));
    }

    inline uint4x4 asuint(const float4x4& v)
    {
        return uint4x4(
            asuint(v[0][0]), asuint(v[0][1]), asuint(v[0][2]), asuint(v[0][3]),
            asuint(v[1][0]), asuint(v[1][1]), asuint(v[1][2]), asuint(v[1][3]),
            asuint(v[2][0]), asuint(v[2][1]), asuint(v[2][2]), asuint(v[2][3]),
            asuint(v[3][0]), asuint(v[3][1]), asuint(v[3][2]), asuint(v[3][3]));
    }

    //inline void asuint(double x, uint* lowbits, uint* highbits)
    //{
    //    union
    //    {
    //        double dval;
    //        struct
    //        {
    //            uint lowbits;
    //            uint highbits;
    //        };
    //    } cvt;
    //
    //    cvt.dval = x;
    //    *lowbits = cvt.lowbits;
    //    *highbits = cvt.highbits;
    //}

    inline float2 asfloat(const int2& v)
    {
        return float2(asfloat(v.x), asfloat(v.y));
    }

    inline float3 asfloat(const int3& v)
    {
        return float3(asfloat(v.x), asfloat(v.y), asfloat(v.z));
    }

    inline float4 asfloat(const int4& v)
    {
        return float4(asfloat(v.x), asfloat(v.y), asfloat(v.z), asfloat(v.w));
    }

    inline float2x2 asfloat(const int2x2& m)
    {
        return float2x2(
            asfloat(m[0][0]), asfloat(m[0][1]),
            asfloat(m[1][0]), asfloat(m[1][1]));
    }

    inline float3x3 asfloat(const int3x3& m)
    {
        return float3x3(
            asfloat(m[0][0]), asfloat(m[0][1]), asfloat(m[0][2]),
            asfloat(m[1][0]), asfloat(m[1][1]), asfloat(m[1][2]),
            asfloat(m[2][0]), asfloat(m[2][1]), asfloat(m[2][2]));
    }

    inline float4x4 asfloat(const int4x4& m)
    {
        return float4x4(
            asfloat(m[0][0]), asfloat(m[0][1]), asfloat(m[0][2]), asfloat(m[0][3]),
            asfloat(m[1][0]), asfloat(m[1][1]), asfloat(m[1][2]), asfloat(m[1][3]),
            asfloat(m[2][0]), asfloat(m[2][1]), asfloat(m[2][2]), asfloat(m[2][3]),
            asfloat(m[3][0]), asfloat(m[3][1]), asfloat(m[3][2]), asfloat(m[3][3]));
    }

    inline float2 asfloat(const uint2& v)
    {
        return float2(asfloat(v.x), asfloat(v.y));
    }

    inline float3 asfloat(const uint3& v)
    {
        return float3(asfloat(v.x), asfloat(v.y), asfloat(v.z));
    }

    inline float4 asfloat(const uint4& v)
    {
        return float4(asfloat(v.x), asfloat(v.y), asfloat(v.z), asfloat(v.w));
    }

    inline float2x2 asfloat(const uint2x2& m)
    {
        return float2x2(
            asfloat(m[0][0]), asfloat(m[0][1]),
            asfloat(m[1][0]), asfloat(m[1][1]));
    }

    inline float3x3 asfloat(const uint3x3& m)
    {
        return float3x3(
            asfloat(m[0][0]), asfloat(m[0][1]), asfloat(m[0][2]),
            asfloat(m[1][0]), asfloat(m[1][1]), asfloat(m[1][2]),
            asfloat(m[2][0]), asfloat(m[2][1]), asfloat(m[2][2]));
    }

    inline float4x4 asfloat(const uint4x4& m)
    {
        return float4x4(
            asfloat(m[0][0]), asfloat(m[0][1]), asfloat(m[0][2]), asfloat(m[0][3]),
            asfloat(m[1][0]), asfloat(m[1][1]), asfloat(m[1][2]), asfloat(m[1][3]),
            asfloat(m[2][0]), asfloat(m[2][1]), asfloat(m[2][2]), asfloat(m[2][3]),
            asfloat(m[3][0]), asfloat(m[3][1]), asfloat(m[3][2]), asfloat(m[3][3]));
    }

    inline float2 asfloat(const float2& v)
    {
        return v;
    }

    inline float3 asfloat(const float3& v)
    {
        return v;
    }

    inline float4 asfloat(const float4& v)
    {
        return v;
    }

    inline float2x2 asfloat(const float2x2& m)
    {
        return m;
    }

    inline float3x3 asfloat(const float3x3& m)
    {
        return m;
    }

    inline float4x4 asfloat(const float4x4& m)
    {
        return m;
    }

    //
    // @region: Common functions
    //

    /* Computes sign of 'x'
     */
    inline int2 sign(const int2& m)
    {
        return int2(sign(m[0]),
                    sign(m[1]));
    }

    /* Computes absolute value
     */
    inline int2 abs(const int2& m)
    {
        return int2(abs(m[0]),
                    abs(m[1]));
    }

    /* Get the smaller value
     */
    inline int2 min(const int2& a, const int2& b)
    {
        return int2(min(a[0], b[0]),
                    min(a[1], b[1]));
    }

    /* Get the larger value
     */
    inline int2 max(const int2& a, const int2& b)
    {
        return int2(max(a[0], b[0]), 
                    max(a[1], b[1]));
    }

    /* Clamps the 'x' value to the [min, max].
     */
    inline int2 clamp(const int2& m, const int2& min, const int2& max)
    {
        return int2(clamp(m[0], min[0], max[0]), 
                    clamp(m[1], min[1], max[1]));
    }

    /* Computes sign of 'x'
     */
    inline int3 sign(const int3& m)
    {
        return int3(sign(m[0]),
                    sign(m[1]),
                    sign(m[2]));
    }

    /* Computes absolute value
     */
    inline int3 abs(const int3& m)
    {
        return int3(abs(m[0]),
                    abs(m[1]),
                    abs(m[2]));
    }

    /* Get the smaller value
     */
    inline int3 min(const int3& a, const int3& b)
    {
        return int3(min(a[0], b[0]),
                    min(a[1], b[1]),
                    min(a[2], b[2]));
    }

    /* Get the larger value
     */
    inline int3 max(const int3& a, const int3& b)
    {
        return int3(max(a[0], b[0]), 
                    max(a[1], b[1]),
                    max(a[2], b[2]));
    }

    /* Clamps the 'x' value to the [min, max].
     */
    inline int3 clamp(const int3& v, const int3& min, const int3& max)
    {
        return int3(clamp(v[0], min[0], max[0]), 
                    clamp(v[1], min[1], max[1]), 
                    clamp(v[2], min[2], max[2]));
    }

    //
    // @region: Common functions
    //

    /* Computes sign of 'x'
     */
    inline int4 sign(const int4& m)
    {
        return int4(sign(m[0]),
                    sign(m[1]),
                    sign(m[2]),
                    sign(m[3]));
    }

    /* Computes absolute value
     */
    inline int4 abs(const int4& m)
    {
        return int4(abs(m[0]),
                    abs(m[1]),
                    abs(m[2]),
                    abs(m[3]));
    }

    /* Get the smaller value
     */
    inline int4 min(const int4& a, const int4& b)
    {
        return int4(min(a[0], b[0]),
                    min(a[1], b[1]),
                    min(a[2], b[2]),
                    min(a[3], b[3]));
    }

    /* Get the larger value
     */
    inline int4 max(const int4& a, const int4& b)
    {
        return int4(max(a[0], b[0]), 
                    max(a[1], b[1]),
                    max(a[2], b[2]),
                    max(a[3], b[3]));
    }

    /* Clamps the 'x' value to the [min, max].
     */
    inline int4 clamp(const int4& v, const int4& min, const int4& max)
    {
        return int4(clamp(v[0], min[0], max[0]), 
                    clamp(v[1], min[1], max[1]), 
                    clamp(v[2], min[2], max[2]), 
                    clamp(v[3], min[3], max[3]));
    }

    //
    // @region: Common functions
    //

    /* Get the smaller value
     */
    inline uint2 min(const uint2& a, const uint2& b)
    {
        return uint2(min(a[0], b[0]),
                     min(a[1], b[1]));
    }

    /* Get the larger value
     */
    inline uint2 max(const uint2& a, const uint2& b)
    {
        return uint2(max(a[0], b[0]), 
                     max(a[1], b[1]));
    }

    /* Clamps the 'x' value to the [min, max].
     */
    inline uint2 clamp(const uint2& m, const uint2& min, const uint2& max)
    {
        return uint2(clamp(m[0], min[0], max[0]), 
                     clamp(m[1], min[1], max[1]));
    }

    //
    // @region: Common functions
    //

    /* Get the smaller value
     */
    inline uint3 min(const uint3& a, const uint3& b)
    {
        return uint3(min(a[0], b[0]),
                     min(a[1], b[1]),
                     min(a[2], b[2]));
    }

    /* Get the larger value
     */
    inline uint3 max(const uint3& a, const uint3& b)
    {
        return uint3(max(a[0], b[0]), 
                     max(a[1], b[1]),
                     max(a[2], b[2]));
    }

    /* Clamps the 'x' value to the [min, max].
     */
    inline uint3 clamp(const uint3& v, const uint3& min, const uint3& max)
    {
        return uint3(clamp(v[0], min[0], max[0]), 
                     clamp(v[1], min[1], max[1]), 
                     clamp(v[2], min[2], max[2]));
    }

    //
    // @region: Common functions
    //

    /* Get the smaller value
     */
    inline uint4 min(const uint4& a, const uint4& b)
    {
        return uint4(min(a[0], b[0]),
                     min(a[1], b[1]),
                     min(a[2], b[2]),
                     min(a[3], b[3]));
    }

    /* Get the larger value
     */
    inline uint4 max(const uint4& a, const uint4& b)
    {
        return uint4(max(a[0], b[0]), 
                     max(a[1], b[1]),
                     max(a[2], b[2]),
                     max(a[3], b[3]));
    }

    /* Clamps the 'x' value to the [min, max].
     */
    inline uint4 clamp(const uint4& v, const uint4& min, const uint4& max)
    {
        return uint4(clamp(v[0], min[0], max[0]), 
                     clamp(v[1], min[1], max[1]), 
                     clamp(v[2], min[2], max[2]), 
                     clamp(v[3], min[3], max[3]));
    }

    //
    // @region: Common functions
    //

    /* Computes sign of 'x'
     */
    inline int2 sign(const float2& v)
    {
        return int2(sign(v.x),
                    sign(v.y));
    }

    /* Computes absolute value
     */
    inline float2 abs(const float2& v)
    {
        return float2(abs(v.x),
                      abs(v.y));
    }

    /* Computes cosine
     */
    inline float2 cos(const float2& v)
    {
        return float2(cos(v.x),
                      cos(v.y));
    }

    /* Computes sine
     */
    inline float2 sin(const float2& v)
    {
        return float2(sin(v.x),
                      sin(v.y));
    }

    /* Computes tangent
     */
    inline float2 tan(const float2& v)
    {
        return float2(tan(v.x),
                      tan(v.y));
    }

    /* Computes hyperbolic cosine
     */
    inline float2 cosh(const float2& v)
    {
        return float2(cosh(v.x),
                      cosh(v.y));
    }

    /* Computes hyperbolic sine
     */
    inline float2 sinh(const float2& v)
    {
        return float2(sinh(v.x),
                      sinh(v.y));
    }

    /* Computes hyperbolic tangent
     */
    inline float2 tanh(const float2& v)
    {
        return float2(tanh(v.x),
                      tanh(v.y));
    }

    /* Computes inverse cosine
     */
    inline float2 acos(const float2& v)
    {
        return float2(acos(v.x),
                      acos(v.y));
    }

    /* Computes inverse sine
     */
    inline float2 asin(const float2& v)
    {
        return float2(asin(v.x),
                      asin(v.y));
    }

    /* Computes inverse tangent
     */
    inline float2 atan(const float2& v)
    {
        return float2(atan(v.x),
                      atan(v.y));
    }

    /* Computes inverse tangent with 2 args
     */
    inline float2 atan2(const float2& a, const float2& b)
    {
        return float2(atan2(a.x, b.x),
                      atan2(a.y, b.y));
    }

    /* Computes Euler number raised to the power 'x'
     */
    inline float2 exp(const float2& v)
    {
        return float2(exp(v.x),
                      exp(v.y));
    }

    /* Computes 2 raised to the power 'x'
     */
    inline float2 exp2(const float2& v)
    {
        return float2(exp2(v.x),
                      exp2(v.y));
    }

    /* Computes the base Euler number logarithm
     */
    inline float2 log(const float2& v)
    {
        return float2(log(v.x),
                      log(v.y));
    }

    /* Computes the base 2 logarithm
     */
    inline float2 log2(const float2& v)
    {
        return float2(log2(v.x),
                      log2(v.y));
    }

    /* Computes the base 10 logarithm
     */
    inline float2 log10(const float2& v)
    {
        return float2(log10(v.x),
                      log10(v.y));
    }

    /* Computes the value of base raised to the power exponent
     */
    inline float2 pow(const float2& a, const float2& b)
    {
        return float2(pow(a.x, b.x),
                      pow(a.y, b.y));
    }

    /* Get the fractal part of floating point
     */
    inline float2 frac(const float2& v)
    {
        return float2(frac(v.x),
                      frac(v.y));
    }

    /* Computes the floating-point remainder of the division operation x/y
     */
    inline float2 fmod(const float2& a, const float2& b)
    {
        return float2(fmod(a.x, b.x),
                      fmod(a.y, b.y));
    }

    /* Computes the smallest integer value not less than 'x'
     */
    inline float2 ceil(const float2& v)
    {
        return float2(ceil(v.x),
                      ceil(v.y));
    }

    /* Computes the largest integer value not greater than 'x'
     */
    inline float2 floor(const float2& v)
    {
        return float2(floor(v.x),
                      floor(v.y));
    }

    /* Computes the nearest integer value
     */
    inline float2 round(const float2& v)
    {
        return float2(round(v.x),
                      round(v.y));
    }

    /* Computes the nearest integer not greater in magnitude than 'x'
     */
    inline float2 trunc(const float2& v)
    {
        return float2(trunc(v.x),
                      trunc(v.y));
    }

    /* Get the smaller value
     */
    inline float2 min(const float2& a, const float2& b)
    {
        return float2(min(a.x, b.x),
                      min(a.y, b.y));
    }

    /* Get the larger value
     */
    inline float2 max(const float2& a, const float2& b)
    {
        return float2(max(a.x, b.x), 
                      max(a.y, b.y));
    }

    /* Clamps the 'x' value to the [min, max].
     */
    inline float2 clamp(const float2& v, const float2& min, const float2& max)
    {
        return float2(clamp(v.x, min.x, max.x), 
                      clamp(v.y, min.y, max.y));
    }

    /* Clamps the specified value within the range of 0 to 1
     */
    inline float2 saturate(const float2& v)
    {
        return float2(saturate(v.x),
                      saturate(v.y));
    }

    /* Compares two values, returning 0 or 1 based on which value is greater.
     */
    inline float2 step(const float2& a, const float2& b)
    {
        return float2(step(a.x, b.x),
                      step(a.y, b.y));
    }

    /* Performs a linear interpolation.
     */
    inline float2 lerp(const float2& a, const float2& b, const float2& t)
    {
        return float2(lerp(a.x, b.x, t.x),
                      lerp(a.y, b.y, t.y));
    }

    /* Performs a linear interpolation.
     */
    inline float2 lerp(const float2& a, const float2& b, float t)
    {
        return float2(lerp(a.x, b.x, t),
                      lerp(a.y, b.y, t));
    }

    /* Compute a smooth Hermite interpolation
     */
    inline float2 smoothstep(const float2& a, const float2& b, const float2& t)
    {
        return float2(smoothstep(a.x, b.x, t.x),
                      smoothstep(a.y, b.y, t.y));
    }

    /* Computes square root of 'x'.
     */
    inline float2 sqrt(const float2& v)
    {
        return float2(sqrt(v.x),
                      sqrt(v.y));
    }

    /* Computes inverse square root of 'x'.
     */
    inline float2 rsqrt(const float2& v)
    {
        return float2(rsqrt(v.x),
                      rsqrt(v.y));
    }

    /* Computes fast inverse square root of 'x'.
     */
    inline float2 fsqrt(const float2& v)
    {
        return float2(fsqrt(v.x),
                      fsqrt(v.y));
    }

    /* Computes fast inverse square root of 'x'.
     */
    inline float2 frsqrt(const float2& v)
    {
        return float2(frsqrt(v.x),
                      frsqrt(v.y));
    }

    //
    // @region: Graphics funtions
    //

    /* Compute dot product of two vectors
     */ 
    inline float dot(const float2& a, const float2& b)
    {
        return a.x * b.x + a.y * b.y;
    }

    /* Compute squared length of vector
     */
    inline float lensqr(const float2& v)
    {
        return dot(v, v);
    }

    /* Compute length of vector
     */
    inline float length(const float2& v)
    {
        return sqrt(lensqr(v));
    }

    /* Compute distance from 'a' to b
     */
    inline float distance(const float2& a, const float2& b)
    {
        return length(a - b);
    }

    /* Compute squared distance from 'a' to b
     */
    inline float distsqr(const float2& a, const float2& b)
    {
        return lensqr(a - b);
    }

    /* Compute normalized vector
     */
    inline float2 normalize(const float2& v)
    {
        const float lsqr = lensqr(v);
        if (lsqr > 0.0f)
        {
            const float f = rsqrt(lsqr);
            return float2(v.x * f, v.y * f);
        }
        else
        {
            return v;
        }
    }

    /* Compute reflection vector
     */
    inline float2 reflect(const float2& v, const float2& n)
    {
        return v - 2.0f * dot(v, n) * n;
    }

    /* Compute refraction vector
     */
    inline float2 refract(const float2& v, const float2& n, float eta)
    {
        const float k = 1.0f - eta * eta * (1.0f - dot(v, n) * dot(v, n));
        return k < 0.0f
            ? float2(0.0f)
            : eta * v - (eta * dot(v, n) + sqrt(k)) * v;
    }

    /* Compute faceforward vector
     */
    inline float2 faceforward(const float2& n, const float2& i, const float2& nref)
    {
        return dot(i, nref) < 0.0f ? n : -n;
    }

    //
    // @region: Common functions
    //

    /* Computes sign of 'x'
     */
    inline int3 sign(const float3& v)
    {
        return int3(sign(v.x),
                    sign(v.y),
                    sign(v.z));
    }

    /* Computes absolute value
     */
    inline float3 abs(const float3& v)
    {
        return float3(abs(v.x),
                      abs(v.y),
                      abs(v.z));
    }

    /* Computes cosine
     */
    inline float3 cos(const float3& v)
    {
        return float3(cos(v.x),
                      cos(v.y),
                      cos(v.z));
    }

    /* Computes sine
     */
    inline float3 sin(const float3& v)
    {
        return float3(sin(v.x),
                      sin(v.y),
                      sin(v.z));
    }

    /* Computes tangent
     */
    inline float3 tan(const float3& v)
    {
        return float3(tan(v.x),
                      tan(v.y),
                      tan(v.z));
    }

    /* Computes hyperbolic cosine
     */
    inline float3 cosh(const float3& v)
    {
        return float3(cosh(v.x),
                      cosh(v.y),
                      cosh(v.z));
    }

    /* Computes hyperbolic sine
     */
    inline float3 sinh(const float3& v)
    {
        return float3(sinh(v.x),
                      sinh(v.y),
                      sinh(v.z));
    }

    /* Computes hyperbolic tangent
     */
    inline float3 tanh(const float3& v)
    {
        return float3(tanh(v.x),
                      tanh(v.y),
                      tanh(v.z));
    }

    /* Computes inverse cosine
     */
    inline float3 acos(const float3& v)
    {
        return float3(acos(v.x),
                      acos(v.y),
                      acos(v.z));
    }

    /* Computes inverse sine
     */
    inline float3 asin(const float3& v)
    {
        return float3(asin(v.x),
                      asin(v.y),
                      asin(v.z));
    }

    /* Computes inverse tangent
     */
    inline float3 atan(const float3& v)
    {
        return float3(atan(v.x),
                      atan(v.y),
                      asin(v.z));
    }

    /* Computes inverse tangent with 2 args
     */
    inline float3 atan2(const float3& a, const float3& b)
    {
        return float3(atan2(a.x, b.x),
                      atan2(a.y, b.y),
                      atan2(a.z, b.z));
    }

    /* Computes Euler number raised to the power 'x'
     */
    inline float3 exp(const float3& v)
    {
        return float3(exp(v.x),
                      exp(v.y),
                      exp(v.z));
    }

    /* Computes 2 raised to the power 'x'
     */
    inline float3 exp2(const float3& v)
    {
        return float3(exp2(v.x),
                      exp2(v.y),
                      exp2(v.z));
    }

    /* Computes the base Euler number logarithm
     */
    inline float3 log(const float3& v)
    {
        return float3(log(v.x),
                      log(v.y),
                      log(v.z));
    }

    /* Computes the base 2 logarithm
     */
    inline float3 log2(const float3& v)
    {
        return float3(log2(v.x),
                      log2(v.y),
                      log2(v.z));
    }

    /* Computes the base 10 logarithm
     */
    inline float3 log10(const float3& v)
    {
        return float3(log10(v.x),
                      log10(v.y),
                      log10(v.z));
    }

    /* Computes the value of base raised to the power exponent
     */
    inline float3 pow(const float3& a, const float3& b)
    {
        return float3(pow(a.x, b.x),
                      pow(a.y, b.y),
                      pow(a.z, b.z));
    }

    /* Get the fractal part of floating point
     */
    inline float3 frac(const float3& v)
    {
        return float3(frac(v.x),
                      frac(v.y),
                      frac(v.z));
    }

    /* Computes the floating-point remainder of the division operation x/y
     */
    inline float3 fmod(const float3& a, const float3& b)
    {
        return float3(fmod(a.x, b.x),
                      fmod(a.y, b.y),
                      fmod(a.z, b.z));
    }

    /* Computes the smallest integer value not less than 'x'
     */
    inline float3 ceil(const float3& v)
    {
        return float3(ceil(v.x),
                      ceil(v.y),
                      ceil(v.z));
    }

    /* Computes the largest integer value not greater than 'x'
     */
    inline float3 floor(const float3& v)
    {
        return float3(floor(v.x),
                      floor(v.y),
                      floor(v.z));
    }

    /* Computes the nearest integer value
     */
    inline float3 round(const float3& v)
    {
        return float3(round(v.x),
                      round(v.y),
                      round(v.z));
    }

    /* Computes the nearest integer not greater in magnitude than 'x'
     */
    inline float3 trunc(const float3& v)
    {
        return float3(trunc(v.x),
                      trunc(v.y),
                      trunc(v.z));
    }

    /* Get the smaller value
     */
    inline float3 min(const float3& a, const float3& b)
    {
        return float3(min(a.x, b.x),
                      min(a.y, b.y),
                      min(a.z, b.z));
    }

    /* Get the larger value
     */
    inline float3 max(const float3& a, const float3& b)
    {
        return float3(max(a.x, b.x), 
                      max(a.y, b.y),
                      max(a.z, b.z));
    }

    /* Clamps the 'x' value to the [min, max].
     */
    inline float3 clamp(const float3& v, const float3& min, const float3& max)
    {
        return float3(clamp(v.x, min.x, max.x), 
                      clamp(v.y, min.y, max.y), 
                      clamp(v.z, min.z, max.z));
    }

    /* Clamps the specified value within the range of 0 to 1
     */
    inline float3 saturate(const float3& v)
    {
        return float3(saturate(v.x),
                      saturate(v.y),
                      saturate(v.z));
    }

    /* Compares two values, returning 0 or 1 based on which value is greater.
     */
    inline float3 step(const float3& a, const float3& b)
    {
        return float3(
            step(a.x, b.x),
            step(a.y, b.y),
            step(a.z, b.z)
        );
    }

    /* Performs a linear interpolation.
     */
    inline float3 lerp(const float3& a, const float3& b, const float3& t)
    {
        return float3(lerp(a.x, b.x, t.x),
                      lerp(a.y, b.y, t.y), 
                      lerp(a.z, b.z, t.z));
    }

    /* Performs a linear interpolation.
     */
    inline float3 lerp(const float3& a, const float3& b, float t)
    {
        return float3(lerp(a.x, b.x, t),
                      lerp(a.y, b.y, t), 
                      lerp(a.z, b.z, t));
    }

    /* Compute a smooth Hermite interpolation
     */
    inline float3 smoothstep(const float3& a, const float3& b, const float3& t)
    {
        return float3(smoothstep(a.x, b.x, t.x),
                      smoothstep(a.y, b.y, t.y),
                      smoothstep(a.z, b.z, t.z));
    }

    /* Computes square root of 'x'.
     */
    inline float3 sqrt(const float3& v)
    {
        return float3(sqrt(v.x),
                      sqrt(v.y),
                      sqrt(v.z));
    }

    /* Computes inverse square root of 'x'.
     */
    inline float3 rsqrt(const float3& v)
    {
        return float3(rsqrt(v.x),
                      rsqrt(v.y),
                      rsqrt(v.z));
    }

    /* Computes fast inverse square root of 'x'.
     */
    inline float3 fsqrt(const float3& v)
    {
        return float3(fsqrt(v.x),
                      fsqrt(v.y),
                      fsqrt(v.z));
    }

    /* Computes fast inverse square root of 'x'.
     */
    inline float3 frsqrt(const float3& v)
    {
        return float3(frsqrt(v.x),
                      frsqrt(v.y),
                      frsqrt(v.z));
    }

    //
    // @region: Graphics functions
    //

    /* Compute cross product of two vectors
     */
    inline float3 cross(const float3& a, const float3& b)
    {
        return float3(
            a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x
        );
    }

    /* Compute dot product of two vectors
     */
    inline float dot(const float3& a, const float3& b)
    {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }

    /* Compute squared length of vector
     */
    inline float lensqr(const float3& v)
    {
        return dot(v, v);
    }

    /* Compute length of vector
     */
    inline float length(const float3& v)
    {
        return sqrt(lensqr(v));
    }

    /* Compute distance from 'a' to b
     */
    inline float distance(const float3& a, const float3& b)
    {
        return length(a - b);
    }

    /* Compute squared distance from 'a' to b
     */
    inline float distsqr(const float3& a, const float3& b)
    {
        return lensqr(a - b);
    }

    /* Compute normalized vector
     */
    inline float3 normalize(const float3& v)
    {
        const float lsqr = lensqr(v);
        if (lsqr > 0.0f)
        {
            const float f = rsqrt(lsqr);
            return float3(v.x * f, v.y * f, v.z * f);
        }
        else
        {
            return v;
        }
    }

    /* Compute reflection vector
     */
    inline float3 reflect(const float3& v, const float3& n)
    {
        return v - 2.0f * dot(v, n) * n;
    }

    /* Compute refraction vector
     */
    inline float3 refract(const float3& v, const float3& n, float eta)
    {
        const float k = 1.0f - eta * eta * (1.0f - dot(v, n) * dot(v, n));
        return k < 0.0f
            ? float3(0.0f)
            : eta * v - (eta * dot(v, n) + sqrt(k)) * n;
    }

    /* Compute faceforward vector
     */
    inline float3 faceforward(const float3& n, const float3& i, const float3& nref)
    {
        return dot(i, nref) < 0.0f ? n : -n;
    }

    //
    // @region: Common functions
    //

    /* Computes sign of 'x'
     */
    inline int4 sign(const float4& v)
    {
        return int4(sign(v.x),
                    sign(v.y),
                    sign(v.z),
                    sign(v.w));
    }

    /* Computes absolute value
     */
    inline float4 abs(const float4& v)
    {
        return float4(abs(v.x),
                      abs(v.y),
                      abs(v.z),
                      abs(v.w));
    }

    /* Computes cosine
     */
    inline float4 cos(const float4& v)
    {
        return float4(cos(v.x),
                      cos(v.y),
                      cos(v.z),
                      cos(v.w));
    }

    /* Computes sine
     */
    inline float4 sin(const float4& v)
    {
        return float4(sin(v.x),
                      sin(v.y),
                      sin(v.z),
                      sin(v.w));
    }

    /* Computes tangent
     */
    inline float4 tan(const float4& v)
    {
        return float4(tan(v.x),
                      tan(v.y),
                      tan(v.z),
                      tan(v.w));
    }

    /* Computes hyperbolic cosine
     */
    inline float4 cosh(const float4& v)
    {
        return float4(cosh(v.x),
                      cosh(v.y),
                      cosh(v.z),
                      cosh(v.w));
    }

    /* Computes hyperbolic sine
     */
    inline float4 sinh(const float4& v)
    {
        return float4(sinh(v.x),
                      sinh(v.y),
                      sinh(v.z),
                      sinh(v.w));
    }

    /* Computes hyperbolic tangent
     */
    inline float4 tanh(const float4& v)
    {
        return float4(tanh(v.x),
                      tanh(v.y),
                      tanh(v.z),
                      tanh(v.w));
    }

    /* Computes inverse cosine
     */
    inline float4 acos(const float4& v)
    {
        return float4(acos(v.x),
                      acos(v.y),
                      acos(v.z),
                      acos(v.w));
    }

    /* Computes inverse sine
     */
    inline float4 asin(const float4& v)
    {
        return float4(asin(v.x),
                      asin(v.y),
                      asin(v.z),
                      asin(v.w));
    }

    /* Computes inverse tangent
     */
    inline float4 atan(const float4& v)
    {
        return float4(atan(v.x),
                      atan(v.y),
                      atan(v.z),
                      atan(v.w));
    }

    /* Computes inverse tangent with 2 args
     */
    inline float4 atan2(const float4& a, const float4& b)
    {
        return float4(atan2(a.x, b.x),
                      atan2(a.y, b.y),
                      atan2(a.z, b.z),
                      atan2(a.w, b.w));
    }

    /* Computes Euler number raised to the power 'x'
     */
    inline float4 exp(const float4& v)
    {
        return float4(exp(v.x),
                      exp(v.y),
                      exp(v.z),
                      exp(v.w));
    }

    /* Computes 2 raised to the power 'x'
     */
    inline float4 exp2(const float4& v)
    {
        return float4(exp2(v.x),
                      exp2(v.y),
                      exp2(v.z),
                      exp2(v.w));
    }

    /* Computes the base Euler number logarithm
     */
    inline float4 log(const float4& v)
    {
        return float4(log(v.x),
                      log(v.y),
                      log(v.z),
                      log(v.w));
    }

    /* Computes the base 2 logarithm
     */
    inline float4 log2(const float4& v)
    {
        return float4(log2(v.x),
                      log2(v.y),
                      log2(v.z),
                      log2(v.w)  );
    }

    /* Computes the base 10 logarithm
     */
    inline float4 log10(const float4& v)
    {
        return float4(log10(v.x),
                      log10(v.y),
                      log10(v.z),
                      log10(v.w));
    }

    /* Computes the value of base raised to the power exponent
     */
    inline float4 pow(const float4& a, const float4& b)
    {
        return float4(pow(a.x, b.x),
                      pow(a.y, b.y),
                      pow(a.z, b.z),
                      pow(a.w, b.w));
    }

    /* Get the fractal part of floating point
     */
    inline float4 frac(const float4& v)
    {
        return float4(frac(v.x),
                      frac(v.y),
                      frac(v.z),
                      frac(v.w));
    }

    /* Computes the floating-point remainder of the division operation x/y
     */
    inline float4 fmod(const float4& a, const float4& b)
    {
        return float4(fmod(a.x, b.x),
                      fmod(a.y, b.y),
                      fmod(a.z, b.z),
                      fmod(a.w, b.w));
    }

    /* Computes the smallest integer value not less than 'x'
     */
    inline float4 ceil(const float4& v)
    {
        return float4(ceil(v.x),
                      ceil(v.y),
                      ceil(v.z),
                      ceil(v.w));
    }

    /* Computes the largest integer value not greater than 'x'
     */
    inline float4 floor(const float4& v)
    {
        return float4(floor(v.x),
                      floor(v.y),
                      floor(v.z),
                      floor(v.w));
    }

    /* Computes the nearest integer value
     */
    inline float4 round(const float4& v)
    {
        return float4(round(v.x),
                      round(v.y),
                      round(v.z),
                      round(v.w));
    }

    /* Computes the nearest integer not greater in magnitude than 'x'
     */
    inline float4 trunc(const float4& v)
    {
        return float4(trunc(v.x),
                      trunc(v.y),
                      trunc(v.z),
                      trunc(v.w));
    }

    /* Get the smaller value
     */
    inline float4 min(const float4& a, const float4& b)
    {
        return float4(min(a.x, b.x),
                      min(a.y, b.y),
                      min(a.z, b.z),
                      min(a.w, b.w));
    }

    /* Get the larger value
     */
    inline float4 max(const float4& a, const float4& b)
    {
        return float4(max(a.x, b.x), 
                      max(a.y, b.y),
                      max(a.z, b.z),
                      max(a.w, b.w));
    }

    /* Clamps the 'x' value to the [min, max].
     */
    inline float4 clamp(const float4& v, const float4& min, const float4& max)
    {
        return float4(clamp(v.x, min.x, max.x), 
                      clamp(v.y, min.y, max.y), 
                      clamp(v.z, min.z, max.z), 
                      clamp(v.w, min.w, max.w));
    }

    /* Clamps the specified value within the range of 0 to 1
     */
    inline float4 saturate(const float4& v)
    {
        return float4(saturate(v.x),
                      saturate(v.y),
                      saturate(v.z),
                      saturate(v.w));
    }

    /* Compares two values, returning 0 or 1 based on which value is greater.
     */
    inline float4 step(const float4& a, const float4& b)
    {
        return float4(step(a.x, b.x),
                      step(a.y, b.y),
                      step(a.z, b.z),
                      step(a.w, b.w));
    }

    /* Performs a linear interpolation.
     */
    inline float4 lerp(const float4& a, const float4& b, const float4& t)
    {
        return float4(lerp(a.x, b.x, t.x),
                      lerp(a.y, b.y, t.y), 
                      lerp(a.z, b.z, t.z), 
                      lerp(a.w, b.w, t.w));
    }

    /* Performs a linear interpolation.
     */
    inline float4 lerp(const float4& a, const float4& b, float t)
    {
        return float4(lerp(a.x, b.x, t),
                      lerp(a.y, b.y, t), 
                      lerp(a.z, b.z, t), 
                      lerp(a.w, b.w, t));
    }

    /* Compute a smooth Hermite interpolation
     */
    inline float4 smoothstep(const float4& a, const float4& b, const float4& t)
    {
        return float4(smoothstep(a.x, b.x, t.x),
                      smoothstep(a.y, b.y, t.y),
                      smoothstep(a.z, b.z, t.z),
                      smoothstep(a.w, b.w, t.w));
    }

    /* Computes square root of 'x'.
     */
    inline float4 sqrt(const float4& v)
    {
        return float4(sqrt(v.x),
                      sqrt(v.y),
                      sqrt(v.z),
                      sqrt(v.w));
    }

    /* Computes inverse square root of 'x'.
     */
    inline float4 rsqrt(const float4& v)
    {
        return float4(rsqrt(v.x),
                      rsqrt(v.y),
                      rsqrt(v.z),
                      rsqrt(v.w));
    }

    /* Computes fast inverse square root of 'x'.
     */
    inline float4 fsqrt(const float4& v)
    {
        return float4(fsqrt(v.x),
                      fsqrt(v.y),
                      fsqrt(v.z),
                      fsqrt(v.w));
    }

    /* Computes fast inverse square root of 'x'.
     */
    inline float4 frsqrt(const float4& v)
    {
        return float4(frsqrt(v.x),
                      frsqrt(v.y),
                      frsqrt(v.z),
                      frsqrt(v.w));
    }

    //
    // @region: Graphics functions
    //

    /* Compute dot product of two vectors
     */
    inline float dot(const float4& a, const float4& b)
    {
        return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
    }

    /* Compute squared length of vector
     */
    inline float lensqr(const float4& v)
    {
        return dot(v, v);
    }

    /* Compute length of vector
     */
    inline float length(const float4& v)
    {
        return sqrt(lensqr(v));
    }

    /* Compute distance from 'a' to b
     */
    inline float distance(const float4& a, const float4& b)
    {
        return length(a - b);
    }

    /* Compute squared distance from 'a' to b
     */
    inline float distsqr(const float4& a, const float4& b)
    {
        return lensqr(a - b);
    }

    /* Compute normalized vector
     */
    inline float4 normalize(const float4& v)
    {
        const float lsqr = lensqr(v);
        if (lsqr > 0.0f)
        {
            const float f = rsqrt(lsqr);
            return float4(v.x * f, v.y * f, v.z * f, v.w * f);
        }
        else
        {
            return v;
        }
    }

    /* Compute normalized vector
     */
    inline quat normalize(const quat& v)
    {
        return quat(normalize(*(float4*)&v));
    }

    /* Compute reflection vector
     */
    inline float4 reflect(const float4& v, const float4& n)
    {
        return v - 2.0f * dot(v, n) * n;
    }

    /* Compute refraction vector
     */
    inline float4 refract(const float4& v, const float4& n, float eta)
    {
        const float k = 1.0f - eta * eta * (1.0f - dot(v, n) * dot(v, n));
        return k < 0.0f
            ? float4(0.0f)
            : eta * v - (eta * dot(v, n) + sqrt(k)) * n;
    }

    /* Compute faceforward vector
     */
    inline float4 faceforward(const float4& n, const float4& i, const float4& nref)
    {
        return dot(i, nref) < 0.0f ? n : -n;
    }

    /* Quaternion multiplication
     */
    inline float4 qmul(const float4& a, const float4& b)
    {
        const float3 a3 = float3(a.x, a.y, a.z);
        const float3 b3 = float3(b.x, b.y, b.z);

        float3 xyz = a3 * b.w + b3 * a.w + cross(a3, b3);
        float  w   = a.w * b.w - dot(a3, b3);
        return float4(xyz, w);
    }

    inline float4 qinverse(const float4& q)
    {
        return float4(q.x, q.y, q.z, -q.w);
    }

    inline float4 qconj(const float4& q)
    {
        return float4(-q.x, -q.y, -q.z, q.w);
    }

    //
    // @region: Common functions
    //

    /* Computes sign of 'x'
     */
    inline int4x4 sign(const int4x4& m)
    {
        return int4x4(sign(m[0]),
                      sign(m[1]),
                      sign(m[2]),
                      sign(m[3]));
    }

    /* Computes absolute value
     */
    inline int4x4 abs(const int4x4& m)
    {
        return int4x4(abs(m[0]),
                      abs(m[1]),
                      abs(m[2]),
                      abs(m[3]));
    }

    /* Get the smaller value
     */
    inline int4x4 min(const int4x4& a, const int4x4& b)
    {
        return int4x4(min(a[0], b[0]),
                      min(a[1], b[1]),
                      min(a[2], b[2]),
                      min(a[3], b[3]));
    }

    /* Get the larger value
     */
    inline int4x4 max(const int4x4& a, const int4x4& b)
    {
        return int4x4(max(a[0], b[0]), 
                      max(a[1], b[1]),
                      max(a[2], b[2]),
                      max(a[3], b[3]));
    }

    /* Clamps the 'x' value to the [min, max].
     */
    inline int4x4 clamp(const int4x4& v, const int4x4& min, const int4x4& max)
    {
        return int4x4(clamp(v[0], min[0], max[0]), 
                      clamp(v[1], min[1], max[1]), 
                      clamp(v[2], min[2], max[2]), 
                      clamp(v[3], min[3], max[3]));
    }

    //
    // @region: Common functions
    //

    /* Computes sign of 'x'
     */
    inline int2x2 sign(const int2x2& m)
    {
        return int2x2(sign(m[0]),
            sign(m[1]));
    }

    /* Computes absolute value
     */
    inline int2x2 abs(const int2x2& m)
    {
        return int2x2(abs(m[0]),
            abs(m[1]));
    }

    /* Get the smaller value
     */
    inline int2x2 min(const int2x2& a, const int2x2& b)
    {
        return int2x2(min(a[0], b[0]),
            min(a[1], b[1]));
    }

    /* Get the larger value
     */
    inline int2x2 max(const int2x2& a, const int2x2& b)
    {
        return int2x2(max(a[0], b[0]),
            max(a[1], b[1]));
    }

    /* Clamps the 'x' value to the [min, max].
     */
    inline int2x2 clamp(const int2x2& m, const int2x2& min, const int2x2& max)
    {
        return int2x2(clamp(m[0], min[0], max[0]),
            clamp(m[1], min[1], max[1]));
    }

    //
    // @region: Operators overloading
    //

    inline int3x3 operator-(const int3x3& m)
    {
        int3x3 result;
        result[0] = -m[0];
        result[1] = -m[1];
        result[2] = -m[2];
        return result;
    }

    inline const int3x3& operator+(const int3x3& m)
    {
        return m;
    }

    inline int3x3& operator--(int3x3& m)
    {
        --m[0];
        --m[1];
        --m[2];
        return m;
    }

    inline int3x3& operator++(int3x3& m)
    {
        ++m[0];
        ++m[1];
        ++m[2];
        return m;
    }

    inline const int3x3& operator--(int3x3& m, int)
    {
        m[0]--;
        m[1]--;
        m[2]--;
        return m;
    }

    inline const int3x3& operator++(int3x3& m, int)
    {
        m[0]++;
        m[1]++;
        m[2]++;
        return m;
    }

    inline int3x3 operator+(const int3x3& a, const int3x3& b)
    {
        int3x3 result;
        result[0] = a[0] + b[0];
        result[1] = a[1] + b[1];
        result[2] = a[2] + b[2];
        return result;
    }

    inline int3x3 operator-(const int3x3& a, const int3x3& b)
    {
        int3x3 result;
        result[0] = a[0] - b[0];
        result[1] = a[1] - b[1];
        result[2] = a[2] - b[2];
        return result;
    }

    inline int3x3 operator*(const int3x3& a, const int3x3& b)
    {
        int3x3 result;
        result[0] = a[0] * b[0];
        result[1] = a[1] * b[1];
        result[2] = a[2] * b[2];
        return result;
    }

    inline int3x3 operator/(const int3x3& a, const int3x3& b)
    {
        int3x3 result;
        result[0] = a[0] / b[0];
        result[1] = a[1] / b[1];
        result[2] = a[2] / b[2];
        return result;
    }

    inline int3x3 operator+(const int3x3& a, int b)
    {
        int3x3 result;
        result[0] = a[0] + b;
        result[1] = a[1] + b;
        result[2] = a[2] + b;
        return result;
    }

    inline int3x3 operator-(const int3x3& a, int b)
    {
        int3x3 result;
        result[0] = a[0] - b;
        result[1] = a[1] - b;
        result[2] = a[2] - b;
        return result;
    }

    inline int3x3 operator*(const int3x3& a, int b)
    {
        int3x3 result;
        result[0] = a[0] * b;
        result[1] = a[1] * b;
        result[2] = a[2] * b;
        return result;
    }

    inline int3x3 operator/(const int3x3& a, int b)
    {
        int3x3 result;
        result[0] = a[0] / b;
        result[1] = a[1] / b;
        result[2] = a[2] / b;
        return result;
    }

    inline int3x3 operator+(int a, const int3x3& b)
    {
        int3x3 result;
        result[0] = a + b[0];
        result[1] = a + b[1];
        result[2] = a + b[2];
        return result;
    }

    inline int3x3 operator-(int a, const int3x3& b)
    {
        int3x3 result;
        result[0] = a - b[0];
        result[1] = a - b[1];
        result[2] = a - b[2];
        return result;
    }

    inline int3x3 operator*(int a, const int3x3& b)
    {
        int3x3 result;
        result[0] = a * b[0];
        result[1] = a * b[1];
        result[2] = a * b[2];
        return result;
    }

    inline int3x3 operator/(int a, const int3x3& b)
    {
        int3x3 result;
        result[0] = a / b[0];
        result[1] = a / b[1];
        result[2] = a / b[2];
        return result;
    }

    inline int3x3& operator+=(int3x3& a, const int3x3& b)
    {
        return (a = a + b);
    }

    inline int3x3& operator+=(int3x3& a, int b)
    {
        return (a = a + b);
    }

    inline int3x3& operator-=(int3x3& a, const int3x3& b)
    {
        return (a = a - b);
    }

    inline int3x3& operator-=(int3x3& a, int b)
    {
        return (a = a - b);
    }

    inline int3x3& operator*=(int3x3& a, const int3x3& b)
    {
        return (a = a * b);
    }

    inline int3x3& operator*=(int3x3& a, int b)
    {
        return (a = a * b);
    }

    inline int3x3& operator/=(int3x3& a, const int3x3& b)
    {
        return (a = a / b);
    }

    inline int3x3& operator/=(int3x3& a, int b)
    {
        return (a = a + b);
    }

    inline bool3x3 operator==(const int3x3& a, const int3x3& b)
    {
        bool3x3 result;
        result[0] = a[0] == b[0];
        result[1] = a[1] == b[1];
        result[2] = a[2] == b[2];
        return result;
    }

    inline bool3x3 operator!=(const int3x3& a, const int3x3& b)
    {
        bool3x3 result;
        result[0] = a[0] != b[0];
        result[1] = a[1] != b[1];
        result[2] = a[2] != b[2];
        return result;
    }

    inline bool3x3 operator<(const int3x3& a, const int3x3& b)
    {
        bool3x3 result;
        result[0] = a[0] < b[0];
        result[1] = a[1] < b[1];
        result[2] = a[2] < b[2];
        return result;
    }

    inline bool3x3 operator>(const int3x3& a, const int3x3& b)
    {
        bool3x3 result;
        result[0] = a[0] > b[0];
        result[1] = a[1] > b[1];
        result[2] = a[2] > b[2];
        return result;
    }

    inline bool3x3 operator<=(const int3x3& a, const int3x3& b)
    {
        bool3x3 result;
        result[0] = a[0] <= b[0];
        result[1] = a[1] <= b[1];
        result[2] = a[2] <= b[2];
        return result;
    }

    inline bool3x3 operator>=(const int3x3& a, const int3x3& b)
    {
        bool3x3 result;
        result[0] = a[0] >= b[0];
        result[1] = a[1] >= b[1];
        result[2] = a[2] >= b[2];
        return result;
    }

    //
    // @region: Common functions
    //

    /* Computes sign of 'x'
     */
    inline int3x3 sign(const int3x3& m)
    {
        return int3x3(sign(m[0]),
            sign(m[1]),
            sign(m[2]));
    }

    /* Computes absolute value
     */
    inline int3x3 abs(const int3x3& m)
    {
        return int3x3(abs(m[0]),
            abs(m[1]),
            abs(m[2]));
    }

    /* Get the smaller value
     */
    inline int3x3 min(const int3x3& a, const int3x3& b)
    {
        return int3x3(min(a[0], b[0]),
            min(a[1], b[1]),
            min(a[2], b[2]));
    }

    /* Get the larger value
     */
    inline int3x3 max(const int3x3& a, const int3x3& b)
    {
        return int3x3(max(a[0], b[0]),
            max(a[1], b[1]),
            max(a[2], b[2]));
    }

    /* Clamps the 'x' value to the [min, max].
     */
    inline int3x3 clamp(const int3x3& v, const int3x3& min, const int3x3& max)
    {
        return int3x3(clamp(v[0], min[0], max[0]),
            clamp(v[1], min[1], max[1]),
            clamp(v[2], min[2], max[2]));
    }

    //
    // @region: Common functions
    //

    /* Get the smaller value
     */
    inline uint2x2 min(const uint2x2& a, const uint2x2& b)
    {
        return uint2x2(min(a[0], b[0]),
            min(a[1], b[1]));
    }

    /* Get the larger value
     */
    inline uint2x2 max(const uint2x2& a, const uint2x2& b)
    {
        return uint2x2(max(a[0], b[0]),
            max(a[1], b[1]));
    }

    /* Clamps the 'x' value to the [min, max].
     */
    inline uint2x2 clamp(const uint2x2& m, const uint2x2& min, const uint2x2& max)
    {
        return uint2x2(clamp(m[0], min[0], max[0]),
            clamp(m[1], min[1], max[1]));
    }

    //
    // @region: Common functions
    //

    /* Get the smaller value
     */
    inline uint3x3 min(const uint3x3& a, const uint3x3& b)
    {
        return uint3x3(min(a[0], b[0]),
                       min(a[1], b[1]),
                       min(a[2], b[2]));
    }

    /* Get the larger value
     */
    inline uint3x3 max(const uint3x3& a, const uint3x3& b)
    {
        return uint3x3(max(a[0], b[0]), 
                       max(a[1], b[1]),
                       max(a[2], b[2]));
    }

    /* Clamps the 'x' value to the [min, max].
     */
    inline uint3x3 clamp(const uint3x3& v, const uint3x3& min, const uint3x3& max)
    {
        return uint3x3(clamp(v[0], min[0], max[0]), 
                       clamp(v[1], min[1], max[1]), 
                       clamp(v[2], min[2], max[2]));
    }

    //
    // @region: Operators overloading
    //

    inline const uint4x4& operator+(const uint4x4& m)
    {
        return m;
    }

    inline uint4x4& operator--(uint4x4& m)
    {
        --m[0];
        --m[1];
        --m[2];
        --m[3];
        return m;
    }

    inline uint4x4& operator++(uint4x4& m)
    {
        ++m[0];
        ++m[1];
        ++m[2];
        ++m[3];
        return m;
    }

    inline const uint4x4& operator--(uint4x4& m, int)
    {
        m[0]--;
        m[1]--;
        m[2]--;
        m[3]--;
        return m;
    }

    inline const uint4x4& operator++(uint4x4& m, int)
    {
        m[0]++;
        m[1]++;
        m[2]++;
        m[3]++;
        return m;
    }

    inline uint4x4 operator+(const uint4x4& a, const uint4x4& b)
    {
        uint4x4 result;
        result[0] = a[0] + b[0];
        result[1] = a[1] + b[1];
        result[2] = a[2] + b[2];
        result[3] = a[3] + b[3];
        return result;
    }

    inline uint4x4 operator+(const uint4x4& a, uint b)
    {
        uint4x4 result;
        result[0] = a[0] + b;
        result[1] = a[1] + b;
        result[2] = a[2] + b;
        result[3] = a[3] + b;
        return result;
    }

    inline uint4x4 operator+(uint a, const uint4x4& b)
    {
        uint4x4 result;
        result[0] = a + b[0];
        result[1] = a + b[1];
        result[2] = a + b[2];
        result[3] = a + b[3];
        return result;
    }

    inline uint4x4 operator-(const uint4x4& a, const uint4x4& b)
    {
        uint4x4 result;
        result[0] = a[0] - b[0];
        result[1] = a[1] - b[1];
        result[2] = a[2] - b[2];
        result[3] = a[3] - b[3];
        return result;
    }

    inline uint4x4 operator-(const uint4x4& a, uint b)
    {
        uint4x4 result;
        result[0] = a[0] - b;
        result[1] = a[1] - b;
        result[2] = a[2] - b;
        result[3] = a[3] - b;
        return result;
    }

    inline uint4x4 operator-(uint a, const uint4x4& b)
    {
        uint4x4 result;
        result[0] = a - b[0];
        result[1] = a - b[1];
        result[2] = a - b[2];
        result[3] = a - b[3];
        return result;
    }

    inline uint4x4 operator*(const uint4x4& a, const uint4x4& b)
    {
        uint4x4 result;
        result[0] = a[0] * b[0];
        result[1] = a[1] * b[1];
        result[2] = a[2] * b[2];
        result[3] = a[3] * b[3];
        return result;
    }

    inline uint4x4 operator*(const uint4x4& a, uint b)
    {
        uint4x4 result;
        result[0] = a[0] * b;
        result[1] = a[1] * b;
        result[2] = a[2] * b;
        result[3] = a[3] * b;
        return result;
    }

    inline uint4x4 operator*(uint a, const uint4x4& b)
    {
        uint4x4 result;
        result[0] = a * b[0];
        result[1] = a * b[1];
        result[2] = a * b[2];
        result[3] = a * b[3];
        return result;
    }

    inline uint4x4 operator/(const uint4x4& a, const uint4x4& b)
    {
        uint4x4 result;
        result[0] = a[0] / b[0];
        result[1] = a[1] / b[1];
        result[2] = a[2] / b[2];
        result[3] = a[3] / b[3];
        return result;
    }

    inline uint4x4 operator/(const uint4x4& a, uint b)
    {
        uint4x4 result;
        result[0] = a[0] / b;
        result[1] = a[1] / b;
        result[2] = a[2] / b;
        result[3] = a[3] / b;
        return result;
    }

    inline uint4x4 operator/(int a, const uint4x4& b)
    {
        uint4x4 result;
        result[0] = a / b[0];
        result[1] = a / b[1];
        result[2] = a / b[2];
        result[3] = a / b[3];
        return result;
    }

    inline uint4x4& operator+=(uint4x4& a, const uint4x4& b)
    {
        return (a = a + b);
    }

    inline uint4x4& operator+=(uint4x4& a, uint b)
    {
        return (a = a + b);
    }

    inline uint4x4& operator-=(uint4x4& a, const uint4x4& b)
    {
        return (a = a - b);
    }

    inline uint4x4& operator-=(uint4x4& a, uint b)
    {
        return (a = a - b);
    }

    inline uint4x4& operator*=(uint4x4& a, const uint4x4& b)
    {
        return (a = a * b);
    }

    inline uint4x4& operator*=(uint4x4& a, uint b)
    {
        return (a = a * b);
    }

    inline uint4x4& operator/=(uint4x4& a, const uint4x4& b)
    {
        return (a = a / b);
    }

    inline uint4x4& operator/=(uint4x4& a, uint b)
    {
        return (a = a + b);
    }

    inline bool4x4 operator==(const uint4x4& a, const uint4x4& b)
    {
        bool4x4 result;
        result[0] = a[0] == b[0];
        result[1] = a[1] == b[1];
        result[2] = a[2] == b[2];
        result[3] = a[3] == b[3];
        return result;
    }

    inline bool4x4 operator!=(const uint4x4& a, const uint4x4& b)
    {
        bool4x4 result;
        result[0] = a[0] != b[0];
        result[1] = a[1] != b[1];
        result[2] = a[2] != b[2];
        result[3] = a[3] != b[3];
        return result;
    }

    inline bool4x4 operator<(const uint4x4& a, const uint4x4& b)
    {
        bool4x4 result;
        result[0] = a[0] < b[0];
        result[1] = a[1] < b[1];
        result[2] = a[2] < b[2];
        result[3] = a[3] < b[3];
        return result;
    }

    inline bool4x4 operator>(const uint4x4& a, const uint4x4& b)
    {
        bool4x4 result;
        result[0] = a[0] > b[0];
        result[1] = a[1] > b[1];
        result[2] = a[2] > b[2];
        result[3] = a[3] > b[3];
        return result;
    }

    inline bool4x4 operator<=(const uint4x4& a, const uint4x4& b)
    {
        bool4x4 result;
        result[0] = a[0] <= b[0];
        result[1] = a[1] <= b[1];
        result[2] = a[2] <= b[2];
        result[3] = a[3] <= b[3];
        return result;
    }

    inline bool4x4 operator>=(const uint4x4& a, const uint4x4& b)
    {
        bool4x4 result;
        result[0] = a[0] >= b[0];
        result[1] = a[1] >= b[1];
        result[2] = a[2] >= b[2];
        result[3] = a[3] >= b[3];
        return result;
    }

    //
    // @region: Common functions
    //

    /* Get the smaller value
     */
    inline uint4x4 min(const uint4x4& a, const uint4x4& b)
    {
        return uint4x4(min(a[0], b[0]),
                       min(a[1], b[1]),
                       min(a[2], b[2]),
                       min(a[3], b[3]));
    }

    /* Get the larger value
     */
    inline uint4x4 max(const uint4x4& a, const uint4x4& b)
    {
        return uint4x4(max(a[0], b[0]), 
                       max(a[1], b[1]),
                       max(a[2], b[2]),
                       max(a[3], b[3]));
    }

    /* Clamps the 'x' value to the [min, max].
     */
    inline uint4x4 clamp(const uint4x4& v, const uint4x4& min, const uint4x4& max)
    {
        return uint4x4(clamp(v[0], min[0], max[0]), 
                       clamp(v[1], min[1], max[1]), 
                       clamp(v[2], min[2], max[2]), 
                       clamp(v[3], min[3], max[3]));
    }

    //
    // @region: Common functions
    //

    /* Computes sign of 'x'
     */
    inline int2x2 sign(const float2x2& m)
    {
        return int2x2(sign(m[0]),
                      sign(m[1]));
    }

    /* Computes absolute value
     */
    inline float2x2 abs(const float2x2& m)
    {
        return float2x2(abs(m[0]),
                        abs(m[1]));
    }

    /* Computes cosine
     */
    inline float2x2 cos(const float2x2& m)
    {
        return float2x2(cos(m[0]),
                        cos(m[1]));
    }

    /* Computes sine
     */
    inline float2x2 sin(const float2x2& m)
    {
        return float2x2(sin(m[0]),
                        sin(m[1]));
    }

    /* Computes tangent
     */
    inline float2x2 tan(const float2x2& m)
    {
        return float2x2(tan(m[0]),
                        tan(m[1]));
    }

    /* Computes hyperbolic cosine
     */
    inline float2x2 cosh(const float2x2& m)
    {
        return float2x2(cosh(m[0]),
                        cosh(m[1]));
    }

    /* Computes hyperbolic sine
     */
    inline float2x2 sinh(const float2x2& m)
    {
        return float2x2(sinh(m[0]),
                        sinh(m[1]));
    }

    /* Computes hyperbolic tangent
     */
    inline float2x2 tanh(const float2x2& m)
    {
        return float2x2(tanh(m[0]),
                        tanh(m[1]));
    }

    /* Computes inverse cosine
     */
    inline float2x2 acos(const float2x2& m)
    {
        return float2x2(acos(m[0]),
                        acos(m[1]));
    }

    /* Computes inverse sine
     */
    inline float2x2 asin(const float2x2& m)
    {
        return float2x2(asin(m[0]),
                        asin(m[1]));
    }

    /* Computes inverse tangent
     */
    inline float2x2 atan(const float2x2& m)
    {
        return float2x2(atan(m[0]),
                        atan(m[1]));
    }

    /* Computes inverse tangent with 2 args
     */
    inline float2x2 atan2(const float2x2& y, const float2x2& x)
    {
        return float2x2(atan2(y[0], x[0]),
                        atan2(y[1], x[1]));
    }

    /* Computes Euler number raised to the power 'x'
     */
    inline float2x2 exp(const float2x2& m)
    {
        return float2x2(exp(m[0]),
                        exp(m[1]));
    }

    /* Computes 2 raised to the power 'x'
     */
    inline float2x2 exp2(const float2x2& m)
    {
        return float2x2(exp2(m[0]),
                        exp2(m[1]));
    }

    /* Computes the base Euler number logarithm
     */
    inline float2x2 log(const float2x2& m)
    {
        return float2x2(log(m[0]),
                        log(m[1]));
    }

    /* Computes the base 2 logarithm
     */
    inline float2x2 log2(const float2x2& m)
    {
        return float2x2(log2(m[0]),
                        log2(m[1]));
    }

    /* Computes the base 10 logarithm
     */
    inline float2x2 log10(const float2x2& m)
    {
        return float2x2(log10(m[0]),
                        log10(m[1]));
    }

    /* Computes the value of base raised to the power exponent
     */
    inline float2x2 pow(const float2x2& x, const float2x2& y)
    {
        return float2x2(pow(x[0], y[0]),
                        pow(x[1], y[1]));
    }

    /* Get the fractal part of floating point
     */
    inline float2x2 frac(const float2x2& m)
    {
        return float2x2(frac(m[0]),
                        frac(m[1]));
    }

    /* Computes the floating-point remainder of the division operation x/y
     */
    inline float2x2 fmod(const float2x2& a, const float2x2& b)
    {
        return float2x2(fmod(a[0], b[0]),
                        fmod(a[1], b[1]));
    }

    /* Computes the smallest integer value not less than 'x'
     */
    inline float2x2 ceil(const float2x2& m)
    {
        return float2x2(ceil(m[0]),
                        ceil(m[0]));
    }

    /* Computes the largest integer value not greater than 'x'
     */
    inline float2x2 floor(const float2x2& m)
    {
        return float2x2(floor(m[0]),
                        floor(m[1]));
    }

    /* Computes the nearest integer value
     */
    inline float2x2 round(const float2x2& m)
    {
        return float2x2(round(m[0]),
                        round(m[1]));
    }

    /* Computes the nearest integer not greater in magnitude than 'x'
     */
    inline float2x2 trunc(const float2x2& m)
    {
        return float2x2(trunc(m[0]),
                        trunc(m[1]));
    }

    /* Get the smaller value
     */
    inline float2x2 min(const float2x2& a, const float2x2& b)
    {
        return float2x2(min(a[0], b[0]),
                        min(a[1], b[1]));
    }

    /* Get the larger value
     */
    inline float2x2 max(const float2x2& a, const float2x2& b)
    {
        return float2x2(max(a[0], b[0]), 
                        max(a[1], b[1]));
    }

    /* Clamps the 'x' value to the [min, max].
     */
    inline float2x2 clamp(const float2x2& m, const float2x2& min, const float2x2& max)
    {
        return float2x2(clamp(m[0], min[0], max[0]), 
                        clamp(m[1], min[1], max[1]));
    }

    /* Clamps the specified value within the range of 0 to 1
     */
    inline float2x2 saturate(const float2x2& m)
    {
        return float2x2(saturate(m[0]),
                        saturate(m[1]));
    }

    /* Compares two values, returning 0 or 1 based on which value is greater.
     */
    inline float2x2 step(const float2x2& a, const float2x2& b)
    {
        return float2x2(step(a[0], b[0]),
                        step(a[1], b[1]));
    }

    /* Performs a linear interpolation.
     */
    inline float2x2 lerp(const float2x2& a, const float2x2& b, const float2x2& t)
    {
        return float2x2(lerp(a[0], b[0], t[0]),
                        lerp(a[1], b[1], t[1]));
    }

    /* Performs a linear interpolation.
     */
    inline float2x2 lerp(const float2x2& a, const float2x2& b, float t)
    {
        return float2x2(lerp(a[0], b[0], t),
                        lerp(a[1], b[1], t));
    }

    /* Compute a smooth Hermite interpolation
     */
    inline float2x2 smoothstep(const float2x2& a, const float2x2& b, const float2x2& t)
    {
        return float2x2(smoothstep(a[0], b[0], t[0]),
                        smoothstep(a[1], b[1], t[1]));
    }

    /* Computes square root of 'x'.
     */
    inline float2x2 sqrt(const float2x2& m)
    {
        return float2x2(sqrt(m[0]),
                        sqrt(m[1]));
    }

    /* Computes inverse square root of 'x'.
     */
    inline float2x2 rsqrt(const float2x2& m)
    {
        return float2x2(rsqrt(m[0]),
                        rsqrt(m[1]));
    }

    /* Computes fast inverse square root of 'x'.
     */
    inline float2x2 fsqrt(const float2x2& m)
    {
        return float2x2(fsqrt(m[0]),
                        fsqrt(m[1]));
    }

    /* Computes fast inverse square root of 'x'.
     */
    inline float2x2 frsqrt(const float2x2& m)
    {
        return float2x2(frsqrt(m[0]),
                        frsqrt(m[1]));
    }

    //
    // @region: matrix operations
    //

    inline float2x2 inverse(const float2x2& m)
    {
        const float det = m[0][0] * m[1][1] - m[0][1] * m[1][0];
        if (det == 0.0f)
        {
            return m;
        }
        else
        {
            const float idet = 1.0f / det;

            return float2x2(
                idet *   m[1][1] , idet * (-m[0][1]),
                idet * (-m[1][0]), idet *   m[0][0]
            );
        }
    }

    inline float2x2 transpose(const float2x2& m)
    {
        return float2x2(
            m[0][0], m[1][0],
            m[0][1], m[1][1]
        );
    }

    inline float2 mul(const float2x2& a, const float2& b)
    {
        return float2(
            a[0][0] * b[0] + a[1][0] * b[1],
            a[0][1] * b[0] + a[1][1] * b[1]
        );
    }

    inline float2 mul(const float2& a, const float2x2& b)
    {
        return float2(
            a[0] * b[0][0] + a[1] * b[0][1],
            a[0] * b[1][0] + a[1] * b[1][1]
        );
    }

    inline float2x2 mul(const float2x2& a, const float2x2& b)
    {
        return float2x2(
            mul(a, b[0]),
            mul(a, b[1])
        );
    }

    //
    // @region: Common functions
    //

    /* Computes sign of 'x'
     */
    inline int3x3 sign(const float3x3& m)
    {
        return int3x3(sign(m[0]),
                      sign(m[1]),
                      sign(m[2]));
    }

    /* Computes absolute value
     */
    inline float3x3 abs(const float3x3& m)
    {
        return float3x3(abs(m[0]),
                        abs(m[1]),
                        abs(m[2]));
    }

    /* Computes cosine
     */
    inline float3x3 cos(const float3x3& m)
    {
        return float3x3(cos(m[0]),
                        cos(m[1]),
                        cos(m[2]));
    }

    /* Computes sine
     */
    inline float3x3 sin(const float3x3& m)
    {
        return float3x3(sin(m[0]),
                        sin(m[1]),
                        sin(m[2]));
    }

    /* Computes tangent
     */
    inline float3x3 tan(const float3x3& m)
    {
        return float3x3(tan(m[0]),
                        tan(m[1]),
                        tan(m[2]));
    }

    /* Computes hyperbolic cosine
     */
    inline float3x3 cosh(const float3x3& m)
    {
        return float3x3(cosh(m[0]),
                        cosh(m[1]),
                        cosh(m[2]));
    }

    /* Computes hyperbolic sine
     */
    inline float3x3 sinh(const float3x3& m)
    {
        return float3x3(sinh(m[0]),
                        sinh(m[1]),
                        sinh(m[2]));
    }

    /* Computes hyperbolic tangent
     */
    inline float3x3 tanh(const float3x3& m)
    {
        return float3x3(tanh(m[0]),
                        tanh(m[1]),
                        tanh(m[2]));
    }

    /* Computes inverse cosine
     */
    inline float3x3 acos(const float3x3& m)
    {
        return float3x3(acos(m[0]),
                        acos(m[1]),
                        acos(m[2]));
    }

    /* Computes inverse sine
     */
    inline float3x3 asin(const float3x3& m)
    {
        return float3x3(asin(m[0]),
                        asin(m[1]),
                        asin(m[2]));
    }

    /* Computes inverse tangent
     */
    inline float3x3 atan(const float3x3& m)
    {
        return float3x3(atan(m[0]),
                        atan(m[1]),
                        asin(m[2]));
    }

    /* Computes inverse tangent with 2 args
     */
    inline float3x3 atan2(const float3x3& a, const float3x3& b)
    {
        return float3x3(atan2(a[0], b[0]),
                        atan2(a[1], b[1]),
                        atan2(a[2], b[2]));
    }

    /* Computes Euler number raised to the power 'x'
     */
    inline float3x3 exp(const float3x3& m)
    {
        return float3x3(exp(m[0]),
                        exp(m[1]),
                        exp(m[2]));
    }

    /* Computes 2 raised to the power 'x'
     */
    inline float3x3 exp2(const float3x3& m)
    {
        return float3x3(exp2(m[0]),
                        exp2(m[1]),
                        exp2(m[2]));
    }

    /* Computes the base Euler number logarithm
     */
    inline float3x3 log(const float3x3& m)
    {
        return float3x3(log(m[0]),
                        log(m[1]),
                        log(m[2]));
    }

    /* Computes the base 2 logarithm
     */
    inline float3x3 log2(const float3x3& m)
    {
        return float3x3(log2(m[0]),
                        log2(m[1]),
                        log2(m[2]));
    }

    /* Computes the base 10 logarithm
     */
    inline float3x3 log10(const float3x3& m)
    {
        return float3x3(log10(m[0]),
                        log10(m[1]),
                        log10(m[2]));
    }

    /* Computes the value of base raised to the power exponent
     */
    inline float3x3 pow(const float3x3& a, const float3x3& b)
    {
        return float3x3(pow(a[0], b[0]),
                        pow(a[1], b[1]),
                        pow(a[2], b[2]));
    }

    /* Get the fractal part of floating point
     */
    inline float3x3 frac(const float3x3& v)
    {
        return float3x3(frac(v[0]),
                        frac(v[1]),
                        frac(v[2]));
    }

    /* Computes the floating-point remainder of the division operation x/y
     */
    inline float3x3 fmod(const float3x3& a, const float3x3& b)
    {
        return float3x3(fmod(a[0], b[0]),
                        fmod(a[1], b[1]),
                        fmod(a[2], b[2]));
    }

    /* Computes the smallest integer value not less than 'x'
     */
    inline float3x3 ceil(const float3x3& m)
    {
        return float3x3(ceil(m[0]),
                        ceil(m[1]),
                        ceil(m[2]));
    }

    /* Computes the largest integer value not greater than 'x'
     */
    inline float3x3 floor(const float3x3& m)
    {
        return float3x3(floor(m[0]),
                        floor(m[1]),
                        floor(m[2]));
    }

    /* Computes the nearest integer value
     */
    inline float3x3 round(const float3x3& m)
    {
        return float3x3(round(m[0]),
                        round(m[1]),
                        round(m[2]));
    }

    /* Computes the nearest integer not greater in magnitude than 'x'
     */
    inline float3x3 trunc(const float3x3& m)
    {
        return float3x3(trunc(m[0]),
                        trunc(m[1]),
                        trunc(m[2]));
    }

    /* Get the smaller value
     */
    inline float3x3 min(const float3x3& a, const float3x3& b)
    {
        return float3x3(min(a[0], b[0]),
                        min(a[1], b[1]),
                        min(a[2], b[2]));
    }

    /* Get the larger value
     */
    inline float3x3 max(const float3x3& a, const float3x3& b)
    {
        return float3x3(max(a[0], b[0]), 
                        max(a[1], b[1]),
                        max(a[2], b[2]));
    }

    /* Clamps the 'x' value to the [min, max].
     */
    inline float3x3 clamp(const float3x3& v, const float3x3& min, const float3x3& max)
    {
        return float3x3(clamp(v[0], min[0], max[0]), 
                        clamp(v[1], min[1], max[1]), 
                        clamp(v[2], min[2], max[2]));
    }

    /* Clamps the specified value within the range of 0 to 1
     */
    inline float3x3 saturate(const float3x3& m)
    {
        return float3x3(saturate(m[0]),
                        saturate(m[1]),
                        saturate(m[2]));
    }

    /* Compares two values, returning 0 or 1 based on which value is greater.
     */
    inline float3x3 step(const float3x3& a, const float3x3& b)
    {
        return float3x3(step(a[0], b[0]),
                        step(a[1], b[1]),
                        step(a[2], b[2]));
    }

    /* Performs a linear interpolation.
     */
    inline float3x3 lerp(const float3x3& a, const float3x3& b, const float3x3& t)
    {
        return float3x3(lerp(a[0], b[0], t[0]),
                        lerp(a[1], b[1], t[1]), 
                        lerp(a[2], b[2], t[2]));
    }

    /* Performs a linear interpolation.
     */
    inline float3x3 lerp(const float3x3& a, const float3x3& b, float t)
    {
        return float3x3(lerp(a[0], b[0], t),
                        lerp(a[1], b[1], t), 
                        lerp(a[2], b[2], t));
    }

    /* Compute a smooth Hermite interpolation
     */
    inline float3x3 smoothstep(const float3x3& a, const float3x3& b, const float3x3& t)
    {
        return float3x3(smoothstep(a[0], b[0], t[0]),
                        smoothstep(a[1], b[1], t[1]),
                        smoothstep(a[2], b[2], t[2]));
    }

    /* Computes square root of 'x'.
     */
    inline float3x3 sqrt(const float3x3& m)
    {
        return float3x3(sqrt(m[0]),
                        sqrt(m[1]),
                        sqrt(m[2]));
    }

    /* Computes inverse square root of 'x'.
     */
    inline float3x3 rsqrt(const float3x3& m)
    {
        return float3x3(rsqrt(m[0]),
                        rsqrt(m[1]),
                        rsqrt(m[2]));
    }

    /* Computes fast inverse square root of 'x'.
     */
    inline float3x3 fsqrt(const float3x3& m)
    {
        return float3x3(fsqrt(m[0]),
                        fsqrt(m[1]),
                        fsqrt(m[2]));
    }

    /* Computes fast inverse square root of 'x'.
     */
    inline float3x3 frsqrt(const float3x3& m)
    {
        return float3x3(frsqrt(m[0]),
                        frsqrt(m[1]),
                        frsqrt(m[2]));
    }

    //
    // @region: Matrix operations
    //

    inline float3x3 transpose(const float3x3& m)
    {
        return float3x3(
            m[0][0], m[1][0], m[2][0],
            m[0][1], m[1][1], m[2][1],
            m[0][2], m[1][2], m[2][2]
        );
    }

    inline float3 mul(const float3x3& a, const float3& b)
    {
        const float3 a0 = float3(a[0][0], a[1][0], a[2][0]);
        const float3 a1 = float3(a[0][1], a[1][1], a[2][1]);
        const float3 a2 = float3(a[0][2], a[1][2], a[2][2]);

        return float3(
            dot(a0, b),
            dot(a1, b),
            dot(a2, b)
        );
    }

    inline float3 mul(const float3& a, const float3x3& b)
    {
        return float3(
            dot(a, b[0]),
            dot(a, b[1]),
            dot(a, b[2])
        );
    }

    inline float3x3 mul(const float3x3& a, const float3x3& b)
    {
        return float3x3(
            mul(a, b[0]),
            mul(a, b[1]),
            mul(a, b[2])
        );
    }

    inline float3x3 inverse(const float3x3& m)
    {
        const float det = 
              m[0][0] * m[1][1] * m[2][2] - m[0][0] * m[1][2] * m[2][1]
            + m[0][1] * m[1][0] * m[2][2] - m[0][1] * m[1][2] * m[2][0]
            + m[0][2] * m[1][0] * m[2][1] - m[0][2] * m[1][1] * m[2][0];
        if (det == 0.0f)
        {
            return m;
        }
        else
        {
            const float idet = 1.0f / det;

            return float3x3(
                idet * (m[1][1] * m[2][2] - m[1][2] * m[2][1]),
                idet * (m[0][2] * m[2][1] - m[0][1] * m[2][2]),
                idet * (m[0][1] * m[1][2] - m[0][2] * m[1][1]),

                idet * (m[1][2] * m[2][0] - m[1][0] * m[2][2]),
                idet * (m[0][0] * m[2][2] - m[0][2] * m[2][0]),
                idet * (m[0][2] * m[1][0] - m[0][0] * m[1][2]),

                idet * (m[1][0] * m[2][1] - m[1][1] * m[2][0]),
                idet * (m[0][1] * m[2][0] - m[0][0] * m[2][1]),
                idet * (m[0][0] * m[1][1] - m[0][1] * m[1][0])
            );
        }
    }

    //
    // @region: Common functions
    //

    /* Computes sign of 'x'
     */
    inline int4x4 sign(const float4x4& m)
    {
        return int4x4(sign(m[0]),
                      sign(m[1]),
                      sign(m[2]),
                      sign(m[3]));
    }

    /* Computes absolute value
     */
    inline float4x4 abs(const float4x4& m)
    {
        return float4x4(abs(m[0]),
                        abs(m[1]),
                        abs(m[2]),
                        abs(m[3]));
    }

    /* Computes cosine
     */
    inline float4x4 cos(const float4x4& m)
    {
        return float4x4(cos(m[0]),
                        cos(m[1]),
                        cos(m[2]),
                        cos(m[3]));
    }

    /* Computes sine
     */
    inline float4x4 sin(const float4x4& m)
    {
        return float4x4(sin(m[0]),
                        sin(m[1]),
                        sin(m[2]),
                        sin(m[3]));
    }

    /* Computes tangent
     */
    inline float4x4 tan(const float4x4& m)
    {
        return float4x4(tan(m[0]),
                        tan(m[1]),
                        tan(m[2]),
                        tan(m[3]));
    }

    /* Computes hyperbolic cosine
     */
    inline float4x4 cosh(const float4x4& m)
    {
        return float4x4(cosh(m[0]),
                        cosh(m[1]),
                        cosh(m[2]),
                        cosh(m[3]));
    }

    /* Computes hyperbolic sine
     */
    inline float4x4 sinh(const float4x4& m)
    {
        return float4x4(sinh(m[0]),
                        sinh(m[1]),
                        sinh(m[2]),
                        sinh(m[3]));
    }

    /* Computes hyperbolic tangent
     */
    inline float4x4 tanh(const float4x4& m)
    {
        return float4x4(tanh(m[0]),
                        tanh(m[1]),
                        tanh(m[2]),
                        tanh(m[3]));
    }

    /* Computes inverse cosine
     */
    inline float4x4 acos(const float4x4& m)
    {
        return float4x4(acos(m[0]),
                        acos(m[1]),
                        acos(m[2]),
                        acos(m[3]));
    }

    /* Computes inverse sine
     */
    inline float4x4 asin(const float4x4& m)
    {
        return float4x4(asin(m[0]),
                        asin(m[1]),
                        asin(m[2]),
                        asin(m[3]));
    }

    /* Computes inverse tangent
     */
    inline float4x4 atan(const float4x4& m)
    {
        return float4x4(atan(m[0]),
                        atan(m[1]),
                        atan(m[2]),
                        atan(m[3]));
    }

    /* Computes inverse tangent with 2 args
     */
    inline float4x4 atan2(const float4x4& a, const float4x4& b)
    {
        return float4x4(atan2(a[0], b[0]),
                        atan2(a[1], b[1]),
                        atan2(a[2], b[2]),
                        atan2(a[3], b[3]));
    }

    /* Computes Euler number raised to the power 'x'
     */
    inline float4x4 exp(const float4x4& m)
    {
        return float4x4(exp(m[0]),
                        exp(m[1]),
                        exp(m[2]),
                        exp(m[3]));
    }

    /* Computes 2 raised to the power 'x'
     */
    inline float4x4 exp2(const float4x4& m)
    {
        return float4x4(exp2(m[0]),
                        exp2(m[1]),
                        exp2(m[2]),
                        exp2(m[3]));
    }

    /* Computes the base Euler number logarithm
     */
    inline float4x4 log(const float4x4& m)
    {
        return float4x4(log(m[0]),
                        log(m[1]),
                        log(m[2]),
                        log(m[3]));
    }

    /* Computes the base 2 logarithm
     */
    inline float4x4 log2(const float4x4& m)
    {
        return float4x4(log2(m[0]),
                        log2(m[1]),
                        log2(m[2]),
                        log2(m[3]));
    }

    /* Computes the base 10 logarithm
     */
    inline float4x4 log10(const float4x4& m)
    {
        return float4x4(log10(m[0]),
                        log10(m[1]),
                        log10(m[2]),
                        log10(m[3]));
    }

    /* Computes the value of base raised to the power exponent
     */
    inline float4x4 pow(const float4x4& a, const float4x4& b)
    {
        return float4x4(pow(a[0], b[0]),
                        pow(a[1], b[1]),
                        pow(a[2], b[2]),
                        pow(a[3], b[3]));
    }

    /* Get the fractal part of floating point
     */
    inline float4x4 frac(const float4x4& m)
    {
        return float4x4(frac(m[0]),
                        frac(m[1]),
                        frac(m[2]),
                        frac(m[3]));
    }

    /* Computes the floating-point remainder of the division operation x/y
     */
    inline float4x4 fmod(const float4x4& a, const float4x4& b)
    {
        return float4x4(fmod(a[0], b[0]),
                        fmod(a[1], b[1]),
                        fmod(a[2], b[2]),
                        fmod(a[3], b[3]));
    }

    /* Computes the smallest integer value not less than 'x'
     */
    inline float4x4 ceil(const float4x4& m)
    {
        return float4x4(ceil(m[0]),
                        ceil(m[1]),
                        ceil(m[2]),
                        ceil(m[3]));
    }

    /* Computes the largest integer value not greater than 'x'
     */
    inline float4x4 floor(const float4x4& m)
    {
        return float4x4(floor(m[0]),
                        floor(m[1]),
                        floor(m[2]),
                        floor(m[3]));
    }

    /* Computes the nearest integer value
     */
    inline float4x4 round(const float4x4& m)
    {
        return float4x4(round(m[0]),
                        round(m[1]),
                        round(m[2]),
                        round(m[3]));
    }

    /* Computes the nearest integer not greater in magnitude than 'x'
     */
    inline float4x4 trunc(const float4x4& m)
    {
        return float4x4(trunc(m[0]),
                        trunc(m[1]),
                        trunc(m[2]),
                        trunc(m[3]));
    }

    /* Get the smaller value
     */
    inline float4x4 min(const float4x4& a, const float4x4& b)
    {
        return float4x4(min(a[0], b[0]),
                        min(a[1], b[1]),
                        min(a[2], b[2]),
                        min(a[3], b[3]));
    }

    /* Get the larger value
     */
    inline float4x4 max(const float4x4& a, const float4x4& b)
    {
        return float4x4(max(a[0], b[0]), 
                        max(a[1], b[1]),
                        max(a[2], b[2]),
                        max(a[3], b[3]));
    }

    /* Clamps the 'x' value to the [min, max].
     */
    inline float4x4 clamp(const float4x4& v, const float4x4& min, const float4x4& max)
    {
        return float4x4(clamp(v[0], min[0], max[0]), 
                        clamp(v[1], min[1], max[1]), 
                        clamp(v[2], min[2], max[2]), 
                        clamp(v[3], min[3], max[3]));
    }

    /* Clamps the specified value within the range of 0 to 1
     */
    inline float4x4 saturate(const float4x4& m)
    {
        return float4x4(saturate(m[0]),
                        saturate(m[1]),
                        saturate(m[2]),
                        saturate(m[3]));
    }

    /* Compares two values, returning 0 or 1 based on which value is greater.
     */
    inline float4x4 step(const float4x4& a, const float4x4& b)
    {
        return float4x4(step(a[0], b[0]),
                        step(a[1], b[1]),
                        step(a[2], b[2]),
                        step(a[3], b[3]));
    }

    /* Performs a linear interpolation.
     */
    inline float4x4 lerp(const float4x4& a, const float4x4& b, const float4x4& t)
    {
        return float4x4(lerp(a[0], b[0], t[0]),
                        lerp(a[1], b[1], t[1]), 
                        lerp(a[2], b[2], t[2]), 
                        lerp(a[3], b[3], t[3]));
    }

    /* Performs a linear interpolation.
     */
    inline float4x4 lerp(const float4x4& a, const float4x4& b, float t)
    {
        return float4x4(lerp(a[0], b[0], t),
                        lerp(a[1], b[1], t), 
                        lerp(a[2], b[2], t), 
                        lerp(a[3], b[3], t));
    }

    /* Compute a smooth Hermite interpolation
     */
    inline float4x4 smoothstep(const float4x4& a, const float4x4& b, const float4x4& t)
    {
        return float4x4(smoothstep(a[0], b[0], t[0]),
                        smoothstep(a[1], b[1], t[1]),
                        smoothstep(a[2], b[2], t[2]),
                        smoothstep(a[3], b[3], t[3]));
    }

    /* Computes square root of 'x'.
     */
    inline float4x4 sqrt(const float4x4& m)
    {
        return float4x4(sqrt(m[0]),
                        sqrt(m[1]),
                        sqrt(m[2]),
                        sqrt(m[3]));
    }

    /* Computes inverse square root of 'x'.
     */
    inline float4x4 rsqrt(const float4x4& m)
    {
        return float4x4(rsqrt(m[0]),
                        rsqrt(m[1]),
                        rsqrt(m[2]),
                        rsqrt(m[3]));
    }

    /* Computes fast inverse square root of 'x'.
     */
    inline float4x4 fsqrt(const float4x4& m)
    {
        return float4x4(fsqrt(m[0]),
                        fsqrt(m[1]),
                        fsqrt(m[2]),
                        fsqrt(m[3]));
    }

    /* Computes fast inverse square root of 'x'.
     */
    inline float4x4 frsqrt(const float4x4& m)
    {
        return float4x4(frsqrt(m[0]),
                        frsqrt(m[1]),
                        frsqrt(m[2]),
                        frsqrt(m[3]));
    }

    //
    // @region: Matrix operations
    //

    inline float4 mul(const float4x4& a, const float4& b)
    {
        const float4 c0 = float4(a[0][0], a[1][0], a[2][0], a[3][0]);
        const float4 c1 = float4(a[0][1], a[1][1], a[2][1], a[3][1]);
        const float4 c2 = float4(a[0][2], a[1][2], a[2][2], a[3][2]);
        const float4 c3 = float4(a[0][3], a[1][3], a[2][3], a[3][3]);

        return float4(
            dot(c0, b),
            dot(c1, b),
            dot(c2, b),
            dot(c3, b)
        );
    }

    inline float4 mul(const float4& a, const float4x4& b)
    {
        return float4(
            dot(a, b[0]),
            dot(a, b[1]),
            dot(a, b[2]),
            dot(a, b[3])
        );
    }

    inline float3 mul(const float4x4& a, const float3& b)
    {
        const float4 b0 = float4(b.x, b.y, b.z, 1.0f);
        const float4 b1 = mul(a, b0);

        const float iw = 1.0f / b1.w;
        return float3(b1.x * iw, b1.y * iw, b1.z * iw);
    }

    inline float3 mul(const float3& a, const float4x4& b)
    {
        const float4 a0 = float4(a.x, a.y, a.z, 1.0f);
        const float4 a1 = mul(a0, b);

        const float iw = 1.0f / a1.w;
        return float3(a1.x * iw, a1.y * iw, a1.z * iw);
    }

    inline float4x4 mul(const float4x4& a, const float4x4& b)
    {
        float4x4 result;
        result[0] = mul(a, b[0]);
        result[1] = mul(a, b[1]);
        result[2] = mul(a, b[2]);
        result[3] = mul(a, b[3]);
        return result;
    }

    inline float4x4 transpose(const float4x4& m)
    {
        float4x4 result;
        result[0][0] = m[0][0]; result[0][1] = m[1][0]; result[0][2] = m[2][0]; result[0][3] = m[3][0];
        result[1][0] = m[0][1]; result[1][1] = m[1][1]; result[1][2] = m[2][1]; result[1][3] = m[3][1];
        result[2][0] = m[0][2]; result[2][1] = m[1][2]; result[2][2] = m[2][2]; result[2][3] = m[3][2];
        result[3][0] = m[0][3]; result[3][1] = m[1][3]; result[3][2] = m[2][3]; result[3][3] = m[3][3];
        return result;
    }

    inline float4x4 inverse(const float4x4& m)
    {
        const float n11 = m[0][0], n12 = m[1][0], n13 = m[2][0], n14 = m[3][0];
        const float n21 = m[0][1], n22 = m[1][1], n23 = m[2][1], n24 = m[3][1];
        const float n31 = m[0][2], n32 = m[1][2], n33 = m[2][2], n34 = m[3][2];
        const float n41 = m[0][3], n42 = m[1][3], n43 = m[2][3], n44 = m[3][3];

        const float t11 = n23 * n34 * n42 - n24 * n33 * n42 + n24 * n32 * n43 - n22 * n34 * n43 - n23 * n32 * n44 + n22 * n33 * n44;
        const float t12 = n14 * n33 * n42 - n13 * n34 * n42 - n14 * n32 * n43 + n12 * n34 * n43 + n13 * n32 * n44 - n12 * n33 * n44;
        const float t13 = n13 * n24 * n42 - n14 * n23 * n42 + n14 * n22 * n43 - n12 * n24 * n43 - n13 * n22 * n44 + n12 * n23 * n44;
        const float t14 = n14 * n23 * n32 - n13 * n24 * n32 - n14 * n22 * n33 + n12 * n24 * n33 + n13 * n22 * n34 - n12 * n23 * n34;

        const float det = n11 * t11 + n21 * t12 + n31 * t13 + n41 * t14;
        if (det < 0.0f)
        {
            return float4x4(0.0f);
        }

        const float idet = 1.0f / det;
        float4x4 result;

        result[0][0] = t11 * idet;
        result[0][1] = (n24 * n33 * n41 - n23 * n34 * n41 - n24 * n31 * n43 + n21 * n34 * n43 + n23 * n31 * n44 - n21 * n33 * n44) * idet;
        result[0][2] = (n22 * n34 * n41 - n24 * n32 * n41 + n24 * n31 * n42 - n21 * n34 * n42 - n22 * n31 * n44 + n21 * n32 * n44) * idet;
        result[0][3] = (n23 * n32 * n41 - n22 * n33 * n41 - n23 * n31 * n42 + n21 * n33 * n42 + n22 * n31 * n43 - n21 * n32 * n43) * idet;

        result[1][0] = t12 * idet;
        result[1][1] = (n13 * n34 * n41 - n14 * n33 * n41 + n14 * n31 * n43 - n11 * n34 * n43 - n13 * n31 * n44 + n11 * n33 * n44) * idet;
        result[1][2] = (n14 * n32 * n41 - n12 * n34 * n41 - n14 * n31 * n42 + n11 * n34 * n42 + n12 * n31 * n44 - n11 * n32 * n44) * idet;
        result[1][3] = (n12 * n33 * n41 - n13 * n32 * n41 + n13 * n31 * n42 - n11 * n33 * n42 - n12 * n31 * n43 + n11 * n32 * n43) * idet;

        result[2][0] = t13 * idet;
        result[2][1] = (n14 * n23 * n41 - n13 * n24 * n41 - n14 * n21 * n43 + n11 * n24 * n43 + n13 * n21 * n44 - n11 * n23 * n44) * idet;
        result[2][2] = (n12 * n24 * n41 - n14 * n22 * n41 + n14 * n21 * n42 - n11 * n24 * n42 - n12 * n21 * n44 + n11 * n22 * n44) * idet;
        result[2][3] = (n13 * n22 * n41 - n12 * n23 * n41 - n13 * n21 * n42 + n11 * n23 * n42 + n12 * n21 * n43 - n11 * n22 * n43) * idet;

        result[3][0] = t14 * idet;
        result[3][1] = (n13 * n24 * n31 - n14 * n23 * n31 + n14 * n21 * n33 - n11 * n24 * n33 - n13 * n21 * n34 + n11 * n23 * n34) * idet;
        result[3][2] = (n14 * n22 * n31 - n12 * n24 * n31 - n14 * n21 * n32 + n11 * n24 * n32 + n12 * n21 * n34 - n11 * n22 * n34) * idet;
        result[3][3] = (n12 * n23 * n31 - n13 * n22 * n31 + n13 * n21 * n32 - n11 * n23 * n32 - n12 * n21 * n33 + n11 * n22 * n33) * idet;

        return result;
    }
} // math namespace


inline quat quat::axisangle(const float3& axis, float angle)
{
    using namespace math;

    if (lensqr(axis) == 0.0f)
    {
        return quat(0, 0, 0, 1);
    }

    float3 tmp = normalize(axis) * math::sin(angle * 0.5f);
    quat r = quat(tmp.x, tmp.y, tmp.z, math::cos(angle * 0.5f));
    return r;
}

inline float4 quat::toaxis(const quat& q)
{
    using namespace math;

    quat c = q;
    if (c.w != 0.0f)
    {
        c = normalize(q);
    }

    float3 axis;
    const float den = math::sqrt(1.0f - c.w * c.w);
    if (den > 0.0001f)
    {
        axis = float3(c.x, c.y, c.z) / den;
    }
    else
    {
        axis = float3(1, 0, 0);
    }

    float angle = 2.0f * math::cos(c.w);
    return float4(axis, angle);
}

inline void quat::toaxis(const quat& quat, float3* axis, float* angle)
{
    using namespace math;

    float4 axisangle = quat::toaxis(quat);
    if (axis)  *axis = float3(axisangle.x, axisangle.y, axisangle.z);
    if (angle) *angle = axisangle.w;
}

inline quat quat::euler(float x, float y, float z)
{
    using namespace math;

    float r;
    float p;

    r = z * 0.5f;
    p = x * 0.5f;
    y = y * 0.5f; // Now y mean yaw

    const float c1 = math::cos(y);
    const float c2 = math::cos(p);
    const float c3 = math::cos(r);
    const float s1 = math::sin(y);
    const float s2 = math::sin(p);
    const float s3 = math::sin(r);

    return float4(
        s1 * s2 * c3 + c1 * c2 * s3,
        s1 * c2 * c3 + c1 * s2 * s3,
        c1 * s2 * c3 - s1 * c2 * s3,
        c1 * c2 * c3 - s1 * s2 * s3
    );
}

inline quat quat::euler(const float3& v)
{
    return quat::euler(v.x, v.y, v.z);
}

inline float2x2 float2x2::rotate(float angle)
{
    const float s = math::sin(angle);
    const float c = math::cos(angle);

    return float2x2(
        c, -s,
        s, c
    );
}

inline float2x2 float2x2::scale(float x)
{
    return float2x2::scale(x, x);
}

inline float2x2 float2x2::scale(const float2& v)
{
    return float2x2::scale(v.x, v.y);
}

inline float2x2 float2x2::scale(float x, float y)
{
    return float2x2(x, 0, 0, y);
}

inline float3x3 float3x3::translate(const float2& v)
{
    return float3x3::translate(v.x, v.y);
}

inline float3x3 float3x3::translate(float x, float y)
{
    return float3x3(
        1, 0, 0,
        0, 1, 0,
        x, y, 1
    );
}

inline float3x3 float3x3::rotate(float angle)
{
    const float c = math::cos(angle);
    const float s = math::sin(angle);
    return float3x3(
        c, -s, 0,
        s, c, 0,
        0, 0, 1
    );
}

inline float3x3 float3x3::scale(const float2& v)
{
    return float3x3::scale(v.x, v.y);
}

inline float3x3 float3x3::scale(float x, float y)
{
    return float3x3(
        x, 0, 0,
        0, y, 0,
        0, 0, 1
    );
}

inline float3x3 float3x3::ortho(float l, float r, float b, float t)
{
    const float w = (r - l);
    const float h = (t - b);
    const float x = 1.0f / w;
    const float y = 1.0f / h;

    return float3x3(
        2.0f * x, 0, 0,
        0, 2.0f * y, 0,
        -x * (l + r), -y * (b + t), 1
    );
}

inline float4x4 float4x4::ortho(float l, float r, float b, float t, float n, float f)
{
    const float x = 1.0f / (r - l);
    const float y = 1.0f / (t - b);
    const float z = 1.0f / (f - n);

    float4x4 result;
    result[0] = float4(2.0f * x, 0, 0, 0);
    result[1] = float4(0, 2.0f * y, 0, 0);
    result[2] = float4(0, 0, 2.0f * z, 0);
    result[3] = float4(-x * (l + r), -y * (b + t), -z * (n + f), 1.0f);
    return result;
}

inline float4x4 float4x4::frustum(float l, float r, float b, float t, float n, float f)
{
    const float x = 1.0f / (r - l);
    const float y = 1.0f / (t - b);
    const float z = 1.0f / (f - n);

    float4x4 result;
    result[0] = float4(2.0f * x, 0, 0, 0);
    result[1] = float4(0, 2.0f * y, 0, 0);
    result[2] = float4(x * (l + r), y * (b + t), z * (n + f), 1.0f);
    result[3] = float4(0, 0, 2.0f * z, 0);
    return result;
}

inline float4x4 float4x4::perspective(float fov, float aspect, float znear, float zfar)
{
    using namespace math;

    const float a = 1.0f / math::tan(fov * 0.5f);
    const float b = zfar / (znear - zfar);

    float4x4 result;
    result[0] = float4(a / aspect, 0, 0, 0);
    result[1] = float4(0, a, 0, 0);
    result[2] = float4(0, 0, b, -1);
    result[3] = float4(0, 0, znear * b, 0);
    return result;
}

inline float4x4 float4x4::lookat(const float3& eye, const float3& target, const float3& up)
{
    using namespace math;

    const float3 z = normalize(eye - target);
    const float3 x = normalize(cross(up, z));
    const float3 y = normalize(cross(z, x));

    float4x4 result;
    result[0] = float4(x.x, y.x, z.x, 0);
    result[1] = float4(x.y, y.y, z.y, 0);
    result[2] = float4(x.z, y.z, z.z, 0);
    result[3] = float4(-dot(x, eye), -dot(y, eye), -dot(z, eye), 1.0f);
    return result;
}

inline float4x4 float4x4::scalation(float s)
{
    return float4x4::scalation(s, s, s);
}

inline float4x4 float4x4::scalation(const float2& v)
{
    return float4x4::scalation(v.x, v.y);
}

inline float4x4 float4x4::scalation(const float3& v)
{
    return float4x4::scalation(v.x, v.y, v.z);
}

inline float4x4 float4x4::scalation(float x, float y, float z)
{
    return float4x4(
        x, 0, 0, 0,
        0, y, 0, 0,
        0, 0, z, 0,
        0, 0, 0, 1
    );
}

inline float4x4 float4x4::translation(const float2& v)
{
    return float4x4::translation(v.x, v.y);
}

inline float4x4 float4x4::translation(const float3& v)
{
    return float4x4::translation(v.x, v.y, v.z);
}

inline float4x4 float4x4::translation(float x, float y, float z)
{
    return float4x4(
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        x, y, z, 1
    );
}

inline float4x4 float4x4::rotation(const float3& axis, float angle)
{
    return float4x4::rotation(axis.x, axis.y, axis.z, angle);
}

inline float4x4 float4x4::rotation(float x, float y, float z, float angle)
{
    using namespace math;

    const float c = math::cos(-angle);
    const float s = math::sin(-angle);
    const float t = 1.0f - c;

    float4x4 result;
    /* Row 1 */
    result[0] = float4(
        t * x * x + c,
        t * x * y - s * z,
        t * x * z + s * y,
        0.0f);

    /* Row 2 */
    result[1] = float4(
        t * x * y + s * z,
        t * y * y + c,
        t * y * z - s * x,
        0.0f);

    /* Row 3 */
    result[2] = float4(
        t * x * z - s * y,
        t * y * z + s * x,
        t * z * z + c,
        0.0f);

    /* Row 4 */
    result[3] = float4(0, 0, 0, 1.0f);
    return result;
}

inline float4x4 float4x4::rotation_x(float angle)
{
    using namespace math;

    const float s = math::sin(angle);
    const float c = math::cos(angle);

    return float4x4(
        1, 0, 0, 0,
        0, c, s, 0,
        0, -s, c, 0,
        0, 0, 0, 1
    );
}

inline float4x4 float4x4::rotation_y(float angle)
{
    using namespace math;

    const float s = math::sin(angle);
    const float c = math::cos(angle);

    return float4x4(
        c, 0, s, 0,
        0, 1, 0, 0,
        -s, 0, c, 0,
        0, 0, 0, 1
    );
}

inline float4x4 float4x4::rotation_z(float angle)
{
    using namespace math;

    const float s = math::sin(angle);
    const float c = math::cos(angle);

    return float4x4(
        c, s, 0, 0,
        -s, c, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    );
}

inline float4x4 float4x4::rotation(const quat& quaternion)
{
    float4 axisangle = quat::toaxis(quaternion);
    return float4x4::rotation(axisangle.x, axisangle.y, axisangle.z, axisangle.w);
}