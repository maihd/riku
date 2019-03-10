#pragma once

#if defined(__GNUC__) && !defined(__clang__)
#error "riku: No GCC support, sorry man."
#endif

#if defined(_MSC_VER) || defined(_WIN32)
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

#if defined(__EMSCRIPTEN__)
#define OS_WEB 1
#else
#define OS_WEB 0
#endif

#if defined(__MINGW64__) || defined(__x86_64__) || defined(__X86_64__) || defined(_M_X64) || defined(__aarch64__)
#define RUNTIME_64BITS 1
#define RUNTIME_32BITS 0
#else
#define RUNTIME_64BITS 0
#define RUNTIME_32BITS 1
#endif

#if defined(__MIPSEL__) || defined(__LITTLE_ENDIAN__)
#define OS_BIG_ENDIAN    0
#define OS_LITTLE_ENDIAN 1
#else
#define OS_BIG_ENDIAN    1
#define OS_LITTLE_ENDIAN 0
#endif

#ifndef __rikuapi
#   ifdef RIKU_SHARED
#       if OS_WINDOWS
#           ifdef RIKU_EXPORT
#               define __rikuapi __declspec(dllexport)
#           else
#               define __rikuapi __declspec(dllimport)
#           endif
#       else
#           define __rikuapi __attribute__((visible("default")))
#       endif
#   else
#       define __rikuapi
#   endif
#endif

#define propdef(getter, setter)   __declspec(property(get=getter, put=setter))
#define propdef_readonly(getter)  __declspec(property(get=getter))
#define propdef_writeonly(setter) __declspec(property(put=setter))

#define __threadstatic __declspec(thread) static

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

#if RUNTIME_64BITS
using usize  = ulong;
using isize  = long;
#else 
using usize  = uint;
using isize  = int;
#endif

using iptr = isize;
using uptr = usize;

struct NullPtr
{
    template <typename T>
    constexpr operator T* () const
    {
        return (T*)0;
    }
};

// ArgsList: alias of va_list
#include <stdarg.h>
using ArgsList = va_list;
#define argslist_begin(args_list, prev_arg) va_start(args_list, prev_arg)
#define argslist_end(args_list)             va_end(args_list)
#define argslist_copy(dst, src)             va_copy(dst, src)

// Assertion helper
#include <assert.h> // Include 
#undef assert       // to remove std assert
#define always_assert(exp, fmt, ...) (!(exp) ? (void)::__assert_abort(#exp, __FUNCTION__, __FILE__, __LINE__, fmt, ##__VA_ARGS__) : (void)0)
#if !defined(NDEBUG) || !NDEBUG
#define assert(exp, fmt, ...) always_assert(exp, fmt, ##__VA_ARGS__)
#else
#define assert(exp, fmt, ...)
#endif

// Assertion functions
__rikuapi void __assert_abort(const char* exp, const char* func, const char* file, int line, const char* fmt, ...);

//
// Memory management
//

#if OS_WINDOWS
#include <malloc.h>
#define stackalloc _alloca
#else
#define stackalloc __builtin_alloca 
#endif

namespace memory
{
    __rikuapi void* alloc(usize size);
    __rikuapi void  dealloc(void* ptr);
    __rikuapi void* realloc(void* ptr, usize size);

    __rikuapi void* init(void* dst, int val, usize size);
    __rikuapi void* copy(void* dst, const void* src, usize size);
    __rikuapi void* move(void* dst, const void* src, usize size);
}

struct RefCount
{
public:
    int __refcount; // __ for avoid member collision.

public:
    constexpr RefCount(void) : __refcount(1) {}

public:
    inline int retain(void)  { return ++__refcount; };
    inline int release(void) { return --__refcount; };
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

struct NewDummy {};
__forceinline void* operator new   (usize, NewDummy, void* ptr) { return ptr; }
__forceinline void  operator delete(void*, NewDummy, void*)     {             }

template <typename T, typename... Args>
__forceinline T* init(void* ptr, Args...args)
{
    return new (NewDummy(), ptr) T(args...);
}

template <typename T, typename... Args>
__forceinline T* create(Args...args)
{
    return new (NewDummy(), memory::alloc(sizeof(T))) T(args...);
}

template <typename T>
__forceinline void destroy(T* ptr)
{
    if (ptr)
    {
        ptr->~T();
        memory::dealloc(ptr);
    }
}

template <typename T>
__forceinline T* create_array(long count)
{
    assert(count > 0, "Number of items must be non-zero positive");
    return new (NewDummy(), memory::alloc(count * sizeof(T))) T[count];
}

template <typename T>
__forceinline void destroy_array(T* ptr)
{
    if (ptr)
    {
        ptr->~T();
        memory::dealloc((void*)ptr);
    }
}

// 
// C-String operator
// 
namespace string
{
    __rikuapi usize length(const char* s);
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
__forceinline WithoutRef<T>&& make_rvalue(T&& value)
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
        : data(NULL) {}

    __forceinline ~Buffer()
    {
        memory::dealloc(data ? (usize*)data - 1 : NULL);
    }

public:
    __forceinline Buffer(Buffer&& buffer)
        : data(buffer.data)
    {
        buffer.data = NULL;
    }

    __forceinline Buffer& operator=(Buffer&& buffer)
    {
        data = buffer.data;
        buffer.data = NULL;
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
    __rikuapi static Buffer alloc(usize length);
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
        : buffer(NULL) {}

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
            this->buffer = NULL;
        }
    }

public: // RAII
    inline String(String&& other)
        : buffer(other.buffer)
    {
        other.buffer = NULL;
    }

    inline String& operator=(String&& other)
    {
        memory::dealloc(buffer ? buffer - sizeof(int) : NULL);
        buffer = other.buffer;
        other.buffer = NULL;
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
            buffer = NULL;
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
        return buffer ? buffer->characters : NULL;
    }

    inline operator const char*(void) const
    {
        return buffer ? buffer->characters : NULL;
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

// Console
namespace console
{
    __rikuapi void log(const char* fmt, ...);
    __rikuapi void info(const char* fmt, ...);
    __rikuapi void warn(const char* fmt, ...);
    __rikuapi void error(const char* fmt, ...);

    __rikuapi void log_args(const char* fmt, ArgsList args_list);
    __rikuapi void info_args(const char* fmt, ArgsList args_list);
    __rikuapi void warn_args(const char* fmt, ArgsList args_list);
    __rikuapi void error_args(const char* fmt, ArgsList args_list);
}

// Current process
namespace process
{
    // Get environment variable
    __rikuapi const char* getenv(const char* name);

    // Set environment variable
    __rikuapi bool setenv(const char* name, const char* value);
    
    // Environment container, read-only
    static struct
    {
        inline const char* operator[](const char* name) const
        {
            return getenv(name);
        };
    } env;

    __rikuapi const char* cwd(void);
    __rikuapi usize       cwd(char* buffer, usize length);
    __rikuapi bool        chdir(const char* directory);

    __rikuapi void        exit(int code);
    __rikuapi void        abort(void);

    __rikuapi int         getpid(void);
}

//
// Performance
// 

namespace performance
{
    __rikuapi long now(void);
    __rikuapi long frequency(void);

    __rikuapi bool sleep(long milliseconds);
    __rikuapi bool usleep(long microseconds);
    __rikuapi bool nsleep(long nanoseconds);

    __rikuapi bool has_monotonic(void);
}

// Date and time
struct Date
{
public:
    int day;
    int month;
    int year;

    int weekday;
    int yearday;

    int hours;
    int minutes;
    int seconds;

public: // Properties
    propdef(get_full_year, set_full_year) int full_year;
    __forceinline int get_full_year(void) const
    {
        return year + 1900;
    }

    __forceinline void set_full_year(int full_year)
    {
        year = full_year - 1900;
    }

#if 0 && PREVIEWING
public: // UTC properties
    propdef(get_utc_day         , set_utc_day           ) int utc_day;
    propdef(get_utc_month       , set_utc_month         ) int utc_month;
    propdef(get_utc_year        , set_utc_year          ) int utc_year;
    propdef(get_utc_weekday     , set_utc_weekday       ) int utc_weekday;
    propdef(get_utc_yearday     , set_utc_yearday       ) int utc_yearday;
    propdef(get_utc_hours       , set_utc_hours         ) int utc_hours;
    propdef(get_utc_minutes     , set_utc_minutes       ) int utc_minutes;
    propdef(get_utc_seconds     , set_utc_seconds       ) int utc_seconds;
    propdef(get_utc_milliseconds, set_utc_milliseconds  ) int utc_milliseconds;

    __rikuapi int  get_utc_day(void) const;
    __rikuapi void set_utc_day(int day);
    
    __rikuapi int  get_utc_month(void) const;
    __rikuapi void set_utc_month(int month);
    
    __rikuapi int  get_utc_year(void) const;
    __rikuapi void set_utc_year(int year);
    
    __rikuapi int  get_utc_weekday(void) const;
    __rikuapi void set_utc_weekday(int weekday);
    
    __rikuapi int  get_utc_yearday(void) const;
    __rikuapi void set_utc_yearday(int yearday);
    
    __rikuapi int  get_utc_hours(void) const;
    __rikuapi void set_utc_hours(int hours);
    
    __rikuapi int  get_utc_minutes(void) const;
    __rikuapi void set_utc_minutes(int minutes);
    
    __rikuapi int  get_utc_seconds(void) const;
    __rikuapi void set_utc_seconds(int seconds);
#endif

public:
    constexpr Date(void) 
        : day(1)
        , month(0)
        , year(0)
        , weekday(0)
        , yearday(0)
        , hours(0)
        , minutes(0)
        , seconds(0)
        {}

    __forceinline ~Date(void) {}

public:
    Date(int year, int month = 0, int day = 1, int hours = 0, int minutes = 0, int seconds = 0)
        : day(day)
        , month(month)
        , year(year - 1900)
        , weekday(weekday_of(year, month, day))
        , yearday(yearday_of(year, month, day))
        , hours(hours)
        , minutes(minutes)
        , seconds(seconds)
    {
        
    }

    Date(int year, int month, int day, int weekday, int yearday, int hours = 0, int minutes = 0, int seconds = 0)
        : day(day)
        , month(month)
        , year(year - 1900)
        , weekday(weekday)
        , yearday(yearday)
        , hours(hours)
        , minutes(minutes)
        , seconds(seconds)
    {
    }
    
public: // Conversation
    __rikuapi const char* to_string(void) const;

public:
    __rikuapi static Date now(void);
    __rikuapi static Date parse(const char* date_string);

    __rikuapi static Date utc(void);
    __rikuapi static Date utc(const Date& date);
    __rikuapi static Date utc(int year, int month = 0, int day = 1, int hours = 0, int minutes = 0, int seconds = 0);

public: // Utils
    // Compute the day of week at given year, month, day
    __forceinline static int weekday_of(int year, int month, int day)
    {
        // Sakamoto's methods
        static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
        year -= month < 2;
        return (year + year / 4 - year / 100 + year / 400 + t[month] + day) % 7;
    }

    // Compute the day of year at given year, month, day
    __forceinline static int yearday_of(int year, int month, int day)
    {
        int N1 = (int)(275 * month / 9) + 1;
        int N2 = (int)((month + 9) / 12) + 1;
        int N3 = (2 + (int)((year - 4 * (int)(year / 4) + 2 + 1) / 3));
        return N1 - (N2 * N3) + day - 30;
    }
};