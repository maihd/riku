// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#pragma once

#include "./core.h"

namespace path
{
#if PLATFORM_WINDOWS
    constexpr const int   max_size  = 1024;
    constexpr const char* sep       = "\\";
    constexpr const char* delimiter = ";";
#else
    constexpr const int   max_size  = 1024;
    constexpr const char* sep       = "/";
    constexpr const char* delimiter = ":";
#endif

    RIKU_API const char* basename(const char* path);
    RIKU_API const char* basename(const char* path, const char* ext);
    RIKU_API const char* basename(const char* path, char* buffer, int length);
    RIKU_API const char* basename(const char* path, const char* ext, char* buffer, int length);
    
    RIKU_API const char* dirname(const char* path, char* buffer, int length);
    RIKU_API const char* dirname(const char* path);
    
    RIKU_API const char* extname(const char* path, char* buffer, int length);
    RIKU_API const char* extname(const char* path);
    
    RIKU_API bool        is_absolute(const char* path);
    RIKU_API bool        is_relative(const char* path);
    
    RIKU_API const char* absolute(const char* path);
    RIKU_API const char* absolute(const char* path, char* buffer, int length);
    
    RIKU_API const char* relative(const char* from, const char* to);
    RIKU_API const char* relative(const char* from, const char* to, char* buffer, int length);
    
    //RIKU_API const char* relative(const char* path, ...);
    //RIKU_API const char* relative(char* buffer, usize length, const char* path, ...);
    
    RIKU_API const char* join(const char* path, ...);
    RIKU_API const char* join(char* buffer, int length, const char* path, ...);
    
    RIKU_API const char* join_args(const char* path, ArgsList args_list);
    RIKU_API const char* join_args(char* buffer, int length, const char* path, ArgsList args_list);
}