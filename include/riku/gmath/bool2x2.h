 // Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#pragma once

#include "./base.h"
#include "./bool2.h"

union bool2x2
{
public: // @region: Constructors
    inline bool2x2()
    {
        (*this)[0] = bool2(1, 0);
        (*this)[1] = bool2(0, 1);
    }

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
        ASSERT(index > -1 && index < 2, "Index out of range");
        return ((bool2*)data)[index];
    }

    inline const bool2& operator[](int index) const
    {
        ASSERT(index > -1 && index < 2, "Index out of range");
        return ((bool2*)data)[index];
    }
    
private: // @region: Internal fields
    struct
    {
        bool data[2][2];
    };
};

namespace math
{
    inline bool all(const bool2x2& v)
    {
        return v[0][0] && v[0][1] && v[1][0] && v[1][1];
    }

    inline bool any(const bool2x2& v)
    {
        return v[0][0] || v[0][1] || v[1][0] || v[1][1];
    }
}