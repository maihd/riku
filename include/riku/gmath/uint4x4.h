// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#pragma once

#include "./base.h"
#include "./uint4.h"
#include "./bool4x4.h"

union uint4x4
{
public: // @region: Constructors
    inline uint4x4(void)
    {
        (*this)[0] = uint4(1, 0, 0, 0);
        (*this)[1] = uint4(0, 1, 0, 0);
        (*this)[2] = uint4(0, 0, 1, 0);
        (*this)[3] = uint4(0, 0, 0, 1);
    }

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
        ASSERT(index > -1 && index < 4, "Index out of range");
        return ((uint4*)data)[index];
    }

    inline const uint4& operator[](int index) const
    {
        ASSERT(index > -1 && index < 4, "Index out of range");
        return ((uint4*)data)[index];
    }
    
private: // @region: Internal fields
    struct
    {
        uint data[4][4];
    };
};

namespace math
{
    inline bool all(const uint4x4& v)
    {
        return
            v[0][0] != 0 && v[0][1] != 0 && v[0][2] != 0 && v[0][3] != 0 &&
            v[1][0] != 0 && v[1][1] != 0 && v[1][2] != 0 && v[1][3] != 0 &&
            v[2][0] != 0 && v[2][1] != 0 && v[2][2] != 0 && v[2][3] != 0 &&
            v[3][0] != 0 && v[3][1] != 0 && v[3][2] != 0 && v[3][3] != 0;
    }

    inline bool any(const uint4x4& v)
    {
        return 
            v[0][0] != 0 || v[0][1] != 0 || v[0][2] != 0 || v[0][3] != 0 ||
            v[1][0] != 0 || v[1][1] != 0 || v[1][2] != 0 || v[1][3] != 0 ||
            v[2][0] != 0 || v[2][1] != 0 || v[2][2] != 0 || v[2][3] != 0 ||
            v[3][0] != 0 || v[3][1] != 0 || v[3][2] != 0 || v[3][3] != 0;
    }
}

