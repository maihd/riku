// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#pragma once

#include "./base.h"
#include "./int3.h"
#include "./bool3.h"

union int3x3
{
public: // @region: Constructors
    inline int3x3(void)
    {
        (*this)[0] = int3(1, 0, 0);
        (*this)[1] = int3(0, 1, 0);
        (*this)[2] = int3(0, 0, 1);
    }

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
        ASSERT(index > -1 && index < 3, "Index out of range");
        return ((int3*)data)[index];
    }

    inline const int3& operator[](int index) const
    {
        ASSERT(index > -1 && index < 3, "Index out of range");
        return ((int3*)data)[index];
    }
    
private: // @region: Internal fields
    struct
    {
        int data[3][3];
    };
};

namespace math
{
    inline bool all(const int3x3& v)
    {
        return
            v[0][0] != 0 && v[0][1] != 0 && v[0][2] != 0 &&
            v[1][0] != 0 && v[1][1] != 0 && v[1][2] != 0 &&
            v[2][0] != 0 && v[2][1] != 0 && v[2][2] != 0;
    }

    inline bool any(const int3x3& v)
    {
        return
		    v[0][0] != 0 || v[0][1] != 0 || v[0][2] != 0 ||
		    v[1][0] != 0 || v[1][1] != 0 || v[1][2] != 0 ||
		    v[2][0] != 0 || v[2][1] != 0 || v[2][2] != 0;
    }
}

