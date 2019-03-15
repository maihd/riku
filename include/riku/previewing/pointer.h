// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#pragma once

#include "./core.h"

//
// Ptr types
//

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
        memory::dealloc(raw);
    }

public:
    inline UniPtr(UniPtr<T>&& other)
        : raw(other.raw)
    {
        other.raw = NULL;
    }

    inline UniPtr<T>& operator=(UniPtr<T>&& other)
    {
        raw = other.raw; other.raw = NULL; return *this;
    }

public:
    inline       T* operator->(void)       { return raw; }
    inline const T* operator->(void) const { return raw; }
};

template <typename T>
struct SharedPtr
{
public:
    T*        raw;
    RefCount* ref;

public:
    inline SharedPtr(T* ptr)
        : raw(ptr)
        , ref(new RefCount()) {}

    inline ~SharedPtr(void)
    {
        if (ref->release() <= 0)
        {
            memory::dealloc(raw);
            delete ref;
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
        // Should release old pointer
        this->~SharedPtr();

        // Assign new pointer
        raw = other.raw;
        ref = other.ref; 
        other.raw = 0;
        other.ref = 0;

        return *this;
    }

    inline SharedPtr(const SharedPtr<T>& other)
        : raw(other.raw)
        , ref(other.ref) 
    {
        ref->retain();
    }

    inline SharedPtr<T>& operator=(const SharedPtr<T>& other)
    {
        // Should release old pointer
        this->~SharedPtr();

        // Assign new pointer
        raw = other.raw;
        ref = other.ref;
        ref->retain();
        return *this;
    }

public:
    inline       T* operator->(void)       { return raw; }
    inline const T* operator->(void) const { return raw; }
};

// WeakPtr: tell the others that donot make hurt the pointer
template <typename T>
struct WeakPtr
{
    T* raw;
    inline WeakPtr(T* ptr) : raw(ptr) {}

    inline       T* operator->(void)       { return raw; }
    inline const T* operator->(void) const { return raw; }
};