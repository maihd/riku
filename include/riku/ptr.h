#pragma once

#include "./types.h"
#include <stdlib.h>

// Raw ptr
template <typename TRet>
struct PtrTrait
{
    using Type = TRet*;
};

template <typename TRet, typename... TArgs>
struct PtrTrait<TRet(TArgs...)>
{
    using Type = TRet(*)(TArgs...);
};

template <typename TRet, typename... TArgs>
using Ptr = PtrTrait<TRet(TArgs...)>::Type; // Ex: using FuncPtr = Ptr<void()>;

template <typename T>
struct UniPtr 
{
public:
    T* raw;

public:
    inline UniPtr(T* ptr)
        : raw(ptr)
    {
    }

    inline ~UniPtr(void)
    {
        free(raw);
    }

public:
    inline UniPtr(UniPtr<T>&& other)
        : raw(other.raw)
    {
        other.raw = nullptr;
    }

    inline UniPtr<T>& operator=(UniPtr<T>&& other)
    {
        raw = other.raw;
        other.raw = nullptr;
        return *this;
    }

public:
    inline T* operator->(void)
    {
        return raw;
    }

    inline const T* operator->(void) const
    {
        return raw;
    }
};

template <typename T>
struct SharedPtr
{
public:
    T*  raw;
    int ref;

public:
    inline SharedPtr(T* ptr)
        : raw(ptr)
        , ref(1) {}

    inline ~SharedPtr(void)
    {
        if (ref <= 1)
        {
            free(raw);
        }
    }

public:
    inline SharedPtr(SharedPtr<T>&& other)
        : raw(other.raw)
        , ref(other.ref) 
    {
        other.raw = 0;
        other.ref = 0;
    }

    inline SharedPtr<T>& operator=(SharedPtr<T>&& other)
    {
        raw = other.raw;
        ref = other.ref; 
        other.raw = 0;
        other.ref = 0;

        return *this;
    }

    inline SharedPtr(const SharedPtr<T>& other)
        : raw(other.raw)
        , ref(other.ref + 1) 
    {
    }

    inline SharedPtr<T>& operator=(const SharedPtr<T>& other)
    {
        raw = other.raw;
        ref = other.ref + 1;

        return *this;
    }
};