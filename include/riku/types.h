#pragma once

// Redefine primitive types

#define DOUBLE_DECIMAL_DIG  17                      // # of decimal digits of rounding precision
#define DOUBLE_DIG          15                      // # of decimal digits of precision
#define DOUBLE_EPSILON      2.2204460492503131e-016 // smallest such that 1.0+DBL_EPSILON != 1.0
#define DOUBLE_HAS_SUBNORM  1                       // type does support subnormal numbers
#define DOUBLE_MANT_DIG     53                      // # of bits in mantissa
#define DOUBLE_MAX          1.7976931348623158e+308 // max value
#define DOUBLE_MAX_10_EXP   308                     // max decimal exponent
#define DOUBLE_MAX_EXP      1024                    // max binary exponent
#define DOUBLE_MIN          2.2250738585072014e-308 // min positive value
#define DOUBLE_MIN_10_EXP   (-307)                  // min decimal exponent
#define DOUBLE_MIN_EXP      (-1021)                 // min binary exponent
#define DOUBLE_RADIX        2                       // exponent radix
#define DOUBLE_TRUE_MIN     4.9406564584124654e-324 // min positive value

#define FLOAT_DECIMAL_DIG  9                       // # of decimal digits of rounding precision
#define FLOAT_DIG          6                       // # of decimal digits of precision
#define FLOAT_EPSILON      1.192092896e-07F        // smallest such that 1.0+FLT_EPSILON != 1.0
#define FLOAT_HAS_SUBNORM  1                       // type does support subnormal numbers
#define FLOAT_GUARD        0
#define FLOAT_MANT_DIG     24                      // # of bits in mantissa
#define FLOAT_MAX          3.402823466e+38F        // max value
#define FLOAT_MAX_10_EXP   38                      // max decimal exponent
#define FLOAT_MAX_EXP      128                     // max binary exponent
#define FLOAT_MIN          1.175494351e-38F        // min normalized positive value
#define FLOAT_MIN_10_EXP   (-37)                   // min decimal exponent
#define FLOAT_MIN_EXP      (-125)                  // min binary exponent
#define FLOAT_NORMALIZE    0
#define FLOAT_RADIX        2                       // exponent radix
#define FLOAT_TRUE_MIN     1.401298464e-45F        // min positive value

#if defined(_MSC_VER) || defined(__unix__)
#define SHORT_MIN   (-32768)                        // minimum (signed) short value
#define SHORT_MAX     32767                         // maximum (signed) short value
#define USHORT_MAX    0xffff                        // maximum unsigned short value
#define INT_MIN     (-2147483647 - 1)               // minimum (signed) int value
#define INT_MAX       2147483647                    // maximum (signed) int value
#define UINT_MAX      0xffffffff                    // maximum unsigned int value
#define LONG_MIN    (-2147483647L - 1)              // minimum (signed) long value
#define LONG_MAX      2147483647L                   // maximum (signed) long value
#define ULONG_MAX     0xffffffffUL                  // maximum unsigned long value
#define LLONG_MAX     9223372036854775807L64        // maximum signed long long int value
#define LLONG_MIN   (-9223372036854775807L64 - 1)   // minimum signed long long int value
#define ULLONG_MAX    0xffffffffffffffffuL64        // maximum unsigned long long int value
#else
#define SHORT_MIN   (-32768)                        // minimum (signed) short value
#define SHORT_MAX     32767                         // maximum (signed) short value
#define USHORT_MAX    0xffff                        // maximum unsigned short value
#define INT_MIN     (-2147483647 - 1)               // minimum (signed) int value
#define INT_MAX       2147483647                    // maximum (signed) int value
#define UINT_MAX      0xffffffff                    // maximum unsigned int value
#define LONG_MIN    (-2147483647L - 1)              // minimum (signed) long value
#define LONG_MAX      2147483647L                   // maximum (signed) long value
#define ULONG_MAX     0xffffffffUL                  // maximum unsigned long value
#define LLONG_MAX     9223372036854775807L64        // maximum signed long long int value
#define LLONG_MIN   (-9223372036854775807L64 - 1)   // minimum signed long long int value
#define ULLONG_MAX    0xffffffffffffffffuL64        // maximum unsigned long long int value
#endif

#if (UINT_MAX != 0xffffffff)
#define int   int32_t
#define long  int64_t
#define short int16_t
#endif

using uint   = unsigned int;
using ulong  = unsigned long;
using ushort = unsigned short;

using byte   = unsigned char;
using sbyte  = char;

using str    = const char*;

// Memory address and size

#if defined(__x86_64__) || UINTPTR_MAX == 0xffffffffffffffff
using usize  = ulong;
using isize  = long;
#else 
using usize  = uint;
using isize  = int;
#endif

using iptr = isize;
using uptr = usize;

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