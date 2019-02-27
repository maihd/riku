#pragma once

#include "./types.h"
#include "./define.h"
#include "./str.h"

namespace console
{
    RIKU_API void log(str fmt, ...);
    RIKU_API void log_info(str fmt, ...);
    RIKU_API void log_warn(str fmt, ...);
    RIKU_API void log_error(str fmt, ...);

    RIKU_API void log_args(str fmt, ArgsList args_list);
    RIKU_API void log_info_args(str fmt, ArgsList args_list);
    RIKU_API void log_warn_args(str fmt, ArgsList args_list);
    RIKU_API void log_error_args(str fmt, ArgsList args_list);
}