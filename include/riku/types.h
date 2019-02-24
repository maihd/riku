#pragma once

#include <limits.h>
#include <stdint.h>

// Redefine primitive types

#if (UINT_MAX != 0xffffffff)
#define int   int32_t
#define long  int64_t
#define short int16_t
#endif

using uint   = uint32_t;
using ulong  = uint64_t;
using ushort = uint16_t;

using byte   = uint8_t;
using sbyte  = int8_t;

using str    = const char*;

// Memory address and size

using iptr   = intptr_t;
using uptr   = uintptr_t;

#if defined(__x86_64__) || UINTPTR_MAX == 0xffffffffffffffff
using usize  = uint64_t;
using isize  = int64_t;
#else 
using usize  = uint32_t;
using isize  = int32_t;
#endif

// Right value trait
template <typename T>
struct WithoutRefTrait
{
    using Type = T;
};

template <typename T>
struct WithoutRefTrait<T&>
{
    using Type = T;
};

template <typename T>
struct WithoutRefTrait<T&&>
{
    using Type = T;
};

template <typename T>
using WithoutRef = typename WithoutRefTrait<T>::Type;

template <typename T>
inline WithoutRef<T>&& make_rvalue(T&& value)
{
    return (static_cast<WithoutRef<T>&&>(value));
}

// Option
template <typename T>
struct Option
{
public: // Metatype
    using ValueType = T;

public:
    ValueType value;
    bool      has_value;

public:
    inline Option(void)
        : value()
        , has_value(false) {}

    inline Option(ValueType&& value)
        : value(make_rvalue(value))
        , has_value(true) {}

    inline Option(const ValueType& value)
        : value(value)
        , has_value(true) {}

    inline Option& operator=(ValueType&& value)
    {
        this->value = make_rvalue(value);
        this->has_value = true;
        return *this;
    }

    inline Option& operator=(const ValueType& value)
    {
        this->value = value;
        this->has_value = true;
        return *this;
    }

public:
    inline operator bool() const { return has_value; }
};