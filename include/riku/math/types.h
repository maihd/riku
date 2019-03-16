// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#pragma once

#include "../core.h"

#if defined(__ARM_NEON)
#if CPU_ARM && !ARCH_64BIT && !PLATFORM_ANDROID        
#define MATH_ENABLE_NEON 0
#else
#include <arm_neon.h>     
#define MATH_ENABLE_NEON 1
#endif         
#else
#define MATH_ENABLE_NEON 0
#endif

union int2
{
public: // @region: Fields
    struct
    {
        int x, y;
    };

public: // @region: Constructors
    inline int2() {}

    inline int2(int x, int y)
        : x(x)
        , y(y) {}

    inline int2(int s)
        : x(s)
        , y(s) {}

public: // @region: Operators
    inline int& operator[](int index)
    {
        assert(index > -1 && index < 2, "Index out of range");
        return ((int*)this)[index];
    }

    inline int  operator[](int index) const
    {
        assert(index > -1 && index < 2, "Index out of range");
        return ((int*)this)[index];
    }
};

union int3
{
public: // @region: Fields
    struct
    {
        int x, y, z;
    };

public: // @region: Constructors
    inline int3() {}

    inline int3(int x, int y, int z)
        : x(x)
        , y(y) 
        , z(z) {}

    inline int3(int s)
        : x(s)
        , y(s)
        , z(s) {}

public: // @region: Fields
    inline int& operator[](int index)
    {
        assert(index > -1 && index < 3, "Index out of range");
        return ((int*)this)[index];
    }

    inline int  operator[](int index) const
    {
        assert(index > -1 && index < 3, "Index out of range");
        return ((int*)this)[index];
    }
};

union int4
{
public: // @region: Fields
    struct
    {
        int x, y, z, w;
    };

public: // @region: Constructors
    inline int4() {}

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
        assert(index > -1 && index < 4, "Index out of range");
        return ((int*)this)[index];
    }

    inline int  operator[](int index) const
    {
        assert(index > -1 && index < 4, "Index out of range");
        return ((int*)this)[index];
    }
};

typedef unsigned int uint;

union uint2
{
public: // @region: Fields
    struct
    {
        uint x, y;
    };

public: // @region: Constructors
    inline uint2() {}

    inline uint2(uint x, uint y)
        : x(x)
        , y(y) {}

    inline uint2(uint s)
        : x(s)
        , y(s) {}

public: // @region: Operators
    inline uint& operator[](int index)
    {
        assert(index > -1 && index < 2, "Index out of range");
        return ((uint*)this)[index];
    }

    inline uint  operator[](int index) const
    {
        assert(index > -1 && index < 2, "Index out of range");
        return ((uint*)this)[index];
    }
};

union uint3
{
public: // @region: Fields
    struct
    {
        uint x, y, z;
    };

public: // @region: Constructors
    inline uint3() {}

    inline uint3(uint x, uint y, uint z)
        : x(x)
        , y(y) 
        , z(z) {}

    inline uint3(uint s)
        : x(s)
        , y(s)
        , z(s) {}

public: // @region: Operators
    inline uint& operator[](int index)
    {
        assert(index > -1 && index < 3, "Index out of range");
        return ((uint*)this)[index];
    }

    inline uint  operator[](int index) const
    {
        assert(index > -1 && index < 3, "Index out of range");
        return ((uint*)this)[index];
    }
};

union uint4
{
public: // @region: Fields
    struct
    {
        uint x, y, z, w;
    };

public: // @region: Constructors
    inline uint4() {}

    inline uint4(uint x, uint y, uint z, uint w)
        : x(x)
        , y(y) 
        , z(z)
        , w(w) {}

    inline uint4(int s)
        : x(s)
        , y(s)
        , z(s)
        , w(s) {}

public: // @region: Operators
    inline uint& operator[](int index)
    {
        assert(index > -1 && index < 4, "Index out of range");
        return ((uint*)this)[index];
    }

    inline uint  operator[](int index) const
    {
        assert(index > -1 && index < 4, "Index out of range");
        return ((uint*)this)[index];
    }
};

union bool2
{
public: // @region: Fields
    struct
    {
        bool x, y;
    };

public: // @region: Constructors
    inline bool2() {}

    inline bool2(bool x, bool y)
        : x(x)
        , y(y) {}

    inline bool2(bool s)
        : x(s)
        , y(s) {}

public: // @region: Operators
    inline bool& operator[](int index)
    {
        assert(index > -1 && index < 2, "Index out of range");
        return ((bool*)this)[index];
    }

    inline int  operator[](int index) const
    {
        assert(index > -1 && index < 2, "Index out of range");
        return ((bool*)this)[index];
    }
};

union bool3
{
public: // @region: Fields
    struct
    {
        bool x, y, z;
    };

public: // @region: Constructors
    inline bool3() {}

    inline bool3(bool x, bool y, bool z)
        : x(x)
        , y(y) 
        , z(z) {}

    inline bool3(bool s)
        : x(s)
        , y(s)
        , z(s) {}

public: // @region: Operators
    inline bool& operator[](int index)
    {
        assert(index > -1 && index < 3, "Index out of range");
        return ((bool*)this)[index];
    }

    inline bool  operator[](int index) const
    {
        assert(index > -1 && index < 3, "Index out of range");
        return ((bool*)this)[index];
    }
};

union bool4
{
public: // @region: Fields
    struct
    {
        bool x, y, z, w;
    };

public: // @region: Constructors
    inline bool4() {}

	inline bool4(bool x, bool y, bool z, bool w)
        : x(x)
        , y(y) 
        , z(z)
        , w(w) {}

    inline bool4(bool s)
        : x(s)
        , y(s)
        , z(s)
        , w(s) {}

public: // @region: Operators
    inline bool& operator[](int index)
    {
        assert(index > -1 && index < 4, "Index out of range");
        return ((bool*)this)[index];
    }

    inline bool  operator[](int index) const
    {
        assert(index > -1 && index < 4, "Index out of range");
        return ((bool*)this)[index];
    }
};

union float2
{
public: // @region: Fields
    struct
    {
        float x, y;
    };

public: // @region: Constructors
    inline float2() {}

    inline float2(float x, float y)
        : x(x)
        , y(y) {}

    inline float2(float s)
        : x(s)
        , y(s) {}

public: // @region: Operators
    inline float& operator[](int index)
    {
        assert(index > -1 && index < 2, "Index out of range");
        return ((float*)this)[index];
    }

    inline float  operator[](int index) const
    {
        assert(index > -1 && index < 2, "Index out of range");
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

union float3
{
public: // @region: Fielda
    struct
    {
        float x, y, z;  
    };    

public: // @region: Constructors
    inline float3() {}

    inline float3(float x, float y, float z = 0.0f)
        : x(x)
        , y(y)
        , z(z) {}

    inline float3(float s)    
        : x(s)
        , y(s)
        , z(s) {}

public: // @region: float2 -> float3
    inline float3(const float2& v)
        : x(v.x)
        , y(v.y)
        , z(0) {}

    inline operator float2(void) const
    {
        return float2(x, y);
    }

public: // @region: Operators
    inline float& operator[](int index)
    {
        assert(index > -1 && index < 3, "Index out of range");
        return ((float*)this)[index];
    }

    inline float  operator[](int index) const
    {
        assert(index > -1 && index < 3, "Index out of range");
        return ((float*)this)[index];
    }
};

union float4
{
public: // @region: Fields
    struct
    {
        float x, y, z, w; 
    };

public: // @region: Constructors
    inline float4() {}

    inline float4(const float3& xyz, float w = 0.0f)
        : x(xyz.x)
        , y(xyz.y)
        , z(xyz.z)
        , w(w) {}

    inline float4(float x, float y, float z, float w)
        : x(x)
        , y(y)
        , z(z)
        , w(w) {}

    inline float4(float s)
        : x(s)
        , y(s)
        , z(s)
        , w(s) {}

public: // @region: Operators
    inline float& operator[](int index)
    {
        assert(index > -1 && index < 4, "Index out of range");
        return ((float*)this)[index];
    }

    inline float  operator[](int index) const
    {
        assert(index > -1 && index < 4, "Index out of range");
        return ((float*)this)[index];
    }

public:
    /* Quaternion from axisangle
     */
    inline static float4 quat(const float3& axis, float angle);

    /* Convert quaternion to axisangle
     * @note: xyz is axis, w is angle
     */
    inline static float4 toaxis(const float4& quat);

    /* Convert quaternion to axisangle
     * @note: xyz is axis, w is angle
     */
    inline static void toaxis(const float4& quat, float3* axis, float* angle);

    /* Quaternion from euler
     */
    inline static float4 euler(float x, float y, float z);

    /* Quaternion from euler
     */
    inline static float4 euler(const float3& v);
};

union int2x2
{
public: // @region: Constructors
    inline int2x2() {}

    inline int2x2(const int2& m0, const int2& m1)
    {
        (*this)[0] = m0;
        (*this)[1] = m1;
    }   

    inline int2x2(int m00, int m01, int m10, int m11)
    {
        (*this)[0] = int2(m00, m01);
        (*this)[1] = int2(m10, m11);
    }

    inline int2x2(int s)
    {
        (*this)[0] = int2(s, s);
        (*this)[1] = int2(s, s);
    }

public: // @region: Operators
    inline int2& operator[](int index)
    {
        assert(index > -1 && index < 2, "Index out of range");
        return ((int2*)data)[index];
    }

    inline const int2& operator[](int index) const
    {
        assert(index > -1 && index < 2, "Index out of range");
        return ((int2*)data)[index];
    }
    
private: // @region: Internal fields
    struct
    {
        int data[2][2];
    };
};

union int3x3
{
public: // @region: Constructors
    inline int3x3() {}

    inline int3x3(const int3& m0, const int3& m1, const int3& m2)
    {
		(*this)[0] = m0;
		(*this)[1] = m1;
		(*this)[2] = m2;
    }

    inline int3x3(int m00, int m01, int m02,
                  int m10, int m11, int m12,
                  int m20, int m21, int m22)
    {
        (*this)[0] = int3(m00, m01, m02);
        (*this)[1] = int3(m10, m11, m12);
        (*this)[2] = int3(m20, m21, m22);
    }

    inline int3x3(int s)
    {
        (*this)[0] = int3(s, s, s);
        (*this)[1] = int3(s, s, s);
        (*this)[2] = int3(s, s, s);
    }

public: // @region: Operators
    inline int3& operator[](int index)
    {
        assert(index > -1 && index < 3, "Index out of range");
        return ((int3*)data)[index];
    }

    inline const int3& operator[](int index) const
    {
        assert(index > -1 && index < 3, "Index out of range");
        return ((int3*)data)[index];
    }
    
private: // @region: Internal fields
    struct
    {
        int data[3][3];
    };
};

union int4x4
{
public: // @region: Constructors
    inline int4x4() {}

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
        assert(index > -1 && index < 4, "Index out of range");
        return ((int4*)data)[index];
    }

    inline const int4& operator[](int index) const
    {
        assert(index > -1 && index < 4, "Index out of range");
        return ((int4*)data)[index];
    }
    
private: // @region: Internal fields
    struct
    {
        int data[4][4];
    };
};

union uint2x2
{
public: // @region: Constructors
    inline uint2x2() {}

    inline uint2x2(const uint2& m0, const uint2& m1)
    {
        (*this)[0] = m0;
        (*this)[1] = m1;
    }

    inline uint2x2(uint m00, uint m01, uint m10, uint m11)
    {
        (*this)[0] = uint2(m00, m01);
        (*this)[1] = uint2(m10, m11);
    }

    inline uint2x2(uint s)
    {
        (*this)[0] = uint2(s, s);
        (*this)[1] = uint2(s, s);
    }

public: // @region: Operators
    inline uint2& operator[](int index)
    {
        assert(index > -1 && index < 2, "Index out of range");
        return ((uint2*)data)[index];
    }

    inline const uint2& operator[](int index) const
    {
        assert(index > -1 && index < 2, "Index out of range");
        return ((uint2*)data)[index];
    }
    
private: // @region: Internal fields
    struct
    {
        uint data[2][2];
    };
};

union uint3x3
{
public: // @region: Constructors
    inline uint3x3() {}

    inline uint3x3(const uint3& m0, const uint3& m1, const uint3& m2)
    {
        (*this)[0] = m0;
        (*this)[1] = m1;
        (*this)[2] = m2;
    }

    inline uint3x3(uint m00, uint m01, uint m02,
                  uint m10, uint m11, uint m12,
                  uint m20, uint m21, uint m22)
    {
        (*this)[0] = uint3(m00, m01, m02);
        (*this)[1] = uint3(m10, m11, m12);
        (*this)[2] = uint3(m20, m21, m22);
    }

    inline uint3x3(uint s)
    {
        (*this)[0] = uint3(s, s, s);
        (*this)[1] = uint3(s, s, s);
        (*this)[2] = uint3(s, s, s);
    }

public: // @region: Operators
    inline uint3& operator[](int index)
    {
        assert(index > -1 && index < 3, "Index out of range");
        return ((uint3*)data)[index];
    }

    inline const uint3& operator[](int index) const
    {
        assert(index > -1 && index < 3, "Index out of range");
        return ((uint3*)data)[index];
    }
    
private: // @region: Internal fields
    struct
    {
        uint data[3][3];
    };
};

union uint4x4
{
public: // @region: Constructors
    inline uint4x4() {}

    inline uint4x4(const uint4& m0, const uint4& m1, const uint4& m2, const uint4& m3)
    {
        (*this)[0] = m0;
        (*this)[1] = m1;
        (*this)[2] = m2;
        (*this)[3] = m3;
    }

    inline uint4x4(uint m00, uint m01, uint m02, uint m03,
                   uint m10, uint m11, uint m12, uint m13,
                   uint m20, uint m21, uint m22, uint m23,
                   uint m30, uint m31, uint m32, uint m33)
    {
        (*this)[0] = uint4(m00, m01, m02, m03);
        (*this)[1] = uint4(m10, m11, m12, m13);
        (*this)[2] = uint4(m20, m21, m22, m23);
        (*this)[3] = uint4(m30, m31, m32, m33);
    }

    inline uint4x4(uint s)
    {
        (*this)[0] = uint4(s, s, s, s);
        (*this)[1] = uint4(s, s, s, s);
        (*this)[2] = uint4(s, s, s, s);
        (*this)[3] = uint4(s, s, s, s);
    }

public: // Constructors
    inline uint4& operator[](int index)
    {
        assert(index > -1 && index < 4, "Index out of range");
        return ((uint4*)data)[index];
    }

    inline const uint4& operator[](int index) const
    {
        assert(index > -1 && index < 4, "Index out of range");
        return ((uint4*)data)[index];
    }
    
private: // @region: Internal fields
    struct
    {
        uint data[4][4];
    };
};

union bool2x2
{
public: // @region: Constructors
    inline bool2x2() {}

    inline bool2x2(const bool2& m0, const bool2& m1)
    {
		(*this)[0] = m0;
		(*this)[1] = m1;
    }

    inline bool2x2(bool m00, bool m01, bool m10, bool m11)
    {
        (*this)[0] = bool2(m00, m01);
        (*this)[1] = bool2(m10, m11);
    }

    inline bool2x2(bool s)
    {
        (*this)[0] = bool2(s, s);
        (*this)[1] = bool2(s, s);
    }

public: // @region: Operators
    inline bool2& operator[](int index)
    {
        assert(index > -1 && index < 2, "Index out of range");
        return ((bool2*)data)[index];
    }

    inline const bool2& operator[](int index) const
    {
        assert(index > -1 && index < 2, "Index out of range");
        return ((bool2*)data)[index];
    }
    
private: // @region: Internal fields
    struct
    {
        bool data[2][2];
    };
};

union bool3x3
{
public: // @region: Constructors
    inline bool3x3() {}

    inline bool3x3(const bool3& m0, const bool3& m1, const bool3& m2)
    {

        (*this)[0] = m0;
        (*this)[1] = m1;
        (*this)[2] = m2;
    }

    inline bool3x3(bool m00, bool m01, bool m02,
                   bool m10, bool m11, bool m12,
                   bool m20, bool m21, bool m22)
    {
        (*this)[0] = bool3(m00, m01, m02);
        (*this)[1] = bool3(m10, m11, m12);
        (*this)[2] = bool3(m20, m21, m22);
    }

    inline bool3x3(bool s)
    {
        (*this)[0] = bool3(s, s, s);
        (*this)[1] = bool3(s, s, s);
        (*this)[2] = bool3(s, s, s);
    }

public: // @region: Operators
    inline bool3& operator[](int index)
    {
        assert(index > -1 && index < 3, "Index out of range");
        return ((bool3*)data)[index];
    }

    inline const bool3& operator[](int index) const
    {
        assert(index > -1 && index < 3, "Index out of range");
        return ((bool3*)data)[index];
    }
    
private: // @region: Internal fields
    struct
    {
        bool data[3][3];
    };
};

union bool4x4
{
public: // @region: Constructors
    inline bool4x4() {}

    inline bool4x4(const bool4& m0, const bool4& m1, const bool4& m2, const bool4& m3)
    {
        (*this)[0] = m0;
        (*this)[1] = m1;
        (*this)[2] = m2;
        (*this)[3] = m3;
    }

    inline bool4x4(bool m00, bool m01, bool m02, bool m03,
                   bool m10, bool m11, bool m12, bool m13,
                   bool m20, bool m21, bool m22, bool m23,
                   bool m30, bool m31, bool m32, bool m33)
    {
        (*this)[0] = bool4(m00, m01, m02, m03);
        (*this)[1] = bool4(m10, m11, m12, m13);
        (*this)[2] = bool4(m20, m21, m22, m23);
        (*this)[3] = bool4(m30, m31, m32, m33);
    }

    inline bool4x4(bool s)
    {
        (*this)[0] = bool4(s, s, s, s);
        (*this)[1] = bool4(s, s, s, s);
        (*this)[2] = bool4(s, s, s, s);
        (*this)[3] = bool4(s, s, s, s);
    }

public: // Constructors
    inline bool4& operator[](int index)
    {
        assert(index > -1 && index < 4, "Index out of range");
        return ((bool4*)data)[index];
    }

    inline const bool4& operator[](int index) const
    {
        assert(index > -1 && index < 4, "Index out of range");
        return ((bool4*)data)[index];
    }
    
private: // @region: Internal fields
    struct
    {
        bool data[4][4];
    };
};

union float2x2
{
public: // @region: Constructors
    inline float2x2() {}

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
        assert(index > -1 && index < 2, "Index out of range");
        return ((float2*)data)[index];
    }

    inline const float2& operator[](int index) const
    {
        assert(index > -1 && index < 2, "Index out of range");
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
union float3x3
{
public: // @region: Constructors
    inline float3x3() {}

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
        assert(index > -1 && index < 3, "float3x3[]: Index out of range");
        return ((float3*)data)[index];
    }

    inline const float3& operator[](int index) const
    {
        assert(index > -1 && index < 3, "float3x3[]: Index out of range");
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

union float4x4
{
public: // @region: Constructors
    inline float4x4() {}

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
        assert(index > -1 && index < 4, "Index out of range");
        return ((float4*)data)[index];
    }

    inline const float4& operator[](int index) const
    {
        assert(index > -1 && index < 4, "Index out of range");
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

    static float4x4 rotation(const float4& quaternion);
    static float4x4 rotation(const float3& axis, float angle);
    static float4x4 rotation(float x, float y, float z, float angle);

    static float4x4 rotation_x(float angle);
    static float4x4 rotation_y(float angle);
    static float4x4 rotation_z(float angle);

    static float4x4 lookat(const float3& eye, const float3& target, const float3& up);

    static float4x4 ortho(float l, float r, float b, float t, float n, float f);
    static float4x4 frustum(float l, float r, float b, float t, float n, float f);
    static float4x4 perspective(float fov, float aspect, float znear, float zfar);

    RIKU_API static void decompose(const float4x4& m, float3* scalation, float4* quaternion, float3* translation);
    RIKU_API static void decompose(const float4x4& m, float3* scalation, float3* axis, float* angle, float3* translation);
    
private: // @region: Internal fields
    struct
    {
        float data[4][4];
    };
};