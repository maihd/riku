// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#pragma once

#include "./core.h"

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
    RIKU_API const char* to_string(const char* fmt) const;

public:
    RIKU_API static Date now(void);
    RIKU_API static Date parse(const char* date_string);
    RIKU_API static Date parse(const char* format, const char* date_string);

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