#include <riku/core.h>

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if OS_WINDOWS
#include <Windows.h>
#elif OS_ANDROID
#include <unistd.h>
#include <android/log.h>
#endif

//
// Assertion functions
// 

void __assert_abort(const char* exp, const char* func, const char* file, int line, const char* fmt, ...)
{
#if OS_ANDROID
    char final_fmt[4096];
    sprintf(final_fmt, "Assertion failed!: %s\n\tIn %s:%s:%d\n\tMessage: %s", exp, func, file, line, fmt);

    ArgsList args_list;
    argslist_begin(args_list, fmt);
    __android_log_vprint(ANDROID_LOG_FATAL, "riku", final_fmt, args_list);
    argslist_end(args_list);
#else
    console::error("Assertion failed!: %s\nIn %s:%s:%d", exp, func, file, line);

    ArgsList args_list;
    argslist_begin(args_list, fmt);
    console::error_args(fmt, args_list);
    argslist_end(args_list);
#endif

    process::abort();
}

//
// Buffer functions
//

Buffer Buffer::alloc(usize length)
{
    Buffer buf;
    if (length)
    {
        buf.data = (byte*)memory::alloc(sizeof(usize) + length);
        *(usize*)buf.data = length;
        buf.data += sizeof(usize);
    }
    return make_rvalue(buf);
}

//
// Memory
// 

namespace memory
{
    void* alloc(usize size)
    {
        return malloc(size);
    }

    void dealloc(void* ptr)
    {
        free(ptr);    
    }

    void* realloc(void* ptr, usize size)
    {
        return ::realloc(ptr, size);
    }

    void* init(void* dst, int val, usize size)
    {
        return memset(dst, val, size);
    }

    void* copy(void* dst, const void* src, usize size)
    {
        return memcpy(dst, src, size);
    }
    
    void* move(void* dst, const void* src, usize size)
    {
        return memmove(dst, src, size);
    }
}

//
// String
// 

namespace string
{
    usize length(const char* s)
    {
        return strlen(s);
    }
}

//
// Console
//

namespace console
{
    void log(const char* fmt, ...)
    {
        ArgsList args_list;
        argslist_begin(args_list, fmt);
        log_args(fmt, args_list);
        argslist_end(args_list);
    }
    
    void info(const char* fmt, ...)
    {
        ArgsList args_list;
        argslist_begin(args_list, fmt);
        info_args(fmt, args_list);
        argslist_end(args_list);
    }

    void warn(const char* fmt, ...)
    {
        ArgsList args_list;
        argslist_begin(args_list, fmt);
        warn_args(fmt, args_list);
        argslist_end(args_list);
    }

    void error(const char* fmt, ...)
    {
        ArgsList args_list;
        argslist_begin(args_list, fmt);
        error_args(fmt, args_list);
        argslist_end(args_list);
    }

    void log_args(const char* fmt, ArgsList args_list)
    {
    #if OS_ANDROID
        __android_log_vprint(ANDROID_LOG_DEFAULT, "riku", fmt, args_list);
    #else
        vfprintf(stdout, fmt, args_list);
        fputc('\n', stdout);
    #endif
    }

    void info_args(const char* fmt, ArgsList args_list)
    {
    #if OS_ANDROID
        __android_log_vprint(ANDROID_LOG_INFO, "riku", fmt, args_list);
    #else
        vfprintf(stdout, fmt, args_list);
        fputc('\n', stdout);
    #endif
    }

    void warn_args(const char* fmt, ArgsList args_list)
    {
    #if OS_ANDROID
        __android_log_vprint(ANDROID_LOG_WARN, "riku", fmt, args_list);
    #else
        vfprintf(stdout, fmt, args_list);
        fputc('\n', stdout);
    #endif
    }

    void error_args(const char* fmt, ArgsList args_list)
    {
    #if OS_ANDROID
        __android_log_vprint(ANDROID_LOG_ERROR, "riku", fmt, args_list);
    #else
        vfprintf(stderr, fmt, args_list);
        fputc('\n', stdout);
    #endif
    }
}

//
// Process
//

namespace process
{
    // Get environment variable
    const char* getenv(const char* name)
    {
        return ::getenv(name);    
    }

    // Set environment variable
    bool setenv(const char* name, const char* value)
    {
#if OS_WINDOWS
        return SetEnvironmentVariableA(name, value);
#elif OS_UNIX
        return ::setenv(name, value, true) == 0;
#endif
    }

    const char* cwd(void)
    {
        __threadstatic char path[1024];

        cwd(path, sizeof(path)); 
        return path;
    }

    usize cwd(char* buffer, usize length)
    {
    #if OS_WINDOWS
        uint size = GetCurrentDirectoryA(length, buffer);
        return size;
    #elif OS_ANDROID
        return (usize)(::getcwd(buffer, length) - buffer);
    #endif
    }

    bool chdir(const char* directory)
    {
    #if OS_WINDOWS
        return SetCurrentDirectoryA(directory);
    #elif OS_ANDROID
        return ::chdir(directory) != 0;
    #endif
    }

    void exit(int code)
    {
        ::exit(code);
    }

    void abort(void)
    {
        ::abort();
    }
    
    int getpid(void)
    {
    #if OS_WINDOWS
        return (int)GetCurrentProcessId();
    #elif OS_WEB
        return -1;
    #elif OS_UNIX
        return (int)::getpid();
    #endif
    }
}

//
// Date and time
// 

#if 0 && PREVIEWING
int  Date::get_utc_day(void) const;
void Date::set_utc_day(int day);
int  Date::get_utc_month(void) const;
void Date::set_utc_month(int month);
int  Date::get_utc_year(void) const;
void Date::set_utc_year(int year);
int  Date::get_utc_weekday(void) const;
void Date::set_utc_weekday(int weekday);
int  Date::get_utc_yearday(void) const;
void Date::set_utc_yearday(int yearday);
int  Date::get_utc_hours(void) const;
void Date::set_utc_hours(int hours);
int  Date::get_utc_minutes(void) const;
void Date::set_utc_minutes(int minutes);
int  Date::get_utc_seconds(void) const;
void Date::set_utc_seconds(int seconds);
#endif

const char* Date::to_string(void) const
{
    const char wday_name[][4] = {
        "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
    };
    const char mon_name[][4] = {
        "Jan", "Feb", "Mar", "Apr", "May", "Jun",
        "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
    };

    __threadstatic char result[64];
    sprintf(result, "%.3s %.3s%3d %d, %.2d:%.2d:%.2d %s",
        wday_name[weekday], mon_name[month], day, 1900 + year,
        hours % 12, minutes, seconds, hours > 12 ? "PM" : "AM");
    return result;
}

Date Date::now(void)
{
    time_t t = time(NULL);
    struct tm* tm = localtime(&t);
    return Date(
        (int)tm->tm_year + 1900, (int)tm->tm_mon, 
        (int)tm->tm_mday, (int)tm->tm_wday, (int)tm->tm_yday,
        (int)tm->tm_hour, (int)tm->tm_min, (int)tm->tm_sec);
}

Date Date::parse(const char* date_string)
{
    (void)date_string;
    return Date();
}

Date Date::utc(void)
{
    time_t t = time(NULL);
    struct tm* tm = gmtime(&t);
    return Date(
        (int)tm->tm_year + 1900, (int)tm->tm_mon,
        (int)tm->tm_mday, (int)tm->tm_wday, (int)tm->tm_yday,
        (int)tm->tm_hour, (int)tm->tm_min, (int)tm->tm_sec);
}

Date Date::utc(const Date& date)
{
    return Date::utc(date.year, date.month, date.day, date.hours, date.minutes, date.seconds);
}

Date Date::utc(int year, int month, int day, int hours, int minutes, int seconds)
{
    time_t t = time(NULL);
    struct tm* tm = localtime(&t);
    tm->tm_year   = year;
    tm->tm_mon    = month;
    tm->tm_mday   = day;
    tm->tm_hour   = hours;
    tm->tm_min    = minutes;
    tm->tm_sec    = seconds;
    t = mktime(tm);

    tm = gmtime(&t);
    return Date(
        (int)tm->tm_year + 1900, (int)tm->tm_mon,
        (int)tm->tm_mday, (int)tm->tm_wday, (int)tm->tm_yday,
        (int)tm->tm_hour, (int)tm->tm_min, (int)tm->tm_sec);
}