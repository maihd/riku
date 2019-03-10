// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#pragma once

// Riku donot support gcc, 'cause it doesnot has __declspec
#if defined(__GNUC__) && !defined(__clang__)
#error "riku: No GCC support, sorry man."
#endif

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
#   if defined(__linux__)
#       undef  PLATFORM_LINUX
#       define PLATFORM_LINUX 1
#   endif
#
#   if defined(__ANDROID__)
#       undef  PLATFORM_ANDROID
#       define PLATFORM_ANDROID 1
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
#define ARCH_64BIT 1
#define ARCH_32BIT 0
#else
#define ARCH_64BIT 0
#define ARCH_32BIT 1
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
#ifndef __rikuapi
#   ifdef RIKU_SHARED
#       if PLATFORM_WINDOWS
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

// Extension operators and specifier

#define countof(buffer)        (sizeof(x) / sizeof((x)[0]))
#define offsetof(Type, member) ((usize)&((Type*)0)->member)
#define deprecate(message)     __declspec(deprecated(message))

#define propdef(getter, setter)   __declspec(property(get=getter, put=setter))
#define propdef_readonly(getter)  __declspec(property(get=getter))
#define propdef_writeonly(setter) __declspec(property(put=setter))

#define __threadstatic __declspec(thread) static

// Primitive types

#if 0
#define int   int32_t
#define long  int64_t
#define short int16_t
#endif

using uint      = unsigned int;
using ulong     = unsigned long int;
using ushort    = unsigned short int;

using bigint    = long long int;
using biguint   = unsigned long long int;
using bigfloat  = long double;

using byte      = unsigned char;
using sbyte     = char;

// Memory address and size

#if ARCH_64BIT
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

#if PLATFORM_WINDOWS
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