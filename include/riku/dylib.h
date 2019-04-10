// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#pragma once

#include "./core.h"


namespace dylib
{
    // Open an dynamic linking library file
    RIKU_API void* open(const char* path);

    // Open dylib file context
    RIKU_API bool  close(void* handle);

    // Load or find a symbol, that is contained by dylib
    RIKU_API void* symbol(void* handle, const char* name);
}