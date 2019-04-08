#pragma once 

#include "./base.h"
#include "./float3.h"
#include "./float4.h"

union quat
{
public: // @region: Fields
    struct
    {
        float x, y, z, w; 
    };

public: // @region: Constructors
    inline quat() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}

    inline quat(const float3& euler)
    {
        *this = quat::euler(euler);
    }

    inline quat(float x, float y, float z)
    {
        *this = quat::euler(x, y, z);
    }

    inline quat(const float3& axis, float angle)
    {
        *this = quat::axisangle(axis, angle);
    }

    inline quat(float x, float y, float z, float w)
        : x(x)
        , y(y)
        , z(z)
        , w(w) {}

    inline quat(float s)
        : x(s)
        , y(s)
        , z(s)
        , w(s) {}

    inline quat(const float4& v)
        : x(v.x)
        , y(v.y)
        , z(v.z)
        , w(v.w) {}

public: // @region: Operators
    inline float& operator[](int index)
    {
        ASSERT(index > -1 && index < 4, "Index out of range");
        return ((float*)this)[index];
    }

    inline float  operator[](int index) const
    {
        ASSERT(index > -1 && index < 4, "Index out of range");
        return ((float*)this)[index];
    }

public:
    /* Quaternion from axisangle
     */
    inline static quat axisangle(const float3& axis, float angle);

    /* Convert quaternion to axisangle
     * @note: xyz is axis, w is angle
     */
    inline static float4 toaxis(const quat& quat);

    /* Convert quaternion to axisangle
     * @note: xyz is axis, w is angle
     */
    inline static void toaxis(const quat& quat, float3* axis, float* angle);

    /* Quaternion from euler
     */
    inline static quat euler(float x, float y, float z);

    /* Quaternion from euler
     */
    inline static quat euler(const float3& v);
};

inline quat operator-(const quat& v)
{
    return quat(-v.x, -v.y, -v.z, -v.w);
}

inline const quat& operator+(const quat& v)
{
    return v;
}

inline quat& operator--(quat& v)
{
    --v.x;
    --v.y;
    --v.z;
    --v.w;
    return v;
}

inline quat& operator++(quat& v)
{
    ++v.x;
    ++v.y;
    ++v.z;
    ++v.w;
    return v;
}

inline quat operator--(quat& v, int)
{
    const quat result = v;

    v.x--;
    v.y--;
    v.z--;
    v.w--;

    return result;
}

inline quat operator++(quat& v, int)
{
    const quat result = v;

    v.x++;
    v.y++;
    v.z++;
    v.w++;

    return result;
}

inline quat operator+(const quat& a, const quat& b)
{
    return quat(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
}

inline quat operator-(const quat& a, const quat& b)
{
    return quat(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
}

inline quat operator*(const quat& a, const quat& b)
{
    return quat(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
}

inline quat operator/(const quat& a, const quat& b)
{
    return quat(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w);
}

inline quat operator+(const quat& a, float b)
{
    return quat(a.x + b, a.y + b, a.z + b, a.w + b);
}

inline quat operator-(const quat& a, float b)
{
    return quat(a.x - b, a.y - b, a.z - b, a.w - b);
}

inline quat operator*(const quat& a, float b)
{
    return quat(a.x * b, a.y * b, a.z * b, a.w * b);
}

inline quat operator/(const quat& a, float b)
{
    return quat(a.x / b, a.y / b, a.z / b, a.w / b);
}

inline quat operator+(float a, const quat& b)
{
    return quat(a + b.x, a + b.y, a + b.z, a + b.w);
}

inline quat operator-(float a, const quat& b)
{
    return quat(a - b.x, a - b.y, a - b.z, a - b.w);
}

inline quat operator*(float a, const quat& b)
{
    return quat(a * b.x, a * b.y, a * b.z, a * b.w);
}

inline quat operator/(float a, const quat& b)
{
    return quat(a / b.x, a / b.y, a / b.z, a / b.w);
}

inline quat& operator+=(quat& a, const quat& b)
{
    return (a = a + b);
}

inline quat& operator+=(quat& a, float b)
{
    return (a = a + b);
}

inline quat& operator-=(quat& a, const quat& b)
{
    return (a = a - b);
}

inline quat& operator-=(quat& a, float b)
{
    return (a = a - b);
}

inline quat& operator*=(quat& a, const quat& b)
{
    return (a = a * b);
}

inline quat& operator*=(quat& a, float b)
{
    return (a = a * b);
}

inline quat& operator/=(quat& a, const quat& b)
{
    return (a = a / b);
}

inline quat& operator/=(quat& a, float b)
{
    return (a = a + b);
}

inline bool4 operator==(const quat& a, const quat& b)
{
    return bool4(a.x == b.x, a.y == b.y, a.z == b.z, a.w == b.w);
}

inline bool4 operator!=(const quat& a, const quat& b)
{
    return bool4(a.x != b.x, a.y != b.y, a.z != b.z, a.w != b.w);
}

inline bool4 operator<(const quat& a, const quat& b)
{
    return bool4(a.x < b.x, a.y < b.y, a.z < b.z, a.w < b.w);
}

inline bool4 operator>(const quat& a, const quat& b)
{
    return bool4(a.x > b.x, a.y > b.y, a.z > b.z, a.w > b.w);
}

inline bool4 operator<=(const quat& a, const quat& b)
{
    return bool4(a.x <= b.x, a.y <= b.y, a.z <= b.z, a.w <= b.w);
}

inline bool4 operator>=(const quat& a, const quat& b)
{
    return bool4(a.x >= b.x, a.y >= b.y, a.z >= b.z, a.w >= b.w);
}

namespace math
{
    inline bool all(const quat& v)
    {
	    return v.x != 0.0f && v.y != 0.0f && v.z != 0.0f && v.w != 0.0f;
    }

    inline bool any(const quat& v)
    {
	    return v.x != 0.0f || v.y != 0.0f || v.z != 0.0f || v.w != 0.0f;
    }
}