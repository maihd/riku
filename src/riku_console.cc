#include <riku/core.h>
#include <riku/array.h>

#include <stdio.h>

#if PLATFORM_ANDROID
#include <android/log.h>
#endif

namespace console
{
    static Logger         s_logger;
    static Array<Logger*> s_loggers;
    static char           s_log_tag[1024] = "Riku";

    const char* get_log_tag(void)
    {
        return s_log_tag;
    }

    const char* set_log_tag(const char* tag)
    {
        if (string::is_valid(tag))
        {
            return string::copy(s_log_tag, tag, sizeof(s_log_tag));
        }
        else
        {
            return s_log_tag;
        }
    }

    void Logger::log(const char* fmt, ...)
    {
        ArgsList args_list;
        argslist_begin(args_list, fmt);
        this->log_args(fmt, args_list);
        argslist_end(args_list);
    }

    void Logger::info(const char* fmt, ...)
    {
        ArgsList args_list;
        argslist_begin(args_list, fmt);
        this->info_args(fmt, args_list);
        argslist_end(args_list);
    }

    void Logger::warn(const char* fmt, ...)
    {
        ArgsList args_list;
        argslist_begin(args_list, fmt);
        this->warn_args(fmt, args_list);
        argslist_end(args_list);
    }

    void Logger::error(const char* fmt, ...)
    {
        ArgsList args_list;
        argslist_begin(args_list, fmt);
        this->error_args(fmt, args_list);
        argslist_end(args_list);
    }

    void Logger::log_assert(const char* exp, const char* func, const char* file, int line, const char* fmt, ...)
    {
        ArgsList args_list;
        argslist_begin(args_list, fmt);
        this->log_assert_args(exp, func, file, line, fmt, args_list);
        argslist_end(args_list);
    }

    void Logger::log_args(const char* fmt, ArgsList args_list)
    {
#if PLATFORM_ANDROID
        __android_log_vprint(ANDROID_LOG_DEFAULT, s_log_tag, fmt, args_list);
#else
        vfprintf(stdout, fmt, args_list);
        fputc('\n', stdout);
#endif
    }

    void Logger::info_args(const char* fmt, ArgsList args_list)
    {
#if PLATFORM_ANDROID
        __android_log_vprint(ANDROID_LOG_INFO, s_log_tag, fmt, args_list);
#else
        vfprintf(stdout, fmt, args_list);
        fputc('\n', stdout);
#endif
    }

    void Logger::warn_args(const char* fmt, ArgsList args_list)
    {
#if PLATFORM_ANDROID
        __android_log_vprint(ANDROID_LOG_WARN, s_log_tag, fmt, args_list);
#else
        vfprintf(stdout, fmt, args_list);
        fputc('\n', stdout);
#endif
    }

    void Logger::error_args(const char* fmt, ArgsList args_list)
    {
#if PLATFORM_ANDROID
        __android_log_vprint(ANDROID_LOG_ERROR, s_log_tag, fmt, args_list);
#else
        vfprintf(stderr, fmt, args_list);
        fputc('\n', stdout);
#endif
    }

    void Logger::log_assert_args(const char* exp, const char* func, const char* file, int line, const char* fmt, ArgsList args_list)
    {
#if PLATFORM_ANDROID
        char final_fmt[4096];
        string::format(final_fmt, "Assertion failed!: %s\n\tIn %s:%s:%d\n\tMessage: %s", exp, func, file, line, fmt);

        __android_log_vprint(ANDROID_LOG_FATAL, s_log_tag, final_fmt, args_list);
#else
        console::error("Assertion failed!: %s\nIn %s:%s:%d", exp, func, file, line);

        console::error_args(fmt, args_list);
#endif

        // donot call abort here
    }

    // Add logger, that will call from log function
    bool add_logger(Logger* logger)
    {
        return s_loggers.push(logger);
    }

    // Remove logger, log function will no longer call logger
    bool remove_logger(Logger* logger)
    {
        return s_loggers.remove(logger);
    }

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

    void log_assert(const char* exp, const char* func, const char* file, int line, const char* fmt, ...)
    {
        ArgsList args_list;
        argslist_begin(args_list, fmt);
        log_assert_args(exp, func, file, line, fmt, args_list);
        argslist_end(args_list);
    }

    void log_args(const char* fmt, ArgsList args_list)
    {
        s_logger.log_args(fmt, args_list);
        for (int i = 0, n = s_loggers.get_length(); i < n; i++)
        {
            Logger* logger = s_loggers[i];
            if (logger)
            {
                logger->log_args(fmt, args_list);
            }
        }
    }

    void info_args(const char* fmt, ArgsList args_list)
    {
        s_logger.info_args(fmt, args_list);
        for (int i = 0, n = s_loggers.get_length(); i < n; i++)
        {
            Logger* logger = s_loggers[i];
            if (logger)
            {
                logger->info_args(fmt, args_list);
            }
        }
    }

    void warn_args(const char* fmt, ArgsList args_list)
    {
        s_logger.warn_args(fmt, args_list);
        for (int i = 0, n = s_loggers.get_length(); i < n; i++)
        {
            Logger* logger = s_loggers[i];
            if (logger)
            {
                logger->warn_args(fmt, args_list);
            }
        }
    }

    void error_args(const char* fmt, ArgsList args_list)
    {
        s_logger.error_args(fmt, args_list);
        for (int i = 0, n = s_loggers.get_length(); i < n; i++)
        {
            Logger* logger = s_loggers[i];
            if (logger)
            {
                logger->error_args(fmt, args_list);
            }
        }
    }

    void log_assert_args(const char* exp, const char* func, const char* file, int line, const char* fmt, ArgsList args_list)
    {
        s_logger.log_assert_args(exp, func, file, line, fmt, args_list);
        for (int i = 0, n = s_loggers.get_length(); i < n; i++)
        {
            Logger* logger = s_loggers[i];
            if (logger)
            {
                logger->log_assert_args(exp, func, file, line, fmt, args_list);
            }
        }

        process::abort();
    }
}