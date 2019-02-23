#pragma once

#include "./define.h"
#include "./property.h"

template <typename TRet, typename ...TArgs>
struct Func;

template <typename TRet, typename ...TArgs>
struct Func<TRet(TArgs...)>
{
public: // 
    void* buffer;

public: // Properties
    propdef_readonly(get_type) int type;

public: // Properties implement
    inline int get_type() const 
    {
        return buffer ? ((int*)buffer)[0] : 0; 
    }

public: // Operators
    inline TRet operator(TArgs... args) const
    {
        return TRet();
    }
};