#pragma once

#include <stdarg.h>

#ifndef RIKU_API
#define RIKU_API
#endif

#if defined(_MSC_VER) || defined(__MINGW32__)
#define OS_WINDOWS 1
#else
#define OS_WINDOWS 0
#endif

#if defined(__linux__)
#define OS_LINUX 1
#else
#define OS_LINUX 0
#endif

#if defined(__unix__)
#define OS_UNIX 1
#else
#define OS_UNIX 0
#endif

#if defined(__ANDROID__)
#define OS_ANDROID 1
#else
#define OS_ANDROID 0
#endif

#if defined(__MINGW64__) || defined(__x86_64__) || defined(__X86_64__) || defined(_M_X64)
#define RUNTIME_64BITS
#else
#define RUNTIME_32BITS
#endif

#if __GNUC__ && !__clang__
#error "riku: No GCC support, sorry man."
#else
#define propdef(getter, setter)   __declspec(property(get=getter, put=setter))
#define propdef_readonly(getter)  __declspec(property(get=getter))
#define propdef_writeonly(setter) __declspec(property(put=setter))
#endif

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
#define LLONG_MAX     9223372036854775807i64        // maximum signed long long int value
#define LLONG_MIN   (-9223372036854775807i64 - 1)   // minimum signed long long int value
#define ULLONG_MAX    0xffffffffffffffffui64        // maximum unsigned long long int value
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
#define LLONG_MAX     9223372036854775807i64        // maximum signed long long int value
#define LLONG_MIN   (-9223372036854775807i64 - 1)   // minimum signed long long int value
#define ULLONG_MAX    0xffffffffffffffffui64        // maximum unsigned long long int value
#endif

#if (UINT_MAX != 0xffffffff)
#define int   int32_t
#define long  int64_t
#define short int16_t
#endif

using uint    = unsigned int;
using ulong   = unsigned long;
using ushort  = unsigned short;

using byte    = unsigned char;
using sbyte   = char;

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

// ArgsList: alias of va_list
using ArgsList = va_list;
#define argslist_begin(args_list, prev_arg) va_start(args_list, prev_arg)
#define argslist_end(args_list)             va_end(args_list)
#define argslist_copy(dst, src)             va_copy(dst, src)

// Assertion helper
#include <assert.h> // Include 
#undef assert       // to remove std assert
#if !defined(NDEBUG) || !NDEBUG
#define assert(exp, fmt, ...) ((exp) ? (void)::__riku::__assert_print(#exp, __FUNCTION__, __FILE__, __LINE__, fmt, __VA_ARGS__) : (void)0)
#else
#define assert(exp, fmt, ...)
#endif

//
// Memory management
//

#if OS_WINDOWS
extern "C" void* __cdecl _alloca(usize size);
#define stackalloc _alloca
#else
extern "C" void* alloca(usize size);
#define stackalloc alloca
#endif

namespace memory
{
    void* alloc(usize size);
    void  dealloc(void* ptr);
    void* realloc(void* ptr, usize size);

    void* init(void* dst, int val, usize size);
    void* copy(void* dst, const void* src, usize size);
    void* move(void* dst, const void* src, usize size);
}

struct RefCount
{
public:
    int refcount;

public:
    constexpr RefCount(void)
        : refcount(1) {}

public:
    inline int retain(void)  { return ++refcount; };
    inline int release(void) { return --refcount; };
};

#if 0 && EXPERIMENTAL
__forceinline void* operator new(usize size) 
{
	return ::memory::alloc(size);
}
__forceinline void operator delete(void* ptr) 
{
	::memory::dealloc(ptr);
}
__forceinline void *operator new[](size_t size) 
{
	return ::memory::alloc(size);
}
__forceinline void operator delete[](void* ptr) 
{
	::memory::dealloc(ptr);
}
#endif

// 
// C-String operator
// 
namespace string
{
    usize length(const char* s);
}

//
// Right value trait
//

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

// Simple memory buffer
struct Buffer 
{
public:
    byte* data;

public:
    __forceinline Buffer()
        : data(nullptr) {}

    __forceinline ~Buffer()
    {
        memory::dealloc(data ? (usize*)data - 1 : nullptr);
    }

public:
    __forceinline Buffer(Buffer&& buffer)
        : data(buffer.data)
    {
        buffer.data = nullptr;
    }

    __forceinline Buffer& operator=(Buffer&& buffer)
    {
        data = buffer.data;
        buffer.data = nullptr;
        return *this;
    }

public:
    propdef_readonly(get_length) usize length;
    __forceinline usize get_length(void) const
    {
        return data ? *((usize*)data - 1) : 0;
    }

public:
    __forceinline operator byte*(void)
    {
        return data;
    }

    __forceinline operator const byte*(void) const
    {
        return data;
    }

public: // Factory functions
    static Buffer alloc(usize length);
};

//
// String types
//

struct String 
{
public: // Members
    struct Buffer
    {
        int  length;
        int  capacity;
        char characters[1];
    };
    Buffer* buffer;

public:
    inline String() 
        : buffer(nullptr) {}

    inline ~String() 
    { 
        if (buffer)
        {
            memory::dealloc(buffer); 
        }
    }

public:
    inline String(const char* buffer)
        : String(buffer, string::length(buffer))
    {
    }

    inline String(const char* buffer, int length)
    {
        if (buffer)
        {
            this->buffer = (Buffer*)memory::alloc(sizeof(Buffer) + length);
            this->buffer->length   = length;
            this->buffer->capacity = length;

            memory::copy(this->buffer->characters, buffer, length + 1);
        }
        else
        {
            this->buffer = nullptr;
        }
    }

public: // RAII
    inline String(String&& other)
        : buffer(other.buffer)
    {
        other.buffer = nullptr;
    }

    inline String& operator=(String&& other)
    {
        memory::dealloc(buffer ? buffer - sizeof(int) : nullptr);
        buffer = other.buffer;
        other.buffer = nullptr;
        return *this;
    }


public: // Copy
    inline String(const String& other)
    {
        if (other.buffer)
        {
            int length = other.length;

            buffer = (Buffer*)memory::alloc(sizeof(Buffer) + length);
            buffer->length   = length;
            buffer->capacity = length;

            memory::copy(buffer->characters, other.buffer->characters, length + 1);
        }
        else
        {
            buffer = nullptr;
        }
    }

    inline String& operator=(const String& other)
    {
        if (other.buffer)
        {
            int length = other.length;
            if (buffer->capacity < length)
            {
                buffer = (Buffer*)memory::realloc(buffer, sizeof(Buffer) + length);
                buffer->capacity = length;
            }

            buffer->length = length;
            memory::copy(buffer->characters, other.buffer->characters, length + 1);
        }
        else if (buffer)
        {
            buffer->length        = 0;
            buffer->characters[0] = 0;
        }
        return *this;
    }

public:
    propdef_readonly(get_length) int length;
    propdef_readonly(get_capacity) int capacity;

    inline int get_length(void) const
    {
        return buffer ? buffer->length : 0;
    }

    inline int get_capacity(void) const
    {
        return buffer ? buffer->capacity : 0;
    }

public:
    inline operator char*(void)
    {
        return buffer ? buffer->characters : nullptr;
    }

    inline operator const char*(void) const
    {
        return buffer ? buffer->characters : nullptr;
    } 
};

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
        other.raw = nullptr;
    }

    inline UniPtr<T>& operator=(UniPtr<T>&& other)
    {
        raw = other.raw; other.raw = nullptr; return *this;
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

// Internal function
namespace __riku 
{
    RIKU_API void __assert_print(const char* exp, const char* func, const char* file, int line, const char* fmt, ...);
}

// Console
namespace console
{
    RIKU_API void log(const char* fmt, ...);
    RIKU_API void log_info(const char* fmt, ...);
    RIKU_API void log_warn(const char* fmt, ...);
    RIKU_API void log_error(const char* fmt, ...);

    RIKU_API void log_args(const char* fmt, ArgsList args_list);
    RIKU_API void log_info_args(const char* fmt, ArgsList args_list);
    RIKU_API void log_warn_args(const char* fmt, ArgsList args_list);
    RIKU_API void log_error_args(const char* fmt, ArgsList args_list);
}

// Current process
namespace process
{
    RIKU_API const char* cwd(void);
    RIKU_API usize       cwd(char* buffer, usize length);
    RIKU_API bool        chdir(const char* directory);

    RIKU_API void        exit(int code);
    RIKU_API void        abort(void);
}