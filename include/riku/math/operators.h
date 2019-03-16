// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#pragma once

#include "./types.h"

//
// @region: Operator overloadng
//

inline int2 operator-(const int2& v)
{
    return int2(-v.x, -v.y);
}

inline int2& operator++(int2& v)
{
    ++v.x;
    ++v.y;
    return v;
}

inline int2& operator--(int2& v)
{
    --v.x;
    --v.y;
    return v;
}

inline int2 operator++(int2& v, int)
{
    const int2 result = v;
    v.x++;
    v.y++;
    return result;
}

inline int2 operator--(int2& v, int)
{
    const int2 result = v;
    v.x--;
    v.y--;
    return result;
}

inline int2 operator+(const int2& a, const int2& b)
{
    return int2(a.x + b.x, a.y + b.y);
}

inline int2 operator-(const int2& a, const int2& b)
{
    return int2(a.x - b.x, a.y - b.y);
}

inline int2 operator*(const int2& a, const int2& b)
{
    return int2(a.x * b.x, a.y * b.y);
}

inline int2 operator/(const int2& a, const int2& b)
{
    return int2(a.x / b.x, a.y / b.y);
}

inline int2 operator+(const int2& a, int b)
{
    return int2(a.x + b, a.y + b);
}

inline int2 operator-(const int2& a, int b)
{
    return int2(a.x - b, a.y - b);
}

inline int2 operator*(const int2& a, int b)
{
    return int2(a.x * b, a.y * b);
}

inline int2 operator/(const int2& a, int b)
{
    return int2(a.x / b, a.y / b);
}

inline int2 operator+(int a, const int2& b)
{
    return int2(a + b.x, a + b.y);
}

inline int2 operator-(int a, const int2& b)
{
    return int2(a - b.x, a - b.y);
}

inline int2 operator*(int a, const int2& b)
{
    return int2(a * b.x, a * b.y);
}

inline int2 operator/(int a, const int2& b)
{
    return int2(a / b.x, a / b.y);
}

inline int2& operator+=(int2& a, int b)
{
    return (a = a + b);
}

inline int2& operator-=(int2& a, int b)
{
    return (a = a - b);
}

inline int2& operator*=(int2& a, int b)
{
    return (a = a * b);
}

inline int2& operator/=(int2& a, int b)
{
    return (a = a / b);
}

inline int2& operator+=(int2& a, const int2& b)
{
    return (a = a + b);
}

inline int2& operator-=(int2& a, const int2& b)
{
    return (a = a - b);
}

inline int2& operator*=(int2& a, const int2& b)
{
    return (a = a * b);
}

inline int2& operator/=(int2& a, const int2& b)
{
    return (a = a / b);
}

inline bool2 operator<(const int2& a, const int2& b)
{
    return bool2(a.x < b.x, a.y < b.y);
}

inline bool2 operator>(const int2& a, const int2& b)
{
    return bool2(a.x > b.x, a.y > b.y);
}

inline bool2 operator<=(const int2& a, const int2& b)
{
    return bool2(a.x <= b.x, a.y <= b.y);
}

inline bool2 operator>=(const int2& a, const int2& b)
{
    return bool2(a.x >= b.x, a.y >= b.y);
}

inline bool2 operator==(const int2& a, const int2& b)
{
    return bool2(a.x == b.x, a.y == b.y);
}

inline bool2 operator!=(const int2& a, const int2& b)
{
    return bool2(a.x != b.x, a.y != b.y);
}

inline int3 operator-(const int3& v)
{
    return int3(-v.x, -v.y, -v.z);
}

inline int3& operator++(int3& v)
{
    ++v.x;
    ++v.y;
    ++v.z;
    return v;
}

inline int3& operator--(int3& v)
{
    --v.x;
    --v.y;
    --v.z;
    return v;
}

inline int3 operator++(int3& v, int)
{
    const int3 result = v;
    v.x++;
    v.y++;
    v.z++;
    return result;
}

inline int3 operator--(int3& v, int)
{
    const int3 result = v;
    v.x--;
    v.y--;
    v.z--;
    return result;
}

inline int3 operator+(const int3& a, const int3& b)
{
    return int3(a.x + b.x, a.y + b.y, a.z + b.z);
}

inline int3 operator-(const int3& a, const int3& b)
{
    return int3(a.x - b.x, a.y - b.y, a.z - b.z);
}

inline int3 operator*(const int3& a, const int3& b)
{
    return int3(a.x * b.x, a.y * b.y, a.z * b.z);
}

inline int3 operator/(const int3& a, const int3& b)
{
    return int3(a.x / b.x, a.y / b.y, a.z / b.z);
}

inline int3 operator+(const int3& a, int b)
{
    return int3(a.x + b, a.y + b, a.z + b);
}

inline int3 operator-(const int3& a, int b)
{
    return int3(a.x - b, a.y - b, a.z - b);
}

inline int3 operator*(const int3& a, int b)
{
    return int3(a.x * b, a.y * b, a.z * b);
}

inline int3 operator/(const int3& a, int b)
{
    return int3(a.x / b, a.y / b, a.z / b);
}

inline int3 operator+(int a, const int3& b)
{
    return int3(a + b.x, a + b.y, a + b.z);
}

inline int3 operator-(int a, const int3& b)
{
    return int3(a - b.x, a - b.y, a - b.z);
}

inline int3 operator*(int a, const int3& b)
{
    return int3(a * b.x, a * b.y, a * b.z);
}

inline int3 operator/(int a, const int3& b)
{
    return int3(a / b.x, a / b.y, a / b.z);
}

inline int3& operator+=(int3& a, int b)
{
    return (a = a + b);
}

inline int3& operator-=(int3& a, int b)
{
    return (a = a - b);
}

inline int3& operator*=(int3& a, int b)
{
    return (a = a * b);
}

inline int3& operator/=(int3& a, int b)
{
    return (a = a / b);
}

inline int3& operator+=(int3& a, const int3& b)
{
    return (a = a + b);
}

inline int3& operator-=(int3& a, const int3& b)
{
    return (a = a - b);
}

inline int3& operator*=(int3& a, const int3& b)
{
    return (a = a * b);
}

inline int3& operator/=(int3& a, const int3& b)
{
    return (a = a / b);
}

inline bool3 operator<(const int3& a, const int3& b)
{
    return bool3(a.x < b.x, a.y < b.y, a.z < b.z);
}

inline bool3 operator>(const int3& a, const int3& b)
{
    return bool3(a.x > b.x, a.y > b.y, a.z > b.z);
}

inline bool3 operator<=(const int3& a, const int3& b)
{
    return bool3(a.x <= b.x, a.y <= b.y, a.z <= b.z);
}

inline bool3 operator>=(const int3& a, const int3& b)
{
    return bool3(a.x >= b.x, a.y >= b.y, a.z >= b.z);
}

inline bool3 operator==(const int3& a, const int3& b)
{
    return bool3(a.x == b.x, a.y == b.y, a.z == b.z);
}

inline bool3 operator!=(const int3& a, const int3& b)
{
    return bool3(a.x != b.x, a.y != b.y, a.z != b.z);
}

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

inline uint2& operator++(uint2& v)
{
    ++v.x;
    ++v.y;
    return v;
}

inline uint2& operator--(uint2& v)
{
    --v.x;
    --v.y;
    return v;
}

inline uint2 operator++(uint2& v, int)
{
    const uint2 result = v;
    v.x++;
    v.y++;
    return result;
}

inline uint2 operator--(uint2& v, int)
{
    const uint2 result = v;
    v.x--;
    v.y--;
    return result;
}

inline uint2 operator+(const uint2& a, const uint2& b)
{
    return uint2(a.x + b.x, a.y + b.y);
}

inline uint2 operator-(const uint2& a, const uint2& b)
{
    return uint2(a.x - b.x, a.y - b.y);
}

inline uint2 operator*(const uint2& a, const uint2& b)
{
    return uint2(a.x * b.x, a.y * b.y);
}

inline uint2 operator/(const uint2& a, const uint2& b)
{
    return uint2(a.x / b.x, a.y / b.y);
}

inline uint2 operator+(const uint2& a, uint b)
{
    return uint2(a.x + b, a.y + b);
}

inline uint2 operator-(const uint2& a, uint b)
{
    return uint2(a.x - b, a.y - b);
}

inline uint2 operator*(const uint2& a, uint b)
{
    return uint2(a.x * b, a.y * b);
}

inline uint2 operator/(const uint2& a, uint b)
{
    return uint2(a.x / b, a.y / b);
}

inline uint2 operator+(uint a, const uint2& b)
{
    return uint2(a + b.x, a + b.y);
}

inline uint2 operator-(uint a, const uint2& b)
{
    return uint2(a - b.x, a - b.y);
}

inline uint2 operator*(uint a, const uint2& b)
{
    return uint2(a * b.x, a * b.y);
}

inline uint2 operator/(uint a, const uint2& b)
{
    return uint2(a / b.x, a / b.y);
}

inline uint2& operator+=(uint2& a, uint b)
{
    return (a = a + b);
}

inline uint2& operator-=(uint2& a, uint b)
{
    return (a = a - b);
}

inline uint2& operator*=(uint2& a, uint b)
{
    return (a = a * b);
}

inline uint2& operator/=(uint2& a, uint b)
{
    return (a = a / b);
}

inline uint2& operator+=(uint2& a, const uint2& b)
{
    return (a = a + b);
}

inline uint2& operator-=(uint2& a, const uint2& b)
{
    return (a = a - b);
}

inline uint2& operator*=(uint2& a, const uint2& b)
{
    return (a = a * b);
}

inline uint2& operator/=(uint2& a, const uint2& b)
{
    return (a = a / b);
}

inline bool2 operator<(const uint2& a, const uint2& b)
{
    return bool2(a.x < b.x, a.y < b.y);
}

inline bool2 operator>(const uint2& a, const uint2& b)
{
    return bool2(a.x > b.x, a.y > b.y);
}

inline bool2 operator<=(const uint2& a, const uint2& b)
{
    return bool2(a.x <= b.x, a.y <= b.y);
}

inline bool2 operator>=(const uint2& a, const uint2& b)
{
    return bool2(a.x >= b.x, a.y >= b.y);
}

inline bool2 operator==(const uint2& a, const uint2& b)
{
    return bool2(a.x == b.x, a.y == b.y);
}

inline bool2 operator!=(const uint2& a, const uint2& b)
{
    return bool2(a.x != b.x, a.y != b.y);
}

inline uint3& operator++(uint3& v)
{
    ++v.x;
    ++v.y;
    ++v.z;
    return v;
}

inline uint3& operator--(uint3& v)
{
    --v.x;
    --v.y;
    --v.z;
    return v;
}

inline uint3 operator++(uint3& v, int)
{
    const uint3 result = v;
    v.x++;
    v.y++;
    v.z++;
    return result;
}

inline uint3 operator--(uint3& v, int)
{
    const uint3 result = v;
    v.x--;
    v.y--;
    v.z--;
    return result;
}

inline uint3 operator+(const uint3& a, const uint3& b)
{
    return uint3(a.x + b.x, a.y + b.y, a.z + b.z);
}

inline uint3 operator-(const uint3& a, const uint3& b)
{
    return uint3(a.x - b.x, a.y - b.y, a.z - b.z);
}

inline uint3 operator*(const uint3& a, const uint3& b)
{
    return uint3(a.x * b.x, a.y * b.y, a.z * b.z);
}

inline uint3 operator/(const uint3& a, const uint3& b)
{
    return uint3(a.x / b.x, a.y / b.y, a.z / b.z);
}

inline uint3 operator+(const uint3& a, uint b)
{
    return uint3(a.x + b, a.y + b, a.z + b);
}

inline uint3 operator-(const uint3& a, uint b)
{
    return uint3(a.x - b, a.y - b, a.z - b);
}

inline uint3 operator*(const uint3& a, uint b)
{
    return uint3(a.x * b, a.y * b, a.z * b);
}

inline uint3 operator/(const uint3& a, uint b)
{
    return uint3(a.x / b, a.y / b, a.z / b);
}

inline uint3 operator+(uint a, const uint3& b)
{
    return uint3(a + b.x, a + b.y, a + b.z);
}

inline uint3 operator-(uint a, const uint3& b)
{
    return uint3(a - b.x, a - b.y, a - b.z);
}

inline uint3 operator*(uint a, const uint3& b)
{
    return uint3(a * b.x, a * b.y, a * b.z);
}

inline uint3 operator/(uint a, const uint3& b)
{
    return uint3(a / b.x, a / b.y, a / b.z);
}

inline uint3& operator+=(uint3& a, uint b)
{
    return (a = a + b);
}

inline uint3& operator-=(uint3& a, uint b)
{
    return (a = a - b);
}

inline uint3& operator*=(uint3& a, uint b)
{
    return (a = a * b);
}

inline uint3& operator/=(uint3& a, uint b)
{
    return (a = a / b);
}

inline uint3& operator+=(uint3& a, const uint3& b)
{
    return (a = a + b);
}

inline uint3& operator-=(uint3& a, const uint3& b)
{
    return (a = a - b);
}

inline uint3& operator*=(uint3& a, const uint3& b)
{
    return (a = a * b);
}

inline uint3& operator/=(uint3& a, const uint3& b)
{
    return (a = a / b);
}

inline bool3 operator<(const uint3& a, const uint3& b)
{
    return bool3(a.x < b.x, a.y < b.y, a.z < b.z);
}

inline bool3 operator>(const uint3& a, const uint3& b)
{
    return bool3(a.x > b.x, a.y > b.y, a.z > b.z);
}

inline bool3 operator<=(const uint3& a, const uint3& b)
{
    return bool3(a.x <= b.x, a.y <= b.y, a.z <= b.z);
}

inline bool3 operator>=(const uint3& a, const uint3& b)
{
    return bool3(a.x >= b.x, a.y >= b.y, a.z >= b.z);
}

inline bool3 operator==(const uint3& a, const uint3& b)
{
    return bool3(a.x == b.x, a.y == b.y, a.z == b.z);
}

inline bool3 operator!=(const uint3& a, const uint3& b)
{
    return bool3(a.x != b.x, a.y != b.y, a.z != b.z);
}

inline uint4& operator++(uint4& v)
{
    ++v.x;
    ++v.y;
    ++v.z;
    ++v.w;
    return v;
}

inline uint4& operator--(uint4& v)
{
    --v.x;
    --v.y;
    --v.z;
    --v.w;
    return v;
}

inline uint4 operator++(uint4& v, int)
{
    const uint4 result = v;
    v.x++;
    v.y++;
    v.z++;
    v.w++;
    return result;
}

inline uint4 operator--(uint4& v, int)
{
    const uint4 result = v;
    v.x--;
    v.y--;
    v.z--;
    v.w--;
    return result;
}

inline uint4 operator+(const uint4& a, const uint4& b)
{
    return uint4(a.x + b.x, a.y + b.y, a.z + b.z, a.w / b.w);
}

inline uint4 operator-(const uint4& a, const uint4& b)
{
    return uint4(a.x - b.x, a.y - b.y, a.z - b.z, a.w / b.w);
}

inline uint4 operator*(const uint4& a, const uint4& b)
{
    return uint4(a.x * b.x, a.y * b.y, a.z * b.z, a.w / b.w);
}

inline uint4 operator/(const uint4& a, const uint4& b)
{
    return uint4(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w);
}

inline uint4 operator+(const uint4& a, uint b)
{
    return uint4(a.x + b, a.y + b, a.z + b, a.w + b);
}

inline uint4 operator-(const uint4& a, uint b)
{
    return uint4(a.x - b, a.y - b, a.z - b, a.w - b);
}

inline uint4 operator*(const uint4& a, uint b)
{
    return uint4(a.x * b, a.y * b, a.z * b, a.w * b);
}

inline uint4 operator/(const uint4& a, uint b)
{
    return uint4(a.x / b, a.y / b, a.z / b, a.w / b);
}

inline uint4 operator+(uint a, const uint4& b)
{
    return uint4(a + b.x, a + b.y, a + b.z, a + b.w);
}

inline uint4 operator-(uint a, const uint4& b)
{
    return uint4(a - b.x, a - b.y, a - b.z, a - b.w);
}

inline uint4 operator*(uint a, const uint4& b)
{
    return uint4(a * b.x, a * b.y, a * b.z, a * b.w);
}

inline uint4 operator/(uint a, const uint4& b)
{
    return uint4(a / b.x, a / b.y, a / b.z, a / b.w);
}

inline uint4& operator+=(uint4& a, uint b)
{
    return (a = a + b);
}

inline uint4& operator-=(uint4& a, uint b)
{
    return (a = a - b);
}

inline uint4& operator*=(uint4& a, uint b)
{
    return (a = a * b);
}

inline uint4& operator/=(uint4& a, uint b)
{
    return (a = a / b);
}

inline uint4& operator+=(uint4& a, const uint4& b)
{
    return (a = a + b);
}

inline uint4& operator-=(uint4& a, const uint4& b)
{
    return (a = a - b);
}

inline uint4& operator*=(uint4& a, const uint4& b)
{
    return (a = a * b);
}

inline uint4& operator/=(uint4& a, const uint4& b)
{
    return (a = a / b);
}

inline bool4 operator<(const uint4& a, const uint4& b)
{
    return bool4(a.x < b.x, a.y < b.y, a.z < b.z, a.w < b.w);
}

inline bool4 operator>(const uint4& a, const uint4& b)
{
    return bool4(a.x > b.x, a.y > b.y, a.z > b.z, a.w > b.w);
}

inline bool4 operator<=(const uint4& a, const uint4& b)
{
    return bool4(a.x <= b.x, a.y <= b.y, a.z <= b.z, a.w <= b.w);
}

inline bool4 operator>=(const uint4& a, const uint4& b)
{
    return bool4(a.x >= b.x, a.y >= b.y, a.z >= b.z, a.w >= b.w);
}

inline bool4 operator==(const uint4& a, const uint4& b)
{
    return bool4(a.x == b.x, a.y == b.y, a.z == b.z, a.w == b.w);
}

inline bool4 operator!=(const uint4& a, const uint4& b)
{
    return bool4(a.x != b.x, a.y != b.y, a.z != b.z, a.w != b.w);
}

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

inline float3 operator-(const float3& v)
{
    return float3(-v.x, -v.y, -v.z);
}

inline const float3& operator+(const float3& v)
{
    return v;
}

inline float3& operator--(float3& v)
{
    --v.x;
    --v.y;
    --v.z;
    return v;
}

inline float3& operator++(float3& v)
{
    ++v.x;
    ++v.y;
    ++v.z;
    return v;
}

inline float3 operator--(float3& v, int)
{
    const float3 result = v;

    v.x--;
    v.y--;
    v.z--;

    return result;
}

inline float3 operator++(float3& v, int)
{
    const float3 result = v;

    v.x++;
    v.y++;
    v.z++;

    return result;
}

inline float3 operator+(const float3& a, const float3& b)
{
    return float3(a.x + b.x, a.y + b.y, a.z + b.z);
}

inline float3 operator-(const float3& a, const float3& b)
{
    return float3(a.x - b.x, a.y - b.y, a.z - b.z);
}

inline float3 operator*(const float3& a, const float3& b)
{
    return float3(a.x * b.x, a.y * b.y, a.z * b.z);
}

inline float3 operator/(const float3& a, const float3& b)
{
    return float3(a.x / b.x, a.y / b.y, a.z / b.z);
}

inline float3 operator+(const float3& a, float b)
{
    return float3(a.x + b, a.y + b, a.z + b);
}

inline float3 operator-(const float3& a, float b)
{
    return float3(a.x - b, a.y - b, a.z - b);
}

inline float3 operator*(const float3& a, float b)
{
    return float3(a.x * b, a.y * b, a.z * b);
}

inline float3 operator/(const float3& a, float b)
{
    return float3(a.x / b, a.y / b, a.z / b);
}

inline float3 operator+(float a, const float3& b)
{
    return float3(a + b.x, a + b.y, a + b.z);
}

inline float3 operator-(float a, const float3& b)
{
    return float3(a - b.x, a - b.y, a - b.z);
}

inline float3 operator*(float a, const float3& b)
{
    return float3(a * b.x, a * b.y, a * b.z);
}

inline float3 operator/(float a, const float3& b)
{
    return float3(a / b.x, a / b.y, a / b.z);
}

inline float3& operator+=(float3& a, const float3& b)
{
    return (a = a + b);
}

inline float3& operator+=(float3& a, float b)
{
    return (a = a + b);
}

inline float3& operator-=(float3& a, const float3& b)
{
    return (a = a - b);
}

inline float3& operator-=(float3& a, float b)
{
    return (a = a - b);
}

inline float3& operator*=(float3& a, const float3& b)
{
    return (a = a * b);
}

inline float3& operator*=(float3& a, float b)
{
    return (a = a * b);
}

inline float3& operator/=(float3& a, const float3& b)
{
    return (a = a / b);
}

inline float3& operator/=(float3& a, float b)
{
    return (a = a + b);
}

inline bool3 operator==(const float3& a, const float3& b)
{
    return bool3(a.x == b.x, a.y == b.y, a.z == b.z);
}

inline bool3 operator!=(const float3& a, const float3& b)
{
    return bool3(a.x != b.x, a.y != b.y, a.z != b.z);
}

inline bool3 operator<(const float3& a, const float3& b)
{
    return bool3(a.x < b.x, a.y < b.y, a.z < b.z);
}

inline bool3 operator>(const float3& a, const float3& b)
{
    return bool3(a.x > b.x, a.y > b.y, a.z > b.z);
}

inline bool3 operator<=(const float3& a, const float3& b)
{
    return bool3(a.x <= b.x, a.y <= b.y, a.z <= b.z);
}

inline bool3 operator>=(const float3& a, const float3& b)
{
    return bool3(a.x >= b.x, a.y >= b.y, a.z >= b.z);
}

inline float4 operator-(const float4& v)
{
    return float4(-v.x, -v.y, -v.z, -v.w);
}

inline const float4& operator+(const float4& v)
{
    return v;
}

inline float4& operator--(float4& v)
{
    --v.x;
    --v.y;
    --v.z;
    --v.w;
    return v;
}

inline float4& operator++(float4& v)
{
    ++v.x;
    ++v.y;
    ++v.z;
    ++v.w;
    return v;
}

inline float4 operator--(float4& v, int)
{
    const float4 result = v;

    v.x--;
    v.y--;
    v.z--;
    v.w--;

    return result;
}

inline float4 operator++(float4& v, int)
{
    const float4 result = v;

    v.x++;
    v.y++;
    v.z++;
    v.w++;

    return result;
}

inline float4 operator+(const float4& a, const float4& b)
{
    return float4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
}

inline float4 operator-(const float4& a, const float4& b)
{
    return float4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
}

inline float4 operator*(const float4& a, const float4& b)
{
    return float4(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
}

inline float4 operator/(const float4& a, const float4& b)
{
    return float4(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w);
}

inline float4 operator+(const float4& a, float b)
{
    return float4(a.x + b, a.y + b, a.z + b, a.w + b);
}

inline float4 operator-(const float4& a, float b)
{
    return float4(a.x - b, a.y - b, a.z - b, a.w - b);
}

inline float4 operator*(const float4& a, float b)
{
    return float4(a.x * b, a.y * b, a.z * b, a.w * b);
}

inline float4 operator/(const float4& a, float b)
{
    return float4(a.x / b, a.y / b, a.z / b, a.w / b);
}

inline float4 operator+(float a, const float4& b)
{
    return float4(a + b.x, a + b.y, a + b.z, a + b.w);
}

inline float4 operator-(float a, const float4& b)
{
    return float4(a - b.x, a - b.y, a - b.z, a - b.w);
}

inline float4 operator*(float a, const float4& b)
{
    return float4(a * b.x, a * b.y, a * b.z, a * b.w);
}

inline float4 operator/(float a, const float4& b)
{
    return float4(a / b.x, a / b.y, a / b.z, a / b.w);
}

inline float4& operator+=(float4& a, const float4& b)
{
    return (a = a + b);
}

inline float4& operator+=(float4& a, float b)
{
    return (a = a + b);
}

inline float4& operator-=(float4& a, const float4& b)
{
    return (a = a - b);
}

inline float4& operator-=(float4& a, float b)
{
    return (a = a - b);
}

inline float4& operator*=(float4& a, const float4& b)
{
    return (a = a * b);
}

inline float4& operator*=(float4& a, float b)
{
    return (a = a * b);
}

inline float4& operator/=(float4& a, const float4& b)
{
    return (a = a / b);
}

inline float4& operator/=(float4& a, float b)
{
    return (a = a + b);
}

inline bool4 operator==(const float4& a, const float4& b)
{
    return bool4(a.x == b.x, a.y == b.y, a.z == b.z, a.w == b.w);
}

inline bool4 operator!=(const float4& a, const float4& b)
{
    return bool4(a.x != b.x, a.y != b.y, a.z != b.z, a.w != b.w);
}

inline bool4 operator<(const float4& a, const float4& b)
{
    return bool4(a.x < b.x, a.y < b.y, a.z < b.z, a.w < b.w);
}

inline bool4 operator>(const float4& a, const float4& b)
{
    return bool4(a.x > b.x, a.y > b.y, a.z > b.z, a.w > b.w);
}

inline bool4 operator<=(const float4& a, const float4& b)
{
    return bool4(a.x <= b.x, a.y <= b.y, a.z <= b.z, a.w <= b.w);
}

inline bool4 operator>=(const float4& a, const float4& b)
{
    return bool4(a.x >= b.x, a.y >= b.y, a.z >= b.z, a.w >= b.w);
}

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

inline uint2x2& operator++(uint2x2& m)
{
    ++m[0][0]; ++m[0][1];
    ++m[1][0]; ++m[1][1];
    return m;
}

inline uint2x2& operator--(uint2x2& m)
{
    --m[0][0]; --m[0][1];
    --m[1][0]; --m[1][1];
    return m;
}

inline uint2x2 operator++(uint2x2& m, int)
{
    const uint2x2 result = m;
    ++m;
    return result;
}

inline uint2x2 operator--(uint2x2& m, int)
{
    const uint2x2 result = m;
    --m;
    return result;
}

inline uint2x2 operator+(const uint2x2& a, const uint2x2& b)
{
    return uint2x2(
        a[0][0] + b[0][0], a[0][1] + b[0][1],
        a[1][0] + b[1][0], a[1][1] + b[1][1]);
}

inline uint2x2 operator-(const uint2x2& a, const uint2x2& b)
{
    return uint2x2(
        a[0][0] - b[0][0], a[0][1] - b[0][1],
        a[1][0] - b[1][0], a[1][1] - b[1][1]);
}

inline uint2x2 operator*(const uint2x2& a, const uint2x2& b)
{
    return uint2x2(
        a[0][0] * b[0][0], a[0][1] * b[0][1],
        a[1][0] * b[1][0], a[1][1] * b[1][1]);
}

inline uint2x2 operator/(const uint2x2& a, const uint2x2& b)
{
    return uint2x2(
        a[0][0] / b[0][0], a[0][1] / b[0][1],
        a[1][0] / b[1][0], a[1][1] / b[1][1]);
}

inline uint2x2 operator+(const uint2x2& a, uint b)
{
    return uint2x2(
        a[0][0] + b, a[0][1] + b,
        a[1][0] + b, a[1][1] + b);
}

inline uint2x2 operator-(const uint2x2& a, uint b)
{
    return uint2x2(
        a[0][0] - b, a[0][1] - b,
        a[1][0] - b, a[1][1] - b);
}

inline uint2x2 operator*(const uint2x2& a, uint b)
{
    return uint2x2(
        a[0][0] * b, a[0][1] * b,
        a[1][0] * b, a[1][1] * b);
}

inline uint2x2 operator/(const uint2x2& a, uint b)
{
    return uint2x2(
        a[0][0] / b, a[0][1] / b,
        a[1][0] / b, a[1][1] / b);
}

inline uint2x2 operator+(uint a, const uint2x2& b)
{
    return uint2x2(
        a + b[0][0], a + b[0][1],
        a + b[1][0], a + b[1][1]);
}

inline uint2x2 operator-(uint a, const uint2x2& b)
{
    return uint2x2(
        a - b[0][0], a - b[0][1],
        a - b[1][0], a - b[1][1]);
}

inline uint2x2 operator*(uint a, const uint2x2& b)
{
    return uint2x2(
        a * b[0][0], a * b[0][1],
        a * b[1][0], a * b[1][1]);
}

inline uint2x2 operator/(uint a, const uint2x2& b)
{
    return uint2x2(
        a / b[0][0], a / b[0][1],
        a / b[1][0], a / b[1][1]);
}

inline uint2x2& operator+=(uint2x2& a, uint b)
{
    return (a = a + b);
}

inline uint2x2& operator-=(uint2x2& a, uint b)
{
    return (a = a - b);
}

inline uint2x2& operator*=(uint2x2& a, uint b)
{
    return (a = a * b);
}

inline uint2x2& operator/=(uint2x2& a, uint b)
{
    return (a = a / b);
}

inline uint2x2& operator+=(uint2x2& a, const uint2x2& b)
{
    return (a = a + b);
}

inline uint2x2& operator-=(uint2x2& a, const uint2x2& b)
{
    return (a = a - b);
}

inline uint2x2& operator*=(uint2x2& a, const uint2x2& b)
{
    return (a = a * b);
}

inline uint2x2& operator/=(uint2x2& a, const uint2x2& b)
{
    return (a = a / b);
}

inline bool2x2 operator<(const uint2x2& a, const uint2x2& b)
{
    return bool2x2(
        a[0][0] < b[0][0], a[0][1] < b[0][1],
        a[1][0] < b[1][0], a[1][1] < b[1][1]);
}

inline bool2x2 operator>(const uint2x2& a, const uint2x2& b)
{
    return bool2x2(
        a[0][0] > b[0][0], a[0][1] > b[0][1],
        a[1][0] > b[1][0], a[1][1] > b[1][1]);
}

inline bool2x2 operator<=(const uint2x2& a, const uint2x2& b)
{
    return bool2x2(
        a[0][0] <= b[0][0], a[0][1] <= b[0][1],
        a[1][0] <= b[1][0], a[1][1] <= b[1][1]);
}

inline bool2x2 operator>=(const uint2x2& a, const uint2x2& b)
{
    return bool2x2(
        a[0][0] >= b[0][0], a[0][1] >= b[0][1],
        a[1][0] >= b[1][0], a[1][1] >= b[1][1]);
}

inline bool2x2 operator==(const uint2x2& a, const uint2x2& b)
{
    return bool2x2(
        a[0][0] == b[0][0], a[0][1] == b[0][1],
        a[1][0] == b[1][0], a[1][1] == b[1][1]);
}

inline bool2x2 operator!=(const uint2x2& a, const uint2x2& b)
{
    return bool2x2(
        a[0][0] != b[0][0], a[0][1] != b[0][1],
        a[1][0] != b[1][0], a[1][1] != b[1][1]);
}

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