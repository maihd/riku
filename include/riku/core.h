// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#pragma once

// Supported platforms
#define PLATFORM_WINDOWS 0 // Platform family: windows  - winrt, win32
#define PLATFORM_UNIX    0 // Platform family: unix     - android, linux
#define PLATFORM_APPLE   0 // Platform family: apple    - ios, osx
#define PLATFORM_WEB     0 // Platform family: web      - asmjs, wasm
#define PLATFORM_WINRT   0
#define PLATFORM_ANDROID 0
#define PLATFORM_LINUX   0
#define PLATFORM_ASMJS   0
#define PLATFORM_WASM    0
#define PLATFORM_IOS     0
#define PLATFORM_OSX     0

// Supported cpus
#define CPU_ARM   0
#define CPU_JIT   0
#define CPU_MIPS  0
#define CPU_PPC   0
#define CPU_RISCV 0
#define CPU_X86   0

// Platform: Windows family
#if defined(_MSC_VER) || defined(_WIN32) || defined(__MINGW64__)
#   undef  PLATFORM_WINDOWS
#   define PLATFORM_WINDOWS 1
#   if !defined(__MINGW64__) && defined(WINAPI_FAMILY) && (WINAPI_FAMILY != WINAPI_FAMILY_DESKTOP_APP)
#       undef  PLATFORM_WINRT
#       define PLATFORM_WINRT 1
#   endif
#endif

// Platform: Unix family
#if defined(__unix__)
#   undef  PLATFORM_UNIX
#   define PLATFORM_UNIX 1
#
#   if defined(__ANDROID__)
#       undef  PLATFORM_ANDROID
#       define PLATFORM_ANDROID 1
#   elif defined(__linux__)
#       undef  PLATFORM_LINUX
#       define PLATFORM_LINUX 1
#   endif
#endif

// Platform: native web family
#if defined(__EMSCRIPTEN__)
#   undef  PLATFORM_WEB
#   define PLATFORM_WEB 1
#   if defined(__asmjs__)
#       undef  PLATFORM_ASMJS
#       define PLATFORM_ASMJS 1
#   else
#       undef  PLATFORM_WASM
#       define PLATFORM_WASM 1
#   endif
#endif

// Platform: Apple family
#if defined(__APPLE__)
#   undef  PLATFORM_APPLE
#   define PLATFORM_APPLE 1
#   if defined(__ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__) || defined(__ENVIRONMENT_TV_OS_VERSION_MIN_REQUIRED__)
#       undef  PLATFORM_IOS
#       define PLATFORM_IOS 1
#   else
#       undef  PLATFORM_OSX
#       define PLATFORM_OSX 1
#   endif
#endif

// Dectect mobile or desktop platform
#if PLATFORM_WINDOWS || PLATFORM_LINUX || PLATFORM_OSX
#   define PLATFORM_MOBILE  0
#   define PLATFORM_DESKTOP 1
#elif PLATFORM_ANDROID || PLATFORM_IOS
#   define PLATFORM_MOBILE  1
#   define PLATFORM_DESKTOP 0
#elif PLATFORM_WEB
#   define PLATFORM_MOBILE  0
#   define PLATFORM_DESKTOP 0
#else
#   error  "Unknown current platform"
#endif

// Detect target cpu
// http://sourceforge.net/apps/mediawiki/predef/index.php?title=Architectures
#if defined(__arm__)     \
 || defined(__aarch64__) \
 || defined(_M_ARM)
#	undef  CPU_ARM
#	define CPU_ARM 1
#	define CACHE_LINE_SIZE 64
#elif defined(__MIPSEL__)     \
 ||   defined(__mips_isa_rev) \
 ||   defined(__mips64)
#	undef  CPU_MIPS
#	define CPU_MIPS 1
#	define CACHE_LINE_SIZE 64
#elif defined(_M_PPC)        \
 ||   defined(__powerpc__)   \
 ||   defined(__powerpc64__)
#	undef  CPU_PPC
#	define CPU_PPC 1
#	define CACHE_LINE_SIZE 128
#elif defined(__riscv)   \
 ||   defined(__riscv__) \
 ||   defined(RISCVEL)
#	undef  CPU_RISCV
#	define CPU_RISCV 1
#	define CACHE_LINE_SIZE 64
#elif defined(_M_IX86)    \
 ||   defined(_M_X64)     \
 ||   defined(__i386__)   \
 ||   defined(__x86_64__)
#	undef  CPU_X86
#	define CPU_X86 1
#	define CACHE_LINE_SIZE 64
#else // PNaCl doesn't have CPU defined.
#	undef  CPU_JIT
#	define CPU_JIT 1
#	define CACHE_LINE_SIZE 64
#endif //

// Runtime architecture
#if defined(__x86_64__)    \
 || defined(_M_X64)        \
 || defined(__aarch64__)   \
 || defined(__64BIT__)     \
 || defined(__mips64)      \
 || defined(__powerpc64__) \
 || defined(__ppc64__)     \
 || defined(__LP64__)
#define ARCH_64BIT   1
#define ARCH_32BIT   0
#define ARCH_BITNESS 64
#else
#define ARCH_64BIT   0
#define ARCH_32BIT   1
#define ARCH_BITNESS 32
#endif

// Dectect cpu endian
#if CPU_PPC
#	if _LITTLE_ENDIAN
#       define CPU_BIG_ENDIAN    0
#       define CPU_LITTLE_ENDIAN 1
#	else
#       define CPU_BIG_ENDIAN    1
#       define CPU_LITTLE_ENDIAN 0
#   endif
#else
#   define CPU_BIG_ENDIAN    0
#   define CPU_LITTLE_ENDIAN 1
#endif

// CPU name
#if defined(__mips__)
#define CPU_NAME "mips"
#elif defined(__MIPSEL__)
#define CPU_NAME "mipsel"
#elif defined(__aarch64__)
#define CPU_NAME "arm64"
#elif defined(__arm__)
#define CPU_NAME "arm"
#elif defined(__i386__)
#define CPU_NAME "x32"
#elif defined(__powerpc__)
#define CPU_NAME "ppc"
#elif defined(__powerpc64__)
#define CPU_NAME "ppc64"
#elif defined(__x86_64__) || defined(_M_X64)
#define CPU_NAME "x64"
#else
#define CPU_NAME "x32"
#endif

// Platform name
#if PLATFORM_WINRT
#   define PLATFORM_NAME   "winrt"
#   define PLATFORM_FAMILY "Windows_NT"
#elif PLATFORM_WINDOWS
#   define PLATFORM_NAME   "windows"
#   define PLATFORM_FAMILY "Windows_NT"
#elif PLATFORM_ANDROID
#   define PLATFORM_NAME   "android"
#   define PLATFORM_FAMILY "Linux"
#elif PLATFORM_LINUX
#   define PLATFORM_NAME   "linux"
#   define PLATFORM_FAMILY "Linux"
#elif PLATFORM_ASMJS
#   define PLATFORM_NAME   "asmjs"
#   define PLATFORM_FAMILY "Emscripten"
#elif PLATFORM_WASM
#   define PLATFORM_NAME   "wasm"
#   define PLATFORM_FAMILY "Emscripten"
#elif PLATFORM_IOS
#   define PLATFORM_NAME   "ios"
#   define PLATFORM_FAMILY "Darwin"
#elif PLATFORM_OSX
#   define PLATFORM_NAME   "osx"
#   define PLATFORM_FAMILY "Darwin"
#endif

// Detect target library compile
#ifndef RIKU_API
#   ifdef RIKU_SHARED
#       if PLATFORM_WINDOWS
#           ifdef RIKU_EXPORT
#               define RIKU_API __declspec(dllexport)
#           else
#               define RIKU_API __declspec(dllimport)
#           endif
#       else
#           define RIKU_API __attribute__((visible("default")))
#       endif
#   else
#       define RIKU_API
#   endif
#endif

// Extension operators and specifier

#define countof(buffer)        (sizeof(x) / sizeof((x)[0]))
//#define offsetof(Type, member) ((usize)&((Type*)0)->member)
//#define deprecate(message)     __declspec(deprecated(message))

#ifndef __has_declspec_attribute       // Optional of course.
#define __has_declspec_attribute(x) 0  // Compatibility with non-clang compilers.
#endif

#if defined(EXTENSION_PROPERTY)
#   if defined(_MSC_VER) || ((defined(__has_declspec_attribute) && __has_declspec_attribute(property)))
#      define PROPERTY(Type, name, getter, setter)   __declspec(property(get=getter, put=setter)) Type name
#      define PROPERTY_READONLY(Type, name, getter)  __declspec(property(get=getter)) Type name
#      define PROPERTY_WRITEONLY(Type, name, setter) __declspec(property(put=setter)) Type name
#   else
#      define PROPERTY(Type, name, getter, setter)   
#      define PROPERTY_READONLY(Type, name, getter)  
#      define PROPERTY_WRITEONLY(Type, name, setter) 
#   endif
#else
#   define PROPERTY(Type, name, getter, setter)   
#   define PROPERTY_READONLY(Type, name, getter)  
#   define PROPERTY_WRITEONLY(Type, name, setter) 
#endif

#if defined(_MSC_VER)
#   define __threadstatic __declspec(thread) static
#else
#   define __threadstatic static __thread
#endif

// Primitive types

using uint      = unsigned int;
using ulong     = unsigned long int;
using ushort    = unsigned short int;

using cstr      = const char*;
using wchar     = short;
using uchar     = int;

// Fixed size types

using i8        = char;
using u8        = unsigned char;
using i16       = short;
using u16       = unsigned short;
using i32       = int;
using u32       = unsigned int;
using i64       = long long;
using u64       = unsigned long long;
static_assert(sizeof(i8)  == 1, "i8 must be 1-bytes size.");
static_assert(sizeof(u8)  == 1, "u8 must be 1-bytes size.");
static_assert(sizeof(i16) == 2, "i16 must be 2-bytes size.");
static_assert(sizeof(u16) == 2, "u16 must be 2-bytes size.");
static_assert(sizeof(i32) == 4, "i32 must be 4-bytes size.");
static_assert(sizeof(u32) == 4, "u32 must be 4-bytes size.");
static_assert(sizeof(i64) == 8, "i64 must be 8-bytes size.");
static_assert(sizeof(u64) == 8, "u64 must be 8-bytes size.");

using byte      = u8;
using sbyte     = i8;
static_assert(sizeof(byte)  == 1, "byte must be 1-bytes size.");
static_assert(sizeof(sbyte) == 1, "sbyte must be 1-bytes size.");

// Memory address and size types

#if ARCH_64BIT
using usize  = u64;
using isize  = i64;
#else 
using usize  = u32;
using isize  = i32;
#endif

using iptr = isize;
using uptr = usize;

using Flags   = u32;
using Flags64 = u64;

// ArgsList: alias of va_list
#include <stdarg.h>
using ArgsList = va_list;
#define argslist_begin(args_list, prev_arg) va_start(args_list, prev_arg)
#define argslist_next(args_list, Type)      va_arg(args_list, Type)
#define argslist_copy(dst, src)             va_copy(dst, src)
#define argslist_end(args_list)             va_end(args_list)

// Assertion helper
#define ALWAYS_ASSERT(exp, fmt, ...) (!(exp) ? (void)::__assert_abort(#exp, __FUNCTION__, __FILE__, __LINE__, fmt, ##__VA_ARGS__) : (void)0)
#define ALWAYS_FALSE_ASSERT(fmt, ...) (void)::__assert_abort("__false_assert__", __FUNCTION__, __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#if !defined(NDEBUG) || !NDEBUG
#   define ASSERT(exp, fmt, ...)  ALWAYS_ASSERT(exp, fmt, ##__VA_ARGS__)
#   define FALSE_ASSERT(fmt, ...) ALWAYS_FALSE_ASSERT(fmt, ##__VA_ARGS__)
#else
#   define ASSERT(exp, fmt, ...)
#   define FALSE_ASSERT(fmt, ...)
#endif

// Assertion functions
RIKU_API void __assert_abort(const char* exp, const char* func, const char* file, int line, const char* fmt, ...);

//
// Memory management
//

#if PLATFORM_WINDOWS
#include <malloc.h>
#   define stackalloc _alloca
#else
#   define stackalloc __builtin_alloca 
#endif

namespace memory
{
    RIKU_API void* alloc(usize size);
    RIKU_API void  dealloc(void* ptr);
    RIKU_API void* realloc(void* ptr, usize size);

    RIKU_API void* init(void* dst, int val, usize size);
    RIKU_API void* copy(void* dst, const void* src, usize size);
    RIKU_API void* move(void* dst, const void* src, usize size);

    RIKU_API int   compare(const void* a, const void* b, usize size);

    inline   void* zero(void* dst, usize size)                          { return init(dst, 0, size);          }
    inline   bool  equal(const void* a, const void* b, usize size)      { return compare(a, b, size) == 0;    }
    inline   bool  not_equal(const void* a, const void* b, usize size)  { return compare(a, b, size) != 0;    }
}

// NULL
#if !defined(NULL)
#   define NULL 0
#endif

// Type of null pointer
using NullPtr = decltype(nullptr);

struct NewDummy {};
inline void* operator new   (decltype(sizeof(0)), NewDummy, void* ptr) { return ptr; }
inline void  operator delete(void*,  NewDummy, void*)     {             }

#define INIT(ptr)    new (NewDummy(), ptr)
#define CREATE(T)    new (NewDummy(), memory::alloc(sizeof(T)))
#define DESTROY(ptr) __DO_DESTROY(ptr)

template <typename T>
inline bool __DO_DESTROY(T* ptr)
{
    if (ptr) 
    { 
        (ptr)->~T(); 
        memory::dealloc(ptr); 
        return true;
    }
    else
    {
        return false;
    }
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

struct RefCount
{
public:
    int _refcount; // _ for avoid member collision.

public:
    constexpr RefCount(void) : _refcount(1) {}

public:
    inline int _refinc(void) { return ++_refcount; };
    inline int _refdec(void) { return --_refcount; };
};

// Simple memory buffer
struct Buffer 
{
public:
    byte* data;

public:
    inline Buffer()
        : data(NULL) {}

    inline ~Buffer()
    {
        memory::dealloc(data ? (usize*)data - 1 : NULL);
    }

public:
    inline Buffer(Buffer&& buffer)
        : data(buffer.data)
    {
        buffer.data = NULL;
    }

    inline Buffer& operator=(Buffer&& buffer)
    {
        data = buffer.data;
        buffer.data = NULL;
        return *this;
    }

public:
    PROPERTY_READONLY(usize, length, get_length);
    inline usize get_length(void) const
    {
        return data ? *((usize*)data - 1) : 0;
    }

public:
    inline operator byte*(void)
    {
        return data;
    }

    inline operator const byte*(void) const
    {
        return data;
    }

public: // Factory functions
    RIKU_API static Buffer alloc(usize length);
};

// String operator
namespace string
{
    RIKU_API usize       length(const char* str);

#if 0 && PREVIEWING
    RIKU_API const char* sub(const char* str, int start);
    RIKU_API const char* sub(const char* str, int start, char* buffer, usize length);

    RIKU_API const char* sub(const char* str, int start, int end);
    RIKU_API const char* sub(const char* str, int start, int end, char* buffer, usize length);
#endif

    RIKU_API const char* copy(char* dst, const char* src);
    RIKU_API const char* copy(char* dst, const char* src, usize length);

    RIKU_API const char* concat(char* dst, const char* src);
    RIKU_API const char* concat(char* dst, const char* src, usize length);

    RIKU_API const char* format(const char* fmt, ...);
    //RIKU_API const char* format(char* buffer, const char* fmt, ...);
    RIKU_API const char* format(char* buffer, usize length, const char* fmt, ...);

    RIKU_API const char* format_args(const char* fmt, ArgsList args_list);
    //RIKU_API const char* format_args(char* buffer, const char* fmt, ArgsList args_list);
    RIKU_API const char* format_args(char* buffer, usize length, const char* fmt, ArgsList args_list);

    RIKU_API int         compare(const char* dst, const char* src);
    RIKU_API int         compare(const char* dst, const char* src, usize length);

    inline bool is_empty(const char* str)               { return !str || str[0] == 0;   }
    inline bool is_valid(const char* str)               { return  str && str[0] != 0;   }
    inline bool equal(const char* a, const char* b)     { return compare(a, b) == 0;    }
    inline bool not_equal(const char* a, const char* b) { return compare(a, b) != 0;    }
}

// Console
namespace console
{
    RIKU_API void log(const char* fmt, ...);
    RIKU_API void info(const char* fmt, ...);
    RIKU_API void warn(const char* fmt, ...);
    RIKU_API void error(const char* fmt, ...);

    RIKU_API void log_args(const char* fmt, ArgsList args_list);
    RIKU_API void info_args(const char* fmt, ArgsList args_list);
    RIKU_API void warn_args(const char* fmt, ArgsList args_list);
    RIKU_API void error_args(const char* fmt, ArgsList args_list);
}

// Current process
namespace process
{
    // Get environment variable
    RIKU_API const char* getenv(const char* name);

    // Set environment variable
    RIKU_API bool setenv(const char* name, const char* value);
    
    // Environment container, read-only
    static struct
    {
        inline const char* operator[](const char* name) const
        {
            return getenv(name);
        };
    } env
#if __GNUC__ || __clang__
    __attribute__((unused))
#endif
    ;

    RIKU_API const char* cwd(void);
    RIKU_API const char* cwd(char* buffer, usize length);
    RIKU_API bool        chdir(const char* directory);

    RIKU_API void        exit(int code);
    RIKU_API void        abort(void);

    RIKU_API int         getpid(void);
}

//
// Performance
// 

namespace performance
{
    RIKU_API long now(void);
    RIKU_API long frequency(void);

    RIKU_API bool sleep(long milliseconds);
    RIKU_API bool usleep(long microseconds);
    RIKU_API bool nsleep(long nanoseconds);

    RIKU_API bool has_monotonic(void);
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
    PROPERTY(int, full_year, get_full_year, set_full_year);
    inline int get_full_year(void) const
    {
        return year + 1900;
    }

    inline void set_full_year(int full_year)
    {
        year = full_year - 1900;
    }

#if 0 && PREVIEWING
public: // UTC properties
    PROPERTY(get_utc_day         , set_utc_day           ) int utc_day;
    PROPERTY(get_utc_month       , set_utc_month         ) int utc_month;
    PROPERTY(get_utc_year        , set_utc_year          ) int utc_year;
    PROPERTY(get_utc_weekday     , set_utc_weekday       ) int utc_weekday;
    PROPERTY(get_utc_yearday     , set_utc_yearday       ) int utc_yearday;
    PROPERTY(get_utc_hours       , set_utc_hours         ) int utc_hours;
    PROPERTY(get_utc_minutes     , set_utc_minutes       ) int utc_minutes;
    PROPERTY(get_utc_seconds     , set_utc_seconds       ) int utc_seconds;
    PROPERTY(get_utc_milliseconds, set_utc_milliseconds  ) int utc_milliseconds;

    RIKU_API int  get_utc_day(void) const;
    RIKU_API void set_utc_day(int day);
    
    RIKU_API int  get_utc_month(void) const;
    RIKU_API void set_utc_month(int month);
    
    RIKU_API int  get_utc_year(void) const;
    RIKU_API void set_utc_year(int year);
    
    RIKU_API int  get_utc_weekday(void) const;
    RIKU_API void set_utc_weekday(int weekday);
    
    RIKU_API int  get_utc_yearday(void) const;
    RIKU_API void set_utc_yearday(int yearday);
    
    RIKU_API int  get_utc_hours(void) const;
    RIKU_API void set_utc_hours(int hours);
    
    RIKU_API int  get_utc_minutes(void) const;
    RIKU_API void set_utc_minutes(int minutes);
    
    RIKU_API int  get_utc_seconds(void) const;
    RIKU_API void set_utc_seconds(int seconds);
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

    inline ~Date(void) {}

public:
    inline Date(int year, int month = 0, int day = 1, int hours = 0, int minutes = 0, int seconds = 0)
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

    inline Date(int year, int month, int day, int weekday, int yearday, int hours = 0, int minutes = 0, int seconds = 0)
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
    RIKU_API const char* to_string(void) const;

public:
    RIKU_API static Date now(void);
    RIKU_API static Date parse(const char* date_string);

    RIKU_API static Date utc(void);
    RIKU_API static Date utc(const Date& date);
    RIKU_API static Date utc(int year, int month = 0, int day = 1, int hours = 0, int minutes = 0, int seconds = 0);

public: // Utils
    // Compute the day of week at given year, month, day
    inline static int weekday_of(int year, int month, int day)
    {
        // Sakamoto's methods
        static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
        year -= month < 2;
        return (year + year / 4 - year / 100 + year / 400 + t[month] + day) % 7;
    }

    // Compute the day of year at given year, month, day
    inline static int yearday_of(int year, int month, int day)
    {
        int N1 = (int)(275 * month / 9) + 1;
        int N2 = (int)((month + 9) / 12) + 1;
        int N3 = (2 + (int)((year - 4 * (int)(year / 4) + 2 + 1) / 3));
        return N1 - (N2 * N3) + day - 30;
    }
};

// Common hash function
RIKU_API u64 calc_hash(const void* buffer, usize length);

// Common hash function
template <typename T>
inline u64 calc_hash(const T& x)
{
    return calc_hash(&x, sizeof(x));
}

// Common hash function, for c-string
template <>
inline u64 calc_hash<cstr>(const cstr& x)
{
    return calc_hash(x, string::length(x));
}

// Common hash function, compute at compile time
template <u32 length>
constexpr u64 calc_hash(const char (&buffer)[length])
{
    u32 h = 0;

    const u32 c1  = 0xcc9e2d51;
    const u32 c2  = 0x1b873593;
    const u32 len = length - 1;

    for (u32 i = 0, n = len >> 2; i < n; i++)
    {
        u32 idx = i * 4;
        u32 b0  = buffer[idx + 0];
        u32 b1  = buffer[idx + 1];
        u32 b2  = buffer[idx + 2];
        u32 b3  = buffer[idx + 3];
#if CPU_LITTLE_ENDIAN
        u32 k   = (b3 << 24) | (b2 << 16) | (b1 << 8) | (b0 << 0);
#else
        u64 k   = (b3 << 0) | (b2 << 8) | (b1 << 16) | (b0 << 24);
#endif

        k *= c1;
        k  = (k << 15) | (k >> 17);
        k *= c2;

        h ^= k;
        h  = (h << 13) | (h >> 19);
        h  = (h * 5) + 0xe6546b64;
    }

    u32 k = 0;
    switch (len & 3) 
    {
    case 3:
        k ^= (u8)buffer[len - 1] << 16;
        k ^= (u8)buffer[len - 2] <<  8;
        k ^= (u8)buffer[len - 3] <<  0;
        break;

    case 2:
        k ^= (u8)buffer[len - 1] <<  8;
        k ^= (u8)buffer[len - 2] <<  0;
        break;

    case 1:
        k ^= (u8)buffer[len - 1] <<  0;
        break;
    };

    k *= c1;
    k  = (k << 15) | (k >> 17);
    k *= c2;
    h ^= k;

    h ^= len;
    h ^= h >> 16;
    h *= 0x85ebca6b;
    h ^= h >> 13;
    h *= 0xc2b2ae35;
    h ^= h >> 16;

    return h;
}