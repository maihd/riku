// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#pragma once

#include "./base.h"
#include "./bool4.h"

union bool4x4
{
public: // @region: Constructors
    inline bool4x4(void) 
    {
        (*this)[0] = bool4(1, 0, 0, 0);
        (*this)[1] = bool4(0, 1, 0, 0);
        (*this)[2] = bool4(0, 0, 1, 0);
        (*this)[3] = bool4(0, 0, 0, 1);
    }

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
        ASSERT(index > -1 && index < 4, "Index out of range");
        return ((bool4*)data)[index];
    }

    inline const bool4& operator[](int index) const
    {
        ASSERT(index > -1 && index < 4, "Index out of range");
        return ((bool4*)data)[index];
    }
    
private: // @region: Internal fields
    struct
    {
        bool data[4][4];
    };
};

namespace math
{
    inline bool all(const bool4x4& v)
    {
        return
            v[0][0] && v[0][1] && v[0][2] && v[0][3] &&
            v[1][0] && v[1][1] && v[1][2] && v[1][3] &&
            v[2][0] && v[2][1] && v[2][2] && v[2][3] &&
            v[3][0] && v[3][1] && v[3][2] && v[3][3];
    }

    inline bool any(const bool4x4& v)
    {
        return 
            v[0][0] || v[0][1] || v[0][2] || v[0][3] ||
            v[1][0] || v[1][1] || v[1][2] || v[1][3] ||
            v[2][0] || v[2][1] || v[2][2] || v[2][3] ||
            v[3][0] || v[3][1] || v[3][2] || v[3][3];
    }
}