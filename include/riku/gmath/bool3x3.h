// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#pragma once

#include "./base.h"
#include "./bool3.h"

union bool3x3
{
public: // @region: Constructors
    inline bool3x3()
    {
        (*this)[0] = bool3(1, 0, 0);
        (*this)[1] = bool3(0, 1, 0);
        (*this)[2] = bool3(0, 0, 1);
    }

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
        ASSERT(index > -1 && index < 3, "Index out of range");
        return ((bool3*)data)[index];
    }

    inline const bool3& operator[](int index) const
    {
        ASSERT(index > -1 && index < 3, "Index out of range");
        return ((bool3*)data)[index];
    }
    
private: // @region: Internal fields
    struct
    {
        bool data[3][3];
    };
};

namespace math
{
    inline bool all(const bool3x3& v)
    {
        return
            v[0][0] && v[0][1] && v[0][2] &&
            v[1][0] && v[1][1] && v[1][2] &&
            v[2][0] && v[2][1] && v[2][2];
    }

    inline bool any(const bool3x3& v)
    {
        return
            v[0][0] || v[0][1] || v[0][2] ||
            v[1][0] || v[1][1] || v[1][2] ||
            v[2][0] || v[2][1] || v[2][2];
    }
}