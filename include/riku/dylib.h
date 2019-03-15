// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#pragma once

#include "./core.h"

namespace dylib
{
    RIKU_API void* open(const char* path);
    RIKU_API bool  close(void* handle);
    RIKU_API void* symbol(void* handle, const char* name);
}