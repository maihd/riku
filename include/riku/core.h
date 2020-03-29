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
#   define ARCH_64BIT   1
#   define ARCH_32BIT   0
#   define ARCH_BITNESS 64
#else
#   define ARCH_64BIT   0
#   define ARCH_32BIT   1
#   define ARCH_BITNESS 32
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
#   define CPU_NAME "mips"
#elif defined(__MIPSEL__)
#   define CPU_NAME "mipsel"
#elif defined(__aarch64__)
#   define CPU_NAME "arm64"
#elif defined(__arm__)
#   define CPU_NAME "arm"
#elif defined(__i386__)
#   define CPU_NAME "x32"
#elif defined(__powerpc__)
#   define CPU_NAME "ppc"
#elif defined(__powerpc64__)
#   define CPU_NAME "ppc64"
#elif defined(__x86_64__) || defined(_M_X64)
#   define CPU_NAME "amd64"
#else
#   define CPU_NAME "x86"
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
#   define PLATFORM_FAMILY "Web"
#elif PLATFORM_WASM
#   define PLATFORM_NAME   "wasm"
#   define PLATFORM_FAMILY "Web"
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

using uint   = unsigned int;
using ulong  = unsigned long int;
using ushort = unsigned short int;

using cstr   = const char*;
using wchar  = short;
using uchar  = int;

// Fixed size types

#if PLATFORM_WINDOWS || (CPU_ARM && ARCH_32BIT)
using i8  = char;
using u8  = unsigned char;
using i16 = short;
using u16 = unsigned short;
using i32 = long;
using u32 = unsigned long;
using i64 = long long;
using u64 = unsigned long long;
#else
using i8  = char;
using u8  = unsigned char;
using i16 = short;
using u16 = unsigned short;
using i32 = int;
using u32 = unsigned int;
using i64 = long;
using u64 = unsigned long;
#endif

static_assert(sizeof(i8)  == 1, "i8 must be 1-bytes size.");
static_assert(sizeof(u8)  == 1, "u8 must be 1-bytes size.");
static_assert(sizeof(i16) == 2, "i16 must be 2-bytes size.");
static_assert(sizeof(u16) == 2, "u16 must be 2-bytes size.");
static_assert(sizeof(i32) == 4, "i32 must be 4-bytes size.");
static_assert(sizeof(u32) == 4, "u32 must be 4-bytes size.");
static_assert(sizeof(i64) == 8, "i64 must be 8-bytes size.");
static_assert(sizeof(u64) == 8, "u64 must be 8-bytes size.");

using byte  = u8;
using sbyte = i8;
static_assert(sizeof(byte)  == 1, "byte must be 1-bytes size.");
static_assert(sizeof(sbyte) == 1, "sbyte must be 1-bytes size.");

// Memory address and size types

#if ARCH_64BIT
using usize = u64;
using isize = i64;
#else 
using usize = u32;
using isize = i32;
#endif

using iptr = isize;
using uptr = usize;

using Flags   = u32;
using Flags64 = u64;

// NULL
#if !defined(NULL)
#   define NULL 0
#endif

// Type of null pointer
using NullPtr = decltype(nullptr);

// ArgsList: alias of va_list
#include <stdarg.h>
using ArgsList = va_list;
#define argslist_begin(args_list, prev_arg) va_start(args_list, prev_arg)
#define argslist_next(args_list, Type)      va_arg(args_list, Type)
#define argslist_copy(dst, src)             va_copy(dst, src)
#define argslist_end(args_list)             va_end(args_list)

// Assertion helper
#define ALWAYS_ASSERT(exp, fmt, ...) (!(exp) ? (void)::console::log_assert(#exp, __FUNCTION__, __FILE__, __LINE__, fmt, ##__VA_ARGS__) : (void)0)
#define ALWAYS_FALSE_ASSERT(fmt, ...) (void)::console::log_assert("__false_assert__", __FUNCTION__, __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#if !defined(NDEBUG) || !NDEBUG
#   define ASSERT(exp, fmt, ...)  ALWAYS_ASSERT(exp, fmt, ##__VA_ARGS__)
#   define FALSE_ASSERT(fmt, ...) ALWAYS_FALSE_ASSERT(fmt, ##__VA_ARGS__)
#else
#   define ASSERT(exp, fmt, ...)
#   define FALSE_ASSERT(fmt, ...)
#endif

// Console
namespace console
{
    struct Logger
    {
        // Log a message, with standard logging-level
        RIKU_API virtual void log(const char* fmt, ...);

        // Log an information message
        RIKU_API virtual void info(const char* fmt, ...);

        // Log a warning message
        RIKU_API virtual void warn(const char* fmt, ...);

        // Log an error message
        RIKU_API virtual void error(const char* fmt, ...);

        // Log assertion message, and abort the process
        RIKU_API virtual void log_assert(const char* exp, const char* func, const char* file, int line, const char* fmt, ...);

        // Log a message, with standard logging-level
        RIKU_API virtual void log_args(const char* fmt, ArgsList args_list);

        // Log an information message
        RIKU_API virtual void info_args(const char* fmt, ArgsList args_list);

        // Log a warning message
        RIKU_API virtual void warn_args(const char* fmt, ArgsList args_list);

        // Log an error message
        RIKU_API virtual void error_args(const char* fmt, ArgsList args_list);

        // Log assertion message, and abort the process
        RIKU_API virtual void log_assert_args(const char* exp, const char* func, const char* file, int line, const char* fmt, ArgsList args_list);
    };

    // Add logger, that will call from log function
    RIKU_API bool add_logger(Logger* logger);

    // Remove logger, log function will no longer call logger
    RIKU_API bool remove_logger(Logger* logger);

    // Get log tag of console, which is presented on logcat and family
    RIKU_API const char* get_log_tag(void);

    // Set log tag of console, which is presented on logcat and family
    RIKU_API const char* set_log_tag(const char* tag);

    // Log a message, with standard logging-level
    RIKU_API void log(const char* fmt, ...);

    // Log an information message
    RIKU_API void info(const char* fmt, ...);

    // Log a warning message
    RIKU_API void warn(const char* fmt, ...);

    // Log an error message
    RIKU_API void error(const char* fmt, ...);

    // Log assertion message, and abort the process
    RIKU_API void log_assert(const char* exp, const char* func, const char* file, int line, const char* fmt, ...);

    // Log a message, with standard logging-level
    RIKU_API void log_args(const char* fmt, ArgsList args_list);

    // Log an information message
    RIKU_API void info_args(const char* fmt, ArgsList args_list);

    // Log a warning message
    RIKU_API void warn_args(const char* fmt, ArgsList args_list);

    // Log an error message
    RIKU_API void error_args(const char* fmt, ArgsList args_list);

    // Log assertion message, and abort the process
    RIKU_API void log_assert_args(const char* exp, const char* func, const char* file, int line, const char* fmt, ArgsList args_list);
}

//
// Memory management
//

#if PLATFORM_WINDOWS
#include <malloc.h>
#   define stackalloc _alloca
#else
#   define stackalloc __builtin_alloca 
#endif

// Memory allocator
struct Allocator
{
    RIKU_API virtual void* alloc(int size, int align);
    RIKU_API virtual void  dealloc(void* ptr);
    RIKU_API virtual void* realloc(void* ptr, int size, int align);

    
    inline void* alloc(int size)
    {
        return alloc(size, 16);
    }

    inline void* realloc(void* ptr, int size)
    {
        return realloc(ptr, size, 16);
    }
};

// Memory management with customable allocator
// @note: Work with process (user space) memory only, use os if you want system (kernel space) memory
namespace memory
{
    // Current allocator of process
    RIKU_API extern Allocator* allocator;

    // Get aligned memory address from memory block
    inline void* align(void* ptr, int align)
    {
        ASSERT(align >= 16 && align <= 256, "Alignment must be between [16, 256]");
        ASSERT((align & (align - 1)) == 0, "Aligment must be a POT number");

        if (ptr)
        {
            iptr address = (iptr)ptr;
            iptr misalign = (address & (align - 1));
            iptr adjustment = (align - misalign);

            *((byte*)ptr + adjustment - 1) = (byte)adjustment;
            void* result = (byte*)ptr + adjustment;
            return result;
        }
        else
        {
            return nullptr;
        }
    }

    // Get origin memory address of aligned memory block
    inline void* dealign(void* ptr)
    {
        if (ptr)
        {
            byte adjustment = *((byte*)ptr - 1);
            return (byte*)ptr - adjustment;
        }
        else
        {
            return nullptr;
        }
    }

    // Allocate a memory block, with 16 bytes alignment
    RIKU_API void* alloc(int size);

    // Re-allocate memory block, with 16 bytes alignment
    RIKU_API void* realloc(void* ptr, int size);

    // Allocate a memory block, with given alignment
    RIKU_API void* alloc(int size, int align);

    // Re-allocate memory block, with given alignment
    RIKU_API void* realloc(void* ptr, int size, int align);

    // De-allocate memory block
    RIKU_API void  dealloc(void* ptr);

    // Initialize memory block
    RIKU_API void* init(void* dst, int val, int size);
    
    // Copy memory block content from src to dst
    RIKU_API void* copy(void* dst, const void* src, int size);

    // Move memory block content from src to dst, if src and dst is collapsed, otherwise just copy it
    RIKU_API void* move(void* dst, const void* src, int size);

    // Compare content of two memory blocks
    RIKU_API int   compare(const void* a, const void* b, int size);

    // Initialize memory block with zero
    inline   void* zero(void* dst, int size)                           { return init(dst, 0, size);          }

    // Determine content of two memory blocks are equal
    inline   bool  equals(const void* a, const void* b, int size)      { return compare(a, b, size) == 0;    }

    // Determine content of two memory blocks are not equal
    inline   bool  not_equals(const void* a, const void* b, int size)  { return compare(a, b, size) != 0;    }
}

// placement new
inline void* operator new(decltype(sizeof(int)), NullPtr, void* placement)
{
    return placement;
}

// placement delete
inline void operator delete(void*, NullPtr, void*)
{
}

// Allocate new object with allocator
inline void* operator new(decltype(sizeof(int)) size, Allocator* allocator)
{
    if (allocator)
    {
        return allocator->alloc((int)size);
    }
    else
    {
        return memory::alloc((int)size);
    }
}

// Delete the object with allocator
inline void operator delete(void* ptr, Allocator* allocator)
{
    if (allocator)
    {
        allocator->dealloc(ptr);
    }
    else
    {
        memory::dealloc(ptr);
    }
}

// Trait utils
// @note: use for traiting only
namespace traits
{
    // Detemine two values are equal
    // @note: use for traiting only
    template <typename TValue>
    inline bool equals(const TValue& a, const TValue& b)
    {
        return a == b;
    }

    // Detemine two values are not equal
    // @note: use for traiting only
    template <typename TValue>
    inline bool not_equals(const TValue& a, const TValue& b)
    {
        return a != b;
    }

    // Detemine a is less than b
    // @note: use for traiting only
    template <typename TValue>
    inline bool less(const TValue& a, const TValue& b)
    {
        return a < b;
    }

    // Detemine a is greater than b
    // @note: use for traiting only
    template <typename TValue>
    inline bool greater(const TValue& a, const TValue& b)
    {
        return a > b;
    }

    // Detemine a is less than b
    // @note: use for traiting only
    template <typename TValue>
    inline bool less_equals(const TValue& a, const TValue& b)
    {
        return a <= b;
    }

    // @note: use for traiting only
    template <typename TValue>
    inline bool greater_equals(const TValue& a, const TValue& b)
    {
        return a >= b;
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

    // Detemine given type is a plain old data structure
    template <typename T>
    constexpr bool is_pod(void)
    {
        return __is_pod(T);
    }

    // Detemine given type is an enum
    template <typename T>
    constexpr bool is_enum(void)
    {
        return __is_enum(T);
    }

    // Detemine given type is an union
    template <typename T>
    constexpr bool is_union(void)
    {
        return __is_union(T);
    }

    // Detemine given type is a struct
    template <typename T>
    constexpr bool is_struct(void)
    {
        return __is_class(T);
    }

    template <typename T>
    struct NameOfTrait
    {
        static const char* nameof(void)
        {
        #ifdef _MSC_VER
            const int FRONT_SIZE = sizeof("traits::NameOfTrait<") - 1;
            const int BACK_SIZE = sizeof(">::nameof") - 1;
            const int SIZE = sizeof(__FUNCTION__) - FRONT_SIZE - BACK_SIZE;

            static char type_name[SIZE];
            for (int i = 0; i < SIZE - 1; i++)
            {
                type_name[i] = __FUNCTION__[FRONT_SIZE + i];
            }
            
            return type_name;
        #else
            const int FRONT_SIZE = sizeof("static const char* traits::NameOfTrait<T>::nameof() [with T = ") - 1;
            const int BACK_SIZE = sizeof("]") - 1;
            const int SIZE = sizeof(__PRETTY_FUNCTION__) - FRONT_SIZE - BACK_SIZE;

            int i = 0;
            static char type_name[SIZE];
            while (__PRETTY_FUNCTION__[FRONT_SIZE + i] && __PRETTY_FUNCTION__[FRONT_SIZE + i] != ']')
            {
                type_name[i] = __PRETTY_FUNCTION__[FRONT_SIZE + i];
                i++;
            }

            return type_name;
        #endif
        }
    };

    // Get true name of type
    template <typename T>
    inline const char* nameof(void)
    {
        return NameOfTrait<T>::nameof();
    }
}

// Optional value container
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

// Reference counter, simple and fast implement
struct RefCount
{
public:
    int _refcount; // _ for avoid member collision.

public:
    constexpr RefCount(void) : _refcount(1) {}

public:
    // Increase counter
    // @note: ridiculous name for avoid member collision
    inline int _incref(void) { return ++_refcount; };

    // Decrease counter
    // @note: ridiculous name for avoid member collision
    inline int _decref(void) { return --_refcount; };
};

// UTF8 string operator
namespace string
{
    // Make a copy of given string, with dynamic allocation
    RIKU_API char*       clone(const char* str);

    // Get length of string
    RIKU_API int         length(const char* str);

    // Get sub string of given string, with given start position
    RIKU_API const char* substr(const char* str, int start);

    // Get sub string of given string, with given start position
    RIKU_API const char* substr(const char* str, int start, char* buffer, int length);

    // Get sub string of given string, with given start and end position
    RIKU_API const char* substr(const char* str, int start, int end);

    // Get sub string of given string, with given start and end position
    RIKU_API const char* substr(const char* str, int start, int end, char* buffer, int length);

    // Get position of given character in given string
    RIKU_API int         index_of(const char* str, char value);

    // Get position of given sub string in given string
    RIKU_API int         index_of(const char* str, const char* value);

    // Get last position of given character in given string
    RIKU_API int         last_index_of(const char* str, char value);

    // Get last position of given sub string in given string
    RIKU_API int         last_index_of(const char* str, const char* value);

    // Copy content of src string to dst string
    RIKU_API const char* copy(char* dst, const char* src);

    // Copy content of src string to dst string
    RIKU_API const char* copy(char* dst, const char* src, int length);

    // Add content of src string to end of dst string
    RIKU_API const char* concat(char* dst, const char* src);

    // Add content of src string to end of dst string
    RIKU_API const char* concat(char* dst, const char* src, int length);

    // Make a string with specified format
    RIKU_API const char* format(const char* fmt, ...);

    // Make a string with specified format
    RIKU_API const char* format(char* buffer, int length, const char* fmt, ...);

    // Make a string with specified format
    RIKU_API const char* format_args(const char* fmt, ArgsList args_list);

    // Make a string with specified format
    RIKU_API const char* format_args(char* buffer, int length, const char* fmt, ArgsList args_list);

    // Compare two strings: 0 -> dst == src, -1 -> dst < src, 1 dst > src
    RIKU_API int         compare(const char* dst, const char* src);

    // Compare two strings: 0 -> dst == src, -1 -> dst < src, 1 dst > src
    RIKU_API int         compare(const char* dst, const char* src, int length);

    // Convert string to 32 bits integer
    RIKU_API i32         to_i32(const char* str);

    // Convert string to 32 bits unsigned integer
    RIKU_API u32         to_u32(const char* str);

    // Convert string to 64 bits integer
    RIKU_API i64         to_i64(const char* str);

    // Convert string to 64 bits unsigned integer
    RIKU_API u64         to_u64(const char* str);

    // Convert string to standard integer
    RIKU_API int         to_int(const char* str);

    // Convert string to standard unsigned integer
    RIKU_API uint        to_uint(const char* str);

    // Convert string to single precision floating-point number
    RIKU_API float       to_float(const char* str);

    // Convert string to double precision floating-point number
    RIKU_API double      to_double(const char* str);

    // Checking string is empty
    inline bool is_empty(const char* str)                { return !str || str[0] == 0;   }

    // Checking string is valid
    inline bool is_valid(const char* str)                { return  str && str[0] != 0;   }

    // Compare two strings are equal
    inline bool equals(const char* a, const char* b)     { return compare(a, b) == 0;    }

    // Compare two strings are not equal
    inline bool not_equals(const char* a, const char* b) { return compare(a, b) != 0;    }

    // Compare two strings are equal
    inline bool equals(const char* a, const char* b, int length)     { return compare(a, b, length) == 0; }

    // Compare two strings are not equal
    inline bool not_equals(const char* a, const char* b, int length) { return compare(a, b, length) != 0; }
}

namespace traits
{
    // Detemine two string are equal or not
    // @note: use for traiting only
    template <>
    inline bool equals<cstr>(const cstr& a, const cstr& b)
    {
        return string::equals(a, b);
    }

    // @note: use for traiting only
    template <>
    inline bool not_equals<cstr>(const cstr& a, const cstr& b)
    {
        return string::not_equals(a, b);
    }

    // @note: use for traiting only
    template <>
    inline bool less<cstr>(const cstr& a, const cstr& b)
    {
        return string::compare(a, b) < 0;
    }

    // @note: use for traiting only
    template <>
    inline bool greater<cstr>(const cstr& a, const cstr& b)
    {
        return string::compare(a, b) > 0;
    }

    // @note: use for traiting only
    template <>
    inline bool less_equals<cstr>(const cstr& a, const cstr& b)
    {
        return string::compare(a, b) <= 0;
    }

    // @note: use for traiting only
    template <>
    inline bool greater_equals<cstr>(const cstr& a, const cstr& b)
    {
        return string::compare(a, b) >= 0;
    }
}

// Working with current process
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

    // Get current working directory of this process
    RIKU_API const char* cwd(void);

    // Get current working directory of this process
    RIKU_API const char* cwd(char* buffer, int length);

    // Change current working directory of this process
    RIKU_API bool        chdir(const char* directory);

    // Exit the process
    RIKU_API void        exit(int code);

    // Abort the process
    RIKU_API void        abort(void);

    // Get process id
    RIKU_API int         getpid(void);
}

// Working with CPU performance
namespace performance
{
    // Current counter of CPU, in OS abstract measure unit
    RIKU_API i64 now(void);

    // Frequency of CPU, in OS abstract measure unit
    RIKU_API i64 frequency(void);

    // Sleep current thread in milliseconds
    RIKU_API bool sleep(long milliseconds);

    // Sleep current thread in microseconds
    RIKU_API bool usleep(long microseconds);

    // Sleep current thread in nanoseconds
    RIKU_API bool nsleep(long nanoseconds);

    // Is system has monotonic timer
    RIKU_API bool has_monotonic(void);

    // Convert tick to seconds
    inline double ticks_to_seconds(i64 ticks)
    {
        return (double)ticks / frequency();
    }
}

// Default 32-bit hash function
RIKU_API u32 calc_hash32(const void* buffer, int length);

// Default 64-bit hash function
RIKU_API u64 calc_hash64(const void* buffer, int length);

// Default hash function, compute at compile time
template <int length>
constexpr u32 calc_hash32(const char (&buffer)[length])
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
        u32 k   = (b3 << 0) | (b2 << 8) | (b1 << 16) | (b0 << 24);
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

// Default 64-bit hash function, compute at compile time
template <int length>
constexpr u64 calc_hash64(const char(&buffer)[length])
{
    u64 h = 0;

    const u64 m = 0xc6a4a7935bd1e995ULL;
    const u64 r = 47;
    const u32 l = length - 1;
    const u32 n = (l >> 3) << 3;

    for (u32 i = 0; i < n; i += 8)
    {
        u64 b0 = buffer[i + 0];
        u64 b1 = buffer[i + 1];
        u64 b2 = buffer[i + 2];
        u64 b3 = buffer[i + 3];
        u64 b4 = buffer[i + 4];
        u64 b5 = buffer[i + 5];
        u64 b6 = buffer[i + 6];
        u64 b7 = buffer[i + 7];
#if CPU_LITTLE_ENDIAN
        u64 k = (b7 << 56) | (b6 << 48) | (b5 << 40) | (b4 << 32) | (b3 << 24) | (b2 << 16) | (b1 << 8) | (b0 << 0);
#else
        u64 k = (b0 << 56) | (b1 << 48) | (b2 << 40) | (b3 << 32) | (b4 << 24) | (b5 << 16) | (b6 << 8) | (b7 << 0);
#endif

        k *= m;
        k ^= k >> r;
        k *= m;

        h ^= k;
        h *= m;
    }

    switch (l & 7)
    {
    case 7: h ^= u64((buffer + n)[6]) << 48;            /* fall through */
    case 6: h ^= u64((buffer + n)[5]) << 40;            /* fall through */
    case 5: h ^= u64((buffer + n)[4]) << 32;            /* fall through */
    case 4: h ^= u64((buffer + n)[3]) << 24;            /* fall through */
    case 3: h ^= u64((buffer + n)[2]) << 16;            /* fall through */
    case 2: h ^= u64((buffer + n)[1]) <<  8;            /* fall through */
    case 1: h ^= u64((buffer + n)[0]) <<  0; h *= m;    /* fall through */
    };

    h ^= h >> r;
    h *= m;
    h ^= h >> r;

    return h;
}

// Function-like operators

// Compute hash of given data
inline u64 hashof(const void* buffer, int length)
{
    return calc_hash64(buffer, length);
}

// Compute hash of given data
template <typename T>
inline u64 hashof(const T& x)
{
    return calc_hash64(&x, sizeof(x));
}

// Compute hash of given data
template <>
inline u64 hashof(const cstr& x)
{
    return calc_hash64(x, string::length(x));
}

// Compute hash of given data
template <int length>
constexpr u64 hashof(const char(&buffer)[length])
{
    return calc_hash64<length>(buffer);
}

// Get length of given buffer
template <typename T, int length>
constexpr int lengthof(const T(&)[length])
{
    return length;
}

// Get length of given buffer
template <int length>
constexpr int lengthof(const char(&)[length])
{
    return length - 1;
}

// Get length of given value
template <typename T>
constexpr int lengthof(const T&)
{
    ALWAYS_FALSE_ASSERT("Cannot get length of T");
    return 1;
} 

// Get length of given string
template <>
inline int lengthof(const cstr& str)
{
    return string::length(str);
}