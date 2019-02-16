#pragma once

template <typename T>
struct Array 
{
public:
    T* buffer;

public:
    inline Array()
        : buffer(nullptr)
    {
    }

    inline ~Array()
    {
    }

public:
    inline int size()
    {
        return buffer ? ((int*)buffer - 2)[0] : 0;
    }

    inline int count()
    {
        return buffer ? ((int*)buffer - 2)[1] : 0;
    }

public:
    inline T& operator[](int index)
    {
        return buffer[index];
    }

    inline const T& operator[](int index) const
    {
        return buffer[index];
    }
};

namespace array 
{
    template <typename T>
    bool push(Array<T>& array, const T& value)
    {
        // Not implement yet
        return false;   
    }
}